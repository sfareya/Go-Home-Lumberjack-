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

#include "hero.h"

bool Hero_load(SDL_Renderer *renderer, Hero *hero, const char *image)
{
    // Load hero image
    if(!Image_load(renderer, &hero->image, image))
    {
        return false;
    }

    return true;
}

void Hero_destroy(Hero *hero)
{
    Image_destroy(&hero->image);
}

void Hero_setX(Hero *hero, int x)
{
    // Hero x coordinate
    hero->image.rect.x = x;
}

void Hero_setY(Hero *hero, int y)
{
    // Hero y coordinate
    hero->image.rect.y = y;
}

void Hero_setCoordinates(Hero *hero, int x, int y)
{
    Hero_setX(hero, x);
    Hero_setY(hero, y);
}

void Hero_moveX(Hero *hero, int x)
{
    Hero_setX(hero, hero->image.rect.x + x);
}

void Hero_moveY(Hero *hero, int y)
{
    Hero_setY(hero, hero->image.rect.y + y);
}

void Hero_setDirection(Hero *hero, SDL_Keycode keycode)
{
    switch (keycode)
    {
    case SDLK_UP:
        hero->direction &= ~DIRECTION_DOWN;
        hero->direction |= DIRECTION_UP;
        break;

    case SDLK_DOWN:
        hero->direction &= ~DIRECTION_UP;
        hero->direction |= DIRECTION_DOWN;
        break;

    case SDLK_RIGHT:
        hero->direction &= ~DIRECTION_LEFT;
        hero->direction |= DIRECTION_RIGHT;
        break;

    case SDLK_LEFT:
        hero->direction &= ~DIRECTION_RIGHT;
        hero->direction |= DIRECTION_LEFT;
        break;
    }
}

void Hero_unsetDirection(Hero *hero, SDL_Keycode keycode)
{
    switch (keycode)
    {
    case SDLK_UP:
        hero->direction &= ~DIRECTION_UP;
        break;

    case SDLK_DOWN:
        hero->direction &= ~DIRECTION_DOWN;
        break;

    case SDLK_RIGHT:
        hero->direction &= ~DIRECTION_RIGHT;
        break;

    case SDLK_LEFT:
        hero->direction &= ~DIRECTION_LEFT;
        break;
    }
}

void Hero_render(SDL_Renderer *renderer, Hero *hero)
{
    // Render hero
    Image_render(renderer, &hero->image);

}

void Hero_move(Hero *hero, int screenWidth, int screenHeight, int framerate)
{
    int heroStep = hero->speed / framerate;

    if( (hero->direction & DIRECTION_UP)
            && hero->image.rect.y - heroStep >= hero->margin)
    {
        Hero_moveY(hero, -heroStep);
        if(hero->image.rect.y<100)
        {

          Hero_setDirection(hero, SDLK_DOWN);

        }
    }
    else if( (hero->direction & DIRECTION_DOWN)
             && hero->image.rect.y < 450)
    {
        Hero_moveY(hero, heroStep);
    }

    if( (hero->direction & DIRECTION_RIGHT)
            && hero->image.rect.x + hero->image.rect.w + heroStep <= screenWidth - hero->margin)
    {
        Hero_moveX(hero, heroStep);
    }
    else if( (hero->direction & DIRECTION_LEFT)
             && hero->image.rect.x - heroStep >= hero->margin)
    {
        Hero_moveX(hero, -heroStep);
    }
}

