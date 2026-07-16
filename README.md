<div align="center">
    <img src="images/tamm-cat.png" width=200>
    <h1><code>catkit.h</code></h1>
    <img src="https://img.shields.io/badge/release-v0.1.0--alpha.1-blue">
    <p><strong>when the cat helps you with C strings in a single header file</strong></p>
</div>

## prerequisites

- C compiler
- C ABI
- (yea that's it)

but you will need Git to download the header file from the repository

## how to use

```bash
# first navigate to your project's folder or where you want the header file to be at
git clone https://github.com/tayenx3/catkit.h.git catkit
cp catkit/catkit.h .
rm -r catkit

# if you.. don't have Git somehow
curl -O https://raw.githubusercontent.com/tayenx3/catkit.h/main/catkit.h
```

you should now see `catkit.h` in the folder you started in

`catkit.h` is used in a stb-style

```c
#define CATKIT_IMPLEMENTATION
#include "catkit.h"

int main(void) {
    // main code
}
```

## features

- quick formatting with `catk_fmt`/`catk_vfmt`
- string builder API with `catk_strbuilder_t` and `catk_strbuilder_*` functions
- prefix stripping with `CATKIT_STRIP_PREFIX`
- new features coming in newer updates (no shit lmao)

check out [docs.md](docs.md) for API reference

## compatible C/C++ versions

for C, `catkit.h` is compatible with C99 and later

for C++, `catkit.h` is compabtible with C++11 and later. C++98 supported if your compiler has a C99-compliant stdlib

## license

MIT

see [LICENSE](LICENSE) for more details
