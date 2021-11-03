#include "Resources.h"
#include "Game.h"

unordered_map<string, shared_ptr<SDL_Texture>> Resources::imageTable;
unordered_map<string, shared_ptr<Mix_Music>> Resources::musicTable;
unordered_map<string, shared_ptr<Mix_Chunk>> Resources::soundTable;

shared_ptr<SDL_Texture> Resources::GetImage(string file)
{
  if (!imageTable.count(file))
  {
    SDL_Texture *texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    imageTable.emplace(file, shared_ptr<SDL_Texture>(texture, [](SDL_Texture *p)
                                                     { SDL_DestroyTexture(p); }));
  }
  if (!imageTable.at(file))
  {
    SDL_Log("Unable to load texture: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  return imageTable.at(file);
}

void Resources::ClearImages()
{
  imageTable.clear();
}

shared_ptr<Mix_Music> Resources::GetMusic(string file)
{
  if (!musicTable.count(file))
  {
    Mix_Music *music = Mix_LoadMUS(file.c_str());
    musicTable.emplace(file, shared_ptr<Mix_Music>(music, [](Mix_Music *p)
                                                   { Mix_FreeMusic(p); }));
  }
  if (musicTable.at(file) == nullptr)
  {
    SDL_Log("Unable to load music: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  return musicTable.at(file);
}

void Resources::ClearMusics()
{
  musicTable.clear();
}

shared_ptr<Mix_Chunk> Resources::GetSound(string file)
{
  if (!soundTable.count(file))
  {
    Mix_Chunk *chunk = Mix_LoadWAV(file.c_str());
    soundTable.emplace(file, shared_ptr<Mix_Chunk>(chunk, [](Mix_Chunk *p)
                                                   { Mix_FreeChunk(p); }));
  }
  if (soundTable.at(file) == nullptr)
  {
    SDL_Log("Unable to load sound: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  return soundTable.at(file);
}

void Resources::ClearSounds()
{
  soundTable.clear();
}