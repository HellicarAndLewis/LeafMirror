LeafMirror
==========

An interactive mirror that uses the Microsoft Kinect for sensing, and Barco MiStrips for display

GUI instructions
================

General
=======

* fill (not used any more): allows to draw the shilouette of the people only with stroke or filled

* debugView: changes the view in the gui screen:
	0. kinect input + thresholding
	1. led screen simulation
	2. output of the fbos used for rendering
	3. output of the movement analisys

* outputOffset: changes the position of the output screen

* outputSize: changes the size of the output screen

* useParticles: (de)activates the painting with movement

Kinect
======

* near/far: controls the distance in which to detect blobs

* minArea/maxArea: min/max area of the detected blobs, can be used to remove noise, the default values should be ok

* minHoleArea/maxHoleArea: min/max area of the detected blobs for holes in them, can be used to remove noise in blobs, high/low values in the min/max control will remove real holes

* tilt: controls the physical inclination of the kinect

* resampling: simplyfies the detected contours making the shilouettes less noisy higher values will loose detail

* smoothing: smooths the contours making the shilouettes more rounded, high values will loose detail


Wall
====

* wallWidth/Height: controls the size in LEDs of the simulation and output

* ledSeparation/ledRadius: only useful to make the simulation resemble the real screen better

* outputTexFilter: makes the output smooth when resizing, should be off

* bacgroundColor: allows to change the background color of the installation

* fillColor: allows to change the color of the blobs

* particlesGlowPasses: makes the glow of the painting more intense making the borders less defined with higher values

* blobsGlowPasses: makes the glow of the blobs more intense making the borders less defined with higher values

Particles
=========

* msGrow: time that takes the painting particles to fade from the background color to it's own color, should be low so there's no apparent lag

* msStay: time that takes the painting particles to begin to fade back to the background color

* msDissolve: time that takes the painting particles to fade back to the background color

* sizePerSecond: During the duration of the 3 previous times the particles are always growing in size, this parameter controls how much they grow in total




Installation
============


Compiling
=========

clone a copy of OF from github the branch being used is in arturoc: arturodevelop:

git clone https://github.com/arturoc/openFrameworks
git checkout arturodevelop

or if you already have an OF repo cloned:

git checkout -b arturodevelop
git pull https://github.com/arturoc/openFrameworks arturodevelop

to compile the application clone the repository with submodules inside OF_ROOT/apps:

git clone --recursive git@github.com:HellicarAndLewis/LeafTree
git submodule init
git submodule update

under linux the addons should be in the addons folder of the openFramewors installation




