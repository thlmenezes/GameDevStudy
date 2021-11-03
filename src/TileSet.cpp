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
  {
    SDL_Log("Invalid attempt to RenderTile on index: %d", index);
    exit(EXIT_FAILURE);
  }

  int clipX = index % columns * tileWidth,
      clipY = index / columns * tileHeight;
  tileSet.SetClip(clipX, clipY, tileWidth, tileHeight);
  tileSet.Render(x, y);
}

int TileSet::GetTileWidth()
{
  return tileWidth;
}

int TileSet::GetTileHeight()
{
  return tileHeight;
}

TileSet::~TileSet()
{
}
