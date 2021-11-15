#ifndef VEC2_H
  #define VEC2_H
  using namespace std;

  class Vec2 {
    float GetDX(float x);
    float GetDY(float y);

    public:
      float x,y;

      Vec2();
      Vec2(int x, int y);
      Vec2 GetRotated(float angle);
      float GetCos(Vec2 pos);
      float GetSin(Vec2 pos);
      float GetDS(Vec2 pos);
      ~Vec2();

      friend Vec2 operator + (Vec2 const &, Vec2 const &);
      friend bool operator == (Vec2 const &, Vec2 const &);

      static float Cos(float rad);
      static float Sin(float rad);
  };
#endif