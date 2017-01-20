

#include <SFML/Audio/SoundStatus.h>
#include <SFML/Audio/Music.h>
#include <stdio.h>

#include "utils.h"
#include "config.h"

#ifdef UTILS_H

sfFont *game_font;

sfVector2i utils_vector_random(int max_x, int max_y)
{
	sfVector2i vect;
	vect.x = rand() % max_x;
	vect.y = rand() % max_y;
	return vect;
}

sfBool utils_vector_same(const sfVector2i v1, const sfVector2i v2)
{
	return v1.x == v2.x && v1.y == v2.y;
}

sfColor utils_int_to_color(int id)
{
	//Add more color if more players
	switch (id) {
	case 0:
		return sfMagenta;
	case 1:
		return sfBlue;
	case 2:
		return sfRed;
	case 3:
		return sfCyan;
	default:
		return sfYellow;
	}
}

sfBool utils_is_valid_key(sfKeyCode keyCode)
{
	return keyCode == sfKeyUp || keyCode == sfKeyDown || keyCode == sfKeyLeft || keyCode == sfKeyRight;
}

sfVector2i utils_update_pos(sfVector2i pos, direction dir)
{
	sfVector2i vec = {pos.x, pos.y};
	switch (dir) {
	case DIR_UP:
		vec.y--;
		break;
	case DIR_DOWN:
		vec.y++;
		break;
	case DIR_LEFT:
		vec.x--;
		break;
	case DIR_RIGHT:
		vec.x++;
	}
	return vec;
}

sfRectangleShape *utils_rec_from_xy_color(int x, int y, int color)
{
	sfRectangleShape *rect = sfRectangleShape_create();
	int cell_side = config_get_int(main_configuration, "CELL_SIDE", 16);
	sfVector2f rectSize = {cell_side, cell_side};
	sfRectangleShape_setSize(rect, rectSize);

	sfVector2f rectPos = {cell_side*x, cell_side * y};
	sfRectangleShape_setPosition(rect, rectPos);

	sfRectangleShape_setFillColor(rect, utils_int_to_color(color));

	return rect;
}

sfText *utils_create_text(char* content, int charSize)
{
	sfText *text = sfText_create();

	sfText_setCharacterSize(text, charSize);
	sfText_setString(text, content);

	//Memory leak ... 
	sfText_setFont(text, game_font);
	return text;
}

sfBool utils_text_contains(sfText* text, float x, float y)
{
	sfFloatRect bound = sfText_getGlobalBounds(text);
	return sfFloatRect_contains(&bound, x, y);
}

void utils_hilight_text(sfText *text, sfMouseMoveEvent ev)
{
	if (utils_text_contains(text, ev.x, ev.y)) {
		sfText_setColor(text, sfRed);
	} else {
		sfText_setColor(text, sfWhite);
	}
}

void utils_toggle_music(sfMusic* music)
{
	sfSoundStatus status = sfMusic_getStatus(music);
	if (status == sfPlaying) {
		sfMusic_pause(music);
	} else {
		sfMusic_play(music);
	}
}

void *utils_safe_malloc(size_t size, char *reason)
{
	void *mall = malloc(size);
	if (mall == NULL) {
		fprintf(stderr, "Failed when doing a malloc, reason : %s\n", reason);
		exit(EXIT_FAILURE);
	}
	return mall;
}

void utils_safe_free(void* to_free)
{
	if (to_free != NULL) {
		free(to_free);
	} else {
		fprintf(stderr, "Tried to free NULL");
	}
}

#endif