project(Springbok)
cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules/")

include(EnableCPP11Flag)
include(Subtargets)

set(SPRINGBOK_VERSION "0.1")

ENABLE_CPP11()

include(SSTest)

include_directories(${CMAKE_SOURCE_DIR})
#include_directories(${CMAKE_SOURCE_DIR}/Framework/)
include_directories(${CMAKE_SOURCE_DIR}/SSTest/)

add_subdirectory(SSTest)
add_subdirectory(Springbok)
if(BUILD_PLATFORM)
	add_subdirectory(Examples)
endif()

enable_testing()
add_sstest_executable(SpringbokTest) 
target_link_libraries(SpringbokTest SSTest Springbok)

find_package(Doxygen)
if(DOXYGEN_FOUND)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
	add_custom_target(doc
	                  ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	                  COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif()