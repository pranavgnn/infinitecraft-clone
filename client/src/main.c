#include <stdio.h>
#include "raylib.h"

#include "components/box.h"
#include "components/sidebar.h"

DraggableBox placedItems[1000];
int placedItemsCount = 0;

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "InfiniteCraft Clone - ADS Project");
    MaximizeWindow();

    Font font = LoadFontEx("resources/fonts/Roboto-Medium.ttf", 32, 0, 250);
    if (!font.texture.id)
        printf("Error loading font\n");

    Sidebar sidebar = CreateSidebar();
    AddSidebarItem(&sidebar, "Earth");
    AddSidebarItem(&sidebar, "Water");
    AddSidebarItem(&sidebar, "Fire");
    AddSidebarItem(&sidebar, "Air");
    AddSidebarItem(&sidebar, "Wind");

    DraggableBox boxes[3];
    boxes[0] = CreateDraggableBox(1, 250, 100, 150, 50, "Water", font);
    boxes[1] = CreateDraggableBox(2, 450, 100, 150, 50, "Fire", font);
    boxes[2] = CreateDraggableBox(3, 650, 100, 150, 50, "Earth", font);

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground((Color){20, 33, 61, 255});

        DrawSidebar(&sidebar, font);

        for (int i = 0; i < 3; i++)
        {
            UpdateDraggableBox(&boxes[i]);
            DrawDraggableBox(&boxes[i]);
        }

        EndDrawing();
    }

    CloseWindow(); // Close the window and clean up

    return 0;
}
