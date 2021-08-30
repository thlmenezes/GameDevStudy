#ifndef HEADER_MUSIC
#define HEADER_MUSIC
  #include <iostream>

  using namespace std;

  #define INCLUDE_SDL_MIXER
  #include "SDL_include.h"

  class Music{
    Mix_Music* music;
    public:
      Music();
      Music(string file);
      void Play(int times = -1);
      void Stop(int msToStop = 1500);
      void Open(string file);
      bool IsOpen();
      ~Music();
  };
#endif