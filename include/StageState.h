#ifndef STAGE_STATE_H
  #define STAGE_STATE_H
  using namespace std;

  #include "Music.h"
  #include "State.h"
  #include "GameObject.h"
  #include "TileSet.h"

  class StageState: public State {
    TileSet *tileSet;
    Music backgroundMusic;

    void CollisionCheck();
    void DeletionCheck();

    public:

      StageState();
      
      void LoadAssets();
      void Update(float dt);
      void Render();
      void Start();
      void Pause();
      void Resume();

      ~StageState();
  };
#endif