int dot_color(int max_step, int cur_step, int near_edge, int near_fract)
{
	int		res;
	int 	mask;
	double	step;
	int		color;
	int 	sht;

	color = (30 * cur_step) % 255;
    res = 0;
    res = res | (color);
    res = res | (color << 8);
	return (res);
}

double mult_re(double a_re, double a_im, double b_re, double b_im)
{
    double res;

    res = a_re * b_re - a_im * b_im;
    return (res);
}

double mult_im(double a_re, double a_im, double b_re, double b_im)
{
    double res;

    res = a_re * b_im + a_im * b_re;
    return (res);
}

double  div_re(double a_re, double a_im, double b_re, double b_im)
{
    double res;

    res = (a_re * b_re + a_im * b_im) / ( b_re * b_re + b_im * b_im);
    return (res);
}

double  div_im(double a_re, double a_im, double b_re, double b_im)
{
    double res;

    res = (a_im * b_re - a_re * b_im) / ( b_re * b_re + b_im * b_im);
    return (res);
}

double  pow_re(double a_re, double a_im, int ext)
{
    int i;
    double v_re;
    double v_im;
    double t_re;
    double t_im;

    v_re = a_re;
    v_im = a_im;
    i = 0;
    while (i < ext - 1)
    {
        t_re = mult_re(v_re, v_im, v_re, v_im);
        t_im = mult_im(v_re, v_im, v_re, v_im);
        v_re = t_re;
        v_im = t_im;
        i++;
    }
    return (v_re);
}

double  pow_im(double a_re, double a_im, int ext)
{
    int i;
    double v_re;
    double v_im;
    double t_re;
    double t_im;

    v_re = a_re;
    v_im = a_im;
    i = 0;
    while (i < ext - 1)
    {
        t_re = mult_re(v_re, v_im, v_re, v_im);
        t_im = mult_im(v_re, v_im, v_re, v_im);
        v_re = t_re;
        v_im = t_im;
        i++;
    }
    return (v_im);
}

__kernel void vector_add(__global const double *X, __global const double *Y, __global int *C, __global const int *i_params,  __global const double *d_params)
{
    int i = get_global_id(0);
    int 	step;
    int     max_step;
    int     n;
    double  z_re;
    double  z_im;
    double  up_re;
    double  up_im;
    double  down_re;
    double  down_im;
    double	count;
    int     edge_color;
    int     fract_color;

    max_step = i_params[0];
    edge_color = i_params[1];
    fract_color = i_params[2];
    z_re = X[i];
    z_im = Y[i];
    n = i_params[3];
    up_re = pow_re(z_re, z_im, n) * (n - 1) + 1;
    up_im = pow_im(z_re, z_im, n) * (n - 1);
    down_re = n * pow_re(z_re, z_im, n - 1);
    down_im = n * pow_im(z_re, z_im, n - 1);
    z_re = div_re(up_re, up_im, down_re, down_im);
    z_im = div_im(up_re, up_im, down_re, down_im);
    step = 0;
    count = 0;
    while (step < max_step)
    {
        count = z_re * z_re + z_im + z_im;
    	if (count > 16)
    		break ;
    	up_re = pow_re(z_re, z_im, n) * (n - 1) + 1;
        up_im = pow_im(z_re, z_im, n) * (n - 1);
        down_re = n * pow_re(z_re, z_im, n - 1);
        down_im = n * pow_im(z_re, z_im, n - 1);
        z_re = div_re(up_re, up_im, down_re, down_im);
        z_im = div_im(up_re, up_im, down_re, down_im);
    	step++;
    }
    if (step < max_step)
        C[i] = dot_color(max_step, step, edge_color, fract_color);
    else
        C[i] = 0xF4A460;
}