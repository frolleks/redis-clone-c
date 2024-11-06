#include "store.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static GHashTable *hash = NULL;

void init_store() {
    if (hash == NULL) {
        hash = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, g_free);
    }
}

void set(const char *key, const char *value) {
    init_store();
    g_hash_table_insert(hash, g_strdup(key), g_strdup(value));
    printf("SET %s %s\n", key, value);
}

const char *get(const char *key) {
    init_store();
    return g_hash_table_lookup(hash, key);
}

void del(const char *key) {
    init_store();
    g_hash_table_remove(hash, key);
    printf("DEL %s\n", key);
}

void destroy_store() {
    if (hash != NULL) {
        g_hash_table_destroy(hash);
        hash = NULL;
    }
}
