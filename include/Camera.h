#ifndef CAMERA_H
  #define CAMERA_H

  #include "GameObject.h"
  #include "Vec2.h"

  class Camera {
    static  GameObject* focus;

    public:
      static void Follow(GameObject* newFocus);
      static void Unfollow();
      static void Update(float dt);
      static GameObject* GetFocus();

      static Vec2 pos;
      static Vec2 speed;
  };
#endif
