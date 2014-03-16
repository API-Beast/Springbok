## class RandomNumberGenerator

A minimal & cheap generator for pseudo-random numbers.

### Constructors

These all set the seed to the specified parameters.
```cpp
RandomNumberGenerator(unsigned int seed = unsigned(std::time(0)));  // Derive the 64-Bit seed from a 32-Bit seed. If no seed is given use the system time as seed.
RandomNumberGenerator(unsigned int lowSeed, unsigned int highSeed);
RandomNumberGenerator(unsigned long long int fullSeed);
```

### Generator Functions

Generate random numbers inside a specific range, this Range is always inclusive. (E.g. it is always possible that it returns the max value itself.)
```cpp
float getFloat();          // float in [0.0, 1.0]
T getNumber(T min, T max); // Number of type T in [min, max].
T getNumber(T max);        // [0, max].
```

These functions generate a random number for every component of the vector and return them, again in a vector.
```cpp
Vec2<T> getVec2(Vec2<T> min, Vec2<T> max);
Vec3<T> getVec3(Vec3<T> min, Vec3<T> max);
```

Generates 32 random bits, all other generator functions are based on this one.
```cpp
unsigned int generate();
```

### Member Variables

```cpp
unsigned int HighSeed; // First 32 Bits of the Seed.
unsigned int LowSeed;  // Last  32 Bits of the Seed.
```

### Global Variables

Outside of class scope
```cpp
extern RandomNumberGenerator gRNG; // A global, default-initialized instance of the RandomNumberGenerator for convinience.
```

