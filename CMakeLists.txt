cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project(MyMod 
  VERSION 0.1.0 
  LANGUAGES C CXX
  )

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_subdirectory(src)

add_subdirectory(external/modloader)
add_subdirectory(external/modloadercommon)
add_subdirectory(external/libmodutils)