/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** manage textures
*/

#include "my_world.h"

static sfVertexArray *display_texture(sfVector2f *point1, sfVector2f *point2,
    sfVector2f *point3)
{
    sfVertexArray *vertex_array = sfVertexArray_create();
    sfVertex vertex1 = {.position = *point1, .color = sfWhite};
    sfVertex vertex2 = {.position = *point2, .color = sfWhite};
    sfVertex vertex3 = {.position = *point3, .color = sfWhite};

    sfVertexArray_append(vertex_array, vertex1);
    sfVertexArray_append(vertex_array, vertex2);
    sfVertexArray_append(vertex_array, vertex3);
    sfVertexArray_setPrimitiveType(vertex_array , sfTriangleStrip);
    return vertex_array;
}

void calc_textures(my_world_t *my_world, sfVector2f **map,
                    sfVector2i coord, sfRenderWindow *window)
{
    sfVertexArray *line;

    if (coord.y < my_world->scale.y - 1 && coord.x < my_world->scale.x - 1) {
        line = display_texture(&map[coord.y][coord.x],
            &map[coord.y + 1][coord.x], &map[coord.y][coord.x + 1]);
        sfRenderWindow_drawVertexArray(window, line, get_map_texture(
                my_world->map[coord.y][coord.x], &my_world->textures));
        sfVertexArray_destroy(line);
        line = display_texture(&map[coord.y + 1][coord.x + 1],
            &map[coord.y + 1][coord.x], &map[coord.y][coord.x + 1]);
        sfRenderWindow_drawVertexArray(window, line, get_map_texture(
                my_world->map[coord.y][coord.x], &my_world->textures));
        sfVertexArray_destroy(line);
    }
}

sfRenderStates *get_map_texture(int level, textures_t *textures)
{
    if (level < DIRT_LEVEL)
        return &textures->water;
    if (level < GRASS_LEVEL)
        return &textures->dirt;
    if (level < STONE_LEVEL)
        return &textures->grass;
    if (level < SNOW_LEVEL)
        return &textures->stone;
    return &textures->snow;
}