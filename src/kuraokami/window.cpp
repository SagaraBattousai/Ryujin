#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.h"
#include <iostream>

void framebuffer_resize_max_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
}

GLFWwindow *create_window(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share)
{
  GLFWwindow *window = glfwCreateWindow(width, height, title, monitor, share);
  if (window == NULL)
  {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return NULL;
  }

  return window;

}
