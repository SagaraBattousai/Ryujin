#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "process_input.h"
#include "window.h"
#include "renderer.h"

extern "C" {
#include "kuraokami/shader.h"
#include "kuraokami/shapes.h"
}

#include <iostream>

void initOpenGL()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}


int main()
{
  initOpenGL();  

  GLFWwindow *window = create_window(800, 600, "Ryujin", NULL, NULL);
  if (window == NULL)
  {
    return -1;
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cerr << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glfwSetFramebufferSizeCallback(window, framebuffer_resize_max_callback);

  unsigned int vertexShader = compile_shader(GL_VERTEX_SHADER, "vertex.glsl");
  int vertex_success = print_compile_error(vertexShader);

  unsigned int fragmentShader = compile_shader(GL_FRAGMENT_SHADER, "fragment.glsl");
  int fragment_success = print_compile_error(fragmentShader);

  if (!(vertex_success && fragment_success))
  {
    return 0;
  }

  unsigned int shaderProgram = create_program_with_shaders(2, vertexShader, fragmentShader);
  int program_success = print_link_error(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  shape_t tri = bind_triangle(1, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);


  while (!glfwWindowShouldClose(window))
  {
    /*------------------------------------------------------------------------/
    /------------------------ Process Input ----------------------------------/
    /------------------------------------------------------------------------*/
    processInput(window);

    /*------------------------------------------------------------------------/
    /-------------------------- Rendering ------------------------------------/
    /------------------------------------------------------------------------*/
    //render_loop();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    

    /*------------------------------------------------------------------------/
    /---------- Check and Call Events and then Swap the Buffers --------------/
    /------------------------------------------------------------------------*/
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}