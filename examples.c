#define CATKIT_IMPLEMENTATION
#include "catkit.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // quick formatting
    char* result = catk_fmt("My name is %s. I am %d years old.", "John Doe", 32);
    printf("%s\n", result);
    free(result);

    // string builder ops
    catk_strbuilder_t sb = {0};
    catk_strbuilder_appendf(&sb, "My name is %s.", "Jane Doe");
    catk_strbuilder_appendf(&sb, " ");
    catk_strbuilder_appendf(&sb, "I am %d years old.", 27);

    catk_strbuilder_t sb2 = {0};
    catk_strbuilder_copy(&sb2, &sb);
    catk_strbuilder_appendf(&sb2, " ");
    catk_strbuilder_appendf(&sb2, "And I like catkit.h.");
    
    char* sb_result = catk_strbuilder_build(&sb);
    printf("%s\n", sb_result);
    free(sb_result);
    const char* sb2_result = catk_strbuilder_get(&sb2);
    printf("%s\n", sb2_result);
    catk_strbuilder_destroy(&sb2);
}