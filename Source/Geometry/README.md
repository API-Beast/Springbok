# Geometry module

- Custom arithmetics for [Vectors](#vectors)
- Custom arithmetics for [Angles](#angles)

## Vectors

2D Vectors are simple containers that contain exactly two values of a single type: X and Y.
```cpp
vec.X;  // Get the X value from vec
vec.Y;  // Get the Y value from vec
vec[0]; // Alternatively you can also get the values by Index, X is 0 and Y is 1 
```

### Initializing Vectors
```cpp
Vec2F a = Vec2F(0.4f, 0.6f);
Vec2F b = Vec2F(3.3f);  // Equal to Vec2F(3.3f, 3.3f);
Vec2F c = {0.4f, 0.6f}; // C++11 Uniform initialization
Vec2F d = 3.3f;    // Implicit conversion from float, equal to Vec2F(3.3f, 3.3f);
Vec2I e = {-6, 8}; // Note the type, I = Int, F = Float, U = Unsigned Int
Vec2<double> f = {4.4, 7.8}; // Or you can use the template parameter
```

### Vector math
All C++ supplied mathematical operators are overloaded in order to simplify many assignments.
```cpp
vecA + vecB; // Adds the X value of vecB to the X value of vecA, the same with the Y value.
vecA + 2.f;  // Adds 2.f to both values of VecA
vecA * -1;   // All math operators are overloaded like this.
obj.Position += obj.Speed * dt; // ... including assignment operators ...
obj.Position % tileSize; // ... and modulo.
```

Of course there are also member functions that define vector specific operations and properties.
```cpp
Vec2F(0.0f, 2.0f).getLength();    // == 2.0f; A single float denoting the length of a vector, also known as magnitude.
Vec2F(5.372f, 0.0f).normalized(); // == {1.0f, 0.0f}; Normalized version of the vector, a vector which points in the same direction but has a length of 1, also known as unit vector.
vecA.dot(vecB); // dot product between VecA and VecB, also knohwn as scalar product.
```

### 3D and 4D Vectors
3D and 4D vectors behave mostly the same as 2D vectors, just that they have more elements.

```cpp
vec3.Z;  // Get the third value from vec3
vec4.A;  // Get the fourth value from vec4
vec4[3]; // Of course index operator also works for higher dimensions.
```

```cpp
Vec3F a = {0.4f, 0.3f, 1.0f};
Vec4F b = {0.5f, 0.5f, 0.5f, 1.0f};
Vec3F c = Vec2F{0.5f, 1.0f}; // The third parameter is defaulted to 0
Vec4I d = Vec3I{1, 9, 20};   // The fourth parameter is defaulted to 1 (_not_ 0)
```

Note: initialization from Angles only works with for 2 dimensional vectors.

You can use a lesser dimensional version of these vectors the same way as it is possible in GLSL.

```cpp
Angle(vec3.YZ); // Get the direction of this vector on the YZ plane.
vec3.XY = 0;    // Set the X and Y coordinates while leaving the Z coordinate untouched
vec4.XYZ.dot(); // Calculate the dot while ignoring the alpha coordinate.h
```

Note that unlike GLSL you can only access consectuitive elements like this, `.ZYX` for example is not valid, nor is `.XXY` and the like.

## Angles

### Angle Literals and Constructors
```cpp
Angle a = 0.5_turn;  // A half turn.
Angle b = 180_deg;   // Equals 180°
Angle c = 3.142_rad; // Is almost 3.142 in Radian. (You probably don't want to declare variables like this)
Angle d = Angle(PI); // The float constructor is explicit and will take Radians as unit.
Angle e = Angle::FromTurn(0.5f); // If you need to pass float variables in other formats.
Angle f = Angle::FromDegree(180.0f);
Angle g = Angle::FromRadians(PI); // Lastly, for verbosity
```
Note that Angles are internally stored as a value wrapped to -PI to +PI.
```cpp
 0.5_turn == 1.5_turn; // true
-0.2_turn == 0.8_turn; // true
```

### Angle Arithmetics
All angle operators are overloaded. Note that most Angle operators only work with other Angles (exceptions are only the * and / operators) and all conversions are explicit, this it to avoid unwanted bugs.

```cpp
0.8_turn + 0.2_turn;  // = 1.0_turn = 0_turn
0.5_turn - 0.3_turn;  // = 0.2_turn
-0.4_turn - 0.2_turn; // = -0.6_turn = 0.4_turn
0.2_turn * 4;         // = 0.8_turn = -0.2_turn
```

Operator< and operator> are defined as "is the difference between the two parameters smaller than 0". This allows to use the same arithmetics for approaching values for both numbers and angles. If the difference is smaller than the the second parameter is clockwise from the first.
```cpp
if(curAngle < targetAngle) // Is the same as "if(curAngle - targetAngle < 0)"
  curAngle += 0.1_turn;    // Rotate clockwise
else                       // The difference is bigger than 0.
  curAngle -= 0.1_turn;    // Rotate counter-clockwise
```

Lastly the Angle class has wrappers for some of the trigonometric functions and some functions for working with vectors.
```cpp
Angle(Vec2F(0, 1.0f));    // Construct a angle from a vector (in this case construct a angle pointing down)
(0.5_turn).toDirection(); // = Vec2F(0, 1.0f); Returns a unit vector pointing into the same direction as the Angle
(20_deg).rotateVec(vecA); // Rotate vecA by 20 degrees.

(0.25_turn).sin(); // Sin of PI/2
(0.25_turn).cos();
Angle::Atan2(400, 600); // Returns the atan2 of 400, 600 as Angle
```