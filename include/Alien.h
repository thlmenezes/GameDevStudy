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
        Action (ActionType type, float x, float y) {
          this->type = type;
          pos.x = x;
          pos.y = y;
        };
        ActionType type;
        Vec2 pos;
    };

    int hp;
    Vec2 speed;
    int nMinions;

    vector<weak_ptr<GameObject>> minionArray;

    queue<Action> taskQueue;

    public:
      Alien(GameObject& associated, int nMinions);

      void Start();
      void Update(float dt);
      void Damage(int damage);
      void Render();
      bool Is(string type);
      void NotifyCollision(GameObject& other);

      ~Alien();
  };
#endif
