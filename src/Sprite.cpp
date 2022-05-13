using namespace std;

#include "Sprite.h"
#include "Game.h"
#include "Component.h"
#include "Resources.h"
#include "Camera.h"
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "GameObject.h"

Sprite::Sprite(GameObject &associated)
    : Component(associated), texture(nullptr), scale(Vec2(1, 1))
{
}

Sprite::Sprite(GameObject &associated, string file)
    : Sprite(associated)
{
  Open(file);
}

void Sprite::Open(string file)
{
  texture = Resources::GetImage(file);

  if (SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height))
  {
    SDL_Log("Could not query texture SDL_QueryTexture: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  SetClip(0, 0, width, height);

  associated.box.w = width;
  associated.box.h = height;
}

void Sprite::SetClip(int x, int y, int w, int h)
{
  clipRect.x = x;
  clipRect.y = y;
  clipRect.w = w;
  clipRect.h = h;
}

void Sprite::SetScaleX(Vec2 scale)
{
  if (scale.x == 0)
    scale.x = this->scale.x;
  if (scale.y == 0)
    scale.y = this->scale.y;

  this->scale = scale;
  associated.box.w = GetWidth();
  associated.box.h = GetHeight();
}

void Sprite::Update(float dt) {}

void Sprite::Render(float x, float y)
{
  SDL_Rect dstrect;
  dstrect.x = x;
  dstrect.y = y;
  dstrect.w = (int)clipRect.w * scale.x;
  dstrect.h = (int)clipRect.h * scale.y;

  SDL_RenderCopyEx(
      Game::GetInstance().GetRenderer(),
      texture.get(),
      &clipRect,
      &dstrect,
      associated.angleDeg,
      nullptr,
      SDL_FLIP_NONE);
}

void Sprite::Render()
{
  Render(associated.box.x - Camera::pos.x, associated.box.y - Camera::pos.y);
}

bool Sprite::Is(string type)
{
  return "Sprite" == type;
}

int Sprite::GetWidth()
{
  return (int)width * scale.x;
}

int Sprite::GetHeight()
{
  return (int)height * scale.y;
}

Vec2 Sprite::GetScale()
{
  return scale;
}

bool Sprite::IsOpen()
{
  return texture != nullptr;
}

Sprite::~Sprite()
{
  texture = nullptr;
}
