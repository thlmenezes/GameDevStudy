#ifndef PENGUIN_BODY_H
  #define PENGUIN_BODY_H

  #include <string>
  #include <queue>

  using namespace std;

  #include "GameObject.h"
  #include "InputManager.h"
  #include "Component.h"
  #include "Vec2.h"
  #include "Sprite.h"

  class PenguinBody : public Component{
    weak_ptr<GameObject> pcannon;
    Vec2 speed;
    float linearSpeed;
    float angle;
    int hp;

    public:
      static PenguinBody *player;

      PenguinBody(GameObject &associated);

      void Start();
      void Update(float dt);
      void Damage(int damage);
      void Render();
      bool Is(string type);
      void NotifyCollision(GameObject& other);
      Vec2 GetPlayerCenter();

      ~PenguinBody();
  };
#endif