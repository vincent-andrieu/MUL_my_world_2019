/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** my_world
*/

#include "my_button.h"
#include "my_world.h"

my_button_shape_t *get_button_shape(sfVector2f pos, sfVector2f scale)
{
    my_button_shape_t *my_button = malloc(sizeof(my_button_shape_t));

    if (!my_button)
        return NULL;
    my_button->pos = pos;
    my_button->scale = scale;
    my_button->toggle = 0;
    my_button->name = NULL;
    my_button->texture = NULL;
    return my_button;
}

int set_texture_button(my_button_shape_t *my_button, char *path_one,
    char *path_two, char *path_three)
{
    my_button->texture = malloc(sizeof(sfTexture *) * NB_TEXTURE);
    if (!my_button->texture)
        return EXIT_ERROR;
    my_button->texture[0] = sfTexture_createFromFile(path_one, NULL);
    my_button->texture[1] = sfTexture_createFromFile(path_two, NULL);
    my_button->texture[2] = sfTexture_createFromFile(path_three, NULL);

    if (!my_button->texture[0] || !my_button->texture[1] ||
        !my_button->texture[3])
        return EXIT_ERROR;
    return EXIT_SUCCESS;
}

void button_shape_destroy(my_button_shape_t *my_button)
{
    if (my_button->name) {
        free(my_button->name);
        sfFont_destroy(my_button->font);
        sfText_destroy(my_button->text);
    }
    sfClock_destroy(my_button->clock_start);
    free(my_button);
}

void button_refresh_stat(my_button_shape_t *my_button, sfRenderWindow *window)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window);
    int temp = my_button->toggle;

    if (mouse_pos.x >= my_button->pos.x &&
    mouse_pos.x <= my_button->pos.x + my_button->scale.x &&
    mouse_pos.y >= my_button->pos.y &&
    mouse_pos.y <= my_button->pos.y + my_button->scale.y) {
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            my_button->is_pressed = true;
            temp = 2;
        }
        else
            temp = 1;
    } else
        temp = 0;
    button_status(temp, my_button);
}

void button_display(my_button_shape_t *my_button, sfRenderWindow *window)
{
    sfSprite* sprite = sfSprite_create();

    sfSprite_setTexture(sprite, my_button->texture[my_button->toggle], sfTrue);
    sfSprite_setScale(sprite, (sfVector2f) {3, 3});
    sfSprite_setPosition(sprite, my_button->pos);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    sfSprite_destroy(sprite);
    if (my_button->name)
        sfRenderWindow_drawText(window, my_button->text, NULL);
    if (my_button->is_activate)
        sfSound_play(my_button->sound.sound);
}