#include <cmath>

using namespace std;

#include "StageState.h"
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
#include "PenguinBody.h"
#include "Collider.h"
#include "Collision.cpp"
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 600

#define loop(x, n) for (long unsigned int x = 0; x < n; ++x)

#define loopS(x, n, s) for (long unsigned int x = s; x < n; ++x)

StageState::StageState()
    : State(),
      backgroundMusic("assets/audio/stageState.ogg")
{
}

void StageState::LoadAssets()
{
  auto backgroundGO = new GameObject();
  backgroundGO->AddComponent(new Sprite(*backgroundGO, "assets/img/ocean.jpg"));
  backgroundGO->AddComponent(new CameraFollower(*backgroundGO));
  AddObject(backgroundGO);

  auto tilemapGO = new GameObject();
  auto tilemap = new TileMap(
      *tilemapGO,
      "assets/map/tileMap.txt",
      new TileSet(64, 64, "assets/img/tileset.png"));
  tilemapGO->AddComponent(tilemap);
  AddObject(tilemapGO);

  loop(i, 3)
  {
    auto alienGO = new GameObject();
    alienGO->AddComponentAsFirst(new Alien(*alienGO, 3));
    alienGO->box.SetCenter(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
    AddObject(alienGO);
  }

  auto PenguinGo = new GameObject();
  auto penguin = new PenguinBody(*PenguinGo);
  PenguinGo->box.SetCenter(704, 640);
  PenguinGo->AddComponent(penguin);
  AddObject(PenguinGo);

  Camera::Follow(PenguinGo);

  backgroundMusic.Play();
}

void StageState::Start()
{
  LoadAssets();
  StartArray();
  started = true;
}

void StageState::Pause()
{
  loop(i, objectArray.size())
  {
    Sound *sound = static_cast<Sound *>(StageState::objectArray[i]->GetComponent("Sound"));
    if (sound)
      sound->Stop();
  }
}

void StageState::Resume()
{
  backgroundMusic.Play();
}

void StageState::CollisionCheck()
{
  loop(i, objectArray.size())
  {
    Collider *colliderI = (Collider *)objectArray[i]->GetComponent("Collider");
    if (colliderI == nullptr)
      continue;
    loopS(j, objectArray.size(), i + 1)
    {
      Collider *colliderJ = (Collider *)objectArray[j]->GetComponent("Collider");
      if (colliderJ == nullptr)
        continue;

      if (colliderI->IsColliding(*colliderJ))
      {
        objectArray[i]->NotifyCollision(*objectArray[j]);
        objectArray[j]->NotifyCollision(*objectArray[i]);
      }
    }
  }
}

void StageState::DeletionCheck()
{
  loop(i, objectArray.size())
  {
    auto object = objectArray[i];
    if (object->IsDead())
    {
      if (Camera::GetFocus() == object.get())
        Camera::Unfollow();
      objectArray.erase(objectArray.begin() + i);
    }
  }
}

void StageState::Update(float dt)
{
  quitRequested = InputManager::GetInstance().QuitRequested();
  if (InputManager::GetInstance().KeyPress(ESCAPE_KEY))
    popRequested = true;

  UpdateArray(dt);
  CollisionCheck();
  DeletionCheck();

  if (!PenguinBody::player)
  {
    // GameData::playerVictory = false;
    // Game::GetInstance().Push(new EndState());
  }
  else if (Alien::alienCount < 1)
  {
    // GameData::playerVictory = true;
    // Game::GetInstance().Push(new EndState());
  }
}

void StageState::Render()
{
  RenderArray();
}

StageState::~StageState()
{
  delete StageState::tileSet;
}