#include <iostream>
#include <exception>

using namespace std;

#include "TileSet.h"
#include "GameObject.h"

TileSet::TileSet(int titleWidth, int titleHeight, string file) : tileSet(*new GameObject())
{
  tileSet.Open(file);
  tileWidth = titleWidth;
  tileHeight = titleHeight;
  rows = tileSet.GetHeight() / tileHeight;
  columns = tileSet.GetWidth() / tileWidth;
}

void TileSet::RenderTile(unsigned int index, float x, float y)
{
  if (index > (unsigned int)(rows * columns - 1))
    throw_with_nested(runtime_error("Invalid RenderTile on index: " + index));

  int clipX = index % columns * tileWidth,
      clipY = index / columns * tileHeight;
  tileSet.SetClip(clipX, clipY, tileWidth, tileHeight);
  tileSet.Render(x, y);
}

int TileSet::getTileWidth()
{
  return tileWidth;
}

int TileSet::getTileHeight()
{
  return tileHeight;
}

TileSet::~TileSet()
{
}
