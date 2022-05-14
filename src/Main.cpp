#include "Game.h"
#include "TitleState.h"

Game *Game::instance = nullptr;
int main(int argc, char **argv)
{
  Game &jogo = Game::GetInstance();
  State *newState = new TitleState();
  jogo.Push(newState);
  jogo.Run();

  return 0;
}