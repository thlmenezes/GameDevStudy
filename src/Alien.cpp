using namespace std;

#include "Alien.h"
#include "Game.h"
#include "Sound.h"
#include "Sprite.h"

Alien::Alien(GameObject &associated, int nMinions)
    : Component(associated), speed(Vec2()), hp(10)
{
  associated.AddComponent(new Sprite(associated, "assets/img/alien.png"));
}

void Alien::Start() {}

void Alien::Update(float dt)
{
  // TODO: page 4/11 PDF
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