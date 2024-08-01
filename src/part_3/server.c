#include <stdlib.h>

#include "fcgi_stdio.h"

int main() {
    while( FCGI_Accept() >= 0) {
        printf("Concept-Type: text/plain\n\n");
        printf("Hello world!\n");
    }
    return 0;
}
