#ifndef STATE_H
  #define STATE_H
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
  #include "PenguinBody.h"
  
  #include "Collider.h"
  // #include "GameData.h"

  #define INCLUDE_SDL
  #include "SDL_include.h"

  class State{
    Music *music;
    void Input();

    protected:
      void StartArray();
      virtual void UpdateArray(float dt);
      virtual void RenderArray();
      bool popRequested;
      bool quitRequested;
      bool started;
      vector<shared_ptr<GameObject>> objectArray;

    public:
      State();

      virtual void LoadAssets() = 0;
      virtual void Update(float dt) = 0;
      virtual void Render() = 0;
      virtual void Start() = 0;
      virtual void Pause () = 0;
      virtual void Resume () = 0;
      virtual weak_ptr<GameObject> AddObject(GameObject *go);
      virtual weak_ptr<GameObject> GetObjectPtr(GameObject *go);
      bool QuitRequested();
      bool PopRequested();

      virtual ~State();
  };
#endif