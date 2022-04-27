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

#ifndef FIRE_H
#define FIRE_H

#include "utils.h"
#include "image.h"
#include<SDL_mixer.h>

typedef struct Animation Animation;

struct Fire
{
    // Fire
    Image image;

    // sound effect
    Mix_Chunk *gameover;

    // Direction
    Direction direction;

    // Speed in pixel/second
    int speed;

    // Margin
    int margin;

    // Cropped
    bool cropped;
};
typedef struct Fire Fire;


bool Fire_load(SDL_Renderer *renderer, Fire *fire, const char *image);
void Fire_destroy(Fire *fire);

void Fire_setX(Fire *fire, int x);
void Fire_setY(Fire *fire, int y);
void Fire_setCoordinates(Fire *fire, int x, int y);

void Fire_moveX(Fire *fire, int x);
void Fire_moveY(Fire *fire, int y);

void Fire_move(Fire *fire, int screenWidth, int screenHeight, int framerate, Animation* animation);

void Fire_setDirection(Fire *fire, SDL_Keycode keycode);
void Fire_unsetDirection(Fire *fire, SDL_Keycode keycode);

void Fire_render(SDL_Renderer *renderer, Fire *fire);

#endif // FIRE_H
