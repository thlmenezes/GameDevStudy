#ifndef GAME_H
  #define GAME_H
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

    int frameStart;
    float dt;
    void CalculateDeltaTime();

    Game(string title, int width, int height);
    public:
      static Game& GetInstance();
      void Run();
      SDL_Renderer* GetRenderer();
      State& GetState();
      float GetDeltaTime();
      ~Game();
  };
#endif