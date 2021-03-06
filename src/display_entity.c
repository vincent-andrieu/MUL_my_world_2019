/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** my_world
*/

#include "my_world.h"

static void display_dog(assets_t *assets, sfVector2f **map,
    my_world_t *my_world)
{
    sfVector2f pos = {0};

    dog_finder(my_world);
    while (!(my_world->dog.pos.y < my_world->scale.y - 1))
        my_world->dog.pos.y--;
    while (!(my_world->dog.pos.x < my_world->scale.x - 1))
        my_world->dog.pos.x--;
    pos = map[my_world->dog.pos.y][my_world->dog.pos.x];
    pos.x -= my_world->zoom * DISPLAY_X;
    pos.y -= my_world->zoom * DISPLAY_Y;
    sfSprite_setScale(my_world->dog.sprite,
        (sfVector2f) {my_world->zoom / 2, my_world->zoom / 2});
    sfSprite_setPosition(my_world->dog.sprite, pos);
    sfRenderWindow_drawSprite(assets->window, my_world->dog.sprite, NULL);
}

void display_player(sfRenderWindow *window, sfVector2f **map,
                    my_world_t *my_world)
{
    sfVector2f pos;

    while (!(my_world->tree.list->pos.y < my_world->scale.y - 1))
        my_world->tree.list->pos.y--;
    while (!(my_world->tree.list->pos.x < my_world->scale.x - 1))
        my_world->tree.list->pos.x--;
    pos = map[my_world->tree.list->pos.y][my_world->tree.list->pos.x];
    pos.x -= my_world->zoom * DISPLAY_X * 0.5;
    pos.y -= my_world->zoom * DISPLAY_Y;
    sfSprite_setScale(my_world->tree.sprite_jaaj,
        (sfVector2f) {my_world->zoom / 2, my_world->zoom / 2});
    sfSprite_setPosition(my_world->tree.sprite_jaaj, pos);
    sfSprite_setScale(my_world->tree.sprite_fish,
        (sfVector2f) {my_world->zoom / 2, my_world->zoom / 2});
    sfSprite_setPosition(my_world->tree.sprite_fish, pos);
    if (my_world->map[my_world->tree.list->pos.y][my_world->tree.list->pos.x]
    > WATER_LEVEL)
        sfRenderWindow_drawSprite(window, my_world->tree.sprite_jaaj, NULL);
    else
        sfRenderWindow_drawSprite(window, my_world->tree.sprite_fish, NULL);
}

static void display_select(assets_t *assets, sfVector2i pos_map,
    my_world_t *my_world, sfVector2f pos)
{
    if (my_world->map[pos_map.y][pos_map.x] > WATER_LEVEL) {
        sfSprite_setScale(my_world->tree.sprite,
            (sfVector2f) {my_world->zoom, my_world->zoom});
        sfSprite_setPosition(my_world->tree.sprite, pos);
        sfRenderWindow_drawSprite(assets->window, my_world->tree.sprite, NULL);
    }
    else {
        sfSprite_setScale(my_world->tree.sprite_kelp,
            (sfVector2f) {my_world->zoom, my_world->zoom});
        sfSprite_setPosition(my_world->tree.sprite_kelp, pos);
        sfRenderWindow_drawSprite(assets->window, my_world->tree.sprite_kelp,
            NULL);
    }
}

void display_something(assets_t *assets, sfVector2f **map, my_world_t *my_world)
{
    sfVector2f pos;
    list_t *end = my_world->tree.list->next;

    while (end) {
        if (end->pos.y < my_world->scale.y - 1 &&
            end->pos.x < my_world->scale.x - 1) {
            pos = map[end->pos.y][end->pos.x];
            pos.x -= my_world->zoom * DISPLAY_X * 0.5;
            pos.y -= my_world->zoom * DISPLAY_Y;
            display_select(assets, end->pos, my_world, pos);
        }
        end = end->next;
    }
    display_player(assets->window, map, my_world);
    display_dog(assets, map, my_world);
}