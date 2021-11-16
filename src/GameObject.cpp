#include <algorithm>
#include <functional>

using namespace std;

#include "GameObject.h"

GameObject::GameObject()
    : isDead(false),
      started(false),
      angleDeg(0)
{
}

void GameObject::Start()
{
  for (auto &component : components)
    component->Start();
}

void GameObject::Update(float dt)
{
  for (auto &component : components)
    component->Update(dt);
}

void GameObject::Render()
{
  for (auto &component : components)
    component->Render();
}

bool GameObject::IsDead()
{
  return isDead;
}

void GameObject::RequestDelete()
{
  isDead = true;
}

void GameObject::AddComponent(Component *cpt)
{
  components.emplace_back(cpt);
  if (started)
    cpt->Start();
}

void GameObject::RemoveComponent(Component *cpt)
{
  remove_if(
      components.begin(),
      components.end(),
      [&cpt](unique_ptr<Component> &c)
      {
        return c.get() == cpt;
      });
}

Component *GameObject::GetComponent(string type)
{
  Component *find_result = nullptr;

  for (auto &component : components)
    if (component->Is(type))
    {
      find_result = component.get();
      break;
    }

  return find_result;
}

GameObject::~GameObject()
{
  components.clear();
}
