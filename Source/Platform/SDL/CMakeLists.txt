
if(SPRINGBOK_HTML5)
  add_library(sbPlatformSDL OBJECT ButtonSpecs.cpp GameSurface.cpp InputMonitor.cpp)
  set_property(TARGET sbPlatformSDL PROPERTY POSITION_INDEPENDENT_CODE ON)
else(SPRINGBOK_HTML5)
  message("SDL is not supported outside of emscripten at the moment!")
endif(SPRINGBOK_HTML5)