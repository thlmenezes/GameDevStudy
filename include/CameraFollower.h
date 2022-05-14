#ifndef CAMERAFOLLOWER_H
  #define CAMERAFOLLOWER_H

  #include <string>

  using namespace std;

  #include "Component.h"

  class CameraFollower : public Component {

    public:
      CameraFollower(GameObject& associated);

      void Update(float dt);
      void Render();
      bool Is(string type);
      void NotifyCollision(GameObject& other);
  };
#endif
