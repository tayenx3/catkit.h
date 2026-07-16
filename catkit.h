/*
 * catkit.h - v0.1.0-alpha.1 - public domain
 * 
 *   MIT license - see [LICENSE](LICENSE) file for full details
 *   SPDX-License-Identifier: MIT
 * 
 *   compatible with: C99 and later
 *   (C89 support is not guaranteed)
 * 
 * # flags
 * 
 * - CATKIT_IMPLEMENTATION - enables function definitions. only declarations are included by default
 * - CATKIT_STRIP_PREFIX - strip the catk_ prefixes from typenames and function names
 * 
 * # redefinable macros
 * 
 * - CATKIT_MALLOC(size) - which malloc() catkit.h will use
 * - CATKIT_REALLOC(block, size) - which realloc() catkit.h will use
 * - CATKIT_FREE(block) - which free() catkit.h will use
 * 
 * # basic usage
 * 
 * check out [examples.c](examples.c) file for examples
 * 
 * # catkit.h's versioning rule
 * 
 * catkit.h's versioning follows [SemVer](https://semver.org)
 * 
 *   vMAJOR.MINOR.PATCH[-PRERELEASE]
 * 
 * - MAJOR versions are inherently incompatible with eachother.
 *   incremented when the changes breaks existing code
 *   this means a 1-line change can be a MAJOR increment
 * - MINOR versions are backward compatible not always forward compatible.
 *   incremented when new stuff are added but does not break backward compatibility
 *   this means a 1000-line change can be a MINOR increment
 * - PATCH versions are compatible with any other patch of the MINOR version it's in.
 *   incremented when bugs are fixed
 * - PRERELEASE tags tells you how 'ready' catkit.h is to use. here's the tags:
 *   - alpha:    core features implemented OR partially-implemented.
 *               API is not frozen and can change or break
 *   - beta:     core features implemented, fairly tested.
 *               API is considered stable but edge-case bugs are expected
 *   - rc:       core features implemented and frozen.
 *               only critical bugs exist and will be fixed before the final release
 *   - (no tag): stable release. can be used in good faith
 */

#ifndef CATKIT_H_
#define CATKIT_H_
#define CATKIT_VERSION "v0.1.0-alpha.1"
#ifdef _WIN32
    #ifndef _CRT_SECURE_NO_WARNINGS
        #define _CRT_SECURE_NO_WARNINGS (1)
    #endif // _CRT_SECURE_NO_WARNINGS
#endif //  _WIN32

#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>

#ifndef CATKIT_MALLOC
#define CATKIT_MALLOC(size) malloc(size)
#endif // CATKIT_MALLOC

#ifndef CATKIT_REALLOC
#define CATKIT_REALLOC(block, size) realloc(block, size)
#endif // CATKIT_REALLOC

#ifndef CATKIT_FREE
#define CATKIT_FREE(block) free(block)
#endif // CATKIT_FREE

#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L
    #error "catkit.h requires a C99 compiler or later"
#endif

// returns an allocated and formatted string. caller must `free()`
char* catk_fmt(const char* fmt, ...);
// returns an allocated and formatted string from a vararg list. caller must `free()`
char* catk_vfmt(const char* fmt, va_list args);

// string builder
typedef struct catk_strbuilder {
    char* data;
    size_t len;
    size_t cap;
} catk_strbuilder_t;

