add_executable(HelloSpringbok HelloWorld.cpp main.cpp)



if(HTML5BUILD)
  target_link_libraries(HelloSpringbok Springbok)
else(HTML5BUILD)
find_package(X11 REQUIRED)
find_package(Xrandr REQUIRED)
  target_link_libraries(HelloSpringbok ${Xrandr_LIBRARIES} ${X11_LIBRARIES} rt Springbok pthread Xxf86vm Xi)
endif(HTML5BUILD)
