#include <iostream>
#include <exception>

using namespace std;

#include "Sprite.h"
#include "Game.h"
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

void Sprite::DestroyTexture()
{
  if (texture != nullptr)
    SDL_DestroyTexture(texture);
}

Sprite::Sprite()
{
  texture = nullptr;
}

Sprite::Sprite(string file)
{
  Sprite();
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

void Sprite::Render(int x, int y)
{
  SDL_Renderer *renderer = Game::GetInstance().GetRenderer();
  SDL_Rect dstrect;
  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = clipRect.w;
  dstrect.h = clipRect.h;

  SDL_RenderCopy(
      renderer,
      texture,
      &clipRect,
      &dstrect);
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