// initiate the string builder with a formatted string. overrwrites the destination but preserved on failure
void catk_strbuilder_initf(catk_strbuilder_t* sb, const char* fmt, ...);
// initiate the string builder with a formatted string with a vararg list. overrwrites the destination but preserved on failure
void catk_strbuilder_vinitf(catk_strbuilder_t* sb, const char* fmt, va_list args);
// initiate the string builder with the supplied string with an upper limit. overrwrites the destination but preserved on failure
void catk_strbuilder_initn(catk_strbuilder_t* sb, const char* data, const size_t count);
// append formatted string to the builder's buffer
void catk_strbuilder_appendf(catk_strbuilder_t* sb, const char* fmt, ...);
// append formatted string to the builder's buffer by a vararg list
void catk_strbuilder_vappendf(catk_strbuilder_t* sb, const char* fmt, va_list args);
// append string with an upper limit to the builder's buffer
void catk_strbuilder_appendn(catk_strbuilder_t* sb, const char* str, const size_t count);
// append character to the builder's buffer
void catk_strbuilder_appendc(catk_strbuilder_t* sb, const char ch);
// insert formated string into the builder's buffer at a position
void catk_strbuilder_insertf(catk_strbuilder_t* sb, const size_t pos, const char* fmt, ...);
// insert formated string into the builder's buffer by a vararg list at a position
void catk_strbuilder_vinsertf(catk_strbuilder_t* sb, const size_t pos, const char* fmt, va_list args);
// insert string with an upper limit to the builder's buffer at a position
void catk_strbuilder_insertn(catk_strbuilder_t* sb, const size_t pos, const char* str, const size_t count);
// insert character to the builder's buffer at a position
void catk_strbuilder_insertc(catk_strbuilder_t* sb, const size_t pos, const char ch);
// take ownership of the current string. string builder is fully reset (including capacity). caller must `free()`
char* catk_strbuilder_build(catk_strbuilder_t* sb);
// peek at the current buffer. does not transfer ownership
const char* catk_strbuilder_get(catk_strbuilder_t* sb);
// deep copy of a builder. destination is overwritten but preserved on failure
void catk_strbuilder_copy(
    catk_strbuilder_t* restrict dest_sb,
    const catk_strbuilder_t* restrict src_sb
);
// pre-allocate a chunk of the builder's buffer. no effect when the builder's capacity is already larger
void catk_strbuilder_reserve(catk_strbuilder_t* sb, size_t cap);
// free all resources. safe to call multiple times
void catk_strbuilder_destroy(catk_strbuilder_t* sb);
// clears the current buffer but does not free resources or reset capacity. safe to call multiple times
void catk_strbuilder_clear(catk_strbuilder_t* sb);

#ifdef CATKIT_STRIP_PREFIX
    #define fmt(...) catk_fmt(__VA_ARGS__)
    #define vfmt(format, args) catk_vfmt(format, args)
    typedef catk_strbuilder_t strbuilder_t;
    #define strbuilder_initf(sb, ...) catk_strbuilder_initf(sb, __VA_ARGS__)
    #define strbuilder_vinitf(format, args) catk_strbuilder_vinitf(format_args)
    #define strbuilder_initn(sb, data, count) catk_strbuilder_initn(sb, data, count)
    #define strbuilder_appendf(sb, ...) catk_strbuilder_appendf(sb, __VA_ARGS__)
    #define strbuilder_vappendf(sb, fmt, args) catk_strbuilder_vappendf(sb, fmt, args)
    #define strbuilder_appendn(sb, str, count) catk_strbuilder_appendn(sb, str, count)
    #define strbuilder_insertf(sb, pos, ...) catk_strbuilder_insertf(sb, pos, __VA_ARGS__)
    #define strbuilder_vinsertf(sb, pos, fmt, args) catk_strbuilder_vinsertf(sb, pos, fmt, args)
    #define strbuilder_insertn(sb, pos, str, count) catk_strbuilder_insertn(sb, pos, str, count)
    #define strbuilder_get(sb) catk_strbuilder_get(sb)
    #define strbuilder_build(sb) catk_strbuilder_build(sb)
    #define strbuilder_copy(dest_sb, src_sb) catk_strbuilder_copy(dest_sb, src_sb)
    #define strbuilder_reserve(sb, cap) catk_strbuilder_reserve(sb, cap)
    #define strbuilder_destroy(sb) catk_strbuilder_destroy(sb)
    #define strbuilder_clear(sb) catk_strbuilder_clear(sb)
#endif

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
    
    char* buf = CATKIT_MALLOC(needed);
    if (buf) vsnprintf(buf, needed, fmt, args);
    
    return buf;
}

