/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_sets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htorp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:00:48 by htorp             #+#    #+#             */
/*   Updated: 2019/03/08 14:00:51 by htorp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	mandel_fract(t_image *image)
{
	image->fract_flag = MANDEL;
	image->left_bor = -2.5;
	image->right_bor = 1.5;
	image->top_bor = -2;
	image->bot_bor = 2;
}

void	julia_fract(t_image *image)
{
	image->fract_flag = JULIA;
	image->left_bor = -2;
	image->right_bor = 2;
	image->top_bor = -2;
	image->bot_bor = 2;
	image->d_params[0] = 0.28;
	image->d_params[1] = 0.0113;
}

void	spider_fract(t_image *image)
{
	image->fract_flag = SPIDER;
	image->left_bor = -250;
	image->right_bor = 150;
	image->top_bor = -200;
	image->bot_bor = 200;
}

void	a_fract(t_image *image)
{
	image->fract_flag = A_FRACT;
	image->left_bor = -450;
	image->right_bor = 550;
	image->top_bor = -500;
	image->bot_bor = 500;
}

void	newton_fract(t_image *image)
{
	image->fract_flag = NEWTON;
	image->left_bor = -2;
	image->right_bor = 2;
	image->top_bor = -2;
	image->bot_bor = 2;
}
