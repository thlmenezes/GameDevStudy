#ifndef GAME_H
  #define GAME_H
  #include <stack>
  
  using namespace std;

  #define INCLUDE_SDL_IMAGE
  #define INCLUDE_SDL_MIXER
  #include "SDL_include.h"
  #include "State.h"
  // #include "StageState.h"
  // #include "TitleState.h"

  class Game {
    static Game* instance;
    SDL_Window* window;
    SDL_Renderer* renderer;
    State* storedState;
    stack<unique_ptr<State>> stateStack;

    int frameStart;
    float dt;
    void CalculateDeltaTime();

    Game(string title, int width, int height);
    public:
      static Game& GetInstance();
      void Run();
      SDL_Renderer* GetRenderer();
      State& GetCurrentState();
      void Push(State *state);
      float GetDeltaTime();
      ~Game();
  };
#endif