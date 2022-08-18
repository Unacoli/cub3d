/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:25:05 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/18 20:48:45 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(int way, t_data *data)
{
	if (way == XK_Right)
	{
		if (data->player.o + 5 > 360)
			data->player.o = -5;
		data->player.o += 5;
	}
	if (way == XK_Left)
	{
		if (data->player.o - 5 < 0)
			data->player.o = 365;
		data->player.o -= 5;
	}
}

void	change_player_pos(double orientation, t_data *data, t_pos dir)
{
	double	t;
	double	v_x;
	double	v_y;

	t = get_rad(orientation);
	v_x = cos(t);
	v_y = sin(t);
	if (data->map[(int)(data->player.y + (v_y * 0.1) * dir.y)][(int)(data->player.x + (v_x * 0.1) * dir.x)] != '1')
	{
		data->player.x += (v_x * 0.1) * dir.x;
		data->player.y += (v_y * 0.1) * dir.y;
	}
}

int	move_player(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		ft_printf("You pressed escape key\nGame closed\n");
		mlx_loop_end(data->mlx);
		return (0);
	}
	if (keycode == XK_Left || keycode == XK_Right)
		rotate_player(keycode, data);
	if (keycode == XK_W)
		change_player_pos(data->player.o, data, point(1, 1, 0));
	if (keycode == XK_S)
		change_player_pos(data->player.o, data, point(-1, -1, 0));
	if (keycode == XK_A)
		change_player_pos(change_angle(data->player.o, 90, '-'), data, point(1, 1, 0));
	if (keycode == XK_D)
		change_player_pos(change_angle(data->player.o, 90, '-'), data, point(-1, -1, 0));
	return (0);
}

int	act_keypress(t_data *data)
{
	if (data->keys.l_arr)
		move_player(XK_Left, data);
	if (data->keys.r_arr)
		move_player(XK_Right, data);
	if (data->keys.w)
		move_player(XK_W, data);
	if (data->keys.s)
		move_player(XK_S, data);
	if (data->keys.a)
		move_player(XK_A, data);
	if (data->keys.d)
		move_player(XK_D, data);
	map_fill(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_2d, 0, 0);
	return (0);
}

int	hook_keypress(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
	{
		ft_printf("You pressed escape key\nGame closed\n");
		mlx_loop_end(data->mlx);
		return (0);
	}
	if (keycode == XK_W || keycode == XK_w)
		data->keys.w = !data->keys.w;
	if (keycode == XK_S || keycode == XK_s)
		data->keys.s = !data->keys.s;
	if (keycode == XK_A || keycode == XK_a) 
		data->keys.a = !data->keys.a;
	if (keycode == XK_D || keycode == XK_d)
		data->keys.d = !data->keys.d;
	if (keycode == XK_M || keycode == XK_m)
		data->keys.m = !data->keys.m;
	if (keycode == XK_Left)
		data->keys.l_arr = !data->keys.l_arr;
	if (keycode == XK_Right)
		data->keys.r_arr = !data->keys.r_arr;
	return (0);
}
