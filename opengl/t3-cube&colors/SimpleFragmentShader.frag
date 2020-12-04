#version 330 core

//Output data
out vec3 color;

//Input data
in vec3 fragmentColor;

void main(){

  //interpolated between all 3 surrounding vertices
  color = fragmentColor;
}
