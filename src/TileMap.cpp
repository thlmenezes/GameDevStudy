#include <fstream>

using namespace std;

#include "TileMap.h"
#include "Camera.h"

TileMap::TileMap(GameObject &associated, string file, TileSet *tileSet)
    : Component(associated)
{
  Load(file);
  this->tileSet = tileSet;
}

void TileMap::Load(string file)
{
  ifstream rs(file, ios::in);

  if (!rs.is_open())
  {
    SDL_Log("Unable to open file: %s", file.c_str());
    exit(EXIT_FAILURE);
  }

  char c;

  // # tileMap.txt
  // mapWidth,mapHeight,mapDepth
  rs >> mapWidth >> c >> mapHeight >> c >> mapDepth >> c;

  int in;
  while (rs >> in)
  {
    tileMatrix.push_back(in - 1);
    rs >> c; // ignore char after number
  }
}

void TileMap::SetTileSet(TileSet *tileSet)
{
  this->tileSet = tileSet;
}

int &TileMap::At(int x, int y, int z)
{
  int index = z * mapWidth * mapHeight + y * mapWidth + x;
  return tileMatrix[index];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
{
  for (int y = 0; y < mapHeight; y++)
    for (int x = 0; x < mapWidth; x++)
    {
      int xPos = x * tileSet->GetTileWidth() - cameraX;
      int yPos = y * tileSet->GetTileHeight() - cameraY;
      tileSet->RenderTile(At(x, y, layer), xPos, yPos);
    }
}

void TileMap::Update(float dt) {}

void TileMap::Render()
{
  for (int layer = 0; layer < mapDepth; layer++)
    RenderLayer(
        layer,
        Camera::pos.x * (1 + (layer * 0.50)),
        Camera::pos.y * (1 + (layer * 0.50)));
}

bool TileMap::Is(string type)
{
  return "TileMap" == type;
}

int TileMap::GetWidth()
{
  return mapWidth;
}

int TileMap::GetHeight()
{
  return mapHeight;
}

int TileMap::GetDepth()
{
  return mapDepth;
}

void TileMap::NotifyCollision(GameObject &other) {}

TileMap::~TileMap() {}
