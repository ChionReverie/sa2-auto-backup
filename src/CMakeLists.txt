add_library(AutoBackup SHARED 
  dllmain.cpp 
  main.cpp 
  pch.cpp 
  debug.cpp 
  config.cpp 
)
target_link_libraries(AutoBackup PRIVATE libmodutils modloader modloadercommon)