#ifndef TITLESTATE_H
  #define TITLESTATE_H
  #include <memory>
  #include <math.h>

  using namespace std;

  #include "Sprite.h"
  #include "Music.h"
  #include "Sound.h"
  #include "InputManager.h"
  #include "Camera.h" 
  #include "CameraFollower.h"
  #include "Alien.h"
  #include "TileMap.h"
  #include "State.h"
  #include "PenguinBody.h"
  // #include "Text.h"
  #include "Collider.h"
  #define INCLUDE_SDL
  #include "SDL_include.h"

  class TitleState : public State {
    public:
      TitleState();

      void LoadAssets();
      void Update(float dt);
      void Render();
      void Start();
      void Pause();
      void Resume();

      ~TitleState();
  };
#endif