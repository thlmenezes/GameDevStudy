#ifndef HEADER_GAME_OBJECT
#define HEADER_GAME_OBJECT
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

      GameObject();
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