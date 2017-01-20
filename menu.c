

#include "game.h"
#include "menu.h"

#ifdef MENU_H

typedef struct text_action {
    sfText *text;
    void (*action)(game *g, sfEvent ev);
} text_action;

text_action *text_action_create(char *text, void (*action)(game *g, sfEvent ev), int text_height) {
    text_action *ta = utils_safe_malloc(sizeof (text_action), "Creating text action");
    ta->text = utils_create_text(text, 75);
    sfVector2f position = {50, text_height};
    sfText_setPosition(ta->text, position);
    ta->action = action;
    return ta;
}

void text_action_deselect(text_action *ta) {
    sfText_setColor(ta->text, sfWhite);
}

void text_action_select(text_action *ta) {
    sfText_setColor(ta->text, sfRed);
}

void *text_action_copy(void* to_copy) {
    text_action *ta_to_copy = to_copy;
    text_action *copy = utils_safe_malloc(sizeof (text_action), "Copying text action");
    copy->text = sfText_copy(ta_to_copy->text);
    copy->action = copy->action;

    return copy;
}

void text_action_destroy(void *to_destroy) {
    text_action *ta_to_destroy = to_destroy;
    sfText_destroy(ta_to_destroy->text);
    free(ta_to_destroy);
    ta_to_destroy = 0;
}

menu * menu_create(char* title) {
    menu *m = utils_safe_malloc(sizeof (menu), "Creating menu");
    m->current_choice = 0;
    m->sub_choices = list_create();
    m->title = utils_create_text(title, 100);
    m->pointer = sfCircleShape_create();
    sfCircleShape_setPointCount(m->pointer, 3);
    sfCircleShape_rotate(m->pointer, 90);
    sfColor select_color = {0, 44, 117, 255};

    sfCircleShape_setFillColor(m->pointer, select_color);
    sfCircleShape_setOutlineColor(m->pointer, sfRed);
    sfCircleShape_setOutlineThickness(m->pointer, 1);
    sfCircleShape_setRadius(m->pointer, 15);


    sfVector2f position = {0, 0};

    sfText_setPosition(m->title, position);

    return m;
}

menu * menu_copy(const menu* to_copy) {
    menu *copy = utils_safe_malloc(sizeof (menu), "Copying menu");
    copy->current_choice = to_copy->current_choice;
    copy->sub_choices = list_copy(to_copy->sub_choices, &text_action_copy);
    copy->title = sfText_copy(to_copy->title);
    copy->pointer = sfCircleShape_copy(to_copy->pointer);
    return copy;
}

void menu_destroy(menu* to_destroy) {
    list_destroy(to_destroy->sub_choices, &text_action_destroy);
    sfText_destroy(to_destroy->title);
    sfCircleShape_destroy(to_destroy->pointer);
    free(to_destroy);
    to_destroy = 0;
}

void menu_add_text(menu* m, char* text, void(*action)(game*, sfEvent)) {
    int text_height = (m->sub_choices->size + 2) * 75;
    text_action *text_a = text_action_create(text, action, text_height);
    list_push(m->sub_choices, text_a);
    if (m->sub_choices->size == 1) {//Just added the first text
        text_action_select(text_a);
        sfVector2f select_position = {40, 75 * 2 + (75 / 2)};
        sfCircleShape_setPosition(m->pointer, select_position);
    }
}

void menu_handle_event(menu* m, game *g, sfEvent ev) {
    //Check if changed, and if so, play a little sound
    int choice_before = m->current_choice;
    if (ev.type == sfEvtKeyPressed && (ev.key.code == sfKeyUp || ev.key.code == sfKeyDown || ev.key.code == sfKeyReturn)) {
        text_action *ta = list_get(m->sub_choices, m->current_choice);
        text_action_deselect(ta);
        if (ev.key.code == sfKeyReturn) {
            (*ta->action)(g, ev); //callback
        } else if (ev.key.code == sfKeyDown) {
            m->current_choice = MIN(m->current_choice + 1, m->sub_choices->size - 1);
        } else /* sfKeydown */ {
            m->current_choice = MAX(m->current_choice - 1, 0);
        }
        text_action *nw_ta = list_get(m->sub_choices, m->current_choice);
        text_action_select(nw_ta);
    } else if (ev.type == sfEvtMouseMoved) {
        for (int i = 0; i < m->sub_choices->size; i++) {
            text_action *ta = list_get(m->sub_choices, i);
            if (utils_text_contains(ta->text, ev.mouseMove.x, ev.mouseMove.y)) {
                text_action *old_ta = list_get(m->sub_choices, m->current_choice);
                text_action_deselect(old_ta);
                m->current_choice = i;
                text_action_select(ta);
            }

        }
    } else if (ev.type == sfEvtMouseButtonPressed) {
        for (int i = 0; i < m->sub_choices->size; i++) {
            text_action *ta = list_get(m->sub_choices, i);
            if (utils_text_contains(ta->text, ev.mouseButton.x, ev.mouseButton.y)) {
                (*ta->action)(g, ev);
            }
        }
    }

    if (choice_before != m->current_choice) {
        audio_manager_play_sound(g->audio_manager, SOUND_CLICK2);
        sfVector2f select_position = {40, 75 * (m->current_choice + 2) + (75 / 2)};
        sfCircleShape_setPosition(m->pointer, select_position);
    }
}

void menu_draw(menu *m, sfRenderWindow *target) {
    sfRenderWindow_drawText(target, m->title, NULL);


    for (int i = 0; i < m->sub_choices->size; i++) {
        text_action *ta = list_get(m->sub_choices, i);
        sfRenderWindow_drawText(target, ta->text, NULL);
    }
    sfRenderWindow_drawCircleShape(target, m->pointer, NULL);
}

#endif