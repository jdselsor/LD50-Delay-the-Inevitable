#include <stdlib.h>
#include <stdio.h>

#include "ecs.h"

void add_kinimatic_component (Entity* entity, Vector2 position, float angle) {
    entity->components.kinimaticComponent = malloc(sizeof(KinimaticComponent));

    entity->components.kinimaticComponent->position = position;
    entity->components.kinimaticComponent->velocity = (Vector2) { 0.0f, 0.0f };

    entity->components.kinimaticComponent->angle = angle;
    entity->components.kinimaticComponent->angluarVelocity = 0.0f;
}

void add_sprite_component (Entity* entity, char* pathToTexture, Color tint) {
    entity->components.spriteComponent = malloc(sizeof(SpriteComponent));

    entity->components.spriteComponent->texture = LoadTexture(pathToTexture);
    entity->components.spriteComponent->tint = tint;
}

void add_animated_sprite_component (Entity* entity, char* pathToTexture, Color tint) {
    entity->components.animatedSpriteComponent = malloc(sizeof(AnimatedSpriteComponent));

    entity->components.animatedSpriteComponent->textureSheet = LoadTexture(pathToTexture);
    
    entity->components.animatedSpriteComponent->frameWidth = (float)(entity->components.animatedSpriteComponent->textureSheet.width / 15);
    entity->components.animatedSpriteComponent->frameHeight = (float)(entity->components.animatedSpriteComponent->textureSheet.height / 15);

    entity->components.animatedSpriteComponent->frameRec = (Rectangle) { 
        0, 
        0, 
        entity->components.animatedSpriteComponent->frameWidth, 
        entity->components.animatedSpriteComponent->frameHeight 
    };
}

void add_animated_sprite_component_with_texture (Entity* entity, Texture2D textureSheet, Color tint) {
    entity->components.animatedSpriteComponent = malloc(sizeof(AnimatedSpriteComponent));

    entity->components.animatedSpriteComponent->textureSheet = textureSheet;

    entity->components.animatedSpriteComponent->frameWidth = (float)(entity->components.animatedSpriteComponent->textureSheet.width / 15);
    entity->components.animatedSpriteComponent->frameHeight = (float)(entity->components.animatedSpriteComponent->textureSheet.height / 15);

    entity->components.animatedSpriteComponent->frameRec = (Rectangle) { 
        0, 
        0, 
        entity->components.animatedSpriteComponent->frameWidth, 
        entity->components.animatedSpriteComponent->frameHeight 
    };
}

void free_entity (Entity* entity) {
    if (entity->components.kinimaticComponent) {
        free (entity->components.kinimaticComponent);
    }

    if (entity->components.spriteComponent) {
        UnloadTexture(entity->components.spriteComponent->texture);
        free (entity->components.spriteComponent);
    }

    if (entity->components.animatedSpriteComponent) {
        UnloadTexture(entity->components.animatedSpriteComponent->textureSheet);
        free (entity->components.animatedSpriteComponent);
    }
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

void sprite_component_render (Entity* entity) {
    if (!entity->components.kinimaticComponent || !entity->components.spriteComponent) {
        return;
    }

    Rectangle entitySrcRect = { 
        0, 
        0, 
        entity->components.spriteComponent->texture.width, 
        entity->components.spriteComponent->texture.height 
    };

    Rectangle entityDestRect = {
        entity->components.kinimaticComponent->position.x, 
        entity->components.kinimaticComponent->position.y, 
        entity->components.spriteComponent->texture.width, 
        entity->components.spriteComponent->texture.height 
    };

    DrawTexturePro (
        entity->components.spriteComponent->texture,
        entitySrcRect,
        entityDestRect,
        (Vector2) { 
            entity->components.spriteComponent->texture.width / 2, 
            entity->components.spriteComponent->texture.height / 2 
        },
        entity->components.kinimaticComponent->angle,
        entity->components.spriteComponent->tint
    );
}

void animated_sprite_component_update (Entity* entity) {
    if (!entity->components.animatedSpriteComponent) {
        return;
    }

    entity->components.animatedSpriteComponent->frameCounter++;

    if (entity->components.animatedSpriteComponent->frameCounter > 2) {
        entity->components.animatedSpriteComponent->currentFrame ++;

        // TODO: add number frames and number lines to struct.
        if (entity->components.animatedSpriteComponent->currentFrame >= 15) {
            entity->components.animatedSpriteComponent->currentFrame = 0;
            entity->components.animatedSpriteComponent->currentLine ++;
            
            // TODO: add number frames and number lines to struct.
            if (entity->components.animatedSpriteComponent->currentLine >= 15) {
                entity->components.animatedSpriteComponent->currentFrame = 0;
            }
        }

        entity->components.animatedSpriteComponent->frameCounter = 0;
    }

    entity->components.animatedSpriteComponent->frameRec.x = entity->components.animatedSpriteComponent->frameWidth * entity->components.animatedSpriteComponent->currentFrame;
    entity->components.animatedSpriteComponent->frameRec.y = entity->components.animatedSpriteComponent->frameHeight *entity->components.animatedSpriteComponent->currentLine;
}

// TODO: make so animated sprites can have rotation 'DrawTexturePro'
void animated_sprite_component_render (Entity* entity) {
    if (!entity->components.kinimaticComponent || !entity->components.animatedSpriteComponent) {
        return;
    }

    DrawTextureRec (
        entity->components.animatedSpriteComponent->textureSheet, 
        entity->components.animatedSpriteComponent->frameRec, 
        (Vector2) { 
            entity->components.kinimaticComponent->position.x, 
            entity->components.kinimaticComponent->position.y 
        }, 
        WHITE
    );
}