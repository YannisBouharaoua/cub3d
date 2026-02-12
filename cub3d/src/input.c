/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:10:00 by coder             #+#    #+#             */
/*   Updated: 2026/02/04 17:10:00 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

#define KEY_ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100

#define KEY_UP 65362
#define KEY_DOWN 65364
#define KEY_LEFT 65361
#define KEY_RIGHT 65363

static int	map_key(int keycode)
{
	if (keycode == KEY_UP)
		return (KEY_W);
	if (keycode == KEY_DOWN)
		return (KEY_S);
	if (keycode == KEY_LEFT)
		return (KEY_A);
	if (keycode == KEY_RIGHT)
		return (KEY_D);
	return (keycode);
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
	exit(0);
	return (0);
}
