using namespace std;

#include "Game.h"
#include "State.h"
#include "InputManager.h"
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

Game::Game(string title, int width, int height)
    : frameStart(0), dt(0), storedState(nullptr)
{
  if (instance != nullptr)
  {
    SDL_Log("Singleton Error");
    exit(EXIT_FAILURE);
  }

  instance = this;

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
  {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  const int sdl_image = IMG_Init(IMG_INIT_JPG);
  if (0 == sdl_image)
  {
    SDL_Log("Unable to initialize SDL_Image: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  const int sdl_mix = Mix_Init(MIX_INIT_OGG);
  if (0 == sdl_mix)
  {
    SDL_Log("Unable to initialize SDL_Mix: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  const int CHUNK_SIZE = 1024;
  if (
      Mix_OpenAudio(
          MIX_DEFAULT_FREQUENCY,
          MIX_DEFAULT_FORMAT,
          MIX_DEFAULT_CHANNELS,
          CHUNK_SIZE))
  {
    SDL_Log("Unable to open audio channel Mix_OpenAudio: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }

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
  {
    SDL_Log("Unable to create window SDL_CreateWindow: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  const int RENDERER_INDEX = -1;
  renderer = SDL_CreateRenderer(
      window,
      RENDERER_INDEX,
      SDL_RENDERER_ACCELERATED);

  if (renderer == nullptr)
  {
    SDL_Log("Unable to create renderer SDL_CreateRenderer: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }
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

void Game::Run()
{
  if (storedState)
  {
    stateStack.emplace(storedState);
    stateStack.top()->Start();
    storedState = nullptr;
  }

  if (stateStack.empty())
    return;

  while (!stateStack.top()->QuitRequested())
  {
    while (!(storedState) &&
           !(stateStack.top()->PopRequested()) &&
           !(stateStack.top()->QuitRequested()))
    {
      if (SDL_RenderClear(renderer))
        SDL_Log("Unable to clear renderer: %s", SDL_GetError());
      CalculateDeltaTime();
      Camera::Update(GetDeltaTime());
      InputManager::GetInstance().Update();
      stateStack.top()->Update(GetDeltaTime());
      stateStack.top()->Render();
      SDL_RenderPresent(renderer);
      SDL_Delay(16); // 30 FPS == 33MS delay
    }

    if (storedState)
    {
      stateStack.top()->Pause();
      stateStack.emplace(storedState);
      stateStack.top()->Start();
      storedState = nullptr;
    }
    else if (stateStack.top()->PopRequested())
    {
      stateStack.pop();
      if (!stateStack.empty())
        stateStack.top()->Resume();
    }
  }
}

SDL_Renderer *Game::GetRenderer()
{
  return renderer;
}

State &Game::GetCurrentState()
{
  return *stateStack.top().get();
}

void Game::Push(State *state)
{
  Game::storedState = state;
}

void Game::CalculateDeltaTime()
{
  dt = SDL_GetTicks() - frameStart;
  frameStart += dt;
}

float Game::GetDeltaTime()
{
  return dt / 1000;
}

Game::~Game()
{
  if (storedState != nullptr)
    delete (storedState);
  while (!stateStack.empty())
    stateStack.pop();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  Mix_CloseAudio();
  Mix_Quit();
  IMG_Quit();
  SDL_Quit();
}
