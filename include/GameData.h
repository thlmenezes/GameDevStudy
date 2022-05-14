#ifndef GAME_DATA_H
  #define GAME_DATA_H
  #include <memory>
  #include <math.h>

  using namespace std;

  #include "Sprite.h"
  #include "Music.h"
  #include "Sound.h"
  #include "InputManager.h"
  #include "Camera.h" 
  #include "CameraFollower.h"
  #include "State.h"
  // #include "Text.h"
  #include "Collider.h"
  #define INCLUDE_SDL
  #include "SDL_include.h"

  class GameData {
    public:
      static bool playerVictory;
  };
#endif