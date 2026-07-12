cmake_minimum_required(VERSION 3.20)

project(SatelliteCoverage)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} -sINITIAL_MEMORY=268435456"
)

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

target_link_options(SatelliteCoverage PRIVATE
    "SHELL:-sDISABLE_EXCEPTION_CATCHING=0"
    "SHELL:-sFETCH=1"
    "SHELL:-lembind"
    "SHELL:-sMODULARIZE=1"
    "SHELL:-sEXPORT_ES6=1"
    "SHELL:-sEXPORT_NAME=createModule"
)