#include <iostream>
#include <exception>

using namespace std;

#include "State.h"
#include "Sprite.h"
#include "Music.h"
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

State::State()
{
  quitRequested = false;
  bg = Sprite();
  music = Music();
}

void State::LoadAssets()
{
  bg.Open("assets/img/ocean.jpg");
  music.Open("assets/audio/stageState.ogg");
}

void State::Update(float dt)
{
  quitRequested = SDL_QuitRequested() == SDL_TRUE;
}

void State::Render()
{
  bg.Render(0, 0);
}

bool State::QuitRequested()
{
  return quitRequested;
}