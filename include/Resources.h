#ifndef RESOURCES_H
  #define RESOURCES_H
  #include <memory>
  #include <string>
  #include <unordered_map>

  using namespace std;

  #define INCLUDE_SDL_IMAGE
  #define INCLUDE_SDL_MIXER
  #define INCLUDE_SDL_TTF
  #include "SDL_include.h"

  class Resources {
    private:
      static unordered_map<string, shared_ptr<SDL_Texture>> imageTable;
      static unordered_map<string, shared_ptr<Mix_Music>> musicTable;
      static unordered_map<string, shared_ptr<Mix_Chunk>> soundTable;
    public:
      static shared_ptr<SDL_Texture> GetImage(string file);
      static void ClearImages();
      static shared_ptr<Mix_Music> GetMusic(string file);
      static void ClearMusics();
      static shared_ptr<Mix_Chunk> GetSound(string file);
      static void ClearSounds();
  };
#endif
