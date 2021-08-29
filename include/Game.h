#ifndef HEADER_GAME
#define HEADER_GAME
  class Game {
    static Game* instance;
    Game();
    public:
      static Game& GetInstance();
      ~Game();
  };
#endif