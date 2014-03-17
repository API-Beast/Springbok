## Animation Module

### Approaching

Approaching is the simplest way of interpolating between two values and well suited for variables that impact gameplay. It changes from one value to a different at a constant pace.
```cpp
void update(float dt)
{
	CurRotation = Approach(CurRotation, TargetRotation, 45_deg * dt);
	// Slowly approach TargetRotation by 45° per second.
	// Does Nothing if CurRotation == TargetRotation
}
```
This simply adds `45_deg * dt` to CurRotation if CurRotation is smaller than TargetRotation, otherwise it subtracts it.

### Keyframing

If you know beforehand how a animation should proceed you can use the `KeyframeMap` class.

```cpp
[... Initializiation ...]
KeyframeMap<Vec3F> BackgroundColor;
BackgroundColor.insert(0.0f, Palette::Green);
BackgroundColor.insert(1.0f, Palette::Blue);
BackgroundColor.insert(1.0f, Palette::Red);
BackgroundColor.setExtrapolation(KeyframeMap::Repeat);
BackgroundColor.setInterpolationMethod(Interpolation::Cubic); // Cubic is already the default, it will work the same without this line
// Other options are Linear, Constant and AutoEase (Explained later.)

float TimeSinceStart = 0.f;
RenderContext Renderer;

[... every frame ...]
TimeSinceStart += deltaTime;
Renderer.setClearColor(BackgroundColor[TimeSinceStart]);
```
TODO: Add .gif of Animation here.

Any class that has basic math operators defined can be used with KeyframeMap.
```cpp
KeyframeMap<int> a;
// You can also initialize KeyframeMaps using C++11 Initializer Lists instead of insert.
KeyframeMap<Angle> b = {{0.0f, -0.5_turn}, {1.0f, 0.0_turn}, {2.0f, 0.5_turn}};
```

#### Easing

Springbok also supports a few easing functions to give Animations more character. The different Easing Functions are defined in "Easing.h".

```cpp
BackgroundColor.setInterpolationMethed(Interpolation::AutoEase, PowerEasing(3)); // Pretty abrupt change
```

TODO: Springbok only has two pretty useless easing functions at the moment... write this segment once it has been extended.