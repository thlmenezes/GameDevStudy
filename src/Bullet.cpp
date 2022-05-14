using namespace std;

#include "Bullet.h"
#include "Game.h"
#include "Sprite.h"
#include "Collider.h"

Bullet::Bullet(GameObject &associated,
               float angle,
               float speed,
               int damage,
               float maxDistance,
               Sprite *sprite,
               bool targetsPlayer)
    : Component(associated),
      speed(Vec2(speed * Vec2::Cos(angle), speed * Vec2::Sin(angle))),
      distanceLeft(maxDistance),
      damage(damage),
      targetsPlayer(targetsPlayer)
{
  associated.AddComponent(sprite);
  associated.angleDeg = angle;
  associated.AddComponent(new Collider(associated));
}

void Bullet::Update(float dt)
{
  if (distanceLeft < 1)
  {
    associated.RequestDelete();
    return;
  }

  associated.box.x += speed.x * dt;
  associated.box.y += speed.y * dt;
  distanceLeft -= Vec2().GetDS(Vec2(speed.x * dt, speed.y * dt));
}

void Bullet::Render() {}

bool Bullet::Is(string type)
{
  return "Bullet" == type;
}

int Bullet::GetDamage()
{
  return damage;
}

void Bullet::NotifyCollision(GameObject &other) {}

Bullet::~Bullet() {}
