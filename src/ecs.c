#include <stdlib.h>

#include "ecs.h"

void add_transform_component (Entity *e, Vector2 position, Vector2 dimensions) {
    e->components.transformComponent = malloc (sizeof (TransformComponent));

    e->components.transformComponent->position = position;
    e->components.transformComponent->dimensions = dimensions;
}

void add_physics_component (Entity *e, bool isStatic, float gravity) {
    e->components.physicsComponent = malloc (sizeof (PhysicsComponent));

    e->components.physicsComponent->isStatic = isStatic;
    e->components.physicsComponent->gravity = gravity;
}

void add_render_box_component (Entity *e, Color color) {
    e->components.renderBoxComponent = malloc (sizeof (RenderBoxComponent));

    e->components.renderBoxComponent->color = color;
}

void free_entity (Entity *e) {
    if (e->components.transformComponent) {
        free (e->components.transformComponent);
    }

    if (e->components.physicsComponent) {
        free (e->components.physicsComponent);
    }

    if (e->components.renderBoxComponent) {
        free (e->components.renderBoxComponent);
    }
}

void render_box (Entity *e) {
    if (!e->components.transformComponent || !e->components.renderBoxComponent) {
        return;
    }

    DrawRectanglePro ((Rectangle) { e->components.transformComponent->position.x, e->components.transformComponent->position.y, e->components.transformComponent->dimensions.x, e->components.transformComponent->dimensions.y}, (Vector2) { 0, 0 }, 0.0f, e->components.renderBoxComponent->color);
}

bool check_collision (Entity *e1, Entity *e2) {
    if (!e1->components.transformComponent || !e1->components.physicsComponent) {
        return false;
    }

    if (!e2->components.transformComponent || !e2->components.physicsComponent) {
        return false;
    }

    if (e1->components.transformComponent->position.x < e2->components.transformComponent->position.x + e2->components.transformComponent->dimensions.y 
        && e1->components.transformComponent->position.x + e1->components.transformComponent->dimensions.x > e2->components.transformComponent->position.x
        && e1->components.transformComponent->position.y < e2->components.transformComponent->dimensions.y + e2->components.transformComponent->dimensions.y
        && e1->components.transformComponent->position.y + e1->components.transformComponent->dimensions.y < e2->components.transformComponent->dimensions.y) {
            return true;
    }
    return false;
}

void apply_gravity (Entity *e) {
    if (!e->components.transformComponent || !e->components.physicsComponent) {
        return;
    }

    e->components.transformComponent->position.y -= e->components.physicsComponent->gravity;
}