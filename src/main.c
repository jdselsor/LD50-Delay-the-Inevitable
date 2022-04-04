#include "raylib/raylib.h"
#include "ecs.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

int main () {
    InitWindow (SCREEN_WIDTH, SCREEN_HEIGHT, "LD50 Game");
    SetTargetFPS (60);

    Entity rect;
    add_transform_component(&rect, (Vector2) {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, (Vector2) {20, 20});
    add_render_box_component(&rect, LIGHTGRAY);
    add_physics_component (&rect, false, -1.0);


    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        
        apply_gravity(&rect);
        render_box(&rect);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}