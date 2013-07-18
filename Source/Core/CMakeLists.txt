set(H_FILES AssetManager.h AssetManager_Template.hpp)
set(CPP_FILES AssetManager.cpp)
add_library(sbCore STATIC ${H_FILES} ${CPP_FILES})
#ADD_SSTEST_FILE(SpringbokTest file.cpp)