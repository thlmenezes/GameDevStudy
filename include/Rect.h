#ifndef RECT_H
#define RECT_H
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