#ifndef ECS_H
#define ECS_H

#include "raylib/raylib.h"

// typedef struct {
//     Vector2 position;
//     Vector2 scale;
//     float rotation;
// } TransformComponent;

// typedef struct {
//     Vector2 size;
//     Color color;
// } RenderRectangleComponent;

// typedef struct {
//     TransformComponent *transformComponent;
//     RenderRectangleComponent *renderRectangleComponent;
// } Components;

// typedef struct {
//     unsigned int uuid;
//     Components components;
// } Entity;

enum {
    KINIMATIC_COMPONENT_ID = 1,
    TEXTURE_RENDERER_COMPONENT_ID = 2
};

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Vector2 acceration;

    float angle;
    float angluarVelocity;
    float angularAcceration;
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

#endif