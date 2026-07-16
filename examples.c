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
    
    catk_strbuilder_t sb3 = {0};
    catk_strbuilder_appendc(&sb3, 'a');
    catk_strbuilder_appendc(&sb3, 'b');
    catk_strbuilder_appendc(&sb3, 'c');
    printf("%s\n", catk_strbuilder_get(&sb3));
    catk_strbuilder_insertc(&sb3, 1, '1');
    catk_strbuilder_insertc(&sb3, 3, '2');
    catk_strbuilder_insertc(&sb3, 5, '3');
    char* sb3_result = catk_strbuilder_build(&sb3);
    printf("%s\n", sb3_result);
    free(sb3_result);
    // reuseable
    catk_strbuilder_appendf(&sb3, "ab", 2);
    char* sb3_result2 = catk_strbuilder_build(&sb3);
    printf("%s\n", sb3_result2);
    free(sb3_result2);
}