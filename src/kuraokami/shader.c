#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <glad/glad.h>
#include <kuraokami/shader.h>

unsigned int compile_shader(GLenum shader_type, const char *source_file)
{
  unsigned int shader = glCreateShader(shader_type);
  if (!shader)
  {
    return 0; // shader == 0 at this point
  }

  load_shader_source(shader, source_file);
  glCompileShader(shader);

  return shader;
}

unsigned int create_program_with_shaders(int num_shaders, ...)
{
  unsigned int shaderProgram = glCreateProgram();
  unsigned int shader;

  va_list args;
  va_start(args, num_shaders);

  for (int i = 0; i < num_shaders; i++) 
  { 
    shader = va_arg(args, unsigned int);
    glAttachShader(shaderProgram, shader);
  }

  va_end(args);

  glLinkProgram(shaderProgram);
  return shaderProgram;
}


int get_compile_error(unsigned int shader, int max_length, int *length, char *info_log)
{
  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(shader, max_length, length, info_log);
  }

  return success;
}

int print_compile_error(unsigned int shader)
{
  int info_log_length;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);

  char *info_log = (char *)malloc(sizeof(char) * info_log_length);
  if (!info_log)
  {
    return 0;
  }
  //size_t actual_length; should equal info_log_length

  int success = get_compile_error(shader, info_log_length, NULL, info_log);

  if (!success)
  {
    fputs("Shader Compiler Error, Log Output Bellow:\n", stderr);
    fwrite(info_log, sizeof(char), info_log_length, stderr);
    fputc('\n', stderr);
  }

  return success;
}

int get_link_error(unsigned int program, int max_length, int *length, char *info_log)
{
  int success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(program, 512, length, info_log);
  }

  return success;
}

int print_link_error(unsigned int program)
{
  int info_log_length;
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);

  char *info_log = (char *)malloc(sizeof(char) * info_log_length);
  if (!info_log)
  {
    return 0;
  }
  //size_t actual_length; should equal info_log_length

  int success = get_compile_error(program, info_log_length, NULL, info_log);

  if (!success)
  {
    fputs("Program Link Error, Log Output Bellow:\n", stderr);
    fwrite(info_log, sizeof(char), info_log_length, stderr);
    fputc('\n', stderr);
  }

  return success;
}

int load_shader_source(unsigned int shader, const char *source_file)
{
  FILE *source = fopen(source_file, "rb");
  if (source == NULL)
  {
    return -1;
  }

  // get file length:
  fseek(source, 0, SEEK_END);
  long length = ftell(source);
  fseek(source, 0, SEEK_SET);

  char *buffer = (char *) malloc(sizeof(char) * length);
  if (buffer == NULL)
  {
    return -1;
  }

  size_t read_count = fread(buffer, sizeof(char), length, source);
  glShaderSource(shader, 1, &buffer, &length);

  free(buffer);

  fclose(source);
  return read_count;
}
