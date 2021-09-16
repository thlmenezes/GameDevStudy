#ifndef HEADER_COMPONENT
#define HEADER_COMPONENT
  #include <iostream>

  using namespace std;

  class GameObject;

  class Component {
    protected:
      GameObject& associated;
    public:
      Component(GameObject& associated);
      virtual void Update(float dt) = 0;
      virtual void Render() = 0;
      virtual bool Is(string type) = 0;
      virtual ~Component();
  };
#endif