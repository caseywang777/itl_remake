# add library
add_library (itl_algorithm hist.cc entropy.cc)
target_link_libraries (itl_algorithm itl_core itl_stat)
