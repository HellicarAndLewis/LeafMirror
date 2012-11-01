/*
 * KinectController.cpp
 *
 *  Created on: Oct 29, 2012
 *      Author: arturo
 */

#include "KinectController.h"
#include <set>
#include "ofxCv.h"

using namespace ofxCv;

KinectController::KinectController() {
	bNewFrame = false;

}


void KinectController::setup(){
	kinect.init(false,true,true);
	kinect.open();
	grayThresFar.allocate(640,480,OF_IMAGE_GRAYSCALE);
	grayThresNear.allocate(640,480,OF_IMAGE_GRAYSCALE);
	thresholdImg.allocate(640,480,OF_IMAGE_GRAYSCALE);
	gray.allocate(640,480,OF_IMAGE_GRAYSCALE);
	grayTex.allocate(640,480,GL_LUMINANCE);
	smoothDepthArray.allocate(640,480,1);
	smoothDepthTex.allocate(gray);

	tilt.addListener(this,&KinectController::tiltChanged);

	parameters.setName("kinect");
	parameters.add(near.set("near",255,0,255));
	parameters.add(far.set("far",0,0,255));
	parameters.add(minArea.set("minArea",1000,0,1000));
	parameters.add(maxArea.set("maxArea",640.*480.,640.*480./10,640*480));
	parameters.add(minHoleArea.set("minHoleArea",100,0,1000));
	parameters.add(maxHoleArea.set("maxHoleArea",1000,0,10000));
	parameters.add(tilt.set("tilt",0,-30,30));
	parameters.add(resampling.set("resampling",3,1,20));
	parameters.add(smoothing.set("smoothing",0.01,0,0.05));
	parameters.add(smoothingShape.set("smoothingShape",0,0,1));
	/*parameters.add(innerBandThreshold.set("innerBandThreshold",5,1,20));
	parameters.add(outerBandThreshold.set("outerBandThreshold",2,1,20));
	parameters.add(kernelSize.set("kernelSize",5,3,19));*/

	updateDepthLookupTable();
}

//---------------------------------------------------------------------------
void KinectController::updateDepthLookupTable() {
	unsigned char nearColor = 255;
	unsigned char farColor = 0;
	unsigned int maxDepthLevels = 10000;
	depthLookupTable.resize(maxDepthLevels);
	depthLookupTable[0] = 0;
	for(int i = 1; i < maxDepthLevels; i++) {
		depthLookupTable[i] = ofMap(i, 500, 4000, nearColor, farColor, true);
	}
}

void KinectController::tiltChanged(int & tilt){
	kinect.setCameraTiltAngle(tilt);
}

