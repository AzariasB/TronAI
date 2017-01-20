
/* 
 * File:   config.h
 * Author: azarias
 *
 * Created on 19 janvier 2017, 19:14
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "list.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct game game;

typedef struct config
{
    list *configs;
} config;

extern config *main_configuration;

/**
 * Creates a config structure
 * parsed the config file
 * and add all the values to its list
 * 
 * @return the created config
 */
config * config_create();

/**
 * Copies the config
 * 
 * @param to_copy the config to copy
 * @return the copied config
 */
config *config_copy(const config* to_copy);

/**
 * Destroys the config
 * 
 * @param to_destroy the config to destroy
 */
void config_destroy(config* to_destroy);

/**
 * Returns the value associated with
 * the given key
 * if the value is not found,
 * returns NULL
 * 
 * @param conf the configuration
 * @param key the key to find
 * @param fallback the value to return if the key is not found
 * @return the value corresponding to the key ( NULL if not found)
 */
char *config_get(config *conf, char *key, char *fallback);

/**
 * Same as confi_get, but casts
 * the char* to int before returning int
 * If the value is not a valid int, or 
 * is not found , returns NULL
 * 
 * @param conf the configuration
 * @param key the key of the value to found
 * @param fallbac the value to return if not found
 * @return the value, as an int
 */
int config_get_int(config *conf, char *key, int fallback);

/**
 * Sets the given value with the given key
 * If the key already exist, its value will
 * be overwritten
 * 
 * @param the configuration
 * @param key the key 
 * @param value the value
 */
void config_set(config *conf, char *key, char *value);


/**
 * Same as config_set
 * but casts the int into
 * a char* before setting it
 * if the key already exists,
 * its value will be overrided
 * 
 * @param conf the configuration
 * @param key the key to add
 * @param value the value
 */
void config_set_int(config *conf, char *key, int value);

/**
 * Saves the given configuration to a file
 * 
 * @param conf the configuration to save
 */
void config_save(const config* conf);

#endif /* CONFIG_H */

