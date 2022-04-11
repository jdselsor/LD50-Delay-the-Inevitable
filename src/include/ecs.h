#ifndef ECS_H
#define ECS_H

#include "raylib/raylib.h"
#include "raylib/raymath.h"

typedef struct {
    Vector2 position;
    Vector2 velocity;

    float angle;
    float angluarVelocity;
} KinimaticComponent;

typedef struct {
    Texture2D texture;
    Color tint;
} SpriteComponent;

typedef struct {
    Texture2D textureSheet;

    int frameCountX;
    int frameCountY;

    float frameWidth;
    float frameHeight;

    Rectangle frameRec;

    int frameCounter;
    int currentFrame;
    int currentLine;

    Color tint;
} AnimatedSpriteComponent;

typedef struct {
    KinimaticComponent* kinimaticComponent;
    SpriteComponent* spriteComponent;
    AnimatedSpriteComponent* animatedSpriteComponent;
} Components;

typedef struct {
    unsigned int id;

    Components components;
} Entity;

void add_kinimatic_component (Entity* entity, Vector2 position, float angle);
void add_sprite_component (Entity* entity, char* pathToTexture, Color tint);
void add_animated_sprite_component (Entity* entity, char* pathToTexture, int frameCountX, int frameCountY, Color tint);
void add_animated_sprite_component_with_texture (Entity* entity, Texture2D textureSheet, int frameCountX, int frameCountY, Color tint);

void free_entity (Entity* entity);

void kinimatic_component_update (Entity* entity);
void kinimatic_component_set_velocity (Entity* entity, Vector2 velocity);
void kinimatic_component_set_angluar_velocity (Entity* entity, float angluar_velocity);
Vector2 kinimatic_component_get_velocity (Entity* entity);
float kinimatic_component_get_angle (Entity* entity);

void sprite_component_render (Entity* entity);

void animated_sprite_component_update (Entity* entity);
void animated_sprite_component_render (Entity* entity);

#endif