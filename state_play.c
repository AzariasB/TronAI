

#include "game.h"
#include "state_play.h"
#include "AI.h"


#ifdef STATE_PLAY_H

void render_player(game *g, sfVector2i pos, int p_id)
{
	sfRectangleShape *rect = utils_rec_from_xy_color(pos.x, pos.y, p_id);
	sfRenderWindow_drawRectangleShape(g->window, rect, NULL);
	sfRectangleShape_destroy(rect);
}

state_play *state_play_create()
{
	state_play *state = utils_safe_malloc(sizeof(state_play), "Creating state play");
	state->super = game_state_create("play");
	state->super->pause = &state_play_pause;
	state->super->init = &state_play_init;
	state->super->draw = &state_play_draw;
	state->super->handle_event = &state_play_handle_event;
	state->super->resume = &state_play_resume;
	state->super->update = &state_play_update;


	state->end_text = utils_create_text("Game ended", 50);
	sfVector2f text_position = {10, 10}; //To center on the screen
	sfText_setPosition(state->end_text, text_position);

	return state;
}

state_play* state_play_copy(state_play* s)
{
	state_play *copy = utils_safe_malloc(sizeof(state_play), "Copying state play");
	copy->super = game_state_copy(s->super);
	copy->end_text = sfText_copy(s->end_text);
	return copy;
}

void state_play_destroy(state_play* s)
{
	game_state_destroy(s->super);
	sfText_destroy(s->end_text);
	free(s);
}

void state_play_init(game* g)
{

}

void state_play_draw(game* g)
{
	for (int y = 0; y < g->board->height; y++) {
		for (int x = 0; x < g->board->width; x++) {
			sfVector2i pos = {x, y};
			if (!grid_is_empty(g->board, pos)) {
				int val = grid_at(g->board, pos);
				render_player(g, pos, val);
			}
		}
	}

	if (g->ended) {
		state_play *st_play = g->st_manager->st_play;
		sfRenderWindow_drawText(g->window, st_play->end_text, NULL);
	}
}

void state_play_pause(game* g)
{
	g->paused = sfTrue;
}

void state_play_resume(game* g)
{
	g->paused = sfTrue; //Wait for user input
	audio_manager_change_music(g->audio_manager, MUSIC_PLAY);
}

void state_play_update(game* g)
{
	if (!g->paused && !g->ended) {
		list *l = g->players;
		for (int i = 0; i < l->size; i++) {
			player *p = list_get(l, i);
			if (!p->is_dead) {
				if (p->is_AI) {
					grid *g_cpy = grid_copy(g->board);
					list *p_copy = list_copy(l, &player_copy);
					p->m_direction = ia_play(g_cpy, p_copy, p->id);
					grid_destroy(g_cpy);
					list_destroy(p_copy, &player_destroy);
				}
				player_update(p);
				if (game_player_is_dead(g, p)) {
					state_play_player_died(g, p);
				} else {
					game_add_player_pos(g, p);
				}
			}
		}
		grid_print(g->board);
	}
}

void state_play_handle_event(game* g, sfEvent event)
{
	int ai_only = config_get_int(main_configuration, "AI_ONLY", 0);
	if (event.type == sfEvtKeyPressed) {
		if (g->ended) {
			if (event.key.code == sfKeyEscape) {
				game_reset(g);
				game_change_state(g, "menu");
			}
		} else if (event.key.code == sfKeySpace) {
			game_change_state(g, "pause");
		} else if (utils_is_valid_key(event.key.code)) {
			g->paused = sfFalse;
			if (ai_only) {
				return;
			}
			player *human = list_get(g->players, 0); //The first player is the human player
			human->m_direction = direction_from_key_code(event.key.code);
		}
	}
}

void state_play_player_died(game* g, player* p)
{
	grid_clear_value(g->board, p->id);
	p->is_dead = sfTrue;
	int alive_players = list_count(g->players, &player_is_alive);
	if (alive_players <= 1) {
		g->ended = sfTrue;
		g->paused = sfTrue;
		//Show the winner
		player *winner = list_first(g->players, &player_is_alive);
		char *text = winner->is_AI ? "IA Won !" : "You won !";
		state_play *st_play = g->st_manager->st_play;
		sfText_setString(st_play->end_text, text);
		audio_manager_play_sound(g->audio_manager, winner->is_AI ? SOUND_NEGATIVE2 : SOUND_POSITIVE);
	} else {
		audio_manager_play_sound(g->audio_manager, SOUND_NEGATIVE1);
	}

}

#endif