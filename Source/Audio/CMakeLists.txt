find_package(OpenAL REQUIRED)

set(H_FILES SoundInstance.h SoundManager.h SoundSample.h SoundSource.h)
set(CPP_FILES SoundInstance.cpp SoundManager.cpp SoundSample.cpp SoundSource.cpp)

include_directories(${OPENAL_INCLUDE_DIR})
add_library(sbAudio STATIC ${H_FILES} ${CPP_FILES})
target_link_libraries(sbAudio ${OPENAL_LIBRARY} sbResources)

#ADD_SSTEST_FILE(SpringbokTest file.cpp)