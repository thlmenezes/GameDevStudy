#ifndef SOUND_H
  #define SOUND_H
  #include <memory>
  using namespace std;

  #define INCLUDE_SDL_MIXER
  #include "SDL_include.h"
  #include "GameObject.h"
  #include "Component.h"
  
  class Sound: public Component{
    shared_ptr<Mix_Chunk> chunk;
    int channel;

    public:
      Sound(GameObject& associated);
      Sound(GameObject& associated, string file);

      void Open(string file);
      void Play(int times = 1);
      void Stop();
      bool IsOpen();
      void Update(float dt);
      void Render();
      bool Is(string type);
      void NotifyCollision(GameObject& other);

      ~Sound();
  };
#endif