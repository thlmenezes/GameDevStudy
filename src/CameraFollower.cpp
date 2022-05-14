// using namespace std;

#include "CameraFollower.h"
#include "Camera.h"

CameraFollower::CameraFollower(GameObject &associated)
    : Component(associated)
{
}

void CameraFollower::Update(float dt)
{
  associated.box.x = Camera::pos.x;
  associated.box.y = Camera::pos.y;
}

void CameraFollower::Render()
{
}

bool CameraFollower::Is(string type)
{
  return "CameraFollower" == type;
}

void CameraFollower::NotifyCollision(GameObject &other) {}