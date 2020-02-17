/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** my_world
*/

#include <math.h>
#include "my.h"
#include "graph.h"
#include "my_world.h"

sfVector2f project_iso_point(int x, int y, int z)
{
    sfVector2f my_2d_vector = {0};

    my_2d_vector.x = cos(ANGLE_X) * x - cos(ANGLE_X) * y;
    my_2d_vector.y = sin(ANGLE_Y) * y + sin(ANGLE_Y) * x - z;
    return my_2d_vector;
}

sfVector2f **create_2d_map(int **three_d_map)
{
    sfVector2f **my_map = malloc(sizeof(sfVector2f *) * (MAP_Y + 1));

    if (!my_map)
        return NULL;
    my_map[MAP_Y] = NULL;
    for (int i = 0; i < MAP_Y; i++) {
        my_map[i] = malloc(sizeof(sfVector2f) * MAP_X);
        if (!my_map[i])
            return NULL;
    }
    for (int y = 0; y < MAP_Y; y++) {
        for (int x = 0; x < MAP_X; x++)
            my_map[y][x] = project_iso_point(x * DISPLAY_X, y * DISPLAY_Y,
                three_d_map[y][x]);
    }
    return my_map;
}

sfVertexArray *create_line(sfVector2f *point1, sfVector2f *point2)
{
    sfVertexArray *vertex_array = sfVertexArray_create();
    sfVertex vertex1 = {.position = *point1, .color = sfWhite};
    sfVertex vertex2 = {.position = *point2, .color = sfWhite};
    sfVertexArray_append(vertex_array, vertex1);
    sfVertexArray_append(vertex_array, vertex2);
    sfVertexArray_setPrimitiveType ( vertex_array , sfLinesStrip ) ;
    return(vertex_array);
}

int draw_2d_map(sfRenderWindow *window, sfVector2f **map)
{
    sfVertexArray *vertexarray;

    for (int y = 0; y < MAP_Y - 1; y++) {
        for (int x = 0; x < MAP_X - 1; x++) {
            vertexarray = create_line (&map[y][x], &map[y][x + 1]);
            sfRenderWindow_drawVertexArray(window, vertexarray, NULL);
            sfVertexArray_destroy(vertexarray);
            vertexarray = create_line (&map[y + 1][x], &map[y][x]);
            sfRenderWindow_drawVertexArray(window, vertexarray, NULL);
            sfVertexArray_destroy(vertexarray);
        }
    }
    return EXIT_SUCCESS;
}