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

#include "animationStart.h"

bool animationStart_start(SDL_Renderer *renderer, int width, int height)
{
    animationStart animationStart = {0};
    animationStart.renderer  = renderer;
    animationStart.width     = width;
    animationStart.height    = height;

    // Load animation assets
    if(!animationStart_load(&animationStart))
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
            quit = animationStart_handleEvent(&animationStart, &e);
        }

        // Each new frame
        int currentFrame = SDL_getFramecount(&fpsmanager);
        if(currentFrame != frame)
        {
            // Update animation frame
            animationStart_update(&animationStart, SDL_getFramerate(&fpsmanager));

            currentFrame = frame;
        }

        // Render animation
        animationStart_render(&animationStart);

        // Update screen
        SDL_RenderPresent(renderer);

        // Delay
        SDL_framerateDelay(&fpsmanager);
    }

    animationStart_destroy(&animationStart);

    return true;
}

bool animationStart_load(animationStart *animationStart)
{
    // Load the ocean image
    if(!Background_load(animationStart->renderer, &animationStart->background, START_IMG))
        return false;

    // Background move direction
    animationStart->background.direction = DIRECTION_LEFT;
    if(!Hero_load(animationStart->renderer, &animationStart->hero, HERO_IMG))
    {
        Background_destroy(&animationStart->background);
        return false;
    }

    animationStart->hero.margin = HERO_MARGIN;

    // Set hero initial position
    Hero_setX(&animationStart->hero, (animationStart->width - animationStart->hero.image.rect.w) / 2); // Horiz. center
    Hero_setY(&animationStart->hero,  450);

    // Hero move direction
    animationStart->hero.direction = DIRECTION_STOP;

    // Hero move speed in pixel/second
    animationStart->hero.speed = HERO_SPEED;

    return true;
}

void animationStart_destroy(animationStart *animationStart)
{
    Background_destroy(&animationStart->background);
    Hero_destroy(&animationStart->hero);
}

bool animationStart_handleEvent(animationStart *animationStart, SDL_Event *e)
{
    bool quit = false;

    // User requests quit
    if(e->type == SDL_QUIT)
    {
        quit = true;
    }
    else if(e->type == SDL_KEYDOWN)
    {
        switch (e->key.keysym.sym)
        {
        case SDLK_RETURN:
            quit = true;
            break;
        case SDLK_UP:
        case SDLK_DOWN:
        case SDLK_RIGHT:
        case SDLK_LEFT:

           Hero_setDirection(&animationStart->hero, e->key.keysym.sym);
            break;
        }
    }
    else if(e->type == SDL_KEYUP)
    {
        switch (e->key.keysym.sym)
        {
        case SDLK_UP:
            break;
        case SDLK_DOWN:
        case SDLK_RIGHT:
        case SDLK_LEFT:

            Hero_unsetDirection(&animationStart->hero, e->key.keysym.sym);
            break;
        }
    }
    return quit;
}

void animationStart_update(animationStart *animationStart, int framerate)
{
    // Move ocean
    Background_move(&animationStart->background, framerate);

    // Move hero
    Hero_move(&animationStart->hero, animationStart->width, animationStart->height, framerate);
}

void animationStart_render(animationStart *animationStart)
{
    // Render ocean
    Background_render(animationStart->renderer, &animationStart->background, animationStart->width, animationStart->height);

    // Render hero
    Hero_render(animationStart->renderer, &animationStart->hero);
}
