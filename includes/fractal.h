/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htorp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:01:28 by htorp             #+#    #+#             */
/*   Updated: 2019/03/08 14:01:30 by htorp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_FRACTAL_H
# define FRACTAL_FRACTAL_H

# include <stdio.h>
# include <stdlib.h>
# include <OpenCL/opencl.h>
# include <math.h>
# include <mlx.h>

# define MAX_S_SIZE		(0x100000)
# define MANDEL			(0x100000)
# define JULIA			(0x010000)
# define SPIDER			(0x001000)
# define A_FRACT		(0x000100)
# define NEWTON			(0x000010)

typedef struct			s_image
{
	double				left_bor;
	double				right_bor;
	double				top_bor;
	double				bot_bor;
	void				*image_ptr;
	void				*mlx_ptr;
	void				*win_ptr;
	char				*data;
	int					bpp;
	int					sl;
	int					enin;
	int					mouse_x;
	int					mouse_y;
	int					l_mouse_flag;
	int					r_mouse_flag;
	int					size;
	int					*i_params;
	double				*d_params;
	int					fract_flag;
	int					jul_x;
	int					jul_y;
	int					shift;
}						t_image;

typedef struct			s_kern_data
{
	double				*cl_p;
	double				*cl_q;
	int					*cl_c;
	int					*ip;
	double				*dp;
}						t_kern_data;

typedef struct			s_kern_params
{
	cl_platform_id		pl_id;
	cl_device_id		did;
	cl_uint				rnd;
	cl_uint				ret_num_pl;
	cl_int				ret;
	cl_context			ct;
	cl_command_queue	cq;
	cl_program			program;
	cl_kernel			k;
	size_t				gis;
	size_t				lis;
	cl_mem				po;
	cl_mem				qo;
	cl_mem				co;
	cl_mem				ip;
	cl_mem				dp;
}						t_kern_params;

void					mandel_fract(t_image *image);
void					julia_fract(t_image *image);
void					spider_fract(t_image *image);
void					a_fract(t_image *image);
void					newton_fract(t_image *image);
int						key_press(int keycode, void *param);
void					draw_fract(t_image *image, double sq_size);
int						mouse_move(int x, int y, void *param);
void					reshape(double p, double q, t_image *image, int flag);
int						mouse_press(int button, int x, int y, void *param);
void					w_kernel(t_kern_data *kd, int ls, t_image *im);
void					set_fd(t_image *im, char **source_str, size_t *s_size);
int						mouse_release(int button, int x, int y, void *param);
int						red_close(void *param);
int						ft_str_cmp(char *str1, char *str2);

#endif
