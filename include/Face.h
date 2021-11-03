#ifndef FACE_H
  #define FACE_H
  using namespace std;

  #include "GameObject.h"
  #include "Component.h"

  class Face: public Component{
    int hitpoints;

    public:
      Face(GameObject& associated);
      void Damage(int damage);
      void Update(float dt);
      void Render();
      bool Is(string type);
  };
#endif