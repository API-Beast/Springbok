find_package(ALSoft REQUIRED)

set(H_FILES SoundInstance.h SoundManager.h SoundSample.h SoundSource.h)
set(CPP_FILES SoundInstance.cpp SoundManager.cpp SoundSample.cpp SoundSource.cpp)

include_directories(${ALSOFT_INCLUDE_DIR})
add_library(sbAudio OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbAudio PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbAudio PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbAudio PROPERTY OBJ_INSTALL_LOCATION Audio)
set_property(TARGET sbAudio PROPERTY OBJ_DEPENDENCIES ${ALSOFT_LIBRARY})

#ADD_SSTEST_FILE(SpringbokTest file.cpp)