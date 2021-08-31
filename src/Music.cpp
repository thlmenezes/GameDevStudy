#include <iostream>
#include <exception>

using namespace std;

#include "Music.h"
#include "Game.h"
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

Music::Music()
{
  music = nullptr;
}

Music::Music(string file)
{
  Music();
  Open(file);
}

void Music::Open(string file)
{
  music = Mix_LoadMUS(file.c_str());
  if (music == nullptr)
    throw_with_nested(runtime_error("Mix_LoadMUS with file: " + file));
}

void Music::Play(int times = -1)
{
  if (music == nullptr)
    throw_with_nested(invalid_argument("Attempt to play uninitialized music"));

  Mix_PlayMusic(music, times);
}

void Music::Stop(int msToStop = 1500)
{
  Mix_FadeOutMusic(msToStop);
}

bool Music::IsOpen()
{
  return music != nullptr;
}

Music::~Music()
{
  Stop(0);
  Mix_FreeMusic(music);
}
