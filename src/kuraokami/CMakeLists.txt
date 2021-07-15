
set(target_name "kuraokami")

set(src_files "main.cpp" "process_input.cpp" "renderer.cpp"
              "window.cpp" "shader.c" "shapes.c")

set(shader_files "vertex.glsl" "fragment.glsl")

set(public_header_dir "${public_header_root}/${target_name}")

file(GLOB private_header_files "*.h")
file(GLOB public_header_files "${public_header_dir}/*.h")

add_executable(${target_name} ${src_files}
                              ${public_header_files}
                              ${private_header_files}
                              ${shader_files})

target_link_libraries(${target_name} glfw glad::glad)
target_include_directories(${target_name} PUBLIC "${public_header_root}")


copy_resources_to_target(${target_name} ${shader_files})
