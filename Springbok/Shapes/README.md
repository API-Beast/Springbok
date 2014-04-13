# Shapes module
The shapes module provides classes for primitive geometry that can be

- Drawing curves & lines with arbitary thickness using the [LineShape](#lines_curves) class

## Lines & Curves

```cpp
LineShape curve;
curve.appendPoint({ 0, 0}, 10); // First point is at 0, 0 with a thickness of 10px
curve.appendPoint({50, 0}, 10); // Next one at 50, 0 with 10px thickness, too
curve.appendPoint({75, 50}, 0); // Next one at 75, 50 fading out to 0px thickness
curve.setInterpolation(Interpolation::Cubic); // Enable cubic interpolation (Just for clarity: Cubic is the default)
curve.setPixelsPerSegment(3.f); // How many vertices the line segment should subdivided into per pixel manhattan distance. (The lower this value the smoother the curve, but the higher the performance cost.)
renderer.draw(curve); // The resulting line can be drawn like any other element, such as a Image
```

### Applying a texture to the curve
TODO

TODO: Pictures