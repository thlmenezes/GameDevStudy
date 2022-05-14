using namespace std;

#include "Alien.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Camera.h"
#include "Minion.h"
#include "Game.h"
#include "Bullet.h"
#include "Sound.h"
#include "Collider.h"
#include "PenguinBody.h"

#define loop(x, n) for (unsigned int x = 0; x < (unsigned int)n; ++x)

int Alien::alienCount = 0;

Alien::Alien(GameObject &associated, int nMinions)
    : Component(associated),
      hp(100),
      speed(Vec2()),
      nMinions(nMinions),
      state(RESTING),
      restTimer(Timer()),
      restTime(1 + (rand() % 11) / 10)
{
  associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));
  associated.AddComponent(new Collider(associated));
  alienCount++;
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
  associated.angleDeg -= 60 * dt;

  if (!PenguinBody::player)
    return;

  if (state == RESTING)
  {
    restTimer.Update(dt);

    if (restTimer.Get() < restTime)
      return;

    state = MOVING;
    restTimer.Restart();
    restTime = 1 + (rand() % 11) / 10;
    destination = PenguinBody::player->GetPlayerCenter();
    return;
  }

  Vec2 curr = associated.box.GetCenter();
  Vec2 dest = destination;

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

  if (curr != dest)
    return;

  state = RESTING;
  destination = PenguinBody::player->GetPlayerCenter();

  if (minionArray.empty())
    return;

  int nearestMinion = 0;
  float minionDS = minionArray[0].lock()->box.GetCenter().GetDS(destination);
  for (unsigned int i = 1; i < minionArray.size(); i++)
  {
    if (minionArray[i].lock()->box.GetCenter().GetDS(destination) < minionDS)
    {
      nearestMinion = i;
      minionDS = minionArray[i].lock()->box.GetCenter().GetDS(destination);
    }
  }
  Minion *minion = static_cast<Minion *>(minionArray[nearestMinion].lock()->GetComponent("Minion"));
  minion->Shoot(destination);
}

void Alien::Damage(int damage)
{
  hp -= damage;
  if (hp > 1)
    return;

  associated.RequestDelete();
  GameObject *alienDeathGO = new GameObject();
  alienDeathGO->AddComponent(new Sprite(*alienDeathGO, "assets/img/aliendeath.png", 4, 0.15, 12.0 / 30.0));
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
  alienCount--;
}