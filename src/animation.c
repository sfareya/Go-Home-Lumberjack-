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

#include "animation.h"

bool Animation_start(SDL_Renderer *renderer, int width, int height)
{
    Animation animation = {0};
    animation.renderer  = renderer;
    animation.width     = width;
    animation.height    = height;
    animation.gameover  = false;

    // Load animation assets
    if(!Animation_load(&animation))
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
    while(!quit && !animation.gameover)
    {
        SDL_Event e;

        // Get available event
        while(SDL_PollEvent(&e))
        {
            // Handle animation events
            quit = Animation_handleEvent(&animation, &e);
        }

        // Each new frame
        int currentFrame = SDL_getFramecount(&fpsmanager);
        if(currentFrame != frame)
        {
            // Update animation frame
            Animation_update(&animation, SDL_getFramerate(&fpsmanager));

            currentFrame = frame;
        }

        // Render animation
        Animation_render(&animation);

        // Update screen
        SDL_RenderPresent(renderer);

        // Delay
        SDL_framerateDelay(&fpsmanager);
    }

    Animation_destroy(&animation);

    return true;
}

bool Animation_load(Animation *animation)
{
    // Load sound effects

    // Hero Jump Effect
    animation->hero.jump = Mix_LoadWAV("assets/jump.wav");
        if(!animation->hero.jump)
        {
            printf("Mix_LoadWAV: %s\n", Mix_GetError());
        }

    // Fire Death effect
    animation->fire.gameover = Mix_LoadWAV("assets/death.wav");
            if(!animation->fire.gameover)
            {

                printf("Mix_LoadWAV: %s\n", Mix_GetError());
            }

    // Spikes Death effect
    animation->spikes.gameover=Mix_LoadWAV("assets/death.wav");
            if(!animation->spikes.gameover)
            {
                printf("Mix_LoadWAV: %s\n", Mix_GetError());
            }

    // Load the NIGHT image
    if(!Background_load(animation->renderer, &animation->background, NIGHT_IMG))
        return false;

    // Background move direction
    animation->background.direction = DIRECTION_LEFT;

    // Background speed in pixel/second
    animation->background.speed = NIGHT_SPEED;

    if(!Hero_load(animation->renderer, &animation->hero, HERO_IMG))
    {
        Background_destroy(&animation->background);
        return false;
    }

    animation->hero.margin = HERO_MARGIN;

    // Set hero initial position
    Hero_setX(&animation->hero, (animation->width - animation->hero.image.rect.w) / 2); // Horiz. center
    Hero_setY(&animation->hero,  450);

    // Hero move direction
    animation->hero.direction = DIRECTION_STOP;

    // Hero move speed in pixel/second
    animation->hero.speed = HERO_SPEED;

    // Fire loading
    if(!Fire_load(animation->renderer, &animation->fire, FIRE_IMG))
    {
        Background_destroy(&animation->background);
        return false;
    }

    animation->fire.margin = FIRE_MARGIN;

    // Set fire initial position
    Fire_setX(&animation->fire, 400); // Horiz. center
    Fire_setY(&animation->fire,  400);

    // Fire move direction
    animation->fire.direction = DIRECTION_LEFT;

    // Fire move speed in pixel/second
    animation->fire.speed = FIRE_SPEED;

    // Spikes loading
    if(!Spikes_load(animation->renderer, &animation->spikes, SPIKES_IMG))
    {
        Background_destroy(&animation->background);
        return false;
    }

    animation->spikes.margin = SPIKES_MARGIN;

    // Set spikes initial position
    Spikes_setX(&animation->spikes, 20); // Horiz. center
    Spikes_setY(&animation->spikes,  475);

    // Spikes move direction
    animation->spikes.direction = DIRECTION_LEFT;

    // Spikes move speed in pixel/second
    animation->spikes.speed = SPIKES_SPEED;

    return true;
}

void Animation_destroy(Animation *animation)
{
    Hero_destroy(&animation->hero);
    Background_destroy(&animation->background);
    Fire_destroy(&animation->fire);
    Spikes_destroy(&animation->spikes);
}

bool Animation_handleEvent(Animation *animation, SDL_Event *e)
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
        case SDLK_ESCAPE:
            quit = true;
            break;

        case SDLK_UP:
        case SDLK_DOWN:
        case SDLK_RIGHT:
        case SDLK_LEFT:

           Hero_setDirection(&animation->hero, e->key.keysym.sym);
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

            Hero_unsetDirection(&animation->hero, e->key.keysym.sym);
            break;
        }
    }
    return quit;
}

void Animation_update(Animation *animation, int framerate)
{
    // Move NIGHT
    Background_move(&animation->background, framerate);

    // Move hero
    Hero_move(&animation->hero, animation->width, animation->height, framerate);

    // Move fire
    Fire_move(&animation->fire, animation->width, animation->height, framerate, animation);

    // Move spikes
    Spikes_move(&animation->spikes, animation->width, animation->height, framerate, animation);

    // Score
    animation->score++/0.00001;
}

void Animation_render(Animation *animation)
{
    // Render NIGHT
    Background_render(animation->renderer, &animation->background, animation->width, animation->height);

    // Render hero
    Hero_render(animation->renderer, &animation->hero);

    // Render fire
    Fire_render(animation->renderer, &animation->fire);

    // Render spikes
    Spikes_render(animation->renderer, &animation->spikes);

    // COLOR
    char score[100];
    sprintf(score, "Score: %d", animation->score);
    stringRGBA(animation->renderer, 570 , 16 , score , 255, 253, 208, 255 );
}
