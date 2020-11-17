import pygame

def UpdatePhysics(entities, room, roomIndex):

    for entity in entities:

        if entity.simulating:

            if entity.direction[0] == 0:

                entity.velocity[0] /= 1 + entity.drag
            
            if entity.direction[1] == 0:

                entity.velocity[1] /= 1 + entity.drag
            
            collider = pygame.sprite.spritecollideany(entity.sprites.sprites()[0], room.collisionSprites)
            trigger = pygame.sprite.spritecollideany(entity.sprites.sprites()[0], room.triggerSprites)

            if collider != None:

                if entity.sprites.sprites()[0].rect.left < collider.rect.left or entity.sprites.sprites()[0].rect.right > collider.rect.right:

                    entity.position[0] -= entity.velocity[0] * (1 + entity.drag)
                    entity.velocity[0] = 0
                
                if entity.sprites.sprites()[0].rect.bottom < collider.rect.bottom or entity.sprites.sprites()[0].rect.top > collider.rect.top:
                    
                    entity.position[1] -= entity.velocity[1] * (1 + entity.drag)
                    entity.velocity[1] = 0
            
            if trigger != None:

                if trigger.direction == 0:

                    roomIndex[0] -= 1
                elif trigger.direction == 1:

                    roomIndex[0] += 1
                elif trigger.direction == 2:

                    roomIndex[1] += 1
                else:

                    roomIndex[1] -= 1

            entity.position[0] += entity.velocity[0]
            entity.position[1] += entity.velocity[1]