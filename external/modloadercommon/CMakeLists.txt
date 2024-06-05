add_library(modloadercommon CodeParser.cpp FileSystem.cpp IniFile.cpp stdafx.cpp TextConv.cpp)

target_include_directories(modloadercommon PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})