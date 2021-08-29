#include "Game.h"

Game::Game(){
  return;
}

Game& Game::GetInstance(){
  if (instance != nullptr) instance = new Game;
  return *instance;
}

Game::~Game(){
}
