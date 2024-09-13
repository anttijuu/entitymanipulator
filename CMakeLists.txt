cmake_minimum_required(VERSION 3.20.0)

project(EntityManipulator)
set(BIN_NAME EntityManipulatorExe) 

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

find_package(Doxygen)
if (DOXYGEN_FOUND)
   configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/doxyfile @ONLY)
   add_custom_target(doc
      ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxyfile
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Generating API documentation with Doxygen" VERBATIM
   )
endif(DOXYGEN_FOUND)


# Populate a CMake variable with the sources
set(EntityManipulator_SRCS
    Entity.h
    Entity.cpp
    EntityComposite.h
    EntityComposite.cpp
    EntityLeaf.h
    EntityLeaf.cpp
    EntityManipulator.h
    JSONMarshaller.h
    JSONMarshaller.cpp
    XMLMarshaller.h
    XMLMarshaller.cpp
    GraphVizMarshaller.h
    GraphVizMarshaller.cpp
    main.cpp
)

add_executable(${BIN_NAME} ${EntityManipulator_SRCS})

set_target_properties(${BIN_NAME} PROPERTIES CXX_STANDARD 20)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

