#include "server.h"
#include "store.h"
#include <stdio.h>

int main() {
    initialize_server(6379);
    init_store();
    return 0;
}