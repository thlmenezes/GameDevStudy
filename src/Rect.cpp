using namespace std;

#include "Rect.h"

Rect::Rect()
    : Rect(0, 0, 0, 0)
{
}

Rect::Rect(int coord_x, int coord_y, int width, int height)
{
  x = coord_x;
  y = coord_y;
  w = width;
  h = height;
}

bool Rect::Contains(initializer_list<float> mouse)
{
  // x,y ------------- x+w,y
  //  |                   |
  // x,y+h------------ x+w,y+h

  initializer_list<float>::iterator mouseIt = mouse.begin();
  float mouseX = *mouseIt++, mouseY = *mouseIt;

  bool outside = mouseX < x ||
                 mouseX > x + w ||
                 mouseY > y + h ||
                 mouseY < y;
  return !outside;
}

Rect::~Rect() {}