void catk_strbuilder_initf(catk_strbuilder_t* sb, const char* fmt, ...) {
    if (sb == NULL) return;
    va_list args;
    va_start(args, fmt);
    catk_strbuilder_vinitf(sb, fmt, args);
    va_end(args);
}

void catk_strbuilder_vinitf(catk_strbuilder_t* sb, const char* fmt, va_list args) {
    if (sb == NULL) return;
    char* new_data = catk_vfmt(fmt, args);
    if (new_data) {
        size_t len = strlen(new_data);
        free(sb->data);
        sb->data = new_data;
        sb->len = len;
        sb->cap = len + 1;
    }
}

void catk_strbuilder_initn(catk_strbuilder_t* sb, const char* data, const size_t count) {
    if (sb == NULL) return;
    size_t len = 0;
    if (data) {
        while (len < count && data[len] != '\0') {
            len++;
        }
    }
    char* new_data = CATKIT_MALLOC(len + 1);
    if (new_data) {
        memcpy(new_data, data, len);
        new_data[len] = '\0';
        free(sb->data);
        sb->data = new_data;
        sb->len = len;
        sb->cap = len + 1;
    }
}

void catk_strbuilder_appendf(catk_strbuilder_t* sb, const char* fmt, ...) {
    if (sb == NULL) return;
    va_list args;
    va_start(args, fmt);
    catk_strbuilder_vappendf(sb, fmt, args);
    va_end(args);
}

void catk_strbuilder_vappendf(catk_strbuilder_t* sb, const char* fmt, va_list args) {
    if (sb == NULL) return;
    char* chunk = catk_vfmt(fmt, args);
    if (chunk == NULL) return;

    size_t chunk_len = strlen(chunk);
    size_t new_len = sb->len + chunk_len;
    
    if (sb->cap <= new_len) {
        size_t new_cap = sb->cap ? sb->cap : 1;
        while (new_cap <= new_len) new_cap *= 2;
        sb->cap = new_cap;
        
        char* new_data = CATKIT_REALLOC(sb->data, sb->cap);
        if (new_data == NULL) {
            CATKIT_FREE(chunk);
            return;
        }
        sb->data = new_data;
    }

    memcpy(sb->data + sb->len, chunk, chunk_len);
    sb->len = new_len;
    sb->data[sb->len] = '\0';
    CATKIT_FREE(chunk);
}

void catk_strbuilder_appendn(catk_strbuilder_t* sb, const char* str, const size_t count) {
    if (sb == NULL) return;
    size_t len = 0;
    if (str != NULL) {
        while (len < count && str[len] != '\0') {
            len++;
        }
    }
    size_t new_len = sb->len + len;
    if (sb->cap <= new_len) {
        size_t new_cap = sb->cap ? sb->cap : 1;
        while (new_cap <= new_len) new_cap *= 2;
        sb->cap = new_cap;
        
        char* new_data = CATKIT_REALLOC(sb->data, sb->cap);
        if (new_data == NULL) return;
        sb->data = new_data;
    }
    memcpy(sb->data + sb->len, str, len);
    sb->len = new_len;
    sb->data[sb->len] = '\0';
}

void catk_strbuilder_appendc(catk_strbuilder_t* sb, const char ch) {
    char temp_str[2] = {ch, '\0'};
    catk_strbuilder_appendn(sb, temp_str, 1);
}

void catk_strbuilder_insertf(catk_strbuilder_t* sb, const size_t pos, const char* fmt, ...) {
    if (sb == NULL) return;
    va_list args;
    va_start(args, fmt);
    catk_strbuilder_vinsertf(sb, pos, fmt, args);
    va_end(args);
}

