

#include <stdio.h>

#include "config.h"
#include "utils.h"
#include "game.h"

#ifdef CONFIG_H

config *main_configuration;

typedef struct config_line {
	char *key;
	char *value;
} config_line;

config_line *config_line_create(char *key, char *value)
{
	config_line *cl = utils_safe_malloc(sizeof(config_line), "Creating config line");
	cl->key = key;
	cl->value = value;
	return cl;
}

void config_line_set_value(config_line *line, char *value)
{
	free(line->value);
	line->value = strdup(value);
}

void *config_line_copy(void *to_c)
{
	config_line *cl = to_c;
	config_line *copy = utils_safe_malloc(sizeof(config_line), "Copying config line");
	copy->key = strdup(cl->key);
	copy->value = strdup(cl->value);
	return copy;
}

void config_line_destroy(void *to_d)
{
	config_line *to_destroy = to_d;
	free(to_destroy->key);
	free(to_destroy->value);
	free(to_destroy);
	to_d = 0;
}

void config_line_print(void *to_p)
{
	config_line *to_print = to_p;
	printf("key : %s, value :%s\n", to_print->key, to_print->value);
}

config *config_create()
{
	//open file
	//	printf("Creating config\n");
	FILE *f = fopen("config.txt", "a+");
	if (f == NULL) {
		fprintf(stderr, "Could not open/create configuration file");
		exit(EXIT_FAILURE);
	}
	config *conf = utils_safe_malloc(sizeof(config), "Creating configuration");
	conf->configs = list_create();
	while (!feof(f)) {
		//Max key/value size => 80
		char *key_buff = utils_safe_malloc(sizeof(char)* 80, "creating key for config");
		char *value_buff = utils_safe_malloc(sizeof(char)*80, "creating value for config");

		int scanned = fscanf(f, "%s %s", key_buff, value_buff);
		if (scanned != 2) {
			fprintf(stderr, "Incorrect config file formation");
			exit(EXIT_FAILURE);
		}
		char *key = strdup(key_buff);
		char *value = strdup(value_buff);
		free(key_buff);
		free(value_buff);
		config_line *line = config_line_create(key, value);
		list_push(conf->configs, line);
	}
	fclose(f);
	return conf;
}

config *config_copy(const config *conf)
{
	config *copy = utils_safe_malloc(sizeof(config), "Copying config");
	for (int i = 0; i < conf->configs->size; i++) {
		config_line *line = list_get(conf->configs, i);
		config_line *line_copy = config_line_copy(line);
		list_push(copy->configs, line_copy);
	}

	return copy;
}

char *config_get(config* conf, char* key, char * fallback)
{
	for (int i = 0; i < conf->configs->size; i++) {
		config_line *cl = list_get(conf->configs, i);
		if (SAME(cl->key, key)) {
			return cl->value;
		}
	}
	return fallback;
}

int config_get_int(config *conf, char *key, int fallback)
{
	char * found_key = config_get(conf, key, NULL);
	if (found_key != NULL) {
		return atoi(found_key);
	}
	return fallback;
}

void config_set(config* conf, char* key, char* value)
{
	for (int i = 0; i < conf->configs->size; i++) {
		config_line *l = list_get(conf->configs, i);
		if (SAME(l->key, key)) {
			config_line_set_value(l, strdup(value));
			return;
		}
	}
	config_line *nw_config = config_line_create(strdup(key), strdup(value));
	list_push(conf->configs, nw_config);
}

void config_set_int(config* conf, char* key, int value)
{
	char *buff = malloc(sizeof(char) * 80);
	sprintf(buff, "%d", value);
	config_set(conf, key, buff);
	free(buff);
}

void config_save(const config* conf)
{
	//Save
}

void config_destroy(config* to_destroy)
{
	list_destroy(to_destroy->configs, &config_line_destroy);
	free(to_destroy);
	to_destroy = 0;
}

#endif