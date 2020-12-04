#version 330 core

//Input vertex data, different for all executions of this shader
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;

//model view projection, constant for the whole mesh
uniform mat4 MVP;

// will be interpolated for each fragment
out vec3 fragmentColor;

void main(){
  // position of the vertex in the output image after transformations
  gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

  //produces color of each fragment with interpolation of each vertex color
  fragmentColor = vertexColor;
}

