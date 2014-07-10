find_package (PythonLibs REQUIRED)
include_directories (${PYTHON_INCLUDE_DIRS})

add_executable (histogram_pointwise histogram_pointwise.cc)
target_link_libraries (histogram_pointwise
                       itl_core itl_stat itl_io itl_algorithm
                       itl_extras)
