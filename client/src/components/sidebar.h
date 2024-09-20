#ifndef SIDEBAR_H
#define SIDEBAR_H

#include "raylib.h"

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
} Sidebar;

Sidebar CreateSidebar();

void AddSidebarItem(Sidebar *sidebar, char text[]);

void DrawSidebar(Sidebar *sidebar, Font font);

#endif