

/* 
 * File:   main.c
 * Author: azarias
 *
 * Created on 11 janvier 2017, 21:18
 */

#include <stdio.h>
#include <stdlib.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>

#include <time.h>
#include "game.h"
#include "config.h"
#include "utils.h"

void processRectPos(sfIntRect *rect)
{
	rect->left = (rect->left + rect->width);
	if (rect->left >= (rect->width * 5)) {
		rect->left = 0;
		rect->top = (rect->top + rect->height) % (rect->height * 2);
	}

}

int main(int argc, char** argv)
{
	srand(time(NULL)); //Rand number init
	main_configuration = config_create();
	game_font = sfFont_createFromFile("tron.ttf");

	game *m_game = game_create();
	game_init_player_pos(m_game);
	sfVector2i window_size = game_window_size(m_game);

	sfVideoMode mode = {0, 0, 32};
	mode.width = window_size.x;
	mode.height = window_size.y;
	sfRenderWindow * window = sfRenderWindow_create(mode, "TRON", sfClose, NULL);
	m_game->window = window;

	//Check if they're not at the same spot
	for (int i = 0; i < m_game->players->size; i++) {
		player *p = list_get(m_game->players, i);
		printf("Player %d => x: %d, y : %d\n", p->id, p->position.x, p->position.y);
	}


	sfRenderWindow_setFramerateLimit(window, 20);

	//Test game copy & destroy
	game *g_cpy = game_copy(m_game);
	game_destroy(g_cpy);

	//	sfMusic_play(music);
	while (sfRenderWindow_isOpen(window)) {
		game_main_loop(m_game);
	}


	game_destroy(m_game);
	sfRenderWindow_destroy(window);
	config_destroy(main_configuration);
	sfFont_destroy(game_font);
	return(EXIT_SUCCESS);
}

