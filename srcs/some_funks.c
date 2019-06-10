/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_funks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htorp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:00:02 by htorp             #+#    #+#             */
/*   Updated: 2019/03/08 14:00:06 by htorp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	set_fd(t_image *image, char **source_str, size_t *source_size)
{
	FILE	*fp;

	if (image->fract_flag == MANDEL)
		fp = fopen("mundelbrot.cl", "r");
	if (image->fract_flag == JULIA)
		fp = fopen("julia.cl", "r");
	if (image->fract_flag == SPIDER)
		fp = fopen("spider.cl", "r");
	if (image->fract_flag == A_FRACT)
		fp = fopen("a_fractal.cl", "r");
	if (image->fract_flag == NEWTON)
		fp = fopen("newton_piscine.cl", "r");
	if (!fp)
	{
		fprintf(stderr, "Failed to load kernel.\n");
		exit(1);
	}
	*source_str = (char*)malloc(MAX_S_SIZE);
	*source_size = fread(*source_str, 1, MAX_S_SIZE, fp);
	fclose(fp);
}

int		mouse_release(int button, int x, int y, void *param)
{
	t_image *image;

	image = (t_image*)param;
	if (button == 1)
		image->l_mouse_flag = 0;
	if ((button == 2) && (image->fract_flag == JULIA))
		image->r_mouse_flag = 0;
	return (0);
}

void	fract_presets(t_kern_data *k_data, t_image *image, double sq_size)
{
	double	hor_step;
	double	ver_step;
	int		x;
	int		y;
	int		sz;

	sz = (int)sq_size;
	k_data->ip = image->i_params;
	k_data->dp = image->d_params;
	k_data->cl_p = (double*)malloc(sizeof(double) * sz * (int)sq_size);
	k_data->cl_q = (double*)malloc(sizeof(double) * sz * (int)sq_size);
	hor_step = (image->right_bor - image->left_bor) / sq_size;
	ver_step = (image->top_bor - image->bot_bor) / sq_size;
	x = 0;
	while (x < (int)sq_size)
	{
		y = 0;
		while (y < (int)sq_size)
		{
			k_data->cl_p[x + y * sz] = image->left_bor + (double)x * hor_step;
			k_data->cl_q[x + y * sz] = image->bot_bor + (double)y * ver_step;
			y++;
		}
		x++;
	}
}

void	draw_fract(t_image *image, double sq_size)
{
	t_kern_data	*kern_data;

	kern_data = (t_kern_data*)malloc(sizeof(t_kern_data));
	fract_presets(kern_data, image, sq_size);
	kern_data->cl_c = (int*)(image->data);
	w_kernel(kern_data, (int)sq_size * (int)sq_size, image);
	free(kern_data->cl_p);
	free(kern_data->cl_q);
	free(kern_data);
}

int		red_close(void *param)
{
	(void)param;
	exit(0);
}
