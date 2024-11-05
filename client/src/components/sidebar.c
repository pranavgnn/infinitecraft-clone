#include <stdlib.h>
#include <string.h>

#include "sidebar.h"
#include "box.h"

#define SIDEBAR_WIDTH 350
#define ITEM_WIDTH_SCALE 0.9
#define ITEM_HEIGHT 50
#define ITEM_PADDING_X 7
#define ITEM_PADDING_Y 100
#define TEXT_PADDING_X 5
#define SCROLLBAR_WIDTH 10
#define SCROLLBAR_PADDING 5

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
    sidebar.scrollPosition = 0;
    sidebar.scrollBarHeight = 0;

    return sidebar;
}

void AddSidebarItem(Sidebar *sidebar, char text[])
{
    for (int i = 0; i < sidebar->itemCount; i++)
        if (strcmp(sidebar->items[i].text, text) == 0) return;

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

    // Update scroll bar height
    sidebar->scrollBarHeight = (float)sidebar->itemCount * (ITEM_HEIGHT + ITEM_PADDING_X) / sidebar->height;
}

void UpdateSidebarItem(SidebarItem *item, DraggableBox *placedItems, int *placedItemsCount, Font font)
{
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), item->rect))
    {
        DraggableBox box = CreateDraggableBox(1, item->x, item->y, item->rect.width, item->rect.height, item->text, font);
        placedItems[(*placedItemsCount)++] = box;
    }
}

void DrawSidebar(Sidebar *sidebar, Font font)
{
    DrawRectangle(sidebar->x, sidebar->y, sidebar->width, sidebar->height, sidebar->bgColor);

    // Draw scroll bar
    Rectangle scrollBarRect = (Rectangle){sidebar->x + sidebar->width - SCROLLBAR_WIDTH - SCROLLBAR_PADDING, sidebar->y, SCROLLBAR_WIDTH, sidebar->height};
    DrawRectangleRec(scrollBarRect, (Color){50, 50, 50, 255});

    // Draw scroll bar handle
    float scrollBarHandleHeight = sidebar->height * (1 - sidebar->scrollBarHeight);
    Rectangle scrollBarHandleRect = (Rectangle){scrollBarRect.x, scrollBarRect.y + (scrollBarRect.height - scrollBarHandleHeight) * sidebar->scrollPosition, scrollBarRect.width, scrollBarHandleHeight};
    DrawRectangleRec(scrollBarHandleRect, (Color){100, 100, 100, 255});

    // Draw sidebar items
    for (int i = 0; i < sidebar->itemCount; i++)
    {
        SidebarItem item = sidebar->items[i];

        // Calculate item position based on scroll position
        int itemY = item.y - (int)(sidebar->scrollPosition * (sidebar->itemCount * (ITEM_HEIGHT + ITEM_PADDING_X)));

        // Check if item is visible
        if (itemY + ITEM_HEIGHT > sidebar->y && itemY < sidebar->y + sidebar->height)
        {
            // Draw item
            DrawRectangleRoundedLines((Rectangle){item.x, itemY, item.rect.width, ITEM_HEIGHT}, 0.25, 12, 2, item.borderColor);
            DrawRectangleRounded((Rectangle){item.x, itemY, item.rect.width, ITEM_HEIGHT}, 0.25, 12, item.bgColor);

            DrawTextEx(font, item.text, (Vector2){ item.x + 10, (int)(itemY + (ITEM_HEIGHT - 32) / 2)}, 32.0, 1, item.textColor);
        }
    }
}

void UpdateSidebarScroll(Sidebar *sidebar)
{
    // Update scroll position based on mouse wheel
    if (GetMouseWheelMove())
    {
        sidebar->scrollPosition += GetMouseWheelMove() * 0.01;
        if (sidebar->scrollPosition < 0) sidebar->scrollPosition = 0;
        if (sidebar->scrollPosition > 1 - sidebar->scrollBarHeight) sidebar->scrollPosition = 1 - sidebar->scrollBarHeight;
    }

    // Update scroll position based on scroll bar handle
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), (Rectangle){sidebar->x + sidebar->width - SCROLLBAR_WIDTH - SCROLLBAR_PADDING, sidebar->y, SCROLLBAR_WIDTH, sidebar->height}))
    {
        sidebar->scrollPosition = (GetMousePosition().y - sidebar->y) / (float)sidebar->height;
        if (sidebar->scrollPosition < 0) sidebar->scrollPosition = 0;
        if (sidebar->scrollPosition > 1 - sidebar->scrollBarHeight) sidebar->scrollPosition = 1 - sidebar->scrollBarHeight;
    }
}