void catk_strbuilder_vinsertf(catk_strbuilder_t* sb, const size_t pos, const char* fmt, va_list args) {
    if (sb == NULL) return;
    if (pos > sb->len) return;
    char* chunk = catk_vfmt(fmt, args);
    if (chunk == NULL) return;
    
    size_t chunk_len = strlen(chunk);
    size_t new_len = sb->len + chunk_len;
    
    if (sb->cap <= new_len) {
        size_t new_cap = sb->cap ? sb->cap : 1;
        while (new_cap <= new_len) new_cap *= 2;
        sb->cap = new_cap;
        
        char* new_data = CATKIT_REALLOC(sb->data, sb->cap);
        if (new_data == NULL) {
            CATKIT_FREE(chunk);
            return;
        }
        sb->data = new_data;
    }

    memmove(
        sb->data + pos + chunk_len,
        sb->data + pos,
        sb->len - pos + 1 // +1 to move the null terminator
    );
    memcpy(sb->data + pos, chunk, chunk_len);
    sb->len = new_len;
    CATKIT_FREE(chunk);
}

void catk_strbuilder_insertn(catk_strbuilder_t* sb, const size_t pos, const char* str, const size_t count) {
    if (sb == NULL) return;
    if (pos > sb->len) return;
    size_t len = 0;
    if (str != NULL) {
        while (len < count && str[len] != '\0') {
            len++;
        }
    }
    size_t new_len = sb->len + len;
    if (sb->cap <= new_len) {
        size_t new_cap = sb->cap ? sb->cap : 1;
        while (new_cap <= new_len) new_cap *= 2;
        sb->cap = new_cap;
        
        char* new_data = CATKIT_REALLOC(sb->data, sb->cap);
        if (new_data == NULL) return;
        sb->data = new_data;
    }
    
    memmove(
        sb->data + pos + len,
        sb->data + pos,
        sb->len - pos + 1 // +1 to move the null terminator
    );
    memcpy(sb->data + pos, str, len);
    sb->len = new_len;
}

void catk_strbuilder_insertc(catk_strbuilder_t* sb, const size_t pos, const char ch) {
    char temp_str[2] = {ch, '\0'};
    catk_strbuilder_insertn(sb, pos, temp_str, 1);
}

char* catk_strbuilder_build(catk_strbuilder_t* sb) {
    if (sb == NULL) return NULL;
    char* result = sb->data;
    sb->data = NULL;
    sb->len = 0;
    sb->cap = 0;
    return result;
}

const char* catk_strbuilder_get(catk_strbuilder_t* sb) {
    if (sb == NULL) return NULL;
    return sb->data;
}

void catk_strbuilder_copy(
    catk_strbuilder_t* restrict dest_sb,
    const catk_strbuilder_t* restrict src_sb
) {
    if (dest_sb == NULL || src_sb == NULL) return;
    
    // if src_sb is empty
    if (src_sb->data == NULL || src_sb->len == 0) {
        CATKIT_FREE(dest_sb->data);
        dest_sb->data = NULL;
        dest_sb->len = 0;
        dest_sb->cap = 0;
        return;
    }
    
    char* new_data = CATKIT_MALLOC(src_sb->len + 1);
    if (new_data) {
        memcpy(new_data, src_sb->data, src_sb->len);
        new_data[src_sb->len] = '\0';
        CATKIT_FREE(dest_sb->data);
        dest_sb->data = new_data;
        dest_sb->len = src_sb->len;
        dest_sb->cap = src_sb->len + 1;
    }
    // if copy failed, preserve original data
}

void catk_strbuilder_reserve(catk_strbuilder_t* sb, size_t cap) {
    if (sb == NULL || cap <= sb->cap) return;
    char* new_data = CATKIT_REALLOC(sb->data, cap);
    if (new_data) {
        sb->data = new_data;
        sb->cap = cap;
    }
}

void catk_strbuilder_destroy(catk_strbuilder_t* sb) {
    if (sb == NULL) return;
    CATKIT_FREE(sb->data);
    sb->data = NULL;
    sb->len = 0;
    sb->cap = 0;
}

void catk_strbuilder_clear(catk_strbuilder_t* sb) {
    if (sb == NULL) return;
    sb->len = 0;
    if (sb->data) sb->data[0] = '\0';
}

#endif // CATKIT_IMPLEMENTATION

#endif // CATKIT_H_