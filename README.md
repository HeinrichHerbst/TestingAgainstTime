# TestingAgainstTime
Examples for how to write tests against time in C++

# Prerequisites
This project makes use of `cmake`, `clang-format`, `clang-tidy`, `python` and `g++`.
If you wish to use the functionality around these tools, then please make sure they are installed.

# Compile-commands
You may wish to create a symbolic link to your compile_commands.json file from the build directory for clang-tidy to detect the correct paths for included files.

```bash
ln -s build/compile_commands.json .
```

# Clang-Format
You may wish to include your own `.clang-format` file if you wish to use format on save.

# Clang-tidy
You may wish to include your own `.clang-tidy` file if you wish to use `builder.py` to analyze your code.
