#include <stdlib.h>
#include <time.h>

using namespace std;

#include "Minion.h"
#include "Game.h"
#include "Sound.h"
#include "Sprite.h"
#include "Bullet.h"
#include "State.h"
#include "Collider.h"

Minion::Minion(GameObject &associated, GameObject &alienCenter, float arcOffsetDeg)
    : Component(associated),
      alienCenter(Game::GetInstance().GetCurrentState().GetObjectPtr(&alienCenter)),
      arc(arcOffsetDeg)
{
  Sprite *minion_ptr = new Sprite(associated, "assets/img/minion.png");
  float scale = 1 + (float)(rand() % 501) / 1000;
  minion_ptr->SetScaleX(Vec2(scale, scale));
  associated.AddComponent(minion_ptr);
  associated.AddComponent(new Collider(associated));
}

void Minion::Shoot(Vec2 pos)
{
  float distance = associated.box.GetCenter().GetDS(pos);
  float angle = associated.box.GetCenter().GetAngle(pos);
  float speed = 800;
  int damage = 1;

  GameObject *go = new GameObject();
  auto sprite_ptr = new Sprite(*go, "assets/img/minionbullet2.png", 3, 0.17);
  sprite_ptr->SetScaleX(Vec2(2, 2));
  go->AddComponentAsFirst(new Bullet(
      *go,
      angle,
      speed,
      damage,
      distance,
      sprite_ptr,
      true));
  go->box.SetCenter(associated.box.GetCenter());
  Game::GetInstance().GetCurrentState().AddObject(go);
}

void Minion::Update(float dt)
{
  if (alienCenter.expired())
  {
    associated.RequestDelete();
    GameObject *minionDeathGO = new GameObject();
    minionDeathGO->AddComponent(new Sprite(*minionDeathGO, "assets/img/miniondeath.png", 4, 0.15, 12.0 / 30.0));
    minionDeathGO->box.SetCenter(associated.box.GetCenter());
    minionDeathGO->angleDeg = rand() % 360;
    Game::GetInstance().GetCurrentState().AddObject(minionDeathGO);
  }
  else
  {
    arc += 60 * dt;
    associated.angleDeg = arc - 90;
    associated.box.x = alienCenter.lock()->box.GetCenter().x + (200 * Vec2::Cos(arc)) - (associated.box.w / 2);
    associated.box.y = alienCenter.lock()->box.GetCenter().y + (200 * Vec2::Sin(arc)) - (associated.box.h / 2);
  }
}

void Minion::Render() {}

bool Minion::Is(string type)
{
  return "Minion" == type;
}

void Minion::NotifyCollision(GameObject &other) {}

Minion::~Minion() {}