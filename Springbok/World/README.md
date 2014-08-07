#World-Module

The World module consists of tools for creating 2D worlds.

##Tile Layer

The TileLayer class provides a simple way of displaying 2D maps consisting of tiles, as they can be created with [Tiled](http://www.mapeditor.org/).

```cpp
TileSet chessTiles;
chessTiles.set(0, Image("black.png"));
chessTiles.set(1, Image("white.png"));

TileLayer chessBoard(8, 8, chessTiles);
for(int x=0; x < 8; x++)
  for(int y=0; y < 8; y++)
    layer.Data.setAt(x, y, x%2 ^ y%2);
    
r.draw(chessBoard); // Draw using a SpriteRenderer
```

Maps created with Tiled can be loaded directly using the Serialization module. In this case you don't need to set up any TileSets or TileLayers, this is done automatically.
```cpp
TiledMap map = Deserialize<TiledMap>(LoadXML("map.tmx"));
for(TileLayer& layer : map.Layers)
  r.draw(layer);
```

###Custom Memory Structures/Allocation
Memory requirements for different kind of games can be vastly different, as such the TileLayer allows you to feed it any kind of data, in a similar fashion as OpenGL Buffers. (Unlike OpenGL Buffers the data is never copied, however.)

```cpp
// We use ASCII characters as index, no need to waste memory with shorts or ints!
char* map = new char[512*512];
TileSet tiles;
tiles.set('#', Image("wall.png"));
tiles.set('_', Image("floor.png"));
[...]

TileLayer mapLayer(512, 512, tiles);
mapLayer.Data             = MemoryBlock::Preallocated(map, 512*512);
mapLayer.Data.ElementSize = sizeof(char); // sizeof(int) is default and maximum
```
More complex data structures can be used too:
```cpp
struct Tile
{
  short Index = 0;
  short Flags = NoFlags;
  bool Solid = true;
};
Tile map[256][256];
TileSet tiles;
[...fill map...]

TileLayer background(256, 256, tiles);
background.Data                = MemoryBlock::Preallocated(map, 256*256);
background.Data.ElementSize    = sizeof(short);
background.Data.ElementPadding = sizeof(Tile) - sizeof(short);
```
The ElementSize is the size of the Index element, the ElementPadding is the size of the content that has to be skipped in order to get to the Index of the tile.

### Modifying maps

TileLayers can be resized and the indices can be directly accessed and manipulated.

```cpp
map.resize(128, 256, 0);
// Resize the map to 128x256
// If the map was smaller the newly assigned memory is filled with the index 0
// If the map was bigger data is lost

map.Data.at(X, Y);        // Getting
map.Data.at(Vec2I(X, Y)); // Getting

map.Data.setAt(X, Y, 1);  // Setting
map.Data.setAt(Pos,  1);  // Setting
```

You can find and replace patterns inside the TileLayer, this is useful for procedurally generating maps. For example you can generate a maze just identifying each tile as either on or off and then use pattern matching to give corners a distinct visual by changing their

```cpp
TileLayer map;
Pattern2D pat = {
  {1, 1},
  {1, 0}
 };
Pattern2D replacement = {
  {2, 3},
  {4, 0}
 };
Vec2I pos = 0; // Start searching at 0, 0
while((pos = map.find(pos, pat)) > -1)
  map.replace(pos, replacement);
```

**TODO:** Make example picture.