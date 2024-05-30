add_library(libmodutils 
  AnimationFile.cpp AnimationFile.h
  GameObject.cpp GameObject.h
  LandTableInfo.cpp LandTableInfo.h
  ModelInfo.cpp ModelInfo.h
  PAKFile.cpp PAKFile.h
  stdafx.cpp stdafx.h
  Trampoline.cpp Trampoline.h
)

target_link_libraries(libmodutils PRIVATE modloader)
target_include_directories(libmodutils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
