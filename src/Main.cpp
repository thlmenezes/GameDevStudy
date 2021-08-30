#include "Game.h"

Game *Game::instance = nullptr;
int main(){

  Game& jogo = Game::GetInstance();

  return 0;
}