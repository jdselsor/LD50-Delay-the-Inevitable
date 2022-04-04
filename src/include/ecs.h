#ifndef ECS_H
#define ECS_H

#include "raylib/raylib.h"

typedef struct {
    Vector2 position;
    Vector2 dimensions;
} TransformComponent;

typedef struct {
    bool isStatic;
    float gravity;
} PhysicsComponent;

typedef struct {
    Color color;
} RenderBoxComponent;

typedef struct {
    TransformComponent *transformComponent;
    PhysicsComponent *physicsComponent;
    RenderBoxComponent *renderBoxComponent;
} Components;

typedef struct {
    unsigned int uuid;
    Components components;
} Entity;

void add_transform_component (Entity *e, Vector2 position, Vector2 dimensions);
void add_physics_component (Entity *e, bool isStatic, float gravity);
void add_render_box_component (Entity *e, Color color);

void free_entity (Entity *e);

// Predefinied Entities

// Component Logic
void render_box (Entity *e);
bool check_collision (Entity *e1, Entity *e2);
void apply_gravity (Entity *e);

#endif