#ifndef _KURAOKAMI_LOAD_SHADER_H_
#define _KURAOKAMI_LOAD_SHADER_H_

#include <glad/glad.h>

int load_shader_source(unsigned int shader, const char *source_file);

unsigned int compile_shader(GLenum shader_type, const char *source_file);

unsigned int create_program_with_shaders(int num_shaders, ...);

int get_compile_error(unsigned int shader, int max_length, int *length, char *info_log);

int print_compile_error(unsigned int shader);

int get_link_error(unsigned int program, int max_length, int *length, char *info_log);

int print_link_error(unsigned int program);

#endif