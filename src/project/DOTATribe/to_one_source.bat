echo "Working dir is : %1"
@echo off
del "source.cpp"
for /r %1 %%X in (*.cpp, *.c) do (echo #include "%%X" >> source.cpp)
PAUSE