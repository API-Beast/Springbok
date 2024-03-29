# Springbok

Springbok is a C++ library for developing full featured 2D games in a limited timeframe. It provides many helpful classes, such as a KeyframeMap for animation, a Image class for managed texture loading and Vec2 and Angle classes to be used in your calculations. Springbok is not a engine, and gives you complete freedom in how you design your games code.

## Getting started

### Documentation

Each subdirectory of Springbok should contain a Markdown file explaning how the component in that directory is used. However, the documentation is currently incredibly incomplete, sorry about that!

### Building Springbok
In order to build Springbok you will need:

- A C++11 compilant compiler (Modern Versions of GCC or Clang, MSVC doesn't qualify  currently)
- A recent version of CMake
- [OpenAL][1], OpenGL 2.1 and [GLFW 3][2]

  [1]: https://github.com/kcat/openal-soft
  [2]: http://www.glfw.org/

Now you need to generate a makefile/project and invoke it, under Linux this typically look like this:

```bash
cmake .           ; Generate Makefile
make -j8          ; Compile library
make install -j8  ; Install library
```

This should also work just as well on Windows via MinGW, but this is currently untested.

## Contributing to Springbok

Make sure you take a look at the existing code before to get a idea of what kind of coding style we are going for.

A few things to keep in mind:

- Springbok should be a modular library, not a engine, as such try to keep new components as flexible as possible.
- Keeping it simple is the smartest thing you can do.
