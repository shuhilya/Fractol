/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_reaction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htorp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:01:20 by htorp             #+#    #+#             */
/*   Updated: 2019/03/08 14:01:22 by htorp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	move_figure(int x, int y, t_image *image)
{
	int		dx;
	int		dy;
	double	hor_step;
	double	ver_step;

	mlx_destroy_image(image->mlx_ptr, image->image_ptr);
	image->image_ptr = mlx_new_image(image->mlx_ptr, image->size, image->size);
	image->data = mlx_get_data_addr(image->image_ptr, &(image->bpp),
									&(image->sl), &(image->enin));
	dx = image->mouse_x - x;
	dy = image->mouse_y - y;
	hor_step = (image->right_bor - image->left_bor) / ((double)(image->size));
	ver_step = (image->top_bor - image->bot_bor) / ((double)(image->size));
	image->left_bor = image->left_bor + dx * hor_step;
	image->right_bor = image->right_bor + dx * hor_step;
	image->top_bor = image->top_bor + dy * ver_step;
	image->bot_bor = image->bot_bor + dy * ver_step;
	draw_fract(image, ((double)(image->size)));
	mlx_clear_window(image->mlx_ptr, image->win_ptr);
	mlx_put_image_to_window(image->mlx_ptr, image->win_ptr,
							image->image_ptr, 0, 0);
	image->mouse_x = x;
	image->mouse_y = y;
}

void	julia_reshape(int x, int y, t_image *image)
{
	int		dx;
	int		dy;
	double	hor_step;
	double	ver_step;

	mlx_destroy_image(image->mlx_ptr, image->image_ptr);
	image->image_ptr = mlx_new_image(image->mlx_ptr, image->size, image->size);
	image->data = mlx_get_data_addr(image->image_ptr, &(image->bpp),
									&(image->sl), &(image->enin));
	dx = image->jul_x - x;
	dy = image->jul_y - y;
	hor_step = (image->right_bor - image->left_bor) / ((double)(image->size));
	ver_step = (image->top_bor - image->bot_bor) / ((double)(image->size));
	image->d_params[0] = image->d_params[0] + hor_step * dx;
	image->d_params[1] = image->d_params[1] + ver_step * dy;
	image->jul_x = x;
	image->jul_y = y;
	draw_fract(image, ((double)(image->size)));
	mlx_clear_window(image->mlx_ptr, image->win_ptr);
	mlx_put_image_to_window(image->mlx_ptr, image->win_ptr,
							image->image_ptr, 0, 0);
}

int		mouse_move(int x, int y, void *param)
{
	t_image *image;

	image = (t_image*)param;
	if (image->l_mouse_flag)
		move_figure(x, y, image);
	if (image->r_mouse_flag)
		julia_reshape(x, y, image);
	return (0);
}

void	change_scale(int x, int y, t_image *image, int button)
{
	double p;
	double q;
	double hor_step;
	double ver_step;

	mlx_destroy_image(image->mlx_ptr, image->image_ptr);
	image->image_ptr = mlx_new_image(image->mlx_ptr, image->size, image->size);
	image->data = mlx_get_data_addr(image->image_ptr, &(image->bpp),
									&(image->sl), &(image->enin));
	hor_step = (image->right_bor - image->left_bor) / ((double)(image->size));
	ver_step = (image->top_bor - image->bot_bor) / ((double)(image->size));
	p = image->left_bor + (double)x * hor_step;
	q = image->bot_bor + (double)y * ver_step;
	if (button == 5)
		reshape(p, q, image, 1);
	if (button == 4)
		reshape(p, q, image, -1);
	draw_fract(image, ((double)(image->size)));
	mlx_clear_window(image->mlx_ptr, image->win_ptr);
	mlx_put_image_to_window(image->mlx_ptr, image->win_ptr,
							image->image_ptr, 0, 0);
}

int		mouse_press(int button, int x, int y, void *param)
{
	t_image *image;

	image = (t_image *)param;
	if ((button == 4) || (button == 5))
		change_scale(x, y, image, button);
	if (button == 1)
	{
		image->mouse_x = x;
		image->mouse_y = y;
		image->l_mouse_flag = 1;
	}
	if ((button == 2) && (image->fract_flag == JULIA))
	{
		image->r_mouse_flag = 1;
		image->jul_x = x;
		image->jul_y = y;
	}
	return (0);
}
