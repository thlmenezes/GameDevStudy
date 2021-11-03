using namespace std;

#include "Music.h"
#include "Game.h"
#include "Resources.h"
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
  music = Resources::GetMusic(file);
}

void Music::Play(int times)
{
  if (music == nullptr)
  {
    SDL_Log("Attempt to play uninitialized music");
    exit(EXIT_FAILURE);
  }

  Mix_PlayMusic(music.get(), times);
}

void Music::Stop(int msToStop)
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
  music = nullptr;
}
