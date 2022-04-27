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

#include "fire.h"
#include "animation.h"

// Define screen dimensions
// #define SUB_SCREEN_WIDTH    500
// #define SUB_SCREEN_HEIGHT   500

bool Fire_load(SDL_Renderer *renderer, Fire *fire, const char *image)
{
    // Load fire image
    if(!Image_load(renderer, &fire->image, image))
    {
        return false;
    }

    return true;
}

void Fire_destroy(Fire *fire)
{
    Image_destroy(&fire->image);
}

void Fire_setX(Fire *fire, int x)
{
    // fire x coordinate
    fire->image.rect.x = x;
}

void Fire_setY(Fire *fire, int y)
{
    // fire y coordinate
    fire->image.rect.y = y;
}

void Fire_setCoordinates(Fire *fire, int x, int y)
{
    Fire_setX(fire, x);
    Fire_setY(fire, y);
}

void Fire_moveX(Fire *fire, int x)
{
    Fire_setX(fire, fire->image.rect.x + x);
}

void Fire_moveY(Fire *fire, int y)
{
    Fire_setY(fire, fire->image.rect.y + y);
}

void Fire_setDirection(Fire *fire, SDL_Keycode keycode)
{
    switch (keycode)
    {
    case SDLK_UP:
        fire->direction &= ~DIRECTION_DOWN;
        fire->direction |= DIRECTION_UP;
        break;

    case SDLK_DOWN:
        fire->direction &= ~DIRECTION_UP;
        fire->direction |= DIRECTION_DOWN;
        break;

    case SDLK_RIGHT:
        fire->direction &= ~DIRECTION_LEFT;
        fire->direction |= DIRECTION_RIGHT;
        break;

    case SDLK_LEFT:
        fire->direction &= ~DIRECTION_RIGHT;
        fire->direction |= DIRECTION_LEFT;
        break;
    }
}

void Fire_unsetDirection(Fire *fire, SDL_Keycode keycode)
{
    switch (keycode)
    {
    case SDLK_UP:
        fire->direction &= ~DIRECTION_UP;
        break;

    case SDLK_DOWN:
        fire->direction &= ~DIRECTION_DOWN;
        break;

    case SDLK_RIGHT:
        fire->direction &= ~DIRECTION_RIGHT;
        break;

    case SDLK_LEFT:
        fire->direction &= ~DIRECTION_LEFT;
        break;
    }
}

void Fire_render(SDL_Renderer *renderer, Fire *fire)
{

    // Render fire
    Image_render(renderer, &fire->image);

}

void Fire_move(Fire *fire, int screenWidth, int screenHeight, int framerate, Animation* animation)
{
    int fireStep = fire->speed / framerate;

    if( (fire->direction & DIRECTION_UP)
            && fire->image.rect.y - fireStep >= fire->margin)
    {
        Fire_moveY(fire, -fireStep);
    }
    else if( (fire->direction & DIRECTION_DOWN)
             && fire->image.rect.y < (screenHeight - fire->image.rect.h) / 2)
    {
        Fire_moveY(fire, fireStep);
    }

    if( (fire->direction & DIRECTION_RIGHT)
            && fire->image.rect.x + fire->image.rect.w + fireStep <= screenWidth - fire->margin)
    {
        Fire_moveX(fire, fireStep);
    }
    else if( (fire->direction & DIRECTION_LEFT))
    {
        Fire_moveX(fire, -fireStep);


         // Detect  collision
        if(fire->image.rect.x <= animation->hero.image.rect.x + animation->hero.image.rect.w
                && fire->image.rect.x +fire->image.rect.w  >= animation->hero.image.rect.x
                // bottom of the box < the top of the hero
                && fire->image.rect.y + fire->image.rect.h >= animation->hero.image.rect.y
                // top of the box < the bottom of the hero
                && fire->image.rect.y <= animation->hero.image.rect.y + animation->hero.image.rect.h )
        {
            animation->gameover = true;
        }

        if(fire->image.rect.x < - fire->image.rect.w )
        {
            fire->image.rect.x = screenWidth - fire->image.rect.w;

            if(rand() % 2)
            {
                fire->image.rect.y = 300;
            }
            else
            {
                fire->image.rect.y = 200;
            }
        }
    }
}
