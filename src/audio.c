#include <SDL2/SDL_audio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "audio.h"

void initSDL(char* hint) {
    SDL_SetHint(SDL_HINT_APP_NAME, hint);

    if (SDL_Init(SDL_INIT_AUDIO)) {
        SDL_Log("failed to init SDL: %s\n", SDL_GetError());
    }
}

void initAudio(char* hint) {
    SDL_SetHint(SDL_HINT_AUDIO_DEVICE_STREAM_NAME, hint);

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) < 0) {
        SDL_Log("failed to open audio: %s\n", Mix_GetError());
    }
}

void loadAudio(Audio* a) {
    a->audio = Mix_LoadMUS(a->name);

    if (a->audio == NULL) {
        SDL_Log("failed to load audio: %s\n", Mix_GetError());
    }

    a->length = Mix_MusicDuration(a->audio);
    a->position = Mix_GetMusicPosition(a->audio);
}

void playAudio(Audio* a) {
    if (Mix_PlayMusic(a->audio, 1) < 0) {
        SDL_Log("failed to paly audio: %s\n", Mix_GetError());
    }
}

void controlAudio(Audio* a) {
    while (Mix_PlayingMusic()) {
        a->position = Mix_GetMusicPosition(a->audio);

        printf("\x1b[1F");
        printf("\x1b[2K");
        printf("%f / %f\n", a->position, a->length);

        sleep(1);
    }
}

void freeAudio(Audio* a) {
    Mix_FreeMusic(a->audio);
    Mix_CloseAudio();
}
