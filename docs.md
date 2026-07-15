# catkit API reference

## quick formatting

```c
char* catk_fmt(const char* fmt, ...);
char* catk_vfmt(const char* fmt, va_list args);
```

returns an allocated and formatted string. caller must `free()`

## string builder

```c
typedef struct {
    char* data;
    size_t len;
    size_t cap;
} catk_strbuilder_t;
```

```c
void catk_strbuilder_appendf(catk_strbuilder_t* sb, const char* fmt, ...);
void catk_strbuilder_vappendf(catk_strbuilder_t* sb, const char* fmt, va_list args);
```
append formatted string to the builder's buffer

```c
const char* catk_strbuilder_get(catk_strbuilder_t* sb);
```
peek at the current buffer. does **not** transfer ownership

```c
char* catk_strbuilder_build(catk_strbuilder_t* sb);
```
take ownership of the current string. string builder is fully reset (including capacity). caller must `free()`

```c
void catk_strbuilder_copy(catk_strbuilder_t* restrict dest, const catk_strbuilder_t* restrict src);
```
deep copy of a builder. destination is overwritten but preserved on failure

```c
void catk_strbuilder_destroy(catk_strbuilder_t* sb);
```
free all resources. safe to call multiple times

```c
void catk_strbuilder_clear(catk_strbuilder_t* sb)
```
clears the current buffer but does not free resources or reset capacity. safe to call multiple times
