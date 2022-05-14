#include "State.h"

#define loop(x, n) for (long unsigned int x = 0; x < n; ++x)

State::State()
    : quitRequested(false),
      started(false),
      popRequested(false)
{
}

void State::LoadAssets() {}

void State::StartArray()
{
  loop(i, objectArray.size())
  {
    objectArray[i]->Start();
  }
}

void State::UpdateArray(float dt)
{
  loop(i, objectArray.size())
  {
    objectArray[i]->Update(dt);
  }
}

void State::RenderArray()
{
  loop(i, objectArray.size())
  {
    objectArray[i]->Render();
  }
}

weak_ptr<GameObject> State::AddObject(GameObject *go)
{
  shared_ptr<GameObject> shared = shared_ptr<GameObject>(go);
  objectArray.push_back(shared);
  if (started)
    shared->Start();
  return shared;
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject *go)
{
  for (auto it = objectArray.begin(); it < objectArray.end(); it++)
    if (it->get() == go)
      return *it;
  return weak_ptr<GameObject>();
}

bool State::QuitRequested()
{
  return quitRequested;
}

bool State::PopRequested()
{
  return popRequested;
}

State::~State()
{
  objectArray.clear();
}