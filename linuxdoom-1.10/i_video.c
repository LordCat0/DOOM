// Emacs style mode select   -*- C++ -*-
//-----------------------------------------------------------------------------
//
// $Id:$
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This source is available for distribution and/or modification
// only under the terms of the DOOM Source Code License as
// published by id Software. All rights reserved.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the DOOM Source Code License
// for more details.
//
// $Log:$
//
// DESCRIPTION:
//	DOOM graphics stuff for X11, UNIX.
//
//-----------------------------------------------------------------------------

#include <motion.h>
#include <pen.h>

#include "doomdef.h"
#include "v_video.h"

int colors[256];

void I_ShutdownGraphics(void)
{
    pen_up();
}

void I_StartFrame(void) {}

void I_StartTic(void) {}

void I_UpdateNoBlit(void) {}

void I_FinishUpdate(void)
{
    int x;
    int y;
    int color;

    erase_all();
    pen_up();
    go_to_xy(-240, 180);

    for (y = 0; y < SCREENHEIGHT; y++)
    {
        go_to_xy(-240, 180 - y * 360 / (SCREENHEIGHT - 1));
        pen_down();

        for (x = 0; x < SCREENWIDTH;)
        {
            color = screens[0][y * SCREENWIDTH + x];
            set_pen_color(colors[color]);

            x++;
            while (x < SCREENWIDTH
                   && screens[0][y * SCREENWIDTH + x] == color)
                x++;

            go_to_xy(-240 + x * 480 / SCREENWIDTH,
                     180 - y * 360 / (SCREENHEIGHT - 1));
        }

        pen_up();
    }
}

void I_ReadScreen(byte* scr)
{
    int i;

    for (i = 0; i < SCREENWIDTH * SCREENHEIGHT; i++)
        scr[i] = screens[0][i];
}

void I_SetPalette(byte* palette)
{
    int i;
    int red;
    int green;
    int blue;

    for (i = 0; i < 256; i++)
    {
        red = gammatable[usegamma][palette[i * 3]];
        green = gammatable[usegamma][palette[i * 3 + 1]];
        blue = gammatable[usegamma][palette[i * 3 + 2]];
        colors[i] = (red << 16) | (green << 8) | blue;
    }
}

void I_InitGraphics(void)
{
    erase_all();
    set_pen_size(2);
    pen_up();
    go_to_xy(-240, 180);
}
