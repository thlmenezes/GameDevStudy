#ifndef MINION_H
  #define MINION_H
  #include <memory>
  #include <string>

  using namespace std;

  #include "Component.h"
  #include "Vec2.h"

  class Minion : public Component {
    weak_ptr<GameObject> alienCenter;
    float arc;

    public:

      Minion(GameObject& associated, GameObject& alienCenter, float arcOffsetDeg = 0);

      void Shoot(Vec2 target);
      void Update(float dt);
      void Render();
      bool Is(string type);
      void NotifyCollision(GameObject& other);

      ~Minion();
  };
#endif
