cmake_minimum_required(VERSION 3.1.0)

project(EntityManipulator)
set(BIN_NAME EntityManipulatorExe) 

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Populate a CMake variable with the sources
set(EntityManipulator_SRCS
    Entity.h
    Entity.cpp
    EntityManipulator.h
    JSONMarshaller.h
    JSONMarshaller.cpp
    XMLMarshaller.h
    XMLMarshaller.cpp
    main.cpp
)

add_executable(${BIN_NAME} ${EntityManipulator_SRCS})

set_target_properties(${BIN_NAME} PROPERTIES CXX_STANDARD 11)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

