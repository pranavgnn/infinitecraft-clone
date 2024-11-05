#ifndef SIDEBAR_H
#define SIDEBAR_H

#include "raylib.h"

typedef struct DraggableBox DraggableBox;

typedef struct SidebarItem
{
    int x, y;
    Rectangle rect;
    char text[100];
    Color bgColor, borderColor, textColor;
    Font font;
} SidebarItem;

typedef struct Sidebar
{
    int x, y;
    int width, height;
    int itemCount;
    Color bgColor;
    SidebarItem *items;
    float scrollPosition;
    float scrollBarHeight;
} Sidebar;

Sidebar CreateSidebar();

void AddSidebarItem(Sidebar *sidebar, char text[]);

void UpdateSidebarItem(SidebarItem *item, DraggableBox *placedItems, int *placedItemsCount, Font font);

void DrawSidebar(Sidebar *sidebar, Font font);

void UpdateSidebarScroll(Sidebar *sidebar);

#endif