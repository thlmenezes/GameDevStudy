#include <stdio.h>

using namespace std;

#include "InputManager.h"
#include "Vec2.h"

InputManager::InputManager()
    : quitRequested(false),
      updateCounter(0),
      mouseX(0),
      mouseY(0)
{
  memset(mouseState, false, sizeof(bool) * 6);
  memset(mouseUpdate, 0, sizeof(int) * 6);
}

void InputManager::Update()
{
  SDL_Event event;
  SDL_GetMouseState(&mouseX, &mouseY);
  quitRequested = false;
  updateCounter++;

  while (SDL_PollEvent(&event))
  {
    if (event.key.repeat == 1)
      continue;

    switch (event.type)
    {
    case SDL_QUIT:
      quitRequested = true;
      break;

    case SDL_MOUSEBUTTONDOWN:
      mouseState[event.button.button] = true;
      mouseUpdate[event.button.button] = updateCounter;
      break;

    case SDL_MOUSEBUTTONUP:
      mouseState[event.button.button] = false;
      mouseUpdate[event.button.button] = updateCounter;
      break;

    case SDL_KEYDOWN:
      keyState[event.key.keysym.sym] = true;
      keyUpdate[event.key.keysym.sym] = updateCounter;
      break;

    case SDL_KEYUP:
      keyState[event.key.keysym.sym] = false;
      keyUpdate[event.key.keysym.sym] = updateCounter;
      break;

    default:
      break;
    }
  }
}

bool InputManager::KeyPress(int key)
{
  return keyUpdate[key] == updateCounter ? keyState[key] : false;
}

bool InputManager::KeyRelease(int key)
{
  // TODO: could be simplified to !KeyPress() ?
  return keyUpdate[key] == updateCounter ? !keyState[key] : false;
}

bool InputManager::IsKeyDown(int key)
{
  return keyState[key];
}

bool InputManager::MousePress(int button)
{
  return mouseUpdate[button] == updateCounter ? mouseState[button] : false;
}

bool InputManager::MouseRelease(int button)
{
  return mouseUpdate[button] == updateCounter ? !mouseState[button] : false;
}

bool InputManager::IsMouseDown(int button)
{
  return mouseState[button];
}

Vec2 InputManager::GetMousePos()
{
  return Vec2(mouseX, mouseY);
}

bool InputManager::QuitRequested()
{
  return quitRequested;
}

InputManager &InputManager::GetInstance()
{
  static InputManager im;
  return im;
}

InputManager::~InputManager() {}