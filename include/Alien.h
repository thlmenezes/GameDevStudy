#ifndef ALIEN_H_
  #define ALIEN_H_

  #include <memory>
  #include <string>
  #include <vector>
  #include <queue>

  using namespace std;

  #include "Component.h"
  #include "Vec2.h"
  #include "Timer.h"

  class Alien : public Component {
    enum AlienState { RESTING, MOVING };
    AlienState state;
    Timer restTimer;
    float restTime;
    Vec2 destination;

    int hp;
    Vec2 speed;
    int nMinions;

    vector<weak_ptr<GameObject>> minionArray;

    public:
      static int alienCount;

    
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
