#ifndef HEADER_GAME
#define HEADER_GAME
  #include <iostream>

  using namespace std;

  #define INCLUDE_SDL_IMAGE
  #define INCLUDE_SDL_MIXER
  #include "SDL_include.h"
  #include "State.h"

  class Game {
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* state;

    Game(string title, int width, int height);
    public:
      static Game& GetInstance();
      ~Game();
  };
#endif