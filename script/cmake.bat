@echo off

set exec=cset_T0
set main=main
g++ "%~dp0..\src\%main%.c" "%~dp0..\src\cset.cpp" "%~dp0..\src\set.cpp" "%~dp0..\src/rbtree.cpp" "%~dp0..\src\llist.cpp" "%~dp0..\src\htable.cpp" -o "%~dp0..\bin\%exec%"
if "%1"=="-r" (
    "%~dp0..\bin\%exec%"
)

echo Compiled src/%main%.c into bin/%exec%.exe

echo on
