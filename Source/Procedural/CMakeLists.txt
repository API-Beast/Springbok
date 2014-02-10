set(H_FILES RandomNumberGenerator.h)
set(CPP_FILES RandomNumberGenerator.cpp)
add_library(sbProcedural STATIC ${H_FILES} ${CPP_FILES})
set_property(TARGET sbProcedural PROPERTY POSITION_INDEPENDENT_CODE ON)

#ADD_SSTEST_FILE(SpringbokTest )

set_property(TARGET sbProcedural PROPERTY PUBLIC_HEADER ${H_FILES})
install(TARGETS sbProcedural PUBLIC_HEADER DESTINATION include/Springbok/Procedural ARCHIVE DESTINATION lib/Springbok)