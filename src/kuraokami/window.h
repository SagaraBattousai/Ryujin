#ifndef _WINDOW_H_
#define _WINDOW_H_

void framebuffer_resize_max_callback(GLFWwindow *window, int width, int height);

GLFWwindow *create_window(int width, int height, const char *title, GLFWmonitor *monitor, GLFWwindow *share);

#endif