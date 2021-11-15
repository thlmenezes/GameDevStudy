#ifndef STATE_H
  #define STATE_H
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
    vector<shared_ptr<GameObject>> objectArray; 
    bool started;

    public:
      State();
      void LoadAssets();
      void Start();
      weak_ptr<GameObject> AddObject(GameObject* go);
      weak_ptr<GameObject> GetObjectPtr(GameObject* go);
      void Update(float dt);
      void Render();
      bool QuitRequested();
      ~State();
  };
#endif