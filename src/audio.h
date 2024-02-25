#include <SDL2/SDL_mixer.h>

typedef struct {
    char* name;
    double length;
    double position;
    Mix_Music* music;
} Audio;

void initAudio(char* hint);

void openAudio(char* hint);

void loadMusic(Audio* a);

void playMusic(Audio* a);

void freeMusic(Audio* a);

void freeAudio(Audio* a);