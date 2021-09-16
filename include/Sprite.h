#ifndef HEADER_SPRITE
#define HEADER_SPRITE
  #include <iostream>

  using namespace std;

  #define INCLUDE_SDL_IMAGE
  #include "SDL_include.h"
  #include "Component.h"

  class Sprite: public Component {
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;
    void DestroyTexture();

    public:
      Sprite(GameObject& associated);
      Sprite(GameObject& associated, string file);
      void Open(string file);
      void SetClip(int x, int y,
                  int w, int h);
      void Update(float dt);
      void Render();
      bool Is(string type);
      int GetWidth();
      int GetHeight();
      bool IsOpen();
      ~Sprite();
  };
#endif