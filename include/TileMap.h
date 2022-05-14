#ifndef TILEMAP_H
  #define TILEMAP_H
  #include <string>
  using namespace std;

  #include "TileSet.h"
  #include "GameObject.h"
  #include "Component.h"

  class TileMap: public Component {
    vector<int> tileMatrix;
    TileSet* tileSet;
    int mapWidth, mapHeight, mapDepth;

    public:
      TileMap(GameObject& associated, string file, TileSet* tileSet);

      void Load(string file);
      void SetTileSet(TileSet* tileSet);
      int& At(int x, int y, int z = 0);
      void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
      void Update(float dt);
      void Render();
      bool Is(string type);
      int GetWidth();
      int GetHeight();
      int GetDepth();
      void NotifyCollision(GameObject& other);

      ~TileMap();
  };
#endif