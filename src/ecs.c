#include <stdlib.h>

#include "ecs.h"

void add_kinimatic_component (Entity* entity, Vector2 position, float angle) {
    entity->components.kinimaticComponent = malloc(sizeof(KinimaticComponent));

    entity->components.kinimaticComponent->position = position;
    entity->components.kinimaticComponent->velocity = (Vector2) { 0.0f, 0.0f };

    entity->components.kinimaticComponent->angle = angle;
    entity->components.kinimaticComponent->angluarVelocity = 0.0f;
}

void add_texture_renderer_component (Entity* entity, char* pathToTexture, Color tint) {
    entity->components.textureRendererComponent = malloc(sizeof(TextureRendererComponent));

    entity->components.textureRendererComponent->texture = LoadTexture(pathToTexture);
    entity->components.textureRendererComponent->tint = tint;
}

void free_entity (Entity* entity) {
    if (entity->components.kinimaticComponent) {
        free (entity->components.kinimaticComponent);
    }

    if (entity->components.textureRendererComponent) {
        UnloadTexture(entity->components.textureRendererComponent->texture);
        free (entity->components.textureRendererComponent);
    }
}

void texture_renderer_component_render (Entity* entity) {
    if (!entity->components.kinimaticComponent || !entity->components.textureRendererComponent) {
        return;
    }

    Rectangle entitySrcRect = { 
        0, 
        0, 
        entity->components.textureRendererComponent->texture.width, 
        entity->components.textureRendererComponent->texture.height 
    };

    Rectangle entityDestRect = {
        entity->components.kinimaticComponent->position.x, 
        entity->components.kinimaticComponent->position.y, 
        entity->components.textureRendererComponent->texture.width, 
        entity->components.textureRendererComponent->texture.height 
    };

    DrawTexturePro (
        entity->components.textureRendererComponent->texture,
        entitySrcRect,
        entityDestRect,
        (Vector2) { 
            entity->components.textureRendererComponent->texture.width / 2, 
            entity->components.textureRendererComponent->texture.height / 2 
        },
        entity->components.kinimaticComponent->angle,
        entity->components.textureRendererComponent->tint
    );
}

void kinimatic_component_update (Entity* entity) {
    if (!entity->components.kinimaticComponent) {
        return;
    }

    entity->components.kinimaticComponent->position = Vector2Add(
        entity->components.kinimaticComponent->position, 
        entity->components.kinimaticComponent->velocity
    );

    entity->components.kinimaticComponent->angle += entity->components.kinimaticComponent->angluarVelocity;
}

void kinimatic_component_set_velocity (Entity* entity, Vector2 velocity) {
    if (!entity->components.kinimaticComponent) {
        return;
    }

    entity->components.kinimaticComponent->velocity = velocity;
}

void kinimatic_component_set_angluar_velocity (Entity* entity, float angluarVelocity) {
    if (!entity->components.kinimaticComponent) {
        return;
    }

    entity->components.kinimaticComponent->angluarVelocity = angluarVelocity;
}

Vector2 kinimatic_component_get_velocity (Entity* entity) {
    if (!entity->components.kinimaticComponent) {
        return (Vector2) { 999999, 999999 };
    }

    return entity->components.kinimaticComponent->velocity;
}

float kinimatic_component_get_angle (Entity* entity) {
    if (!entity->components.kinimaticComponent) {
        return 99999.99999;
    }

    return entity->components.kinimaticComponent->angle;
}