using namespace std;

#include "PenguinCannon.h"
#include "Bullet.h"
#include "Camera.h"
#include "Game.h"
#include "Collider.h"
#include "Timer.h"

PenguinCannon::PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody)
    : Component(associated),
      pbody(penguinBody),
      angle(0),
      cooldown(Timer())
{
  associated.AddComponent(new Sprite(associated, "./assets/img/cubngun.png"));
  associated.AddComponent(new Collider(associated));
}

void PenguinCannon::Start() {}

void PenguinCannon::Shoot()
{
  if (cooldown.Get() < 0.5)
    return;

  GameObject *go = new GameObject();
  Sprite *sprite = new Sprite(*go, "assets/img/penguinbullet.png", 4, 0.33);
  sprite->SetScaleX(Vec2(1, 1));
  go->AddComponentAsFirst(new Bullet(*go, angle, 800, 1, 1000, sprite, false));
  go->box.SetCenter(associated.box.GetCenter() + Vec2(Vec2::Cos(angle) * associated.box.w / 2, Vec2::Sin(angle) * associated.box.w / 2));
  Game::GetInstance().GetCurrentState().AddObject(go);

  cooldown.Restart();
}

void PenguinCannon::Update(float dt)
{
  if (pbody.expired())
  {
    associated.RequestDelete();
    return;
  }
  cooldown.Update(dt);
  associated.box.SetCenter(pbody.lock()->box.GetCenter());
  angle = associated.box.GetCenter().GetAngle(
      InputManager::GetInstance().GetMousePos() +
      Camera::pos);
  associated.angleDeg = angle;
  if (InputManager::GetInstance().IsMouseDown(LEFT_MOUSE_BUTTON))
    Shoot();
}

void PenguinCannon::Render() {}

bool PenguinCannon::Is(string type)
{
  return "PenguinCannon" == type;
}

void PenguinCannon::NotifyCollision(GameObject &other) {}