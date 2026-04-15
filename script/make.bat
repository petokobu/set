@ECHO OFF

g++ "%~dp0../src/main.cpp" "%~dp0../src/set.cpp" "%~dp0../src/rbtree.cpp" -o "%~dp0../bin/set"
IF "%1"=="-r" (
    "%~dp0../bin/set"
)

ECHO ON
