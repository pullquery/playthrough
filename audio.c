#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

typedef struct {
    char* name;
    double length;
    double position;
    Mix_Music* audio;
} Audio;

void initSDL(char* appHint) {
    SDL_SetHint(SDL_HINT_APP_NAME, appHint);

    if (SDL_Init(SDL_INIT_AUDIO)) {
        SDL_Log("failed to init SDL: %s\n", SDL_GetError());
        exit(-1);
    }
}

void initAudio(char* streamHint) {
    SDL_SetHint(SDL_HINT_AUDIO_DEVICE_STREAM_NAME, streamHint);

    if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        SDL_Log("failed to open audio: %s\n", Mix_GetError());
        exit(-1);
    }
}

void loadAudio(Audio* a) {
    if ((a->audio = Mix_LoadMUS(a->name)) == NULL) {
        SDL_Log("failed to load audio: %s\n", Mix_GetError());
        exit(-1);
    } else {
        a->position = Mix_GetMusicPosition(a->audio);
    }
}

void playAudio(Audio* a) {
    if (Mix_PlayMusic(a->audio, 1) < 0) {
        SDL_Log("failed to paly audio: %s\n", Mix_GetError());
        exit(-1);
    } else {
        a->length = Mix_MusicDuration(a->audio);
    }
}

void controlAudio(Audio* a) {
    while (Mix_PlayingMusic() == 1) {
        a->position = Mix_GetMusicPosition(a->audio);
        printf("%f / %f\n", a->position, a->length);
        sleep(1);
    }
}

void freeAudio(Audio* a) {
    Mix_FreeMusic(a->audio);
    Mix_CloseAudio();
}


int main(int argc, char** argv) {
    initSDL("Player");

    Audio current;
    current.name = argv[1];

    initAudio(current.name);
    loadAudio(&current);
    playAudio(&current);
    controlAudio(&current);
    freeAudio(&current);

    return 0;
}