void KinectController::findContours(){
	vector<vector<cv::Point> > allContours;
	vector<Vec4i> hierarchy;
	vector<cv::Point> simplifiedContour;
	contourCopy = thresholdImg;
	cv::Mat threshodlMat = toCv(contourCopy);
	cv::findContours(threshodlMat, allContours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	map<int,int> index;
	int p = 0;
	paths.resize(hierarchy.size());
	for(u_int i=0;i<hierarchy.size();++i){
		double curArea = contourArea(Mat(allContours[i]));
		if(hierarchy[i][3]==-1){
			if(curArea >= minArea && curArea <= maxArea){
				paths[p].clear();
				ofPolyline polyline = toOf(allContours[i]);
				polyline = polyline.getResampledBySpacing(resampling);
				polyline = polyline.getSmoothed(smoothing*polyline.size(),smoothingShape);
				ofPath & path = paths[p];
				for(u_int j=0;j<polyline.size();j++){
					path.lineTo(polyline[j]);
				}
				path.close();
				index[i] = p;
				p++;
			}
		}else if(curArea >= minHoleArea && curArea <= maxHoleArea
				&& index.find(hierarchy[i][3])!=index.end()){
			ofPolyline polyline = toOf(allContours[i]);
			polyline = polyline.getResampledBySpacing(resampling);
			polyline = polyline.getSmoothed(smoothing*polyline.size(),smoothingShape);
			paths[index[hierarchy[i][3]]].moveTo(polyline[0]);
			for(u_int j=1;j<polyline.size();j++){
				paths[index[hierarchy[i][3]]].lineTo(polyline[j]);
			}
		}
	}
	paths.resize(p);

}

void KinectController::smoothDepth(){
	int width = 640;
	int height = 480;
	// We will be using these numbers for constraints on indexes
	int widthBound = width - 1;
	int heightBound = height - 1;
	ofShortPixels & depthArray = kinect.getRawDepthPixelsRef();
	int filterSize = kernelSize;
	if(kernelSize%2!=0)filterSize--;
	int filterCollectionSize = filterSize*filterSize;
	filterSize/=2;
	// We process each row in parallel
	// Process each pixel in the row
	smoothDepthArray.set(0);

	// The filter collection is used to count the frequency of each
	// depth value in the filter array. This is used later to determine
	// the statistical mode for possible assignment to the candidate.
	short filterCollection[filterCollectionSize][2];

	for(int y=0; y<480; y++){
		for (int x = 0; x < 640; x++){
			int depthIndex = x + (y * 640);

			// We are only concerned with eliminating 'white' noise from the data.
			// We consider any pixel with a depth of 0 as a possible candidate for filtering.
			if (depthArray[depthIndex] == 0){
				  // From the depth index, we can determine the X and Y coordinates that the index
				  // will appear in the image. We use this to help us define our filter matrix.
				  memset(filterCollection,0,sizeof(filterCollection));

				  // The inner and outer band counts are used later to compare against the threshold
				  // values set in the UI to identify a positive filter result.
				  int innerBandCount = 0;
				  int outerBandCount = 0;

				  // The following loops will loop through a 5 X 5 matrix of pixels surrounding the
				  // candidate pixel. This defines 2 distinct 'bands' around the candidate pixel.
				  // If any of the pixels in this matrix are non-0, we will accumulate them and count
				  // how many non-0 pixels are in each band. If the number of non-0 pixels breaks the
				  // threshold in either band, then the average of all non-0 pixels in the matrix is applied
				  // to the candidate pixel.
				  for (int yi = -filterSize; yi < filterSize+1; yi++)
				  {
					for (int xi = -filterSize; xi < filterSize+1; xi++)
					{
					  // yi and xi are modifiers that will be subtracted from and added to the
					  // candidate pixel's x and y coordinates that we calculated earlier. From the
					  // resulting coordinates, we can calculate the index to be addressed for processing.

					  // We do not want to consider the candidate
					  // pixel (xi = 0, yi = 0) in our process at this point.
					  // We already know that it's 0
					  if (xi != 0 || yi != 0)
					  {
						// We then create our modified coordinates for each pass
						int xSearch = x + xi;
						int ySearch = y + yi;

						// While the modified coordinates may in fact calculate out to an actual index, it
						// might not be the one we want. Be sure to check
						// to make sure that the modified coordinates
						// match up with our image bounds.
						if (xSearch >= 0 && xSearch <= widthBound && ySearch >= 0 && ySearch <= heightBound){
						  int index = xSearch + (ySearch * width);
						  // We only want to look for non-0 values
						  if (depthArray[index] != 0)
						  {
							// We want to find count the frequency of each depth
							for (int i = 0; i < filterCollectionSize; i++)
							{
							  if (filterCollection[i][0] == depthArray[index])
							  {
								// When the depth is already in the filter collection
								// we will just increment the frequency.
								filterCollection[i][1]++;
								break;
							  }
							  else if (filterCollection[i][0] == 0)
							  {
								// When we encounter a 0 depth in the filter collection
								// this means we have reached the end of values already counted.
								// We will then add the new depth and start it's frequency at 1.
								filterCollection[i][0] = depthArray[index];
								filterCollection[i][1]++;
								break;
							  }
							}

							// We will then determine which band the non-0 pixel
							// was found in, and increment the band counters.
							if (yi != filterSize && yi != -filterSize && xi != filterSize && xi != -filterSize)
							  innerBandCount++;
							else
							  outerBandCount++;
						  }
						}
					  }
					}
				  }

				  // Once we have determined our inner and outer band non-zero counts, and
				  // accumulated all of those values, we can compare it against the threshold
				  // to determine if our candidate pixel will be changed to the
				  // statistical mode of the non-zero surrounding pixels.
				  if (innerBandCount >= innerBandThreshold || outerBandCount >= outerBandThreshold)
				  {
					short frequency = 0;
					short depth = 0;
					// This loop will determine the statistical mode
					// of the surrounding pixels for assignment to
					// the candidate.
					for (int i = 0; i < filterCollectionSize; i++)
					{
					  // This means we have reached the end of our
					  // frequency distribution and can break out of the
					  // loop to save time.
					  if (filterCollection[i][0] == 0)
						break;
					  if (filterCollection[i][1] > frequency)
					  {
						depth = filterCollection[i][0];
						frequency = filterCollection[i][1];
					  }
					}

					smoothDepthArray[depthIndex] = depth;
				  }
			}else{
			  // If the pixel is not zero, we will keep the original depth.
			  smoothDepthArray[depthIndex] = depthArray[depthIndex];
			}
		}
	}
	/*averageQueue.push_back(averageQueue.front());
	averageQueue.pop_front();

	int denominator = 0;
	int count = 1;

	sumDepthArray.set(0);
	// We first create a single array, summing all of the pixels
	// of each frame on a weighted basis and determining the denominator
	// that we will be using later.
	for(u_int i=0;i<averageQueue.size();i++){
	    for(int j=0;j<averageQueue[0]->size();j++){
	        sumDepthArray[j] += averageQueue[i]->getPixels()[j] * count;
	    }
	    denominator += count;
	    count++;
	}

	// Once we have summed all of the information on a weighted basis,
	// we can divide each pixel by our denominator to get a weighted average.
    for(int i=0;i<smoothDepthArray.size();i++){
	    averagedDepthArray[i] = (short)(double(sumDepthArray[i]) / double(denominator));
	}*/
}

void KinectController::update(){
	kinect.update();
	if(kinect.isFrameNew()){
		gray = kinect.getDepthPixelsRef();
		/*smoothDepth();
		int n = 640*480;
		for(int i = 0; i < n; i++) {
			gray[i] = depthLookupTable[smoothDepthArray[i]];
		}*/
		threshold(gray,grayThresFar,far);
		threshold(gray,grayThresNear,near,true);
		cv::Mat thresholdMat = toCv(thresholdImg);
		cv::bitwise_and(toCv(grayThresNear), toCv(grayThresFar), thresholdMat);
		findContours();
		thresholdImg.update();
		grayTex.loadData(gray);
		smoothDepthTex.loadData(gray);
		bNewFrame = true;
	}else{
		bNewFrame = false;
	}
}

bool KinectController::isFrameNew(){
	return bNewFrame;
}

void KinectController::drawDebug(float x, float y){
	kinect.draw(x,y,320,240);
	kinect.drawDepth(x+330,y,320,240);
	thresholdImg.draw(x,y+250,320,240);
	smoothDepthTex.draw(x+330,y+250,320,240);
}


vector<ofPath> & KinectController::getBlobs(){
	return paths;
}

ofPixels & KinectController::getThreshold(){
	return thresholdImg.getPixelsRef();
}

ofPixels & KinectController::getDepth(){
	return gray;
}
