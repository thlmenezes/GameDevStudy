#include <cmath>

using namespace std;

#include "State.h"
#include "Sprite.h"
#include "Face.h"
#include "Vec2.h"
#include "GameObject.h"
#include "Game.h"
#include "Sound.h"
#include "Music.h"
#include "TileSet.h"
#include "TileMap.h"
#include "InputManager.h"
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#define PI 3.14159265358979323846
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 600

State::State()
    : music("assets/audio/stageState.ogg")
{
  quitRequested = false;
  music.Play(-1);
  LoadAssets();
}

void State::LoadAssets()
{
  auto background = new GameObject();
  bg = new Sprite(*background, "assets/img/ocean.jpg");
  background->AddComponent(bg);
  objectArray.emplace_back(background);

  auto tilemap = new GameObject();
  auto scenario = new TileMap(
      *tilemap,
      "assets/map/tileMap.txt",
      new TileSet(64, 64, "assets/img/tileset.png"));

  tilemap->AddComponent(scenario);
  objectArray.emplace_back(tilemap);
}

void State::Update(float dt)
{
  quitRequested = InputManager::GetInstance().QuitRequested() ||
                  InputManager::GetInstance().KeyPress(ESCAPE_KEY);

  if (InputManager::GetInstance().KeyPress(SPACE_KEY))
  {
    int mouseX = InputManager::GetInstance().GetMouseX(),
        mouseY = InputManager::GetInstance().GetMouseY();

    Vec2 objPos = Vec2(200, 0).GetRotated(-PI + PI * (rand() % 1001) / 500.0) + Vec2(mouseX, mouseY);
    AddObject((int)objPos.x, (int)objPos.y);
  }

  for (auto it = objectArray.begin(); it < objectArray.end(); it++)
  {
    auto object = it->get();
    object->Update(dt);
    if (object->IsDead())
      objectArray.erase(it, it + 1);
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

void State::AddObject(int mouseX, int mouseY)
{
  GameObject *enemy = new GameObject();
  Sprite *enemySprite = new Sprite(*enemy, "assets/img/penguinface.png");
  enemy->AddComponent(enemySprite);

  int spriteWidth = enemySprite->GetWidth();
  int spriteHeight = enemySprite->GetHeight();
  int spriteHalfWidth = (int)rint(spriteWidth / 2);
  int spriteHalfHeight = (int)rint(spriteHeight / 2);

  // TODO: no method to getWindow yet
  // int screenWidth, screenHeight;
  // SDL_GetWindowSize(Game::GetInstance().GetWindow(), &screenWidth, &screenHeight);
  /* 
    0,0 -------------- SW,0
    |                   |
    |                   |
    |                   |
    0,SH -------------- SW,SH
  */

  enemy->box.x = (int)fmin(SCREEN_WIDTH - spriteWidth, fmax(mouseX - spriteHalfWidth, 0));
  enemy->box.y = (int)fmin(SCREEN_HEIGHT - spriteHeight, fmax(mouseY - spriteHalfHeight, 0));
  enemy->box.w = spriteWidth;
  enemy->box.h = spriteHeight;

  enemy->AddComponent(new Sound(*enemy, "assets/audio/boom.wav"));
  enemy->AddComponent(new Face(*enemy));

  objectArray.emplace_back(enemy);
}