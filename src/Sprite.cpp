#include <iostream>
#include <exception>

using namespace std;

#include "Sprite.h"
#include "Game.h"
#include "Component.h"
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "GameObject.h"

void Sprite::DestroyTexture()
{
  if (texture != nullptr)
    SDL_DestroyTexture(texture);
}

Sprite::Sprite(GameObject &associated) : Component(associated)
{
  texture = nullptr;
}

Sprite::Sprite(GameObject &associated, string file) : Sprite(associated)
{
  Open(file);
}

void Sprite::Open(string file)
{
  DestroyTexture();
  SDL_Renderer *renderer = Game::GetInstance().GetRenderer();
  texture = IMG_LoadTexture(
      renderer,
      file.c_str());

  if (texture == nullptr)
  {
    cerr << SDL_GetError();
    throw_with_nested(runtime_error("IMG_LoadTexture with file: " + file));
  }

  if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height))
    throw_with_nested(runtime_error("Invalid Texture with file: " + file));

  SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h)
{
  clipRect.x = x;
  clipRect.y = y;
  clipRect.w = w;
  clipRect.h = h;
}

void Sprite::Update(float dt)
{
}

void Sprite::Render()
{
  SDL_Renderer *renderer = Game::GetInstance().GetRenderer();
  SDL_Rect dstrect;
  dstrect.x = associated.box.x;
  dstrect.y = associated.box.y;
  dstrect.w = clipRect.w;
  dstrect.h = clipRect.h;

  SDL_RenderCopy(
      renderer,
      texture,
      &clipRect,
      &dstrect);
}

bool Sprite::Is(string type)
{
  return "Sprite" == type;
}

int Sprite::GetWidth()
{
  return width;
}

int Sprite::GetHeight()
{
  return height;
}

bool Sprite::IsOpen()
{
  return texture != nullptr;
}

Sprite::~Sprite()
{
  DestroyTexture();
}
