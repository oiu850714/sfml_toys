cmake_minimum_required(VERSION 3.16)

install(FILES 
    openal32.dll 
    sfml-audio-2.dll 
    sfml-audio-d-2.dll 
    sfml-graphics-2.dll 
    sfml-graphics-d-2.dll 
    sfml-network-2.dll 
    sfml-network-d-2.dll 
    sfml-system-2.dll 
    sfml-system-d-2.dll 
    sfml-window-2.dll 
    sfml-window-d-2.dll 
    DESTINATION ${CMAKE_INSTALL_PREFIX}
)
