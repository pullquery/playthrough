#include <SDL2/SDL_mixer.h>

typedef struct {
    char* name;
    double length;
    double position;
    Mix_Music* audio;
} Audio;

void initSDL(char* hint);

void initAudio(char* hint);

void loadAudio(Audio* a);

void playAudio(Audio* a);

void controlAudio(Audio* a);

void freeAudio(Audio* a);