using namespace std;

#include "PenguinBody.h"
#include "PenguinCannon.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"
#include "Bullet.h"
#include "Collider.h"

PenguinBody *PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject &associated)
    : Component(associated),
      speed(Vec2()),
      linearSpeed(0.1),
      angle(0),
      hp(10)
{
  associated.AddComponent(new Sprite(associated, "./assets/img/penguin.png"));
  player = this;
  associated.AddComponent(new Collider(associated));
}

void PenguinBody::Start()
{
  GameObject *cannonGO = new GameObject();
  cannonGO->AddComponent(
      new PenguinCannon(
          *cannonGO,
          Game::GetInstance().GetState().GetObjectPtr(&associated)));
  pcannon = Game::GetInstance().GetState().AddObject(cannonGO);
}

void PenguinBody::Update(float dt)
{
  if (InputManager::GetInstance().IsKeyDown(W_KEY))
  {
    linearSpeed += 200 * dt;
    if (linearSpeed > 600)
      linearSpeed = 600;
  }

  if (InputManager::GetInstance().IsKeyDown(S_KEY))
  {
    linearSpeed -= 200 * dt;
    if (linearSpeed < -200)
      linearSpeed = -200;
  }

  if (InputManager::GetInstance().IsKeyDown(D_KEY))
  {
    angle += 180 * dt;
    associated.angleDeg = angle;
  }

  if (InputManager::GetInstance().IsKeyDown(A_KEY))
  {
    angle -= 180 * dt;
    associated.angleDeg = angle;
  }

  speed.x = Vec2::Cos(angle) * linearSpeed;
  speed.y = Vec2::Sin(angle) * linearSpeed;
  associated.box.SetPos(associated.box.GetPos() + speed * dt);

  if (hp <= 0)
  {
    if (shared_ptr<GameObject> go = pcannon.lock())
    {
      go->RequestDelete();
    }
    associated.RequestDelete();
    Camera::Unfollow();
  }
}

void PenguinBody::Damage(int damage)
{
  hp -= damage;
  if (hp > 1)
    return;
  associated.RequestDelete();
  GameObject *penguinDeathGO = new GameObject();
  penguinDeathGO->AddComponent(new Sprite(*penguinDeathGO, "assets/img/penguindeath.png", 5, 0.15, 15.0 / 30.0));
  Sound *sound = new Sound(*penguinDeathGO, "assets/audio/boom.wav");
  sound->Play();
  penguinDeathGO->AddComponent(sound);
  penguinDeathGO->box.SetCenter(associated.box.GetCenter());
  penguinDeathGO->angleDeg = rand() % 360;
  Game::GetInstance().GetState().AddObject(penguinDeathGO);
}

void PenguinBody::Render() {}

bool PenguinBody::Is(string type)
{
  return "PenguinBody" == type;
}

void PenguinBody::NotifyCollision(GameObject &other)
{
  Bullet *bullet = static_cast<Bullet *>(other.GetComponent("Bullet"));
  if (bullet == nullptr ||
      !bullet->targetsPlayer)
    return;
  Damage(bullet->GetDamage());
}

Vec2 PenguinBody::GetPlayerCenter()
{
  return associated.box.GetCenter();
}

PenguinBody::~PenguinBody()
{
  player = nullptr;
}