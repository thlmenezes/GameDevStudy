#ifndef RECT_H
#define RECT_H
  #include <initializer_list>

  using namespace std;

  #include "Vec2.h"

  class Rect {
    public:
      float x,y,w,h;

      Rect();
      Rect(int x, int y, int width, int height);
      bool Contains(initializer_list<float> mouse);
      void SetPos(float x, float y);
      void SetPos(Vec2 pos);
      Vec2 GetPos();
      void SetCenter(float x, float y);
      void SetCenter(Vec2 center);
      Vec2 GetCenter();
      ~Rect();
  };
#endif