#define GL_GLEXT_PROTOTYPES
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "shader.hpp"

//still dont know what it means kek
#include <GL/glew.h>

//window and keyboard handler (still dont understand it)
#include <GLFW/glfw3.h> 
GLFWwindow* window;

//glm is a math lib for handling vectors with classes like vec3 and others
#include <glm/glm.hpp>
using namespace glm;


int main() {
  if(!glfwInit())
  {
    std::cerr << "Failed to initialize GLFW...\n";
    getchar();
    return -1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4); //4x antialiasin
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);//set version 3.3 of Opengl
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(1024, 768, "firstWindow", NULL, NULL);

  if(window == NULL){
    std::cerr << "failed to open GLFW window";
    getchar();
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window); //init GLEW

  glewExperimental = true;
  if(glewInit() != GLEW_OK){
    std::cerr << "Failed to init GLEW";
    getchar();
    glfwTerminate();
    return -1;
  }

  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

  //vertexArrayObject Definition
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  GLuint programID = LoadShaders("SimpleVertexShader.vert", "SimpleFragmentShader.frag");

  //my triangle vertices
  static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
     0.0f,  1.0f, 0.0f
  };

  //vertex buffer def
  GLuint vertexBuffer;
  //gen 1 buffer, with a ref to vertexBuffer
  glGenBuffers(1, &vertexBuffer);
  //binds the buffer to the generated buffer
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

  //writes in the buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


  do{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(programID);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(
        0, //buffer (same as shader)
        3, //size
        GL_FLOAT, //type
        GL_FALSE, //is it normalized?
        0, //stride: if the array contained more than one type of data, the stride would be the travel size of the pointer to get to another set ex: x1,y1,nx1,ny1,r1,g1,b1,a1  x2 ... -> stride = 32 
        (void*)0 //array buffer offset
        );

    //draw the triangle
    glDrawArrays(GL_TRIANGLES, 0, 3); //vertex 0 to 3 
    glDisableVertexAttribArray(0); 

    glfwSwapBuffers(window);
    glfwPollEvents();
  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

  glDeleteBuffers(1, &vertexBuffer);
  glDeleteVertexArrays(1, &VertexArrayID);
  glDeleteProgram(programID);

  glfwTerminate();
  return 0;
}
