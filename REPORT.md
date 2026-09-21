## Feature-2 Report Questions

**1. Explain the linking rule `$(TARGET): $(OBJECTS)`. How does it differ from linking against a library?**

This rule tells `make` that `bin/client` depends on all the `.o` files. When any `.c` file changes, `make` rebuilds that `.o` file and then re-links all objects directly into the executable. Linking against a library is different — instead of listing every `.o` file, you compile the reusable code once into a library file (`.a` or `.so`), and the final program links against that single library file using `-l` instead of individual object files.

**2. What is a git tag and why is it useful? Difference between a simple and annotated tag?**

A git tag marks a specific commit as an important point in the project's history, usually a release version (e.g. `v0.1.1-multifile`). It's useful because it lets you go back to or reference a stable version by name instead of a commit hash. A simple (lightweight) tag is just a name pointing to a commit — no extra info. An annotated tag stores extra metadata: author, date, and a message, and it's a full object in git, which is why it's the recommended type for releases.

**3. What is the purpose of a GitHub Release? Why attach binaries?**

A GitHub Release packages a specific tagged version of the project with a title, description, and downloadable files. It's meant for end users who want to use the software without building it themselves. Attaching the compiled binary (`bin/client`) lets someone download and run the program directly, instead of cloning the repo and compiling it manually.

## Feature-3 Report Questions

**1. Compare the Makefile from Feature-2 and Feature-3. What are the key differences?**

In Feature-2, the executable target (`bin/client`) depended directly on all three `.o` files and linked them together in one `gcc` command. In Feature-3, `mystrfunctions.o` and `myfilefunctions.o` are no longer linked directly — instead they're archived into `lib/libmyutils.a` using `ar rcs`. The executable (`bin/client_static`) now depends on `obj/main.o` and `lib/libmyutils.a`, and the final link command uses `-Llib -lmyutils` (library path + library name) instead of listing the object files individually.

**2. What is the purpose of the `ar` command? Why is `ranlib` often used after it?**

`ar` bundles multiple object files into a single archive file (`.a`), which acts as a static library. `ranlib` generates an index inside the archive that speeds up symbol lookups during linking — without it, the linker would have to scan every object file in the archive sequentially. The `s` flag in `ar rcs` does this indexing automatically, so a separate `ranlib` call isn't needed in this case.

**3. When you run `nm` on `client_static`, are symbols like `mystrlen` present? What does this tell you about static linking?**

Yes — `mystrlen` and the other functions appear as defined (`T`) symbols directly inside `client_static`. This confirms that static linking copies the actual machine code of the library's functions into the final executable at build time, rather than just referencing them. That's why static executables are self-contained but larger than dynamically linked ones.

## Feature-4 Report Questions

**1. What is Position-Independent Code (-fPIC) and why is it required for shared libraries?**

`-fPIC` compiles code so it can run correctly no matter where in memory it gets loaded, using relative addressing instead of fixed absolute addresses. This is required for shared libraries because a `.so` file can be loaded at different memory addresses in different programs (or even in the same program run multiple times), and the OS needs to be able to place it anywhere without breaking internal references.

**2. Explain the file size difference between the static and dynamic clients.**

`client_static` (16792 bytes) is larger than `client_dynamic` (16448 bytes) — a 344-byte difference. This is because the static build copies the actual compiled code of `libmyutils` directly into the executable, while the dynamic build only stores a reference to `libmyutils.so`, which is loaded separately at runtime. The difference is small here since the library only has a few small functions, but it would scale up significantly with a larger library.

**3. What is LD_LIBRARY_PATH and why was it needed?**

`LD_LIBRARY_PATH` is an environment variable that tells the dynamic loader additional directories to search for shared libraries at runtime. It was necessary because `libmyutils.so` isn't installed in a standard system library path (like `/usr/lib`), so without setting it, the loader couldn't find the library and the program failed with a "cannot open shared object file" error. This shows that the OS loader is responsible for resolving and loading shared library dependencies at program startup, not at compile time.
