cmake_minimum_required (VERSION 3.16)

add_library(space_invaders STATIC
  "bullets.cpp"
  "space-invaders.cpp"
  "ship.cpp"
  "pygame-sprite-facade.cpp"
  "aliens.cpp"
  "detail.cpp"
  "game_states.cpp"
)
target_include_directories(space_invaders PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(space_invaders sfml-graphics)

add_executable (space_invaders_main "main.cpp")
target_include_directories(space_invaders_main PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(space_invaders_main PRIVATE space_invaders)

install(TARGETS space_invaders_main
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})

