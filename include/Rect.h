#ifndef HEADER_RECT
#define HEADER_RECT
  #include <iostream>
  #include <initializer_list>

  using namespace std;

  class Rect {
    public:
      float x,y,w,h;

      Rect();
      Rect(int x, int y, int width, int height);
      bool Contains(initializer_list<float> mouse);
      ~Rect();
  };
#endif