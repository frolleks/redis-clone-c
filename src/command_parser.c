#include "command_parser.h"
#include "resp_decode.h"
#include "resp_encode.h"
#include "store.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *parse_command(char *command) {
    int array_size;
    printf("Parsing command: %s\n", command);

    char **decoded_array =
        decode_array(command, &array_size); // Decode command as RESP array
    if (decoded_array == NULL) {
        printf("DEBUG: Failed to decode array. Command format might be "
               "incorrect.\n");
        return encode_error("Invalid command format");
    }

    printf("DEBUG: Command decoded as array with %d elements.\n", array_size);
    if (array_size < 1) {
        printf(
            "DEBUG: Decoded array is empty. Expected at least one element.\n");
        free(decoded_array); // Freeing memory if decode_array allocated it,
                             // check decode_array’s behavior
        return encode_error("Invalid command format");
    }

    // Print each element of the array for debugging
    for (int i = 0; i < array_size; i++) {
        if (decoded_array[i] != NULL) {
            printf("DEBUG: Element %d: %s\n", i, decoded_array[i]);
        } else {
            printf("DEBUG: Element %d is NULL\n", i);
        }
    }

    // The first element is the command (e.g., GET, SET, DEL, INFO)
    char *action = decoded_array[0];
    char *response = NULL;

    // Handle SET command (expects exactly 2 arguments: key and value)
    if (strcmp(action, "SET") == 0) {
        if (array_size == 3) {
            char *key = decoded_array[1];
            char *value = decoded_array[2];
            set(key, value);
            response =
                encode_simple_string("OK"); // RESP simple string for success
        } else {
            response = encode_error(
                "SET command requires exactly 2 arguments: key and value");
        }
    }
    // Handle GET command (expects exactly 1 argument: key)
    else if (strcmp(action, "GET") == 0) {
        if (array_size == 2) {
            char *key = decoded_array[1];
            const char *value = get(key);
            if (value) {
                response = encode_bulk_string(value);
            } else {
                response = encode_error("Key not found");
            }
        } else {
            response =
                encode_error("GET command requires exactly 1 argument: key");
        }
    }
    // Handle DEL command (expects exactly 1 argument: key)
    else if (strcmp(action, "DEL") == 0) {
        if (array_size == 2) {
            char *key = decoded_array[1];
            del(key);
            response = encode_simple_string("OK");
        } else {
            response =
                encode_error("DEL command requires exactly 1 argument: key");
        }
    }
    // Handle INFO command (expects no arguments)
    else if (strcmp(action, "INFO") == 0) {
        if (array_size == 1) {
            response = encode_simple_string(
                "INFO command executed"); // Replace with actual info response
                                          // if needed
        } else {
            response = encode_error("INFO command takes no arguments");
        }
    }
    // Unknown command
    else {
        response = encode_error("Unknown command");
    }

    // Clean up decoded array
    for (int i = 0; i < array_size; i++) {
        free(decoded_array[i]);
    }
    free(decoded_array);

    return response;
}