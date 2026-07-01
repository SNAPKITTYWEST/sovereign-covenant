#include <stdio.h>
#include <string.h>
#include "sovereign_covenant.h"

int main(void) {
    printf("Step 1: Creating hash...\n");
    char h[HASH_BUF_LEN];
    covenant_hash_string("test", h);
    printf("Step 2: Hash = %s\n", h);
    
    printf("Step 3: Creating temple...\n");
    Temple t;
    temple_create(&t, "Test", "Chicago");
    printf("Step 4: Temple created\n");
    
    printf("Step 5: Creating sheik...\n");
    GrandSheik s;
    sheik_create(&s, "Test Sheik");
    printf("Step 6: Sheik created\n");
    
    printf("All done.\n");
    return 0;
}
