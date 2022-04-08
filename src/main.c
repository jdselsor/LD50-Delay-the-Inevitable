#include "raylib/raylib.h"
#include "raylib/raymath.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Texture2D texture;
} Player;

void init ();
void update ();
void render ();
void clean_up ();

void draw_player(Player* player);
void update_player (Player* player);

Player player;

int main () {
    init();

    while (!WindowShouldClose()) {

        update();
        render();
    }

    clean_up();

    return 0;
}

void init () {
    InitWindow (SCREEN_WIDTH, SCREEN_HEIGHT, "LD50 Game");
    SetTargetFPS (60);

    player.texture = LoadTexture("res/kenny_simplespace/ship_b.png");
    player.position = (Vector2) { SCREEN_WIDTH / 2 - player.texture.width / 2, SCREEN_HEIGHT / 2 - player.texture.height / 2};
    player.velocity = (Vector2) { 0, 1.0 };
}

void update () {
    update_player(&player);
}

void render () {
    BeginDrawing();

    ClearBackground(BLACK);

    draw_player(&player);

    EndDrawing();
}

void clean_up () {
    UnloadTexture (player.texture);

    CloseWindow();
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