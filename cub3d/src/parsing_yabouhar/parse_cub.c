/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmestron <mmestron@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:38:23 by mmestron          #+#    #+#             */
/*   Updated: 2026/03/07 14:38:23 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	init_gm(t_gm *gm, t_cub *cub)
{
	gm->cub = cub;
	gm->fd = -1;
	gm->line = NULL;
	gm->in_map = 0;
	gm->player_count = 0;
	gm->width = 0;
	gm->height = 0;
	gm->cap = 0;
	gm->lines = NULL;
	gm->pad = NULL;
	gm->no = 0;
	gm->so = 0;
	gm->we = 0;
	gm->ea = 0;
	gm->f = 0;
	gm->c = 0;
}

static int	parse_fail(t_gm *gm, char *msg)
{
	if (gm->fd != -1)
		close(gm->fd);
	if (gm->line)
		free(gm->line);
	gm_free_lines(gm->lines, gm->height);
	gnl_clear();
	free_cub(gm->cub);
	return (print_error(msg));
}

static int	check_path_map(char *path_map)
{
	if (!gm_has_cub_ext(path_map))
		return (print_error("map file must use the .cub extension"));
	if (!not_directory(path_map))
		return (print_error("map path is a directory"));
	return (1);
}

int	parse_cub(t_cub *cub, char *path_map)
{
	t_gm	gm;

	init_cub(cub);
	if (!check_path_map(path_map))
		return (0);
	init_gm(&gm, cub);
	gm.fd = open(path_map, O_RDONLY);
	if (gm.fd == -1)
		return (print_error("could not open map file"));
	if (!read_cub_file(&gm))
		return (parse_fail(&gm, "invalid scene description"));
	close(gm.fd);
	gm.fd = -1;
	if (!build_map(&gm))
		return (parse_fail(&gm, "invalid map"));
	return (1);
}
