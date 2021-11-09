#ifndef ALIEN_H_
  #define ALIEN_H_

  #include <memory>
  #include <string>
  #include <vector>
  #include <queue>

  using namespace std;

  #include "Component.h"
  #include "Vec2.h"

  class Alien : public Component {
    class Action {
      public:
        enum ActionType { MOVE, SHOOT };
        Action (ActionType type, float x, float y);
        ActionType type;
        Vec2 pos;
    };

    int hp;
    Vec2 speed;

    vector<weak_ptr<GameObject>> minionArray;

    queue<Action> taskQueue;

    public:
      Alien(GameObject& associated, int nMinions);

      void Start();
      void Update(float dt);
      void Render();
      bool Is(string type);

      ~Alien();
  };
#endif