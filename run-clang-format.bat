@echo off

fd -0 -e h -e cpp -E "src/shader" -a | xargs -0 clang-format -i
