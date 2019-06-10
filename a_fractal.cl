int dot_color(int max_step, int cur_step, int near_edge, int near_fract)
{
	int		res;
	int 	mask;
	double	step;
	int		color;
	int 	sht;

	res = 0;
	mask = 0xFF0000;
	sht = 16;
	step = ((double)(((mask & near_fract) >> sht)  - ((mask & near_edge) >> sht))) / (double)max_step;
	color = (int)(step * (double)cur_step) + ((mask & near_edge) >> sht);
	res = res |(color << sht);
	mask = 0xFF00;
	sht = 8;
	step = ((double)(((mask & near_fract) >> sht)  - ((mask & near_edge) >> sht))) / (double)max_step;
	color = (int)(step * (double)cur_step) + ((mask & near_edge) >> sht);
	res = res |(color << sht);
	mask = 0xFF;
	sht = 0;
	step = ((double)(((mask & near_fract) >> sht)  - ((mask & near_edge) >> sht))) / (double)max_step;
	color = (int)(step * (double)cur_step) + ((mask & near_edge) >> sht);
	res = res | (color << sht);
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
    p = 0.85;
    q = 0.6;
    while (step < max_step)
    {
    	x_f = x;
    	y_f = y;
    	x = (p * x - q * y) * (1 - x) + y * (p * y + q * x);
    	y = (p * y + q * x) * (1 - x) - y * (p * x - q * y);
    	count = x * x + y * y;
    	if (count > 100)
    		break ;
    	step++;
    }
    if (step < max_step)
        C[i] = dot_color(max_step, step, edge_color, fract_color);
    else
        C[i] = 0xFFFFFF;
}