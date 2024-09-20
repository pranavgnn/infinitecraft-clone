#ifndef BOX_H
#define BOX_H

#include "raylib.h"

typedef struct DraggableBox
{
    int id;
    Rectangle rect;
    const char *text;
    bool isDragging;
    Vector2 dragOffset;
    Color bgColor, borderColor, textColor;
    Font font;
} DraggableBox;

DraggableBox CreateDraggableBox(int id, float x, float y, float width, float height, const char *text, Font font);

void UpdateDraggableBox(DraggableBox *box);

void DrawDraggableBox(DraggableBox *box);

#endif