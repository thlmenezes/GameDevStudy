#ifndef HEADER_RECT
#define HEADER_RECT
  #include <iostream>

  using namespace std;

  class Rect {
    public:
      Rect();
      Rect(int x, int y, int width, int height);
      float x,y,w,h;
      ~Rect();
  };
#endif