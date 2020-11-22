import sys
import pygame

def update_physics(rooms, room_index):

    entities = rooms[room_index[0]][room_index[1]].entities

    for key in entities:

        if entities[key].direction[0] == 0:

            if abs(entities[key].velocity[0]) >= 0.01:

                entities[key].velocity[0] /= 1 + entities[key].drag
            else:

                entities[key].velocity[0] = 0.0
            
        if entities[key].direction[1] == 0:

            if abs(entities[key].velocity[1]) >= 0.01:

                entities[key].velocity[1] /= 1 + entities[key].drag
            else:

                entities[key].velocity[1] = 0.0
            
        collider = pygame.sprite.spritecollideany(entities[key].sprites.sprites()[0], rooms[room_index[0]][room_index[1]].collision_sprites)
        trigger = pygame.sprite.spritecollideany(entities[key].sprites.sprites()[0], rooms[room_index[0]][room_index[1]].trigger_sprites)

        if collider != None:

            if entities[key].sprites.sprites()[0].rect.left < collider.rect.left or entities[key].sprites.sprites()[0].rect.right > collider.rect.right:

                entities[key].position[0] -= entities[key].velocity[0] * (1.0 + entities[key].drag)
                entities[key].velocity[0] = 0.0
                
            if entities[key].sprites.sprites()[0].rect.bottom < collider.rect.bottom or entities[key].sprites.sprites()[0].rect.top > collider.rect.top:
                    
                entities[key].position[1] -= entities[key].velocity[1] * (1.0 + entities[key].drag)
                entities[key].velocity[1] = 0.0

        entities[key].position[0] += entities[key].velocity[0]
        entities[key].position[1] += entities[key].velocity[1]
        
        entities[key].sprites.update(entities[key].position[0], entities[key].position[1], entities[key].direction[0])

        if trigger != None:

            if trigger.direction == 0:

                temp = room_index[0]
                room_index[0] -= 1
                rooms[room_index[0]][room_index[1]].entities[key] = entities[key]
                del rooms[temp][room_index[1]].entities[key]
                rooms[room_index[0]][room_index[1]].entities[key].position[0] = rooms[room_index[0]][room_index[1]].doors_leaving_position[1][0]
                rooms[room_index[0]][room_index[1]].entities[key].position[1] = rooms[room_index[0]][room_index[1]].doors_leaving_position[1][1] - 10
            elif trigger.direction == 1:

                temp = room_index[0]
                room_index[0] += 1
                rooms[room_index[0]][room_index[1]].entities[key] = entities[key]
                del rooms[temp][room_index[1]].entities[key]
                rooms[room_index[0]][room_index[1]].entities[key].position[0] = rooms[room_index[0]][room_index[1]].doors_leaving_position[0][0]
                rooms[room_index[0]][room_index[1]].entities[key].position[1] = rooms[room_index[0]][room_index[1]].doors_leaving_position[0][1] + 10
            elif trigger.direction == 2:

                temp = room_index[1]
                room_index[1] += 1
                rooms[room_index[0]][room_index[1]].entities[key] = entities[key]
                del rooms[room_index[0]][temp].entities[key]
                rooms[room_index[0]][room_index[1]].entities[key].position[0] = rooms[room_index[0]][room_index[1]].doors_leaving_position[3][0] + 10
                rooms[room_index[0]][room_index[1]].entities[key].position[1] = rooms[room_index[0]][room_index[1]].doors_leaving_position[3][1]
            else:

                temp = room_index[1]
                room_index[1] -= 1
                rooms[room_index[0]][room_index[1]].entities[key] = entities[key]
                del rooms[room_index[0]][temp].entities[key]
                rooms[room_index[0]][room_index[1]].entities[key].position[0] = rooms[room_index[0]][room_index[1]].doors_leaving_position[2][0] - 10
                rooms[room_index[0]][room_index[1]].entities[key].position[1] = rooms[room_index[0]][room_index[1]].doors_leaving_position[2][1]
            
            break