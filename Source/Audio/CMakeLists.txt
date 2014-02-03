find_package(OpenAL REQUIRED)

set(H_FILES SoundInstance.h SoundManager.h SoundSample.h SoundSource.h)
set(CPP_FILES SoundInstance.cpp SoundManager.cpp SoundSample.cpp SoundSource.cpp)

include_directories(${OPENAL_INCLUDE_DIR})
add_library(sbAudio STATIC ${H_FILES} ${CPP_FILES})
target_link_libraries(sbAudio ${OPENAL_LIBRARY} sbResources)

set_property(TARGET sbAudio PROPERTY PUBLIC_HEADER ${H_FILES})
install(TARGETS sbAudio PUBLIC_HEADER DESTINATION include/Springbok/Audio ARCHIVE DESTINATION lib/Springbok)

#ADD_SSTEST_FILE(SpringbokTest file.cpp)