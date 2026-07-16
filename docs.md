# catkit API reference

(as of v0.1.0-alpha.1)

## prefix stripping

you can define `CATKIT_STRIP_PREFIX` like so:
```c
#define CATKIT_STRIP_PREFIX
```
and `catkit.h` will provide typenames and functions without the explicit `catk_` prefix

## quick formatting

```c
char* catk_fmt(const char* fmt, ...);
char* catk_vfmt(const char* fmt, va_list args);
```

returns an allocated and string. caller must `free()`

## string builder

```c
typedef struct {
    char* data;
    size_t len;
    size_t cap;
} catk_strbuilder_t;
```

```c
void catk_strbuilder_initf(catk_strbuilder_t* sb, const char* fmt, ...);
void catk_strbuilder_vinitf(catk_strbuilder_t* sb, const char* fmt, va_list args);
void catk_strbuilder_initn(catk_strbuilder_t* sb, const char* data, size_t count);
```
initiate the string builder with the supplied string. overrwrites the destination but preserved on failure

```c
void catk_strbuilder_appendf(catk_strbuilder_t* sb, const char* fmt, ...);
void catk_strbuilder_vappendf(catk_strbuilder_t* sb, const char* fmt, va_list args);
void catk_strbuilder_appendn(catk_strbuilder_t* sb, const char* fmt, const size_t count);
void catk_strbuilder_appendc(catk_strbuilder_t* sb, const char ch);
```
append string to the builder's buffer

```c
void catk_strbuilder_insertf(catk_strbuilder_t* sb, const size_t pos, const char* fmt, ...);
void catk_strbuilder_vinsertf(catk_strbuilder_t* sb, const size_t pos, const char* fmt, va_list args);
void catk_strbuilder_insertn(catk_strbuilder_t* sb, const size_t pos, const char* str, const size_t count);
void catk_strbuilder_insertc(catk_strbuilder_t* sb, const size_t pos, const char ch);
```
insert formated string into the builder's buffer at a position

```c
const char* catk_strbuilder_get(catk_strbuilder_t* sb);
```
peek at the current buffer. does **not** transfer ownership. caller must not `free()`

```c
char* catk_strbuilder_build(catk_strbuilder_t* sb);
```
take ownership of the current string. string builder is fully reset (including capacity). caller must `free()`

```c
void catk_strbuilder_copy(catk_strbuilder_t* restrict dest, const catk_strbuilder_t* restrict src);
```
deep copy of a builder. destination is overwritten but preserved on failure

```c
void catk_strbuilder_reserve(catk_strbuilder_t* sb, size_t cap);
```
pre-allocate a chunk of the builder's buffer. no effect when the builder's capacity is already larger or equal to the wanted capacity

```c
void catk_strbuilder_destroy(catk_strbuilder_t* sb);
```
free all resources. safe to call multiple times

```c
void catk_strbuilder_clear(catk_strbuilder_t* sb)
```
clears the current buffer but does not free resources or reset capacity. safe to call multiple times
