#ifndef END_STATE_H
  #define END_STATE_H
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

  class EndState : public State {
    Music *backgroundMusic;
    public:
      EndState();

      void LoadAssets();
      void Update(float dt);
      void Render();

      void Start();
      void Pause();
      void Resume();

      ~EndState();
  };
#endif