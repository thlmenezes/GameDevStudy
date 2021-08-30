#ifndef HEADER_GAME
#define HEADER_GAME
  #include <iostream>
  using namespace std;

  class Game {
    static Game* instance;
    Game(string title, int width, int height);
    public:
      static Game& GetInstance();
      ~Game();
  };
#endif