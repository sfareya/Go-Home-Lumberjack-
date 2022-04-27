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

#ifndef HERO_H
#define HERO_H

#include "utils.h"
#include "image.h"
#include<SDL_mixer.h>

struct Hero
{
    // Hero
    Image image;

    // sound effect
    Mix_Chunk *jump;

    // Direction
    Direction direction;

    // Speed in pixel/second
    int speed;

    // Margin
    int margin;

    // Cropped
    bool cropped;
};
typedef struct Hero Hero;


bool Hero_load(SDL_Renderer *renderer, Hero *hero, const char *image);
void Hero_destroy(Hero *hero);

void Hero_setX(Hero *hero, int x);
void Hero_setY(Hero *hero, int y);
void Hero_setCoordinates(Hero *hero, int x, int y);

void Hero_moveX(Hero *hero, int x);
void Hero_moveY(Hero *hero, int y);

void Hero_move(Hero *hero, int screenWidth, int screenHeight, int framerate);

void Hero_setDirection(Hero *hero, SDL_Keycode keycode);
void Hero_unsetDirection(Hero *hero, SDL_Keycode keycode);

void Hero_render(SDL_Renderer *renderer, Hero *hero);

#endif // HERO_H
