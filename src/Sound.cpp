#include <exception>

using namespace std;

#include "Sound.h"
#include "Component.h"
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
  chunk = Mix_LoadWAV(file.c_str());
  if (chunk == nullptr)
    throw_with_nested(runtime_error("Mix_LoadWAV with file: " + file));
}

void Sound::Play(int times)
{
  if (chunk == nullptr)
    throw_with_nested(invalid_argument("Attempt to play uninitialized sound"));

  int channel = -1;
  int loops = times - 1;
  channel = Mix_PlayChannel(channel, chunk, loops);
}

void Sound::Stop()
{
  if (chunk == nullptr)
    throw_with_nested(invalid_argument("Attempt to stop uninitialized sound"));

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
  {
    Stop();
    Mix_FreeChunk(chunk);
  }
}
