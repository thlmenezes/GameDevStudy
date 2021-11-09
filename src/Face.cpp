#include <cmath>

using namespace std;

#include "Face.h"
#include "Sound.h"
#include "Component.h"
#include "InputManager.h"
#include "Camera.h"

Face::Face(GameObject &associated)
    : Component(associated)
{
  hitpoints = 30;
}

void Face::Damage(int damage)
{
  hitpoints = fmax(hitpoints - abs(damage), 0);
  Sound *sound = (Sound *)associated.GetComponent("Sound");

  if (hitpoints < 1 && !associated.IsDead())
  {
    associated.RequestDelete();
    if (sound != nullptr)
    {
      sound->Play();
      // NOTE: GAMBIARRA
      while (Mix_Playing(-1))
      {
      }
    }
  }
}

void Face::Update(float dt)
{
  if (!InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON))
    return;

  int mouseX = InputManager::GetInstance().GetMouseX() + Camera::pos.x,
      mouseY = InputManager::GetInstance().GetMouseY() + Camera::pos.y;

  if (associated.box.Contains({(float)mouseX, (float)mouseY}))
    Damage(rand() % 10 + 10);
}

void Face::Render() {}

bool Face::Is(string type)
{
  return "Face" == type;
}
