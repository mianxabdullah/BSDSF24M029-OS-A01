## Feature-2 Report Questions

**1. Explain the linking rule `$(TARGET): $(OBJECTS)`. How does it differ from linking against a library?**

This rule tells `make` that `bin/client` depends on all the `.o` files. When any `.c` file changes, `make` rebuilds that `.o` file and then re-links all objects directly into the executable. Linking against a library is different — instead of listing every `.o` file, you compile the reusable code once into a library file (`.a` or `.so`), and the final program links against that single library file using `-l` instead of individual object files.

**2. What is a git tag and why is it useful? Difference between a simple and annotated tag?**

A git tag marks a specific commit as an important point in the project's history, usually a release version (e.g. `v0.1.1-multifile`). It's useful because it lets you go back to or reference a stable version by name instead of a commit hash. A simple (lightweight) tag is just a name pointing to a commit — no extra info. An annotated tag stores extra metadata: author, date, and a message, and it's a full object in git, which is why it's the recommended type for releases.

**3. What is the purpose of a GitHub Release? Why attach binaries?**

A GitHub Release packages a specific tagged version of the project with a title, description, and downloadable files. It's meant for end users who want to use the software without building it themselves. Attaching the compiled binary (`bin/client`) lets someone download and run the program directly, instead of cloning the repo and compiling it manually.
