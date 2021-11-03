#ifndef VEC2_H
  #define VEC2_H
  using namespace std;

  class Vec2 {
    public:
      float x,y;

      Vec2();
      Vec2(int x, int y);
      Vec2 GetRotated(float angle);
      ~Vec2();

      friend Vec2 operator + (Vec2 const &, Vec2 const &);
  };
#endif