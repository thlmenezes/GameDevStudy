#include "Camera.h"
#include "Game.h"
#include "InputManager.h"

GameObject *Camera::focus = nullptr;
Vec2 Camera::pos = Vec2();
Vec2 Camera::speed = Vec2(300, 300);

void Camera::Follow(GameObject *newFocus)
{
  focus = newFocus;
}

void Camera::Unfollow()
{
  focus = nullptr;
}

void Camera::Update(float dt)
{
  if (focus)
    return;

  if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY))
    pos.y -= speed.y * dt;

  if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY))
    pos.y += speed.y * dt;

  if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY))
    pos.x -= speed.x * dt;

  if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY))
    pos.x += speed.x * dt;
}
