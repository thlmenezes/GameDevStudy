#ifndef HEADER_SPRITE
#define HEADER_SPRITE
  #include <iostream>

  using namespace std;

  #define INCLUDE_SDL_IMAGE
  #include "SDL_include.h"

  class Sprite{
    SDL_Texture* texture;
    int width;
    int height;
    SDL_Rect clipRect;
    void DestroyTexture();

    public:
      Sprite();
      Sprite(string file);
      void Open(string file);
      void SetClip(int x, int y,
                  int w, int h);
      void Render(int x, int y);
      int GetWidth();
      int GetHeight();
      bool IsOpen();
      ~Sprite();
  };
#endif