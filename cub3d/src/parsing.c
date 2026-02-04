/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabouhar <yabouhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:28:19 by yabouhar          #+#    #+#             */
/*   Updated: 2026/02/04 14:28:19 by yabouhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int good_map();

int not_directory(char *str)
{
    int fd;

    fd = open(str, O_RDONLY | O_DIRECTORY);
    if(fd = -1)
    {
        close(fd);
        return 1;
    }
}

int parsing(int ac, char **av)
{
    char *path_map = av[1];

    if(not_directory(path_map))
    {
        if(good_map())
        {
            printf("GoodMap\n");
            return(0);
        }
        printf("BadMap Format\n");
        return(1);
    }
    printf("Is a Directory\n");
    return(1);
}