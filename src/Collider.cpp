#include "Collider.h"
#include "Game.h"
#include "Collision.cpp"

// DEBUG
#ifdef DEBUG
#include "Camera.h"
#include "Game.h"

#include <SDL2/SDL.h>
#endif // DEBUG

Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset) : Component(associated)
{
  this->scale = scale;
  this->offset = offset;
}

void Collider::Start() {}

void Collider::Update(float dt)
{
  box = associated.box;
  box.w *= scale.x;
  box.h *= scale.y;
  float angle = associated.angleDeg * (M_PI / 180);
  Vec2 offsetRotated = offset.Rotate(angle);
  box.x = (box.GetCenter().x + offsetRotated.x) - box.w / 2;
  box.y = (box.GetCenter().y + offsetRotated.y) - box.h / 2;
}

void Collider::Render()
{
#ifdef DEBUG
  Vec2 center(box.GetCenter());
  SDL_Point points[5];

  Vec2 point = (Vec2(box.x, box.y) - center).Rotate(associated.angleDeg / (180 / M_PI)) + center - Camera::pos;
  points[0] = {(int)point.x, (int)point.y};
  points[4] = {(int)point.x, (int)point.y};

  point = (Vec2(box.x + box.w, box.y) - center).Rotate(associated.angleDeg / (180 / M_PI)) + center - Camera::pos;
  points[1] = {(int)point.x, (int)point.y};

  point = (Vec2(box.x + box.w, box.y + box.h) - center).Rotate(associated.angleDeg / (180 / M_PI)) + center - Camera::pos;
  points[2] = {(int)point.x, (int)point.y};

  point = (Vec2(box.x, box.y + box.h) - center).Rotate(associated.angleDeg / (180 / M_PI)) + center - Camera::pos;
  points[3] = {(int)point.x, (int)point.y};

  SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

bool Collider::Is(string type)
{
  return "Collider" == type;
}

bool Collider::IsColliding(Collider collidingRect)
{
  float angle1 = associated.angleDeg * (M_PI / 180);
  float angle2 = collidingRect.associated.angleDeg * (M_PI / 180);
  Rect box2 = collidingRect.box;
  return Collision::IsColliding(box, box2, angle1, angle2);
}

void Collider::SetScale(Vec2 scale)
{
  this->scale = scale;
}

void Collider::SetOffset(Vec2 offset)
{
  this->offset = offset;
}

void Collider::NotifyCollision(GameObject &other) {}