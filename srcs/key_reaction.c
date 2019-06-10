/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_reaction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htorp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:00:18 by htorp             #+#    #+#             */
/*   Updated: 2019/03/08 14:00:20 by htorp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	move_sets(int keycode, t_image *image)
{
	double	hor_step;
	double	ver_step;
	double	shift;

	shift = image->shift;
	hor_step = (image->right_bor - image->left_bor) / ((double)(image->size));
	ver_step = (image->top_bor - image->bot_bor) / ((double)(image->size));
	if (keycode == 123)
		image->left_bor = image->left_bor + shift * hor_step;
	if (keycode == 123)
		image->right_bor = image->right_bor + shift * hor_step;
	if (keycode == 124)
		image->left_bor = image->left_bor - shift * hor_step;
	if (keycode == 124)
		image->right_bor = image->right_bor - shift * hor_step;
	if (keycode == 126)
	{
		image->top_bor = image->top_bor + shift * ver_step;
		image->bot_bor = image->bot_bor + shift * ver_step;
	}
	if (keycode == 125)
	{
		image->top_bor = image->top_bor - shift * ver_step;
		image->bot_bor = image->bot_bor - shift * ver_step;
	}
}

void	set_fract(int keycode, t_image *image)
{
	if (keycode == 18)
		mandel_fract(image);
	if (keycode == 19)
		julia_fract(image);
	if (keycode == 20)
		spider_fract(image);
	if (keycode == 21)
		a_fract(image);
	if (keycode == 23)
		newton_fract(image);
}

void	newt_sets(int keycode, t_image *image)
{
	newton_fract(image);
	if (keycode == 85)
		image->i_params[3] = 3;
	if (keycode == 86)
		image->i_params[3] = 4;
	if (keycode == 87)
		image->i_params[3] = 5;
	if (keycode == 88)
		image->i_params[3] = 6;
	if (keycode == 89)
		image->i_params[3] = 7;
	if (keycode == 91)
		image->i_params[3] = 8;
	if (keycode == 92)
		image->i_params[3] = 9;
}

int		key_press(int keycode, void *param)
{
	t_image	*image;

	image = (t_image*)param;
	mlx_destroy_image(image->mlx_ptr, image->image_ptr);
	image->image_ptr = mlx_new_image(image->mlx_ptr, image->size, image->size);
	image->data = mlx_get_data_addr(image->image_ptr, &(image->bpp),
									&(image->sl), &(image->enin));
	if (keycode == 53)
		exit(0);
	if ((keycode >= 123) && (keycode <= 126))
		move_sets(keycode, image);
	image->shift = (keycode == 69) ? (image->shift + 3) : image->shift;
	image->shift = (keycode == 78) ? (image->shift - 3) : image->shift;
	set_fract(keycode, image);
	if (image->fract_flag == NEWTON)
		newt_sets(keycode, image);
	if (keycode == 24)
		image->i_params[0] = image->i_params[0] + 10;
	if ((keycode == 27) && (image->i_params[0] >= 110))
		image->i_params[0] = image->i_params[0] - 10;
	draw_fract(image, ((double)(image->size)));
	mlx_clear_window(image->mlx_ptr, image->win_ptr);
	mlx_put_image_to_window(image->mlx_ptr, image->win_ptr,
							image->image_ptr, 0, 0);
	return (0);
}

int		ft_str_cmp(char *str1, char *str2)
{
	int i;
	int	res;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if (str1[i] != str2[i])
		return (0);
	return (1);
}
