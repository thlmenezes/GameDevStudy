using namespace std;

#include "Sound.h"
#include "Component.h"
#include "Resources.h"
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

Sound::Sound(GameObject &associated) : Component(associated)
{
  chunk = nullptr;
}

Sound::Sound(GameObject &associated, string file) : Sound(associated)
{
  Open(file);
}

void Sound::Open(string file)
{
  chunk = Resources::GetSound(file);
}

void Sound::Play(int times)
{
  if (chunk == nullptr)
  {
    SDL_Log("Attempt to play uninitialized sound");
    exit(EXIT_FAILURE);
  }

  int channel = -1;
  int loops = times - 1;
  channel = Mix_PlayChannel(channel, chunk.get(), loops);
}

void Sound::Stop()
{
  if (chunk == nullptr)
  {
    SDL_Log("Attempt to stop uninitialized sound");
    exit(EXIT_FAILURE);
  }

  Mix_HaltChannel(channel);
}

bool Sound::IsOpen()
{
  return chunk != nullptr;
}

void Sound::Update(float dt)
{
}

void Sound::Render()
{
}

bool Sound::Is(string type)
{
  return "Sound" == type;
}

Sound::~Sound()
{
  if (IsOpen())
    Stop();
}
