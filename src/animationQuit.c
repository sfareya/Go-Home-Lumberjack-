/* Eya Sfar, Amal Bouakez, Sarra Ben Rejeb
 * Copyright (c) 2018 Amine Ben Hassouna <amine.benhassouna@gmail.com>
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

#include "animationQuit.h"

bool animationQuit_start(SDL_Renderer *renderer, int width, int height)
{
    animationQuit animationQuit = {0};
    animationQuit.renderer  = renderer;
    animationQuit.width     = width;
    animationQuit.height    = height;

    // Load animation assets
    if(!animationQuit_load(&animationQuit))
        return false;


    // Initialize framerate manager : 30 FPS
    FPSmanager fpsmanager;
    SDL_initFramerate(&fpsmanager);
    SDL_setFramerate(&fpsmanager, 60);

    // Initialize start frame
    int frame = SDL_getFramecount(&fpsmanager);

    // Event loop exit flag
    bool quit = false;

    // Event loop
    while(!quit)
    {
        SDL_Event e;

        // Get available event
        while(SDL_PollEvent(&e))
        {
            // Handle animation events
            quit = animationQuit_handleEvent(&animationQuit, &e);
        }

        // Each new frame
        int currentFrame = SDL_getFramecount(&fpsmanager);
        if(currentFrame != frame)
        {
            // Update animation frame
            animationQuit_update(&animationQuit, SDL_getFramerate(&fpsmanager));

            currentFrame = frame;
        }

        // Render animation
        animationQuit_render(&animationQuit);

        // Update screen
        SDL_RenderPresent(renderer);

        // Delay
        SDL_framerateDelay(&fpsmanager);
    }

    animationQuit_destroy(&animationQuit);

    return true;
}

bool animationQuit_load(animationQuit *animationQuit)
{
    // Load the ocean image
    if(!Background_load(animationQuit->renderer, &animationQuit->background, DEATH_IMG))
        return false;

    // Background move direction
    animationQuit->background.direction = DIRECTION_LEFT;

    return true;
}

void animationQuit_destroy(animationQuit *animationQuit)
{
    Background_destroy(&animationQuit->background);
}

bool animationQuit_handleEvent(animationQuit *animationQuit, SDL_Event *e)
{
    bool quit = false;

    // User requests quit
    if(e->type == SDL_QUIT)
    {
        quit = true;
    }
    return quit;
}

void animationQuit_update(animationQuit *animationQuit, int framerate)
{
    // Move ocean
    Background_move(&animationQuit->background, framerate);
}

void animationQuit_render(animationQuit *animationQuit)
{
    // Render ocean
    Background_render(animationQuit->renderer, &animationQuit->background, animationQuit->width, animationQuit->height);
}
