@echo off

fd -0 -e cpp -E "src/shader" -a | xargs -0 clang-tidy -p build\debug -header-filter="debug*" --fix
