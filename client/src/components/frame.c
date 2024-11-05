#include "frame.h"

Frame newFrame(Vector2 position, Vector2 size) {
    return (Frame) {
        .super = newComponent(position, size),
    };
}

void drawFrame(Frame frame) {
    drawComponent(frame.super);
}