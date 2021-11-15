using namespace std;

#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"

Alien::Alien(GameObject &associated, int nMinions)
    : Component(associated), speed(Vec2()), hp(10)
{
  associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));
}

void Alien::Start() {}

void Alien::Update(float dt)
{
  auto clickX = InputManager::GetInstance().GetMouseX() + Camera::pos.x,
       clickY = InputManager::GetInstance().GetMouseY() + Camera::pos.y;

  if (InputManager::GetInstance().IsMouseDown(LEFT_MOUSE_BUTTON))
    taskQueue.push(Action(Action::SHOOT, clickX, clickY));

  if (InputManager::GetInstance().IsMouseDown(RIGHT_MOUSE_BUTTON))
    taskQueue.push(Action(Action::MOVE, clickX, clickY));

  if (hp < 1)
    associated.RequestDelete();

  if (!taskQueue.size())
    return;

  auto act = taskQueue.front();

  if (act.type == act.SHOOT)
  {
    taskQueue.pop();
    return;
  }

  auto curr = associated.box.GetCenter();
  auto dest = act.pos;

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

void Alien::Render() {}

bool Alien::Is(string type)
{
  return "Alien" == type;
}

Alien::~Alien()
{
  minionArray.clear();
}