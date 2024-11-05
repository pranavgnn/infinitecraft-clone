#include <stdio.h>
#include "raylib.h"

#include "components/box.h"
#include "components/sidebar.h"
// #include "components/frame.h"

#include "util/requests.h"

DraggableBox placedItems[1000];
int placedItemsCount = 0;

int main()
{
    // char *response;

    // response = requestGET("http://127.0.0.1/craft?item1=Fire&item2=Water");

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "InfiniteCraft Clone - ADS Project");
    MaximizeWindow();

    // Frame frame = newFrame((Vector2){20, 20}, (Vector2){100, 100});

    Font font = LoadFontEx("resources/fonts/Roboto-Medium.ttf", 32, 0, 250);
    if (!font.texture.id)
        printf("Error loading font\n");

    Sidebar sidebar = CreateSidebar();
    AddSidebarItem(&sidebar, "Earth");
    AddSidebarItem(&sidebar, "Water");
    AddSidebarItem(&sidebar, "Fire");
    AddSidebarItem(&sidebar, "Air");
    AddSidebarItem(&sidebar, "Wind");

    DraggableBox placedItems[1000];
    int placedItemsCount = 0;

    // ...

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground((Color){20, 33, 61, 255});

        DrawSidebar(&sidebar, font);

        for (int i = 0; i < sidebar.itemCount; i++)
            UpdateSidebarItem(&sidebar.items[i], placedItems, &placedItemsCount, font);

        UpdateSidebarScroll(&sidebar);

        for (int i = 0; i < placedItemsCount; i++)
        {
            UpdateDraggableBox(&placedItems[i], placedItems, &placedItemsCount, &sidebar);
            DrawDraggableBox(&placedItems[i]);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}