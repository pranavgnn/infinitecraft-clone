#ifndef FRAME_H
#define FRAME_H

#include "basecomp.h"
#include "raylib.h"

typedef struct Frame
{
    Component super;
} Frame;

Frame newFrame(Vector2 position, Vector2 size);

void drawFrame(Frame frame);

#endif