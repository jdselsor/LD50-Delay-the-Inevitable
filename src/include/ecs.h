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
} TextureRendererComponent;

typedef struct {
    KinimaticComponent* kinimaticComponent;
    TextureRendererComponent* textureRendererComponent;
} Components;

typedef struct {
    unsigned int uuid;

    Components components;
} Entity;

void add_kinimatic_component (Entity* entity, Vector2 position, float angle);
void add_texture_renderer_component (Entity* entity, char* pathToTexture, Color tint);

void free_entity (Entity* entity);

void texture_renderer_component_render (Entity* entity);

void kinimatic_component_update (Entity* entity);
void kinimatic_component_set_velocity (Entity* entity, Vector2 velocity);
void kinimatic_component_set_angluar_velocity (Entity* entity, float angluar_velocity);
Vector2 kinimatic_component_get_velocity (Entity* entity);
float kinimatic_component_get_angle (Entity* entity);

#endif