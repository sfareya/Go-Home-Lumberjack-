/* Eya Sfar, Amal Bouakez, Sarra Ben Rejeb
 * Copyright (c) 2018, 2019 Amine Ben Hassouna <amine.benhassouna@gmail.com>
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any
 * person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the
 * Software without restriction, including without
 * limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice
 * shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
 * ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
 * SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#include "utils.h"
#include "animation.h"
#include "animationQuit.h"
#include <SDL_mixer.h>

// Defining the background music
#define WAVES_SOUND "assets/background.wav"

// Define screen dimensions
#define SCREEN_WIDTH    1200
#define SCREEN_HEIGHT   600

// Define sub screen dimensions
#define SUB_SCREEN_WIDTH    600
#define SUB_SCREEN_HEIGHT   300

int main(int argc, char* argv[])
{
    // Unused argc, argv
    (void) argc;
    (void) argv;

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL could not be initialized!\n"
                        "SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    // Initialize SDL image
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if((IMG_Init(flags) & flags) != flags) {
        fprintf(stderr, "SDL_image could not be initialized with JPG and PNG support!\n"
                        "SDL_image Error: %s\n", IMG_GetError());
        return 0;
    }

    //Initialize SDL_mixer
     if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
     {
         printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
         return 0;
     }

#if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
    // Disable compositor bypass
    if(!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0"))
    {
        fprintf(stderr, "SDL can not disable compositor bypass!\n");
        return 0;
    }
#endif

    // Create death window
    SDL_Window *startWindow = SDL_CreateWindow("Welcome to the game!",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if(!startWindow)
    {
        fprintf(stderr, "Window could not be created!\n"
                        "SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // Create renderer
        SDL_Renderer *startRenderer = SDL_CreateRenderer(startWindow, -1, SDL_RENDERER_ACCELERATED);
        if(!startRenderer)
        {
            fprintf(stderr, "Renderer could not be created!\n"
                            "SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            // Start animation
            animationStart_start(startRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);

            // Destroy renderer
            SDL_DestroyRenderer(startRenderer);


    }
        // Destroy window
        SDL_DestroyWindow(startWindow);
 }

    // Create game window
    SDL_Window *window = SDL_CreateWindow("Basic Mario-lookalike.",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if(!window)
    {
        fprintf(stderr, "Window could not be created!\n"
                        "SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // Create renderer
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(!renderer)
        {
            fprintf(stderr, "Renderer could not be created!\n"
                            "SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
             // Load .WAV sound
             SDL_AudioSpec wavSpec;
             Uint32 wavLength;
             Uint8 *wavBuffer;
             {
             if(!SDL_LoadWAV(WAVES_SOUND, &wavSpec, &wavBuffer, &wavLength))
             {
                 printf(".WAV sound '%s' could not be loaded!\n"
                        "SDL_Error: %s\n", WAVES_SOUND, SDL_GetError());
                 return 0;
             }

            // Open audio device
             SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
             if(!deviceId)
             {
                 printf("Audio device could not be opened!\n"
                        "SDL_Error: %s\n", SDL_GetError());
                 SDL_FreeWAV(wavBuffer);
                 return 0;
             }

            // Queue audio (~ Add to playlist)
             if(SDL_QueueAudio(deviceId, wavBuffer, wavLength) < 0)
             {
                 printf("Audio could not be queued!\n"
                        "SDL_Error: %s\n", SDL_GetError());
                 SDL_CloseAudioDevice(deviceId);
                 SDL_FreeWAV(wavBuffer);
                 return 0;
             }

            // Play audio
             SDL_PauseAudioDevice(deviceId, 0);

            // Start animation
            Animation_start(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

            // Clean up audio
             SDL_CloseAudioDevice(deviceId);
             SDL_FreeWAV(wavBuffer);

            // Destroy renderer
            SDL_DestroyRenderer(renderer);
        }

        // Destroy window
        SDL_DestroyWindow(window);
    }
    // Quit SDL_Mixer
     Mix_Quit();
 }

    // Create death window
    SDL_Window *subWindow = SDL_CreateWindow("You died!",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SUB_SCREEN_WIDTH, SUB_SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if(!subWindow)
    {
        fprintf(stderr, "Window could not be created!\n"
                        "SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // Create renderer
        SDL_Renderer *subRenderer = SDL_CreateRenderer(subWindow, -1, SDL_RENDERER_ACCELERATED);
        if(!subRenderer)
        {
            fprintf(stderr, "Renderer could not be created!\n"
                            "SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            // Start animation
            animationQuit_start(subRenderer, SUB_SCREEN_WIDTH, SUB_SCREEN_HEIGHT);

            // Destroy renderer
            SDL_DestroyRenderer(subRenderer);


    }
        // Destroy window
        SDL_DestroyWindow(subWindow);
 }

    // Quit SDL
    SDL_Quit();

    return 0;
}
