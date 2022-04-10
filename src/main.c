#include "raylib/raylib.h"
#include "raylib/raymath.h"

#include "ecs.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define GLSL_VERSION 330

// TODO: merge player and planet struct into some entity structure. Maybe try
//       to remplement and ecs.
//
// TODO: Add some sort of DEBUG infomation. Could be useful to lean some sort
//       of compile instruction to toggle a DEBUG definition. Also could
//       change the makefile.
// typedef struct {
//     Texture2D texture;

//     Vector2 position;
//     Vector2 velocity;

//     float roation;
//     float rotationVelocity;
// } Player;

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

void update_planet (Planet* planet);
void render_planet (Planet* planet);

RenderTexture2D target;

Shader shader;

//Player player;
Planet planet;
Entity player;

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
    planet.texture = LoadTexture("res/planets/planet1.png");

    add_kinimatic_component (
        &player, 
        (Vector2) { 
            SCREEN_WIDTH / 2 - 16, 
            SCREEN_HEIGHT / 2 - 16
        },
        0.0f
    );

    add_texture_renderer_component (
        &player,
        "res/kenny_simplespace/ship_b.png",
        WHITE
    );

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
        kinimatic_component_set_angluar_velocity (&player, 5);
    }
    if (IsKeyDown(KEY_A)) {
        kinimatic_component_set_angluar_velocity (&player, -5);
    }
    if (IsKeyDown(KEY_W)) {
        kinimatic_component_set_velocity (
            &player, 
            (Vector2) { 
                5 * sin(kinimatic_component_get_angle(&player) * DEG2RAD), 
                -5 * cos (kinimatic_component_get_angle(&player) * DEG2RAD) 
            }
        );
    }

    if (IsKeyReleased(KEY_D)) {
        kinimatic_component_set_angluar_velocity(&player, 0);
    }
    if (IsKeyReleased(KEY_A)) {
        kinimatic_component_set_angluar_velocity(&player, 0);
    }

    if (IsKeyReleased (KEY_W)) {
        kinimatic_component_set_velocity (&player, (Vector2) { 0, 0 });
    }
}

void update () {
    poll_input ();

    update_planet(&planet);
    //update_player(&player);
    kinimatic_component_update(&player);
}

void render () {
    // TODO: see if I could move this into init. This seems like somthing that
    //       does not need to be run on each render call.
    BeginTextureMode(target);

        ClearBackground((Color) { 17, 17, 17 });
        DrawRectangle (0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

    EndTextureMode ();

    BeginDrawing();

        ClearBackground((Color) { 17, 17, 17 });

            BeginShaderMode(shader);

                DrawTextureRec(
                    target.texture, 
                    (Rectangle) {0, 0, (float)target.texture.width, (float)-target.texture.height}, 
                    (Vector2) { 0.0f, 0.0f }, 
                    WHITE
                );
            
            EndShaderMode();

        render_planet(&planet);

        texture_renderer_component_render (&player);

    EndDrawing();
}

void clean_up () {
    UnloadShader(shader);

    UnloadRenderTexture (target);

    free_entity(&player);

    UnloadTexture (planet.texture);

    CloseWindow();
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