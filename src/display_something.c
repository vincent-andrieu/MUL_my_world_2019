/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** my_world
*/

#include "my_world.h"

my_sprite_s get_sprite(void)
{
    my_sprite_s my_struct = {0};

    my_struct.sprite = sfSprite_create();
    my_struct.texture = sfTexture_createFromFile("./ressources/tree.png", NULL);
    sfSprite_setTexture(my_struct.sprite, my_struct.texture, sfTrue);
    my_struct.list = make_list();
    my_struct.select = false;
    return my_struct;
}

void display_something(assets_t *assets, sfVector2f **map, my_world_t *my_world)
{
    sfVector2f pos;
    list_t *end = my_world->tree.list;

    while (end) {
        pos = map[end->pos.y][end->pos.x];
        pos.x -= my_world->zoom * DISPLAY_X * 0.5;
        pos.y -= my_world->zoom * DISPLAY_Y;
        sfSprite_setScale(my_world->tree.sprite,
            (sfVector2f) {my_world->zoom, my_world->zoom});
        sfSprite_setPosition(my_world->tree.sprite, pos);
        sfRenderWindow_drawSprite(assets->window, my_world->tree.sprite, NULL);
        end = end->next;
    }
}

static sfVector2i get_tree_select(assets_t *assets, sfVector2f **map, my_world_t *world)
{
    sfVector2i mouse = sfMouse_getPositionRenderWindow(assets->window);

    for (int y = 0; y < world->scale.y; y++)
        for (int x = 0; x < world->scale.x; x++)
            if (map[y][x].x - mouse.x > -MOUSE_ACC
            && map[y][x].x - mouse.x < MOUSE_ACC
            && map[y][x].y - mouse.y > -MOUSE_ACC
            && map[y][x].y - mouse.y < MOUSE_ACC) {
                return (sfVector2i) {x, y};
            }
    return (sfVector2i) {-1, -1};
}

static void destroy_it(list_t *list, sfVector2i coords)
{
    list_t *prev = list->next;
    if (!prev)
        return;
    list_t *end = prev->next;

    while (end) {
        if (end->pos.x == coords.x && end->pos.y == coords.y) {
            prev->next = end->next;
            free(end);
            return;
        }
        prev = end;
        end = end->next;
    }
}

void my_tree_gest(assets_t *assets, sfVector2f **map, my_world_t *my_world)
{
    sfVector2i tree;

    if (sfMouse_isButtonPressed(sfMouseLeft) && my_world->tree.select) {
        tree = get_tree_select(assets, map, my_world);
        if (tree.x != -1 && tree.y != -1)
            if (my_world->map[tree.y][tree.x] > WATER_LEVEL)
                add_one(my_world->tree.list, tree);
    }
    else if (sfMouse_isButtonPressed(sfMouseRight)) {
        tree = get_tree_select(assets, map, my_world);
        if (tree.x != -1 && tree.y != -1)
            destroy_it(my_world->tree.list, tree);
    }
}