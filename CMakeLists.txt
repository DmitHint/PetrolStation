cmake_minimum_required(VERSION 3.27)
project(PetrolStation)

set(CMAKE_CXX_STANDARD 17)

#=========
# Specify paths to source files and header files
set(SOURCE_FILES
        src/Base.cpp
        src/Car.cpp
        src/ControlPanel.cpp
        src/DisplayClass.cpp
        src/OperatorClass.cpp
        src/PetrolStation.cpp
        src/System.cpp
        src/main.cpp
)

set(HEADER_FILES
        include/Base.h
        include/Car.h
        include/ControlPanel.h
        include/DisplayClass.h
        include/OperatorClass.h
        include/PetrolStation.h
        include/System.h
)
#=========

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE include)
