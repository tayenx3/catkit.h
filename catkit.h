#ifndef CATKIT_H_
#define CATKIT_H_

#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>

// returns an allocated and formatted string. caller must `free()`
char* catk_fmt(const char* fmt, ...);
// returns an allocated and formatted string. caller must `free()`
char* catk_vfmt(const char* fmt, va_list args);

// string builder
typedef struct catk_strbuilder {
    char* data;
    size_t len;
    size_t cap;
} catk_strbuilder_t;

// append formatted string to the builder's buffer
void catk_strbuilder_appendf(catk_strbuilder_t* sb, const char* fmt, ...);
// append formatted string to the builder's buffer
void catk_strbuilder_vappendf(catk_strbuilder_t* sb, const char* fmt, va_list args);
// take ownership of the current string. string builder is fully reset (including capacity). caller must `free()`
char* catk_strbuilder_build(catk_strbuilder_t* sb);
// peek at the current buffer. does not transfer ownership
const char* catk_strbuilder_get(catk_strbuilder_t* sb);
// deep copy of a builder. destination is overwritten but preserved on failure
void catk_strbuilder_copy(catk_strbuilder_t* restrict dest_sb,
                        const catk_strbuilder_t* restrict src_sb);
// free all resources. safe to call multiple times
void catk_strbuilder_destroy(catk_strbuilder_t* sb);
// clears the current buffer but does not free resources or reset capacity. safe to call multiple times
void catk_strbuilder_clear(catk_strbuilder_t* sb);

#ifdef CATKIT_IMPLEMENTATION

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* catk_fmt(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char* buf = catk_vfmt(fmt, args);

    va_end(args);
    return buf;
}

char* catk_vfmt(const char* fmt, va_list args) {
    va_list args_copy;
    va_copy(args_copy, args);
    int needed = vsnprintf(NULL, 0, fmt, args_copy) + 1;
    va_end(args_copy);
    if (needed < 0) return NULL;
    
    char* buf = (char*)malloc(needed);
    if (buf) vsnprintf(buf, needed, fmt, args);
    
    return buf;
}

void catk_strbuilder_appendf(catk_strbuilder_t* sb, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    catk_strbuilder_vappendf(sb, fmt, args);
    va_end(args);
}

void catk_strbuilder_vappendf(catk_strbuilder_t* sb, const char* fmt, va_list args) {
    char* chunk = catk_vfmt(fmt, args);
    if (!chunk) return;

    size_t chunk_len = strlen(chunk);
    size_t new_len = sb->len + chunk_len;
    
    if (sb->cap <= new_len) {
        size_t new_cap = sb->cap ? sb->cap : 1;
        while (new_cap <= new_len) new_cap *= 2;
        sb->cap = new_cap;
        
        char* new_data = realloc(sb->data, sb->cap);
        if (!new_data) {
            free(chunk);
            return;
        }
        sb->data = new_data;
    }

    memcpy(sb->data + sb->len, chunk, chunk_len);
    sb->len += chunk_len;
    sb->data[sb->len] = '\0';
    free(chunk);
}

const char* catk_strbuilder_get(catk_strbuilder_t* sb) {
    return sb->data;
}

char* catk_strbuilder_build(catk_strbuilder_t* sb) {
    char* result = sb->data;
    sb->data = NULL; // not free() because we need the data
    sb->len = 0;
    sb->cap = 0;
    return result;
}

void catk_strbuilder_copy(catk_strbuilder_t* restrict dest_sb,
                        const catk_strbuilder_t* restrict src_sb)
{
    // if src_sb is empty
    if (src_sb->data == NULL || src_sb->len == 0) {
        free(dest_sb->data);
        dest_sb->data = NULL;
        dest_sb->len = 0;
        dest_sb->cap = 0;
        return;
    }
    
    char* new_data = malloc(src_sb->len + 1);
    if (new_data) {
        memcpy(new_data, src_sb->data, src_sb->len);
        new_data[src_sb->len] = '\0';
        free(dest_sb->data);
        dest_sb->data = new_data;
        dest_sb->len = src_sb->len;
        dest_sb->cap = src_sb->len + 1;
    }
    // if copy failed, preserve original data
}

void catk_strbuilder_destroy(catk_strbuilder_t* sb) {
    free(sb->data);
    sb->data = NULL;
    sb->len = 0;
    sb->cap = 0;
}

void catk_strbuilder_clear(catk_strbuilder_t* sb) {
    sb->len = 0;
    if (sb->data) sb->data[0] = '\0';
}

#endif // ifdef CATKIT_IMPLEMENTATION

#endif // ifndef CATKIT_H_