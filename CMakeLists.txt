cmake_minimum_required(VERSION 3.12)
project(MeditationTimerProject)

set(CMAKE_CXX_STANDARD 14)

# Find SFML
find_package(SFML 2.6 COMPONENTS graphics window system audio REQUIRED)

# Add source files
set(SOURCES
    main.cpp
    MeditationTimer.cpp
)

# Create the executable
add_executable(MeditationTimer ${SOURCES})

# Link SFML libraries
target_link_libraries(MeditationTimer PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
