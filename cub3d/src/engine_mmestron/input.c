/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:10:00 by coder             #+#    #+#             */
/*   Updated: 2026/03/07 02:50:30 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

#define KEY_ESC 65307
#define RAW_LEFT 65361
#define RAW_RIGHT 65363

static int	map_key(int keycode)
{
	if (keycode == RAW_LEFT)
		return (ACT_TURN_LEFT);
	if (keycode == RAW_RIGHT)
		return (ACT_TURN_RIGHT);
	if (keycode == 'w' || keycode == 'W')
		return (ACT_MOVE_FWD);
	if (keycode == 'a' || keycode == 'A')
		return (ACT_MOVE_LEFT);
	if (keycode == 's' || keycode == 'S')
		return (ACT_MOVE_BACK);
	if (keycode == 'd' || keycode == 'D')
		return (ACT_MOVE_RIGHT);
	return (-1);
}

int	key_press(int keycode, t_game *g)
{
	int	k;

	if (!g)
		return (0);
	if (keycode == KEY_ESC)
		return (on_close(g));
	k = map_key(keycode);
	if (k >= 0 && k < 1024)
		g->keys[k] = 1;
	return (0);
}

int	key_release(int keycode, t_game *g)
{
	int	k;

	if (!g)
		return (0);
	k = map_key(keycode);
	if (k >= 0 && k < 1024)
		g->keys[k] = 0;
	return (0);
}

int	on_close(t_game *g)
{
	mlx_destroy(g);
	free_cub(&g->cub);
	exit(0);
	return (0);
}
