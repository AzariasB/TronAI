

#include "state_menu.h"
#include "game.h"
#include "audio_manager.h"

#ifdef STATE_MENU_H

void state_menu_clicked_exit(game *g, sfEvent ev)
{
	game_exit(g);
}

void state_menu_clicked_play(game *g, sfEvent ev)
{
	game_reset(g);
	game_change_state(g, "play");
}

state_menu *state_menu_create()
{
	state_menu *st_menu = utils_safe_malloc(sizeof(state_menu), "Creating menu state");
	st_menu->super = game_state_create("menu");

	st_menu->super->pause = &state_menu_pause;
	st_menu->super->init = &state_menu_init;
	st_menu->super->draw = &state_menu_draw;
	st_menu->super->handle_event = &state_menu_handle_event;
	st_menu->super->resume = &state_menu_resume;
	st_menu->super->update = &state_menu_update;

	st_menu->menu = menu_create("Menu");
	menu_add_text(st_menu->menu, "Play", &state_menu_clicked_play);
	menu_add_text(st_menu->menu, "Exit", &state_menu_clicked_exit);


	return st_menu;
}

void state_menu_init(game *g)
{

}

void state_menu_pause(game *g)
{
	//    state_menu *m = g->st_manager->st_menu;
}

void state_menu_resume(game *g)
{
	audio_manager_change_music(g->audio_manager, MUSIC_MENU);
	//    state_menu *m = g->st_manager->st_menu;
}

void state_menu_handle_event(game *g, sfEvent event)
{
	state_menu *st_menu = g->st_manager->st_menu;
	menu_handle_event(st_menu->menu, g, event);
}

void state_menu_draw(game* g)
{
	state_menu *m = g->st_manager->st_menu;
	menu_draw(m->menu, g->window);
}

void state_menu_update(game *g)
{

}

state_menu *state_menu_copy(state_menu* s)
{
	state_menu *copy = utils_safe_malloc(sizeof(state_manager), "copying state menu");
	copy->super = game_state_copy(s->super);
	copy->menu = menu_copy(s->menu);

	return copy;
}

void state_menu_destroy(state_menu *s)
{
	game_state_destroy(s->super);
	menu_destroy(s->menu);
	free(s);
}

#endif
