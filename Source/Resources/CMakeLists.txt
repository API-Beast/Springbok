set(H_FILES ResourceManager.h ResourceManager_Templates.hpp)
set(CPP_FILES ResourceManager.cpp)
add_library(sbResources STATIC ${H_FILES} ${CPP_FILES})
target_link_libraries(sbResources sbGeneric sbPlatform)
#ADD_SSTEST_FILE(SpringbokTest file.cpp)

set_property(TARGET sbResources PROPERTY PUBLIC_HEADER ${H_FILES})
install(TARGETS sbResources PUBLIC_HEADER DESTINATION include/Springbok/Resources ARCHIVE DESTINATION lib/Springbok)