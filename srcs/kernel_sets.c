/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_sets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htorp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:00:31 by htorp             #+#    #+#             */
/*   Updated: 2019/03/08 14:00:34 by htorp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	kernel_presets(t_kern_params *k)
{
	cl_device_type type;

	type = CL_DEVICE_TYPE_GPU;
	k->pl_id = NULL;
	k->did = NULL;
	k->ret = clGetPlatformIDs(1, &(k->pl_id), &(k->ret_num_pl));
	k->ret = clGetDeviceIDs((k->pl_id), type, 1, &(k->did), &(k->rnd));
	k->ct = clCreateContext(NULL, 1, &(k->did), NULL, NULL, &(k->ret));
	k->cq = clCreateCommandQueue(k->ct, k->did, 0, &(k->ret));
}

void	mem_sets(t_kern_params *k, t_kern_data *kd, int ls)
{
	cl_mem_flags	ro;
	cl_mem_flags	wo;
	size_t			sd;
	size_t			si;
	cl_bool			b;

	ro = CL_MEM_READ_ONLY;
	wo = CL_MEM_WRITE_ONLY;
	sd = sizeof(double);
	si = sizeof(int);
	b = CL_TRUE;
	k->po = clCreateBuffer(k->ct, ro, ls * sd, NULL, &(k->ret));
	k->qo = clCreateBuffer(k->ct, ro, ls * sd, NULL, &(k->ret));
	k->co = clCreateBuffer(k->ct, wo, ls * si, NULL, &(k->ret));
	k->ip = clCreateBuffer(k->ct, ro, 4 * si, NULL, &(k->ret));
	k->dp = clCreateBuffer(k->ct, ro, 2 * sd, NULL, &(k->ret));
	clEnqueueWriteBuffer(k->cq, k->po, b, 0, ls * sd, kd->cl_p, 0, NULL, NULL);
	clEnqueueWriteBuffer(k->cq, k->qo, b, 0, ls * sd, kd->cl_q, 0, NULL, NULL);
	clEnqueueWriteBuffer(k->cq, k->ip, b, 0, 4 * si, kd->ip, 0, NULL, NULL);
	clEnqueueWriteBuffer(k->cq, k->dp, b, 0, 2 * sd, kd->dp, 0, NULL, NULL);
}

void	kernel_build(t_kern_params *kp, char *s_str, size_t s_size, int ls)
{
	const char		**str;
	const size_t	*size;
	const size_t	*gis;
	const size_t	*lis;

	str = (const char **)&s_str;
	size = (const size_t *)&s_size;
	gis = &(kp->gis);
	lis = &(kp->lis);
	kp->program = clCreateProgramWithSource(kp->ct, 1, str, size, &(kp->ret));
	kp->ret = clBuildProgram(kp->program, 1, &(kp->did), NULL, NULL, NULL);
	kp->k = clCreateKernel(kp->program, "vector_add", &(kp->ret));
	clSetKernelArg(kp->k, 0, sizeof(cl_mem), (void *)&(kp->po));
	clSetKernelArg(kp->k, 1, sizeof(cl_mem), (void *)&(kp->qo));
	clSetKernelArg(kp->k, 2, sizeof(cl_mem), (void *)&(kp->co));
	clSetKernelArg(kp->k, 3, sizeof(cl_mem), (void *)&(kp->ip));
	clSetKernelArg(kp->k, 4, sizeof(cl_mem), (void *)&(kp->dp));
	kp->gis = ls;
	kp->lis = 64;
	clEnqueueNDRangeKernel(kp->cq, kp->k, 1, NULL, gis, lis, 0, NULL, NULL);
}

void	kernel_free(t_kern_params *kern_params, char *source_str)
{
	kern_params->ret = clFlush(kern_params->cq);
	kern_params->ret = clFinish(kern_params->cq);
	kern_params->ret = clReleaseKernel(kern_params->k);
	kern_params->ret = clReleaseProgram(kern_params->program);
	kern_params->ret = clReleaseMemObject(kern_params->po);
	kern_params->ret = clReleaseMemObject(kern_params->qo);
	kern_params->ret = clReleaseMemObject(kern_params->co);
	kern_params->ret = clReleaseMemObject(kern_params->ip);
	kern_params->ret = clReleaseMemObject(kern_params->dp);
	kern_params->ret = clReleaseCommandQueue(kern_params->cq);
	kern_params->ret = clReleaseContext(kern_params->ct);
	free(source_str);
}

void	w_kernel(t_kern_data *kd, int ls, t_image *image)
{
	char			*source_str;
	size_t			source_size;
	t_kern_params	*k;
	size_t			s;
	cl_bool			b;

	b = CL_TRUE;
	s = ls * sizeof(int);
	set_fd(image, &source_str, &source_size);
	k = (t_kern_params*)malloc(sizeof(t_kern_params));
	kernel_presets(k);
	mem_sets(k, kd, ls);
	kernel_build(k, source_str, source_size, ls);
	clEnqueueReadBuffer(k->cq, k->co, b, 0, s, kd->cl_c, 0, NULL, NULL);
	kernel_free(k, source_str);
}
