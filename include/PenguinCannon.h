#ifndef PENGUIN_CANNON_H
  #define PENGUIN_CANNON_H

  #include <string>
  #include <queue>

  using namespace std;
  
  #include "GameObject.h"
  #include "InputManager.h"
  #include "Component.h"
  #include "Vec2.h"
  #include "Sprite.h"
  #include "Sound.h"
  #include "Timer.h"

  class PenguinCannon : public Component {
    weak_ptr<GameObject> pbody;
    float angle;
    Timer cooldown;

    public:

      PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody);

      void Start();
      void Shoot();
      void Update(float dt);
      void Render();
      bool Is(string type);
      void NotifyCollision(GameObject& other);
  };
#endif