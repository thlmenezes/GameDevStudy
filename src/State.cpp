#include <iostream>
#include <exception>
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
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#define PI 3.14159265358979323846
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 600

State::State() : bg(*new GameObject(), "assets/img/ocean.jpg")
{
  quitRequested = false;
  music = *new Music();
  LoadAssets();
}

void State::LoadAssets()
{
  GameObject *associated = new GameObject();
  associated->AddComponent(&bg);

  associated->box.x = 0;
  associated->box.y = 0;
  associated->box.w = bg.GetWidth();
  associated->box.h = bg.GetHeight();

  objectArray.emplace_back(associated);
  music.Open("assets/audio/stageState.ogg");
  music.Play();
}

void State::Update(float dt)
{
  Input();

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

void State::Input()
{
  SDL_Event event;
  int mouseX, mouseY;

  // Obtenha as coordenadas do mouse
  SDL_GetMouseState(&mouseX, &mouseY);

  // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
  while (SDL_PollEvent(&event))
  {

    // Se o evento for quit, setar a flag para terminação
    if (event.type == SDL_QUIT)
    {
      quitRequested = true;
    }

    // Se o evento for clique...
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {

      // Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
      for (int i = objectArray.size() - 1; i >= 0; --i)
      {
        // Obtem o ponteiro e casta pra Face.
        GameObject *go = (GameObject *)objectArray[i].get();
        // Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
        // O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
        // ao usar get(), violamos esse princípio e estamos menos seguros.
        // Esse código, assim como a classe Face, é provisório. Futuramente, para
        // chamar funções de GameObjects, use objectArray[i]->função() direto.

        if (go->box.Contains({(float)mouseX, (float)mouseY}))
        {
          Face *face = (Face *)go->GetComponent("Face");
          if (nullptr != face)
          {
            // Aplica dano
            face->Damage(std::rand() % 10 + 10);
            // Sai do loop (só queremos acertar um)
            break;
          }
        }
      }
    }
    if (event.type == SDL_KEYDOWN)
    {
      // Se a tecla for ESC, setar a flag de quit
      if (event.key.keysym.sym == SDLK_ESCAPE)
      {
        quitRequested = true;
      }
      // Se não, crie um objeto
      else
      {
        Vec2 objPos = Vec2(200, 0).GetRotated(-PI + PI * (rand() % 1001) / 500.0) + Vec2(mouseX, mouseY);
        AddObject((int)objPos.x, (int)objPos.y);
      }
    }
  }
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