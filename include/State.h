#ifndef HEADER_STATE
#define HEADER_STATE
  #include <iostream>

  using namespace std;

  #include "Music.h"
  #include "Sprite.h"

  class State {
    bool quitRequested;
    Music music;
    Sprite bg;
    public:
      State();
      bool QuitRequested();
      void LoadAssets();
      void Update(float dt);
      void Render();
      ~State();
  };
#endif