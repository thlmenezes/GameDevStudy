using namespace std;

#include "Sprite.h"
#include "Game.h"
#include "Component.h"
#include "Resources.h"
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "GameObject.h"

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
  SDL_Renderer *renderer = Game::GetInstance().GetRenderer();
  texture = Resources::GetImage(file);

  if (SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height))
  {
    SDL_Log("Could not query texture SDL_QueryTexture: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }

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

void Sprite::Render(float x, float y)
{
  SDL_Rect dstrect;
  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = clipRect.w;
  dstrect.h = clipRect.h;

  SDL_RenderCopy(
      Game::GetInstance().GetRenderer(),
      texture.get(),
      &clipRect,
      &dstrect);
}

void Sprite::Render()
{
  Render(associated.box.x, associated.box.y);
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
}
