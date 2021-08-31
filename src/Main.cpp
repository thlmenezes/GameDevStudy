#include "Game.h"

Game *Game::instance = nullptr;
int main(int argc, char **argv)
{
  Game &jogo = Game::GetInstance();

  // TODO: run game

  return 0;
}