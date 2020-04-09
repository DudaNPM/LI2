cmake_minimum_required(VERSION 3.10)
project(Projeto_Rastros C)

set(CMAKE_C_STANDARD 99)

add_executable(Projeto_Rastros main.c dados.c dados.h logica.c logica.h interface.c interface.h listas.c listas.h)