#include <cmath>

using namespace std;

#include "State.h"
#include "Sprite.h"
#include "Vec2.h"
#include "GameObject.h"
#include "Game.h"
#include "Sound.h"
#include "Music.h"
#include "TileSet.h"
#include "TileMap.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#define PI 3.14159265358979323846
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 600

#define loop(x, n) for (long unsigned int x = 0; x < n; ++x)

State::State()
    : quitRequested(false),
      music("assets/audio/stageState.ogg"),
      started(false)
{
}

void State::LoadAssets()
{
  music.Play(-1);
  auto background = new GameObject();
  bg = new Sprite(*background, "assets/img/ocean.jpg");
  background->AddComponent(bg);
  background->AddComponent(new CameraFollower(*background));
  objectArray.emplace_back(background);

  auto tilemap = new GameObject();
  auto scenario = new TileMap(
      *tilemap,
      "assets/map/tileMap.txt",
      new TileSet(64, 64, "assets/img/tileset.png"));

  tilemap->AddComponent(scenario);
  objectArray.emplace_back(tilemap);

  auto alien = new GameObject();
  auto et = new Alien(*alien, 3);
  alien->box.SetCenter(512, 300);
  alien->AddComponent(et);
  objectArray.emplace_back(alien);
}

void State::Start()
{
  LoadAssets();

  loop(i, objectArray.size())
  {
    auto object = objectArray[i];
    object->Start();
  }

  started = true;
}

weak_ptr<GameObject> State::AddObject(GameObject *go)
{
  shared_ptr<GameObject> shared = shared_ptr<GameObject>(go);
  State::objectArray.push_back(shared);
  if (State::started)
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

void State::Update(float dt)
{
  quitRequested = InputManager::GetInstance().QuitRequested() ||
                  InputManager::GetInstance().KeyPress(ESCAPE_KEY);

  Camera::Update(dt);

  loop(i, objectArray.size())
  {
    auto object = objectArray[i];
    object->Update(dt);
    if (object->IsDead())
      objectArray.erase(objectArray.begin() + i);
  }
}

void State::Render()
{
  for (auto &object : objectArray)
  {
    object->Render();
  }
}

bool State::QuitRequested()
{
  return quitRequested;
}

State::~State()
{
  objectArray.clear();
}