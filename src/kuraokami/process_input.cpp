#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "process_input.h"

void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, true);
  }
}