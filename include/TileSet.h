#ifndef TILESET_H
  #define TILESET_H
  #include <iostream>

  using namespace std;

  #include "Sprite.h"

  class TileSet {
    Sprite tileSet;
    int tileWidth, tileHeight, rows, columns;

    public:
      TileSet(int titleWidth, int titleHeight, string file);
      void RenderTile(unsigned int index, float x, float y);
      int GetTileWidth();
      int GetTileHeight();
      ~TileSet();
  };
#endif