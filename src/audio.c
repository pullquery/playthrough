#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "audio.h"

void initAudio(char* hint) {
    SDL_SetHint(SDL_HINT_APP_NAME, hint);

    if (SDL_Init(SDL_INIT_AUDIO)) {
        SDL_Log("failed to init SDL: %s\n", SDL_GetError());
    }
}

void openAudio(char* hint) {
    SDL_SetHint(SDL_HINT_AUDIO_DEVICE_STREAM_NAME, hint);

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) < 0) {
        SDL_Log("failed to open audio: %s\n", Mix_GetError());
    }
}

void loadMusic(Audio* a) {
    a->music = Mix_LoadMUS(a->name);

    if (a->music == NULL) {
        SDL_Log("failed to load audio: %s\n", Mix_GetError());
    }

    a->length = Mix_MusicDuration(a->music);
    a->position = Mix_GetMusicPosition(a->music);
}

void sample(void *udata, Uint8 *stream, int len) {
    Audio* a = udata;
    a->length = Mix_MusicDuration(a->music);
    a->position = Mix_GetMusicPosition(a->music);

    printf("%f / %f / %s\r", a->position, a->length, a->name);
    fflush(stdout);
}

void playMusic(Audio* a) {
    if (Mix_PlayMusic(a->music, 1) < 0) {
        SDL_Log("failed to paly audio: %s\n", Mix_GetError());
    }

    Mix_SetPostMix(sample, a);
}

void freeMusic(Audio* a) {
    Mix_FreeMusic(a->music);
}

void freeAudio(Audio* a) {
    Mix_CloseAudio();
}
