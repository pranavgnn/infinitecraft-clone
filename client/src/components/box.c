#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "box.h"
#include "../util/requests.h"

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

float GetRectOverlappingArea(Rectangle rect1, Rectangle rect2)
{
    int minX = fmax(rect1.x, rect2.x);
    int maxX = fmin(rect1.x + rect1.width, rect2.x + rect2.width);
    int minY = fmax(rect1.y, rect2.y);
    int maxY = fmin(rect1.y + rect1.height, rect2.y + rect2.height);

    if (minX < maxX && minY < maxY)
        return (float) (maxX - minX) * (maxY - minY);
    else
        return 0.0f;
}

void UpdateDraggableBox(DraggableBox *box, DraggableBox *placedItems, int *placedItemsCount, Sidebar* sidebar)
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

            // Check if any other box is mostly inside the current box
            for (int i = 0; i < *placedItemsCount; i++)
            {
                if (i != box - placedItems)
                {
                    Rectangle otherRect = placedItems[i].rect;
                    float overlapArea = GetRectOverlappingArea(box->rect, otherRect);
                    float boxArea = box->rect.width * box->rect.height;
                    float otherArea = otherRect.width * otherRect.height;

                    if (overlapArea / boxArea > 0.5f || overlapArea / otherArea > 0.5f)
                    {
                        // char* combinationText;
                        char* response;

                        char requestUrl[] = "http://127.0.0.1/craft?item1=";
                        strcat(requestUrl, box->text);
                        strcat(requestUrl, "&item2=");
                        strcat(requestUrl, placedItems[i].text);

                        response = requestGET(requestUrl);

                        DraggableBox newBox = CreateDraggableBox(1, box->rect.x, box->rect.y, box->rect.width, box->rect.height, response, box->font);
                        newBox.dragOffset = (Vector2){GetMouseX() - box->rect.x, GetMouseY() - box->rect.y};
                        newBox.isDragging = true;
                        placedItems[(*placedItemsCount)++] = newBox;
                        AddSidebarItem(sidebar, response);

                        for (int j = box - placedItems; j < *placedItemsCount - 1; j++)
                            placedItems[j] = placedItems[j + 1];

                        (*placedItemsCount)--;

                        for (int j = i; j < *placedItemsCount - 1; j++)
                            placedItems[j] = placedItems[j + 1];

                        (*placedItemsCount)--;

                        box->isDragging = false;
                        break;
                    }
                }
            }
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