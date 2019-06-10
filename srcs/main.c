/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htorp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 13:59:48 by htorp             #+#    #+#             */
/*   Updated: 2019/03/08 13:59:53 by htorp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	reshape(double p, double q, t_image *image, int flag)
{
	double	d_l;
	double	d_r;
	double	d_t;
	double	d_b;
	double	mult;

	mult = 0.9;
	d_l = image->left_bor - p;
	d_r = image->right_bor - p;
	d_t = image->top_bor - q;
	d_b = image->bot_bor - q;
	if (flag == 1)
	{
		image->left_bor = d_l * mult + p;
		image->right_bor = d_r * mult + p;
		image->top_bor = d_t * mult + q;
		image->bot_bor = d_b * mult + q;
	}
	if (flag == -1)
	{
		image->left_bor = d_l / mult + p;
		image->right_bor = d_r / mult + p;
		image->top_bor = d_t / mult + q;
		image->bot_bor = d_b / mult + q;
	}
}

void	image_presets(t_image *image, int size, char *s)
{
	image->shift = 5;
	image->size = size;
	image->r_mouse_flag = 0;
	image->l_mouse_flag = 0;
	image->bpp = 8;
	image->sl = 400;
	image->enin = 0;
	image->mlx_ptr = mlx_init();
	image->win_ptr = mlx_new_window(image->mlx_ptr, size, size, s);
	image->image_ptr = mlx_new_image(image->mlx_ptr, size, size);
	image->data = mlx_get_data_addr(image->image_ptr,
			&(image->bpp), &(image->sl), &(image->enin));
	image->i_params = (int*)malloc(sizeof(int) * 4);
	image->i_params[0] = 100;
	image->i_params[1] = 0x2F1F3F;
	image->i_params[2] = 0xFFFFFF;
	image->i_params[3] = 3;
	image->d_params = (double*)malloc(sizeof(double) * 2);
}

void	usage()
{
	write(1, "Please, write only one parameter from this list:\n", 49);
	write(1, "    Mandelbrot;\n", 16);
	write(1, "    Julia;\n", 11);
	write(1, "    A_fract;\n", 13);
	write(1, "    Spider;\n", 12);
	write(1, "    Newton.\n", 12);
	exit(0);
}

void	set_user_fract(t_image *image, char *s)
{
	image->fract_flag = 0;
	if (ft_str_cmp(s, "Mandelbrot"))
		mandel_fract(image);
	if (ft_str_cmp(s, "Julia"))
		julia_fract(image);
	if (ft_str_cmp(s, "A_fract"))
		a_fract(image);
	if (ft_str_cmp(s, "Spider"))
		spider_fract(image);
	if (ft_str_cmp(s, "Newton"))
		newton_fract(image);
	if (image->fract_flag == 0)
		usage();
}

int		main(int argc, char **argv)
{
	t_image	*im1;
	int		size;

	if (argc != 2)
		usage();
	size = 1024;
	im1 = (t_image*)malloc(sizeof(t_image));
	image_presets(im1, size, "fdf1");
	set_user_fract(im1, argv[1]);
	draw_fract(im1, (double)size);
	mlx_clear_window(im1->mlx_ptr, im1->win_ptr);
	mlx_put_image_to_window(im1->mlx_ptr, im1->win_ptr, im1->image_ptr, 0, 0);
	mlx_hook(im1->win_ptr, 2, 0, key_press, im1);
	mlx_hook(im1->win_ptr, 4, 0, mouse_press, im1);
	mlx_hook(im1->win_ptr, 5, 0, mouse_release, im1);
	mlx_hook(im1->win_ptr, 6, 0, mouse_move, im1);
	mlx_hook(im1->win_ptr, 17, 0, red_close, im1);
	mlx_loop(im1->mlx_ptr);
	return (0);
}
