#include <stdlib.h>
#include <time.h>

using namespace std;

#include "Minion.h"
#include "Game.h"
#include "Sound.h"
#include "Sprite.h"
#include "Bullet.h"
#include "State.h"

Minion::Minion(GameObject &associated, GameObject &alienCenter, float arcOffsetDeg)
    : Component(associated),
      alienCenter(alienCenter),
      arc(arcOffsetDeg)
{
  Sprite *minion_ptr = new Sprite(associated, "assets/img/minion.png");
  float scale = 1 + (float)(rand() % 501) / 1000;
  minion_ptr->SetScaleX(Vec2(scale, scale));
  associated.AddComponent(minion_ptr);
}

void Minion::Shoot(Vec2 pos)
{
  float distance = associated.box.GetCenter().GetDS(pos);
  float angle = associated.box.GetCenter().GetAngle(pos);
  float speed = 800;
  int damage = 1;

  GameObject *go = new GameObject();
  go->AddComponent(new Bullet(
      *go,
      angle,
      speed,
      damage,
      distance,
      "assets/img/minionbullet1.png"));
  go->box.SetCenter(associated.box.GetCenter());
  Game::GetInstance().GetState().AddObject(go);
}

void Minion::Update(float dt)
{
  arc += 60 * dt;
  associated.angleDeg = arc - 90;
  associated.box.x = alienCenter.box.GetCenter().x + (200 * Vec2::Cos(arc)) - (associated.box.w / 2);
  associated.box.y = alienCenter.box.GetCenter().y + (200 * Vec2::Sin(arc)) - (associated.box.h / 2);
}

void Minion::Render() {}

bool Minion::Is(string type)
{
  return "Minion" == type;
}

Minion::~Minion() {}