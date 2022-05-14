using namespace std;

#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Minion.h"
#include "Game.h"
#include "Bullet.h"
#include "Sound.h"

#define loop(x, n) for (unsigned int x = 0; x < (unsigned int)n; ++x)

Alien::Alien(GameObject &associated, int nMinions)
    : Component(associated),
      hp(10),
      speed(Vec2()),
      nMinions(nMinions)
{
  associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));
}

void Alien::Start()
{
  loop(i, nMinions)
  {
    GameObject *minion = new GameObject();
    minion->AddComponent(new Minion(
        *minion,
        associated,
        i * (360 / nMinions)));
    minionArray.push_back(
        Game::GetInstance().GetState().AddObject(minion));
  }
}

void Alien::Update(float dt)
{
  Alien::associated.angleDeg -= 60 * dt;

  auto clickX = InputManager::GetInstance().GetMousePos().x + Camera::pos.x,
       clickY = InputManager::GetInstance().GetMousePos().y + Camera::pos.y;

  if (InputManager::GetInstance().IsMouseDown(LEFT_MOUSE_BUTTON))
    taskQueue.push(Action(Action::SHOOT, clickX, clickY));

  if (InputManager::GetInstance().IsMouseDown(RIGHT_MOUSE_BUTTON))
    taskQueue.push(Action(Action::MOVE, clickX, clickY));

  if (hp < 1)
    associated.RequestDelete();

  if (!taskQueue.size())
    return;

  auto act = taskQueue.front();
  auto curr = associated.box.GetCenter();
  auto dest = act.pos;

  if (act.type == act.SHOOT)
  {
    if (minionArray.empty())
      return;

    ((Minion *)(minionArray[rand() % nMinions]
                    .lock()
                    ->GetComponent("Minion")))
        ->Shoot(dest);

    taskQueue.pop();
    return;
  }

  float sin = curr.GetSin(dest);
  if (sin != sin)
    sin = 0;

  float cos = curr.GetCos(dest);
  if (cos != cos)
    cos = 0;

  Alien::speed = Vec2(500 * cos, 500 * sin);

  if ((curr.x < dest.x && curr.x + speed.x * dt > dest.x) ||
      (curr.x > dest.x && curr.x + speed.x * dt < dest.x))
    curr.x = dest.x;
  else
    curr.x += speed.x * dt;

  if ((curr.y < dest.y && curr.y + speed.y * dt > dest.y) ||
      (curr.y > dest.y && curr.y + speed.y * dt < dest.y))
    curr.y = dest.y;
  else
    curr.y += speed.y * dt;

  associated.box.SetCenter(curr);

  if (curr == dest)
    taskQueue.pop();
}

void Alien::Damage(int damage)
{
  hp -= damage;
  if (hp > 1)
    return;

  associated.RequestDelete();
  GameObject *alienDeathGO = new GameObject();
  alienDeathGO->AddComponent(new Sprite(*alienDeathGO, "assets/img/aliendeath.png", 4, 0.15));
  Sound *sound = new Sound(*alienDeathGO, "assets/audio/boom.wav");
  sound->Play();
  alienDeathGO->AddComponent(sound);
  alienDeathGO->box.SetCenter(Alien::associated.box.GetCenter());
  alienDeathGO->angleDeg = rand() % 360;
  Game::GetInstance().GetState().AddObject(alienDeathGO);
}

void Alien::Render() {}

bool Alien::Is(string type)
{
  return "Alien" == type;
}

void Alien::NotifyCollision(GameObject &other)
{
  Bullet *bullet = static_cast<Bullet *>(other.GetComponent("Bullet"));
  if (bullet == nullptr ||
      bullet->targetsPlayer)
    return;
  Damage(bullet->GetDamage());
}

Alien::~Alien()
{
  minionArray.clear();
}