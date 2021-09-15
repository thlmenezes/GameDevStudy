#ifndef HEADER_VEC2
#define HEADER_VEC2
  #include <iostream>

  using namespace std;

  class Vec2 {
    public:
      Vec2(int x, int y);
      float x,y;
      ~Vec2();
  };
#endif