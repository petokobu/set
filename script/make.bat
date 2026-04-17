@ECHO OFF

set exec=set
set main=main
IF "%2"=="-t" (
    set exec=set_T0
    set main=testing
)
g++ "%~dp0..\src\%main%.cpp" "%~dp0..\src\set.cpp" "%~dp0..\src/rbtree.cpp" "%~dp0..\src\llist.cpp" "%~dp0..\src\htable.cpp" -o "%~dp0..\bin\%exec%"
IF "%1"=="-r" (
    "%~dp0..\bin\%exec%"
)

ECHO ON
