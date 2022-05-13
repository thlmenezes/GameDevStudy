#ifndef BULLET_H
  #define BULLET_H
  #include <string>

  using namespace std;

  #include "Component.h"
  #include "Vec2.h"

  class Bullet : public Component {
    Vec2 speed;
    float distanceLeft;
    int damage;

    public:

      Bullet(GameObject& associated,
             float angle,
             float speed,
             int damage,
             float maxDistance,
             string sprite,
             int frameCount = 1,
             int frameTime = 1);

      void Update(float dt);
      void Render();
      bool Is(string type);
      int GetDamage();

      ~Bullet();
  };
#endif
