#include "basecomp.h"

Component newComponent(Vector2 position, Vector2 size) {
    return (Component) {
        .rect = (Rectangle) {position.x, position.y, size.x, size.y},
        .bgColor = WHITE,
        .borderColor = BLACK,
    };
}

void onMouseDown(Component *c, void (*callback)(void)) {
    c->onMouseDown = callback;
}

void onMouseDragging(Component *c, void (*callback)(void)) {
    c->onMouseDragging = callback;
}

void drawComponent(Component c) {
    DrawRectangleRoundedLines(c.rect, 0.25, 12, 2, c.borderColor);
    DrawRectangleRounded(c.rect, 0.25, 12, c.bgColor);
}