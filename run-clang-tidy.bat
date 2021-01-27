@echo off

fd -0 -e cpp -a | xargs -0 clang-tidy -p build\debug -header-filter="debug*" --fix
