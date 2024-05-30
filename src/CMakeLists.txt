add_library(main SHARED dllmain.cpp main.cpp pch.cpp)
target_link_libraries(main libmodutils modloader)