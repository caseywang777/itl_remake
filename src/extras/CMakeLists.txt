find_package (PythonLibs REQUIRED)
include_directories (${PYTHON_INCLUDE_DIRS})

add_library (itl_extras pyplot.cc)
target_link_libraries (itl_extras ${PYTHON_LIBRARIES} itl_stat)
