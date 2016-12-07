cmake_minimum_required (VERSION 3.1)
set(CMAKE_CXX_STANDARD 14) 

add_compile_options(-fvisibility=hidden)
add_library(Int_c SHARED Int_c.cpp)

#add_custom_command(
#  TARGET Int_c 
#  POST_BUILD 
#  COMMAND strip -x libInt_c.dylib)
