#include "EndState.h"
#include "StageState.h"
#include "TitleState.h"
#include "Game.h"
#include "PenguinBody.h"
#include "GameData.h"

EndState::EndState()
{
  Camera::pos = Vec2(0, 0);
  if (GameData::playerVictory)
  {
    GameObject *go = new GameObject();
    Sprite *title = new Sprite(*go, "./assets/img/win.jpg");
    go->AddComponent(title);
    objectArray.emplace_back(go);
    go->box.x = go->box.y = 0;
    // GameObject *goText = new GameObject();
    // SDL_Color color = {0, 0, 0, 255};
    // Text *text = new Text(*goText, "./assets/font/Call me maybe.ttf", 20, Text::BLENDED, "Pressione espaco para voltar ao Menu ou ESC para sair", color, 0.5);
    // goText->AddComponent(text);
    // objectArray.emplace_back(goText);
    // goText->box.x = 300;
    // goText->box.y = 500;
    backgroundMusic = new Music("./assets/audio/endStateWin.ogg");
    backgroundMusic->Play();
  }
  else
  {
    if (PenguinBody::player == nullptr)
    {
      GameObject *go = new GameObject();
      Sprite *title = new Sprite(*go, "./assets/img/lose.jpg");
      go->box.x = go->box.y = 0;
      go->AddComponent(title);
      objectArray.emplace_back(go);
      // GameObject *goText = new GameObject();
      // SDL_Color color = {0, 0, 0, 255};
      // Text *text = new Text(*goText, "./assets/font/Call me maybe.ttf", 20, Text::BLENDED, "Pressione espaco para voltar ao Menu ou ESC para sair", color, 0.5);
      // goText->AddComponent(text);
      // objectArray.emplace_back(goText);
      // goText->box.x = 300;
      // goText->box.y = 550;
      backgroundMusic = new Music("./assets/audio/endStateLose.ogg");
      backgroundMusic->Play();
    }
  }
}

void EndState::Start() {}

void EndState::LoadAssets() {}

void EndState::Render()
{
  Camera::pos = Vec2(0, 0);
  RenderArray();
}

void EndState::Update(float dt)
{
  if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested())
    quitRequested = true;
  if (InputManager::GetInstance().KeyPress(SPACE_KEY))
  {
    popRequested = true;
    Game::GetInstance().Push(new TitleState());
  }
  UpdateArray(dt);
}

void EndState::Resume() {}

void EndState::Pause() {}

EndState::~EndState()
{
  objectArray.clear();
  backgroundMusic->Stop();
}
