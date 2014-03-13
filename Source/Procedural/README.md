# Procedural Module

## Generating Pseudo-Random Numbers
Springbok has it's own, extremly simple, Pseudo-Random generator.

```cpp
RandomNumberGenerator RNG;   // The default constructor initializes the seed by unix time.
RNG.getFloat();              // Returns a random float between 0.0f and 1.0f
RNG.getNumber(10);           // Returns a random number between 0 and 10, inclusive (e.g. lowest possible result is 0, highest possible result is 10)
RNG.getNumber(0, 10);        // Ditto.
                             // The template parameter is automatically deduced in above example.
RNG.getNumber<float>(0, 10); // Returns a random float between 0 and 10, for example 5.362f
RNG.getVec2(Vec2F(-100, -100), Vec2F(100, 100)); // Calculates 2 random numbers between -100 and +100 and puts them into one Vec2, for example Vec2F(43.823f, -22.8590f)

// For convinience sake Springbok defines a global, default initialized RandomNumberGenerator, that you can use.
gRandom.getFloat();
```

The generator is very minimal and has a very insignificant overhead of 2 32-Bit Integers. Due to it's simplicity it is also extremly fast.
The quality of the generated numbers are higher than that of the C stdlib `rand` and `random` functions, but lower than that of Mersenne Twister.

It is based on the [GameRNG][1] algorithm from IanBullard.

  [1]: http://www.redditmirror.cc/cache/websites/mjolnirstudios.com_7yjlc/mjolnirstudios.com/IanBullard/files/79ffbca75a75720f066d491e9ea935a0-10.html

### Saving and Loading Seeds

The seed are saved in the two member variables `HighSeed` and `LowSeed` which can be modified and read from.

```cpp
// Save the world seed so that it can be reused later.
saveGame["World.LowSeed"]  = WorldRNG.LowSeed;
saveGame["World.HighSeed"] = WorldRNG.HighSeed;
// [...] Use WorldRNG here
```

```cpp
// Savegame loaded, now regenerate the world with the same seed
WorldRNG.LowSeed  = saveGame["World.LowSeed" ].toUInt();
WorldRNG.HighSeed = saveGame["World.HighSeed"].toUInt();
// [...] WorldRNG will now produce the same series of numbers as at that time when it was saved
```