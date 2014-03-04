project(Springbok)
cmake_minimum_required(VERSION 2.8.9)

if(EMSCRIPTEN)
	set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules/Emscripten/")
else()
	set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules/")
endif()

include(EnableCPP11Flag)
include(Subtargets)

set(SPRINGBOK_VERSION "0.1")

ENABLE_CPP11()

include(SSTest)

include_directories(${CMAKE_SOURCE_DIR})
#include_directories(${CMAKE_SOURCE_DIR}/Framework/)
include_directories(${CMAKE_SOURCE_DIR}/SSTest/)

if(NOT EMSCRIPTEN)
add_subdirectory(SSTest)
endif()
add_subdirectory(Source)
add_subdirectory(MyExamples)
if(BUILD_PLATFORM)
	add_subdirectory(Examples)
endif()

if(EMSCRIPTEN)
	target_link_libraries(Springbok)
else()
	enable_testing()
	add_sstest_executable(SpringbokTest) 
	target_link_libraries(SpringbokTest SSTest Springbok)
endif()

find_package(Doxygen)
if(DOXYGEN_FOUND)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
	add_custom_target(doc
	                  ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	                  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
	                  COMMENT "Generating API documentation with Doxygen" VERBATIM)
endif()
