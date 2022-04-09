#include "raylib/raylib.h"
#include "raylib/raymath.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define GLSL_VERSION 330

// TODO: merge player and planet struct into some entity structure. Maybe try
//       to remplement and ecs.
//
// TODO: Add some sort of DEBUG infomation. Could be useful to lean some sort
//       of compile instruction to toggle a DEBUG definition. Also could
//       change the makefile.
typedef struct {
    Texture2D texture;

    Vector2 position;
    Vector2 velocity;

    float roation;
    float rotationVelocity;
} Player;

typedef struct {
    Texture2D texture;

    float frameWidth;
    float frameHeight;
    Rectangle frameRec;

    int frameCounter;
    int currentFrame;
    int currentLine;

    float radius;
} Planet;

void init ();
void poll_input ();
void update ();
void render ();
void clean_up ();

void render_player(Player* player);
void update_player (Player* player);

void update_planet (Planet* planet);
void render_planet (Planet* planet);

RenderTexture2D target;

Shader shader;

Player player;
Planet planet;

int main () {
    init();

    while (!WindowShouldClose()) {
        update();
        render();
    }

    clean_up();

    return 0;
}

// TODO: clean up
void init () {
    InitWindow (SCREEN_WIDTH, SCREEN_HEIGHT, "LD50 Game");
    SetTargetFPS (60);

    // creates star bg.
    target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);

    shader = LoadShader(0, TextFormat("res/shaders/star.fs", GLSL_VERSION));
    float screenSize[2] = { (float) GetScreenWidth(), (float) GetScreenHeight() };
    SetShaderValue(shader, GetShaderLocation(shader, "iResolution"), &screenSize, SHADER_UNIFORM_VEC3);

    float rng_time[1] = { (float) GetFrameTime() };
    SetShaderValue(shader, GetShaderLocation(shader, "iTime"), &rng_time, SHADER_UNIFORM_FLOAT);

    // loads texture assets
    player.texture = LoadTexture("res/kenny_simplespace/ship_b.png");
    planet.texture = LoadTexture("res/planets/planet1.png");

    // defines player
    player.position = (Vector2) { SCREEN_WIDTH / 2 - player.texture.width / 2, SCREEN_HEIGHT / 2 - player.texture.height / 2};
    player.velocity = (Vector2) { 0, 0 };

    player.roation = 0.0f;
    player.rotationVelocity = 0.0f;

    // defines planet
    // This feels wrong, but it works.
    planet.texture.width *= 2;
    planet.texture.height *= 2;
    planet.radius = 98;

    planet.frameWidth = (float)(planet.texture.width / 15);
    planet.frameHeight = (float) (planet.texture.height / 15);
    planet.frameRec = (Rectangle) { 0, 0, planet.frameWidth, planet.frameHeight };
}

void poll_input () {
    if (IsKeyDown(KEY_D)) {
        player.rotationVelocity = 5;
    }
    if (IsKeyDown(KEY_A)) {
        player.rotationVelocity = -5;
    }
    if (IsKeyDown(KEY_W)) {
        player.velocity = (Vector2) { 5 * sin(player.roation * DEG2RAD), -5 * cos (player.roation * DEG2RAD) };
    }

    if (IsKeyReleased(KEY_D)) {
        player.rotationVelocity = 0;
    }
    if (IsKeyReleased(KEY_A)) {
        player.rotationVelocity = 0;
    }

    if (IsKeyReleased (KEY_W)) {
        player.velocity = (Vector2) { 0, 0 };
    }
}

void update () {
    poll_input ();

    update_planet(&planet);
    update_player(&player);
}

void render () {
    // TODO: see if I could move this into init. This seems like somthing that
    //       does not need to be run on each render call.
    BeginTextureMode(target);

        ClearBackground(BLACK);
        DrawRectangle (0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

    EndTextureMode ();

    BeginDrawing();

        ClearBackground(BLACK);

            BeginShaderMode(shader);

                DrawTextureRec(
                    target.texture, 
                    (Rectangle) {0, 0, (float)target.texture.width, (float)-target.texture.height}, 
                    (Vector2) { 0.0f, 0.0f }, 
                    WHITE
                );
            
            EndShaderMode();

        render_planet(&planet);
        render_player(&player);

    EndDrawing();
}

void clean_up () {
    UnloadShader(shader);

    UnloadRenderTexture (target);
    UnloadTexture (player.texture);
    UnloadTexture (planet.texture);

    CloseWindow();
}

void render_player (Player* player) {
    DrawTexturePro (
        player->texture,
        (Rectangle) { 0, 0, player->texture.width, player->texture.height },
        (Rectangle) { player->position.x, player->position.y, player->texture.width, player->texture.height },
        (Vector2) { player->texture.width / 2, player->texture.height / 2 },
        player->roation,
        WHITE
    );

    DrawCircleLines (
        player->position.x, 
        player->position.y, 
        13, 
        GREEN
    );
}

void update_player (Player* player) {
    player->position = Vector2Add(player->position, player->velocity);
    player->roation = player->roation + player->rotationVelocity;
}

void update_planet (Planet* planet) {
    planet->frameCounter++;
    if (planet->frameCounter > 2) {
        planet->currentFrame ++;

        if (planet->currentFrame >= 15) {
            planet->currentFrame = 0;
            planet->currentLine++;

            if (planet->currentLine >= 15) {
                planet->currentLine = 0;
            }
        }

        planet->frameCounter = 0;
    }

    planet->frameRec.x = planet->frameWidth * planet->currentFrame;
    planet->frameRec.y = planet->frameHeight * planet->currentLine;
}

void render_planet (Planet* planet) {

    DrawTextureRec (
        planet->texture, 
        planet->frameRec, 
        (Vector2) { SCREEN_WIDTH / 2 - planet->frameRec.width / 2, SCREEN_HEIGHT / 2 - planet->frameRec.height / 2 }, 
        WHITE
    );

    DrawCircleLines (
        SCREEN_WIDTH / 2,
        SCREEN_HEIGHT / 2, 
        planet->radius, 
        GREEN
    );
};