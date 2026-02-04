/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabouhar <yabouhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:25:53 by yabouhar          #+#    #+#             */
/*   Updated: 2026/02/04 14:25:53 by yabouhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>

//PARSING
int parsing(int ac, char **av);
int not_directory(char *str);

//Structure couleur RGB
typedef struct s_color
{
    int r;
    int g;
    int b;
}   t_color;

//Structure map
typedef struct s_map
{
    char **grid;
    int width;
    int height;
}  t_map;

//Stucture CUB3D
typedef struct s_cub
{
    t_texture tex;
    t_color floor;
    t_color ceiling;
    t_map map;
}   t_cub;

typedef struct s_texture
{
    char *north;
    char *south;
    char *west;
    char *east;
}   t_texture;

#endif