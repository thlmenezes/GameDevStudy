#include <iostream>
#include <exception>

using namespace std;

#include "Game.h"
#include "State.h"
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

Game::Game(string title, int width, int height)
{
  if (instance != nullptr)
    throw_with_nested(runtime_error("Singleton Error"));
  instance = this;

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
    throw_with_nested(runtime_error(SDL_GetError()));

  const int sdl_image = IMG_Init(IMG_INIT_JPG);
  if (0 == sdl_image)
  {
    cerr << sdl_image;
    throw_with_nested(runtime_error("SDL Image Init"));
  }

  const int sdl_mix = Mix_Init(MIX_INIT_OGG);
  if (0 == sdl_mix)
  {
    cerr << sdl_mix;
    throw_with_nested(runtime_error("MIX Audio Init"));
  }

  const int CHUNK_SIZE = 1024;
  if (
      Mix_OpenAudio(
          MIX_DEFAULT_FREQUENCY,
          MIX_DEFAULT_FORMAT,
          MIX_DEFAULT_CHANNELS,
          CHUNK_SIZE))
    throw_with_nested(runtime_error("MIX Open Audio"));

  const int NUM_CHANNELS = 32;
  Mix_AllocateChannels(NUM_CHANNELS);

  const Uint32 WINDOW_FLAGS = 0;
  window = SDL_CreateWindow(
      title.c_str(),
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      width,
      height,
      WINDOW_FLAGS);

  if (window == nullptr)
    throw_with_nested(runtime_error("SDL Create Window"));

  const int RENDERER_INDEX = -1;
  renderer = SDL_CreateRenderer(
      window,
      RENDERER_INDEX,
      SDL_RENDERER_ACCELERATED);

  if (renderer == nullptr)
    throw_with_nested(runtime_error("SDL Create Renderer"));

  // TODO: state = new State();

  return;
}

Game &Game::GetInstance()
{
  const string TITLE = "Thales Lima Menezes - 170045919";
  const int WIDTH = 1024;
  const int HEIGHT = 600;

  if (instance == nullptr)
    instance = new Game(TITLE, WIDTH, HEIGHT);

  return *instance;
}

Game::~Game()
{
}
