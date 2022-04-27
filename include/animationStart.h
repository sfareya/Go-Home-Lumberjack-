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

#ifndef ANIMATIONSTART_H
#define ANIMATIONSTART_H

#include <SDL2_gfxPrimitives.h>

#include "utils.h"
#include "background.h"
#include "hero.h"

#define START_IMG      "assets/start.jpg"

#define HERO_IMG       "assets/hero.png"
#define HERO_SPEED     250
#define HERO_MARGIN    20

struct animationStart
{
    // Animation screen dimensions
    int width;
    int height;

    // Animation renderer
    SDL_Renderer *renderer;

    // Background
    Background background;

    // Hero
    Hero hero;
};
typedef struct animationStart animationStart;


bool animationStart_start(SDL_Renderer *renderer, int width, int height);

bool animationStart_load(animationStart *animationStart);
void animationStart_destroy(animationStart *animationStart);

bool animationStart_handleEvent(animationStart *animationStart, SDL_Event *e);
void animationStart_update(animationStart *animationStart, int framerate);
void animationStart_render(animationStart *animationStart);

#endif // ANIMATIONSTART_H
