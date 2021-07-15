
function(copy_resources_to_target target)
  list(TRANSFORM ARGN PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/")
  add_custom_command(
    TARGET ${target} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E 
      copy_if_different
      ${ARGN}
      ${CMAKE_CURRENT_BINARY_DIR}
    VERBATIM)
endfunction()
