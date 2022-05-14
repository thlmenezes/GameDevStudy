#ifndef SPRITE_H
  #define SPRITE_H
  #include <memory>
  using namespace std;

  #define INCLUDE_SDL_IMAGE
  #include "SDL_include.h"
  #include "Component.h"
  #include "Vec2.h"

  class Sprite: public Component {
    shared_ptr<SDL_Texture> texture;
    int width;
    int height;
    int frameCount;
    int currentFrame;
    float frameTime;
    float timeElapsed;
    SDL_Rect clipRect;
    Vec2 scale;

    public:
      Sprite(GameObject& associated);
      Sprite(GameObject& associated, string file, int frameCount = 1, float frameTime = 1);

      void Open(string file);
      void SetClip(int x, int y,
                  int w, int h);
      void SetScaleX(Vec2 scale);
      void Update(float dt);
      void Render();
      void Render(float x, float y);
      bool Is(string type);
      int GetWidth();
      int GetHeight();
      Vec2 GetScale();
      bool IsOpen();
      void SetFrame(int frame);
      void SetFrameCount(int frameCount);
      void SetFrameTime(float frameTime);
      void NotifyCollision(GameObject& other);

      ~Sprite();
  };
#endif