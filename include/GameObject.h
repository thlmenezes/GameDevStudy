#ifndef GAME_OBJECT_H
  #define GAME_OBJECT_H
  #include <vector>
  #include <memory>

  using namespace std;

  #include "Rect.h"
  #include "Component.h"

  class GameObject {
    vector<unique_ptr<Component>> components;
    bool isDead;

    public:
      Rect box;
      bool started;
      double angleDeg;

      GameObject();
      void Start();
      void Update(float dt);
      void Render();
      bool IsDead();
      void RequestDelete();
      void AddComponent(Component* cpt);
      void RemoveComponent(Component* cpt);
      Component* GetComponent(string type);
      ~GameObject();
  };
#endif