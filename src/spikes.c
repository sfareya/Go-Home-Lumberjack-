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

#include "spikes.h"
#include "animation.h"

bool Spikes_load(SDL_Renderer *renderer, Spikes *spikes, const char *image)
{
    // Load spikes image
    if(!Image_load(renderer, &spikes->image, image))
    {
        return false;
    }

    return true;
}

void Spikes_destroy(Spikes *spikes)
{
    Image_destroy(&spikes->image);
}

void Spikes_setX(Spikes *spikes, int x)
{
    // spikes x coordinate
    spikes->image.rect.x = x;
}

void Spikes_setY(Spikes *spikes, int y)
{
    // spikes y coordinate
    spikes->image.rect.y = y;
}

void Spikes_setCoordinates(Spikes *spikes, int x, int y)
{
    Spikes_setX(spikes, x);
    Spikes_setY(spikes, y);
}

void Spikes_moveX(Spikes *spikes, int x)
{
    Spikes_setX(spikes, spikes->image.rect.x + x);
}

void Spikes_moveY(Spikes *spikes, int y)
{
    Spikes_setY(spikes, spikes->image.rect.y + y);
}

void Spikes_setDirection(Spikes *spikes, SDL_Keycode keycode)
{
    switch (keycode)
    {
    case SDLK_UP:
        spikes->direction &= ~DIRECTION_DOWN;
        spikes->direction |= DIRECTION_UP;
        break;

    case SDLK_DOWN:
        spikes->direction &= ~DIRECTION_UP;
        spikes->direction |= DIRECTION_DOWN;
        break;

    case SDLK_RIGHT:
        spikes->direction &= ~DIRECTION_LEFT;
        spikes->direction |= DIRECTION_RIGHT;
        break;

    case SDLK_LEFT:
        spikes->direction &= ~DIRECTION_RIGHT;
        spikes->direction |= DIRECTION_LEFT;
        break;
    }
}

void Spikes_unsetDirection(Spikes *spikes, SDL_Keycode keycode)
{
    switch (keycode)
    {
    case SDLK_UP:
        spikes->direction &= ~DIRECTION_UP;
        break;

    case SDLK_DOWN:
        spikes->direction &= ~DIRECTION_DOWN;
        break;

    case SDLK_RIGHT:
        spikes->direction &= ~DIRECTION_RIGHT;
        break;

    case SDLK_LEFT:
        spikes->direction &= ~DIRECTION_LEFT;
        break;
    }
}

void Spikes_render(SDL_Renderer *renderer, Spikes *spikes)
{

    // Render spikes
    Image_render(renderer, &spikes->image);

}

void Spikes_move(Spikes *spikes, int screenWidth, int screenHeight, int framerate, Animation* animation)
{
    int spikesStep = spikes->speed / framerate;

    if( (spikes->direction & DIRECTION_UP)
            && spikes->image.rect.y - spikesStep >= spikes->margin)
    {
        Spikes_moveY(spikes, -spikesStep);
    }
    else if( (spikes->direction & DIRECTION_DOWN)
             && spikes->image.rect.y < (screenHeight - spikes->image.rect.h) / 2)
    {
        Spikes_moveY(spikes, spikesStep);
    }

    if( (spikes->direction & DIRECTION_RIGHT)
            && spikes->image.rect.x + spikes->image.rect.w + spikesStep <= screenWidth - spikes->margin)
    {
        Spikes_moveX(spikes, spikesStep);
    }
    else if( (spikes->direction & DIRECTION_LEFT))
    {
        Spikes_moveX(spikes, -spikesStep);


         // Detect  collision
        if(spikes->image.rect.x <= animation->hero.image.rect.x + animation->hero.image.rect.w
                && spikes->image.rect.x +spikes->image.rect.w  >= animation->hero.image.rect.x
                // bottom of the box < the top of the hero
                && spikes->image.rect.y + spikes->image.rect.h >= animation->hero.image.rect.y
                // top of the box < the bottom of the hero
                && spikes->image.rect.y <= animation->hero.image.rect.y + animation->hero.image.rect.h )
        {
            animation->gameover = true;
        }

        if(spikes->image.rect.x < - spikes->image.rect.w )
        {
            spikes->image.rect.x = screenWidth - spikes->image.rect.w;

             if(rand() % 5)
            {
                spikes->image.rect.y = 500;
            }
            else
            {
                spikes->image.rect.y = 200;
            }
        }
    }
}
