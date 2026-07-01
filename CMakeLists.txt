cmake_minimum_required(VERSION 3.20)

project(SatelliteCoverage)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR})

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "src/*.cpp"
    "src/*.c"
)

add_executable(SatelliteCoverage ${SOURCES})

file(GLOB SGP4_SOURCES
    "libs/libsgp4/*.cc"
)

add_library(sgp4 ${SGP4_SOURCES})

target_include_directories(sgp4 PUBLIC
    libs/libsgp4
)

target_include_directories(SatelliteCoverage PRIVATE
    include
)

target_link_libraries(SatelliteCoverage PRIVATE sgp4)
