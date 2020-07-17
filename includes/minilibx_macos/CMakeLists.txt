cmake_minimum_required(VERSION 3.16)
project(minilibx_macos C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(minilibx_macos
        font.c
        mlx.h
        mlx_init_loop.m
        mlx_int.h
        mlx_int_str_to_wordtab.c
        mlx_new_image.m
        mlx_new_window.h
        mlx_new_window.m
        mlx_rgb.c
        mlx_shaders.c
        mlx_xpm.c)
