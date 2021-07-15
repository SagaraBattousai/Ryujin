#ifndef _KURAOKAMI_SHAPES_H_
#define _KURAOKAMI_SHAPES_H_

#include <glad/glad.h>

typedef struct
{
  unsigned int VBO;
  unsigned int EBO;
} shape_t;

shape_t bind_triangle(int width, GLenum usage);

#endif