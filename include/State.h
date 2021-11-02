#ifndef HEADER_STATE
#define HEADER_STATE
  #include <vector>
  #include <memory>

  using namespace std;

  #include "Music.h"
  #include "Sprite.h"
  #include "GameObject.h"

  class State {
    bool quitRequested;
    Music music;
    Sprite* bg;
    void Input();
    void AddObject(int mouseX, int mouseY);
    vector<unique_ptr<GameObject>> objectArray;

    public:
      State();
      void LoadAssets();
      void Update(float dt);
      void Render();
      bool QuitRequested();
      ~State();
  };
#endif