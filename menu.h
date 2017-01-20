


/* 
 * File:   menu.h
 * Author: azarias
 *
 * Created on 19 janvier 2017, 19:03
 */

#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics/Types.h>
#include <SFML/Window/Event.h>

#include "list.h"

typedef struct game game;

typedef struct menu {
    sfText* title;
    sfCircleShape *pointer;
    list *sub_choices;
    int current_choice;
} menu;

/**
 * Creates a menu with the given title
 * and no sub-choices
 * 
 * @param title the title to display at the top of the windows
 * @return the created menu
 */
menu *menu_create(char *title);

/**
 * Copies the menu
 * 
 * @param to_copy the menu to copy
 * @return The copied menu
 */
menu *menu_copy(const menu* to_copy);

/**
 * Destroys the menu
 * 
 * @param to_destroy the menu to destroy
 */
void menu_destroy(menu *to_destroy);

/**
 * Adds a new text to the menu
 * When the text is chosen
 * (clicked or pressed enter)
 * the given action is trigerred
 * 
 * @param m the menu
 * @param text the text to add
 * @param action the function to call when the text is selected
 */
void menu_add_text(menu *m, char *text, void (*action)(game *g, sfEvent ev));


/**
 * Called to update the menu
 * based on its events
 * 
 * @param m the menu
 * @param g the game
 * @param ev the event
 */
void menu_handle_event(menu *m, game* g, sfEvent ev);


/**
 * Draws the menu elements
 * in the given render window
 * 
 * @param m the menu to draw
 * @param target the render window in which to draw
 */
void menu_draw(menu *m, sfRenderWindow *target);

#endif /* MENU_H */

