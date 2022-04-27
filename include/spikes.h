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

#ifndef SPIKES_H
#define SPIKES_H

#include "utils.h"
#include "image.h"
#include<SDL_mixer.h>

typedef struct Animation Animation;

struct Spikes
{
    // Spikes
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
typedef struct Spikes Spikes;


bool Spikes_load(SDL_Renderer *renderer, Spikes *spikes, const char *image);
void Spikes_destroy(Spikes *spikes);

void Spikes_setX(Spikes *spikes, int x);
void Spikes_setY(Spikes *spikes, int y);
void Spikes_setCoordinates(Spikes *spikes, int x, int y);

void Spikes_moveX(Spikes *spikes, int x);
void Spikes_moveY(Spikes *spikes, int y);

void Spikes_move(Spikes *spikes, int screenWidth, int screenHeight, int framerate, Animation* animation);

void Spikes_setDirection(Spikes *spikes, SDL_Keycode keycode);
void Spikes_unsetDirection(Spikes *spikes, SDL_Keycode keycode);

void Spikes_render(SDL_Renderer *renderer, Spikes *spikes);

#endif // SPIKES_H
