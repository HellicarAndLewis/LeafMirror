#version 120
void main() {
    gl_FrontColor = gl_Color;
    gl_PointSize = 3;//gl_Normal.x;
  	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
  	//gl_Position = ft_transform();
} 