cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(sim)

find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/../../)

file(COPY ${PROJECT_SOURCE_DIR}/suit.obj DESTINATION ${CMAKE_BINARY_DIR}/)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(sim sim.cc ${sources} ${headers})
target_link_libraries(sim ${Geant4_LIBRARIES}) 

