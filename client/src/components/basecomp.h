#ifndef BASE_COMP_H
#define BASE_COMP_H

#include "raylib.h"

typedef enum {
    NEUTRAL,
    MOUSE1_DOWN,
    MOUSE2_DOWN,
    MOUSE3_DOWN,
    DRAGGING,
} State;

typedef struct Component {
    // Vector2 position = (Vector2){0, 0};
    // Vector2 size = (Vector2){10, 10};
    Rectangle rect;
    Color bgColor;
    Color borderColor;
    State inputState;
    void (*onMouseDown)(void);
    void (*onMouseDragging)(void);
} Component;

Component newComponent(Vector2 position, Vector2 size);

void onMouseDown(Component *c, void (*callback)(void));

void onMouseDragging(Component *c, void (*callback)(void));

void drawComponent(Component c);

#endif