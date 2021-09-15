#include <iostream>
#include <exception>

using namespace std;

#include "Rect.h"

Rect::Rect(int coord_x, int coord_y, int width, int height)
{
  x = coord_x;
  y = coord_y;
  w = width;
  h = height;
}

Rect::~Rect()
{
}
