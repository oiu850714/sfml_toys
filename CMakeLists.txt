# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.16)

project ("space_invaders")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(SFML 2.5 
  COMPONENTS 
    system window graphics REQUIRED)

# Include sub-projects.
add_subdirectory ("dlls")
add_subdirectory ("src")


install(DIRECTORY
    assets
    DESTINATION ${CMAKE_INSTALL_PREFIX}
)
