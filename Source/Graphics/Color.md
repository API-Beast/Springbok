@defgroup Color

Springbok has a few classes that represent colors in different Colorspaces, including functions to convert them to ColorRGB, a color in the native RGB colorspace. ColorHSY provides a color in a colorspace suitable to generate color shemes from.

Example for using ColorHSY and TintHSY to generate new colors from a base color:
```cpp
TintHSY shadowTint;
shadowTint.HueShift = -0.3f;
shadowTint.SaturationMult = 1.2f;
shadowTint.LumaMult = 0.5f;
shadowTint.LumaAdd  = -0.1f;

TintHSY highlightTint{+0.1f, 0.8f, 2.0f};
highlightTint.HueShift = +0.1f;
highlightTint.SaturationMult = 0.5f;
highlightTint.LumaAdd = +0.4f;

ColorHSY           base = ColorRGB::Green;
ColorHSY    shadowColor = base.tint(shadowTint);
ColorHSY highlightColor = base.tint(highlightTint);
```

ColorRGB also provides mathematical operators between two colors for different kinds of blending:
