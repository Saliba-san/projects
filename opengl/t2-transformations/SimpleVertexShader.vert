#version 330 core

//Input vertex data, different for all executions of this shader
layout(location = 0) in vec3 vertexPosition_modelspace;

//model view projection, constant for the whole mesh
uniform mat4 MVP;

void main(){
  // position of the vertex in the output image after transformations
  gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
}

