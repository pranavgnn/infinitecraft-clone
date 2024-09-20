#include "box.h"

DraggableBox CreateDraggableBox(int id, float x, float y, float width, float height, const char *text, Font font)
{
    DraggableBox box;
    box.id = id;
    box.rect = (Rectangle){x, y, width, height};
    box.text = text;
    box.isDragging = false;
    box.dragOffset = (Vector2){0, 0};
    box.bgColor = (Color){0, 0, 0, 255};
    box.borderColor = (Color){252, 163, 17, 255};
    box.textColor = (Color){255, 255, 255, 255};
    box.font = font;
    return box;
}

void UpdateDraggableBox(DraggableBox *box)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), box->rect))
    {
        box->isDragging = true;
        box->dragOffset = (Vector2){GetMouseX() - box->rect.x, GetMouseY() - box->rect.y};
    }

    if (box->isDragging)
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            box->rect.x = GetMouseX() - box->dragOffset.x;
            box->rect.y = GetMouseY() - box->dragOffset.y;

        }
        else
            box->isDragging = false;
    }
}

void DrawDraggableBox(DraggableBox *box)
{
    DrawRectangleRoundedLines(box->rect, 0.25, 12, 2, box->borderColor);
    DrawRectangleRounded(box->rect, 0.25, 12, box->bgColor);

    Vector2 textBounds = MeasureTextEx(box->font, box->text, box->font.baseSize, box->font.glyphPadding);

    DrawTextEx(
        box->font, box->text,
        (Vector2){box->rect.x + (box->rect.width - textBounds.x) / 2, box->rect.y + (box->rect.height - textBounds.y) / 2},
        (float)box->font.baseSize, 2, box->textColor
    );
}