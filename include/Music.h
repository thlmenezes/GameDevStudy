#ifndef MUSIC_H
  #define MUSIC_H
  using namespace std;

  #define INCLUDE_SDL_MIXER
  #include "SDL_include.h"

  class Music{
    Mix_Music* music;
    public:
      Music();
      Music(string file);
      void Open(string file);
      void Play(int times = -1);
      void Stop(int msToStop = 1500);
      bool IsOpen();
      ~Music();
  };
#endif