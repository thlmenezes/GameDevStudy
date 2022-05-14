using namespace std;

#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject &associated)
    : associated(associated)
{
}

void Component::NotifyCollision(GameObject &other) {}

Component::~Component() {}