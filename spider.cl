int dot_color(int cur_step)
{
	int		res;
	int		color;

	color = (30 * cur_step) % 255;
	res = 0;
	res = res | (color);
	res = res | (color << 8);
	return (res);
}

__kernel void vector_add(__global const double *X, __global const double *Y, __global int *C, __global const int *i_params,  __global const double *d_params)
{

    // Get the index of the current element to be processed
    int i = get_global_id(0);
    double	x;
    double	y;
    double	count;
    double	x_f;
    double  y_f;
    double  p;
    double  q;
    int 	step;
    int     max_step;
    int     edge_color;
    int     fract_color;

    // Do the operation
    max_step = i_params[0];
    edge_color = i_params[1];
    fract_color = i_params[2];
    //fract_color = 0xFFFFFF;
    step = 0;
    x = X[i] * 0.01;
    y = Y[i] * 0.01;
    p = x;
    q = y;
    while (step < max_step)
    {
    	x_f = x;
    	y_f = y;
    	x = x * x - y * y + p;
    	y = 2 * x_f * y + q;
    	p = p /2 + x;
    	q = q /2 + y;
    	count = x * x + y * y;
    	if (count > 4)
    		break ;
    	step++;
    }
    if (step < max_step)
        C[i] = dot_color(step);
    else
        C[i] = 0xFFFFFF;
}