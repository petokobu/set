@echo off

set exec=set
set main=main
if "%2"=="-t" (
    set exec=set_T0
    set main=testing
)
if "%1"=="-t" (
    set exec=set_T0
    set main=testing
)
g++ "%~dp0..\src\%main%.cpp" "%~dp0..\src\set.cpp" "%~dp0..\src/rbtree.cpp" "%~dp0..\src\llist.cpp" "%~dp0..\src\htable.cpp" -o "%~dp0..\bin\%exec%"
if "%1"=="-r" (
    "%~dp0..\bin\%exec%"
)

echo Compiled src/%main%.cpp into bin/%exec%.exe

echo on
