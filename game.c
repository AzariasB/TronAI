


#include "game.h"
#include "game_state.h"
#include "state_play.h"
#include "state_pause.h"
#include "config.h"

#ifdef GAME_H

game *game_create()
{
	game *g = utils_safe_malloc(sizeof(game), "game creation");

	int player_number = config_get_int(main_configuration, "PLAYERS", 2);
	g->players = list_create();

	for (int i = 0; i < player_number; i++) {
		player *p = NULL;
		if (i == 0) {
			p = player_create(i, sfFalse);
		} else {
			p = player_create(i, sfTrue);
		}
		list_push(g->players, p);
	}

	int board_width = config_get_int(main_configuration, "BOARD_WIDTH", 30);
	int board_height = config_get_int(main_configuration, "BOARD_HEIGHT", 20);
	int cell_side = config_get_int(main_configuration, "CELL_SIDE", 16);
	int screen_width = cell_side * board_width;
	int screen_height = cell_side * board_height;
	config_set_int(main_configuration, "SCREEN_WIDTH", screen_width);
	config_set_int(main_configuration, "SCREEN_HEIGHT", screen_height);

	g->board = grid_create(board_width, board_height);
	g->ended = sfFalse;
	g->paused = sfTrue;
	g->st_manager = state_manager_create();
	g->audio_manager = audio_manager_create();
	(*g->st_manager->current_state->resume)(g);

	g->background_texture = sfTexture_createFromFile("textures/background.png", NULL);
	g->background_sprite = sfSprite_create();

	sfSprite_setTexture(g->background_sprite, g->background_texture, sfFalse);

	sfFloatRect background_bounds = sfSprite_getGlobalBounds(g->background_sprite);
	sfVector2f background_scale = {screen_width / background_bounds.width, screen_height / background_bounds.height};
	sfSprite_setScale(g->background_sprite, background_scale);

	g->background_glow_texture = sfTexture_createFromFile("textures/glow.png", NULL);
	g->background_glow_sprite = sfSprite_create();

	sfSprite_setTexture(g->background_glow_sprite, g->background_glow_texture, sfFalse);
	sfFloatRect glow_bounds = sfSprite_getGlobalBounds(g->background_glow_sprite);
	sfVector2f glow_scale = {screen_width / glow_bounds.width, screen_height / glow_bounds.height};
	sfSprite_setScale(g->background_glow_sprite, glow_scale);

	return g;
}

sfVector2i game_window_size(const game* g)
{
	int cell_side = config_get_int(main_configuration, "CELL_SIDE", 16);
	sfVector2i size = {g->board->width * cell_side, g->board->height * cell_side};
	return size;
}

void game_main_loop(game* g)
{
	sfEvent ev;
	while (sfRenderWindow_pollEvent(g->window, &ev)) {
		if (ev.type == sfEvtClosed) {
			sfRenderWindow_close(g->window);
		} else if (ev.type == sfEvtKeyPressed && ev.key.code == sfKeyM) {
			//Toggle game music
		} else {
			(*g->st_manager->current_state->handle_event)(g, ev);

		}
	}
	(*g->st_manager->current_state->update)(g);
	sfRenderWindow_clear(g->window, sfBlack);
	sfRenderWindow_drawSprite(g->window, g->background_sprite, NULL);
	sfRenderWindow_drawSprite(g->window, g->background_glow_sprite, NULL);
	(*g->st_manager->current_state->draw)(g);
	sfRenderWindow_display(g->window);

}

sfBool game_player_is_dead(game* g, player* p)
{
	if (p->is_dead || !grid_contains(g->board, p->position)) {
		return sfTrue;
	}
	return !game_cell_is_empty(g, p->position);
}

sfBool game_cell_is_empty(game* g, sfVector2i pos)
{
	if (!grid_contains(g->board, pos)) {
		return sfFalse;
	}
	return grid_at(g->board, pos) == -1;
}

void game_init_player_pos(game* g)
{
	for (int i = 0; i < g->players->size; i++) {
		sfBool already_taken = sfFalse;
		sfVector2i rand_pos = utils_vector_random(g->board->width, g->board->height);
		do {
			already_taken = sfFalse;
			rand_pos = utils_vector_random(g->board->width, g->board->height);
			for (int j = 0; j < i; j++) {
				player *p = list_get(g->players, j);
				already_taken = utils_vector_same(p->position, rand_pos) || already_taken;

			}
		} while (already_taken);
		player *p = list_get(g->players, i);
		p->position = rand_pos;
		grid_set(g->board, p->position, p->id);
	}
}

void game_reset_players(game* g)
{
	for (int i = 0; i < g->players->size; i++) {
		player *p = list_get(g->players, i);
		sfVector2i position = {-1, -1};
		p->position = position;
		p->is_dead = sfFalse;
		p->m_direction = DIR_DOWN;
	}
}

void game_add_player_pos(game* g, player* p)
{
	grid_set(g->board, p->position, p->id);
}

void game_change_state(game* g, char* state_name)
{
	state_manager_change_state(g->st_manager, g, state_name);
}

void game_reset(game* g)
{
	grid_reset(g->board);
	game_reset_players(g);
	game_init_player_pos(g);
	g->ended = sfFalse;
}

game *game_copy(const game* g)
{
	game *copy = utils_safe_malloc(sizeof(game), "Copying game");
	copy->background_texture = sfTexture_copy(g->background_texture);
	copy->background_sprite = sfSprite_copy(g->background_sprite);
	copy->background_glow_texture = sfTexture_copy(g->background_glow_texture);
	copy->background_glow_sprite = sfSprite_copy(g->background_glow_sprite);
	copy->board = grid_copy(g->board);
	copy->players = list_copy(g->players, &player_copy);
	copy->paused = g->paused;
	copy->ended = g->ended;
	copy->st_manager = state_manager_copy(g->st_manager);
	copy->audio_manager = NULL; //can't copy audio_manager because can't copy sfMusic
	copy->window = g->window;
	return copy;
}

void game_destroy(game* g)
{
	grid_destroy(g->board);
	list_destroy(g->players, &player_destroy);
	state_manager_destroy(g->st_manager);
	if (g->audio_manager != NULL) {
		audio_manager_destroy(g->audio_manager);
	}
	sfSprite_destroy(g->background_sprite);
	sfTexture_destroy(g->background_texture);
	sfSprite_destroy(g->background_glow_sprite);
	sfTexture_destroy(g->background_glow_texture);
	free(g);
	g = 0;
}

void game_exit(game* g)
{
	sfRenderWindow_close(g->window);
}

#endif
