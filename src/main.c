#include "raylib/raylib.h"
#include "raylib/raymath.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Texture2D texture;
} Player;

void draw_player(Player* player);
void update_player (Player* player);

int main () {
    InitWindow (SCREEN_WIDTH, SCREEN_HEIGHT, "LD50 Game");
    SetTargetFPS (60);

    Player player;
    player.texture = LoadTexture("res/kenny_simplespace/ship_b.png");
    player.position = (Vector2) { SCREEN_WIDTH / 2 - player.texture.width / 2, SCREEN_HEIGHT / 2 - player.texture.height / 2};
    player.velocity = (Vector2) { 0, 1.0 };

    while (!WindowShouldClose()) {

        update_player(&player);

        BeginDrawing();

        ClearBackground(BLACK);

        draw_player(&player);

        EndDrawing();
    }

    UnloadTexture (player.texture);

    CloseWindow();

    return 0;
}

void draw_player (Player* player) {
    DrawTexture (
        player->texture,
        player->position.x,
        player->position.y,
        WHITE
    );
}

void update_player (Player* player) {
    player->position = Vector2Add(player->position, player->velocity);
}