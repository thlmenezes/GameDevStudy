#ifndef MINION_H
  #define MINION_H
  #include <memory>
  #include <string>

  using namespace std;

  #include "Component.h"
  #include "Vec2.h"

  class Minion : public Component {
    GameObject& alienCenter;
    float arc;

    public:

      Minion(GameObject& associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);

      void Shoot(Vec2 target);
      void Update(float dt);
      void Render();
      bool Is(string type);

      ~Minion();
  };
#endif