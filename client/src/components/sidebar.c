#include <stdlib.h>
#include <string.h>

#include "sidebar.h"

#define SIDEBAR_WIDTH 350
#define ITEM_WIDTH_SCALE 0.9
#define ITEM_HEIGHT 50
#define ITEM_PADDING_X 7
#define ITEM_PADDING_Y 100
#define TEXT_PADDING_X 5

Sidebar CreateSidebar()
{
    int sidebarX = GetScreenWidth() - SIDEBAR_WIDTH;

    Sidebar sidebar;

    sidebar.x = sidebarX;
    sidebar.y = 0;
    sidebar.width = SIDEBAR_WIDTH;
    sidebar.height = GetScreenHeight();
    sidebar.bgColor = (Color){0, 0, 0, 255};
    sidebar.itemCount = 0;
    sidebar.items = (SidebarItem *)malloc(1000 * sizeof(SidebarItem));

    return sidebar;
}

void AddSidebarItem(Sidebar *sidebar, char text[])
{
    int itemWidth = (int)(ITEM_WIDTH_SCALE * SIDEBAR_WIDTH);
    int itemX = (int)sidebar->x + (sidebar->width - itemWidth) / 2;
    int itemY = sidebar->itemCount * (ITEM_HEIGHT + ITEM_PADDING_X) + ITEM_PADDING_Y;

    SidebarItem item;

    item.x = itemX;
    item.y = itemY;
    strcpy(item.text, text);
    item.rect = (Rectangle){itemX, itemY, itemWidth, ITEM_HEIGHT};
    item.bgColor = (Color){10, 17, 31, 255};
    item.borderColor = (Color){121, 75, 1, 255};
    item.textColor = (Color){252, 163, 17, 255};
    // item.font = font;

    sidebar->items[(sidebar->itemCount)++] = item;
}

void DrawSidebar(Sidebar *sidebar, Font font)
{
    DrawRectangle(sidebar->x, sidebar->y, sidebar->width, sidebar->height, sidebar->bgColor);

    for (int i = 0; i < sidebar->itemCount; i++)
    {

        SidebarItem item = sidebar->items[i];
        // Vector2 textBounds = MeasureTextEx(item.font, item.text, item.font.baseSize, item.font.glyphPadding);

        DrawRectangleRoundedLines(item.rect, 0.25, 12, 2, item.borderColor);
        DrawRectangleRounded(item.rect, 0.25, 12, item.bgColor);

        DrawTextEx(font, item.text, (Vector2){item.x + 10, (int)(item.y + (ITEM_HEIGHT - 32) / 2)}, 32.0, 1, item.textColor);
    }
}