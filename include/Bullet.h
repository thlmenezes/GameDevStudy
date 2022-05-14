#ifndef BULLET_H
  #define BULLET_H
  #include <string>

  using namespace std;

  #include "Component.h"
  #include "Vec2.h"
  #include "Sprite.h"

  class Bullet : public Component {
    Vec2 speed;
    float distanceLeft;
    int damage;

    public:
      bool targetsPlayer;

      Bullet(GameObject& associated,
             float angle,
             float speed,
             int damage,
             float maxDistance,
             Sprite* sprite,
             bool targetsPlayer);

      void Update(float dt);
      void Render();
      bool Is(string type);
      int GetDamage();
      void NotifyCollision(GameObject& other);

      ~Bullet();
  };
#endif
