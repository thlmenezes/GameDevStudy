#include <cmath>

using namespace std;

#include "Face.h"
#include "Sound.h"
#include "Component.h"

Face::Face(GameObject &associated) : Component(associated)
{
  hitpoints = 30;
}

void Face::Damage(int damage)
{
  hitpoints = fmax(hitpoints - abs(damage), 0);
  Sound *sound = (Sound *)associated.GetComponent("Sound");

  if (hitpoints < 1)
  {
    associated.RequestDelete();
    if (sound != nullptr)
      sound->Play();
  }
}

void Face::Update(float dt)
{
}

void Face::Render()
{
}

bool Face::Is(string type)
{
  return "Face" == type;
}
