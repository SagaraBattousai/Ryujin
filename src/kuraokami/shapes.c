#include <math.h>
#include <glad/glad.h>
#include <kuraokami/shapes.h>

#define TRIANGLE_HALF_Y_SCALE (sqrtf(3) / 4.0f)
#define TRIANGLE_HALF_X_SCALE (1.0f / 2.0f)


shape_t bind_triangle(int width, GLenum usage)
{
  unsigned int buffers[2];
  glGenBuffers(2, buffers);

  glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[1]);

  unsigned int indices[] = { 0, 1, 2 };

  float x = TRIANGLE_HALF_X_SCALE * width;
  float y = TRIANGLE_HALF_Y_SCALE * width;

  float verticies[] = {
    0.0f, y, 0.0f,
    x, -1 * y, 0.0f,
    -1 * x, -1 * y, 0.0f
  };

  glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, usage);


  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, usage);

  shape_t out = { .VBO = buffers[0], .EBO = buffers[1] };
  return out;
}