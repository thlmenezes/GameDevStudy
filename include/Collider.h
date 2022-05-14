#ifndef COLLIDER_H
  #define COLLIDER_H
  #include <string>
  #include <queue>

  using namespace std;

  #include "GameObject.h"
  #include "Component.h"
  #include "Vec2.h"
  #include "InputManager.h"

  class Collider : public Component{
    Vec2 scale;
    Vec2 offset;

    public:
      Rect box;

      Collider(GameObject& associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});
      void Start();
      void Update(float dt);
      void Render();
      bool Is(string type);
      bool IsColliding(Collider collidingRect);
      void SetScale(Vec2 scale );
      void SetOffset(Vec2 offset);
      void NotifyCollision(GameObject& other);
  };
#endif