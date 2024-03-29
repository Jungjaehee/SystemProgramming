/********************************************************

 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "201701594",              /* Team name */

    "Jaehee, Jung",     /* First member full name */
    "wogml5890@gmail.com",  /* First member email address */

    "",                   /* Second member full name (leave blank if none) */
    ""                    /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst) 
{
    int i,j;
    int dim_1 = (dim - 1) * dim;
    int tmp= 0;
    for (i = 0; i < dim; i += 32)
    {
	for (j = 0; j < dim; j++)
	{
		dst[dim_1] = src[tmp];
		tmp += dim;
		dst[(dim_1+1)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 2)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 3)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 4)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 5)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 6)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 7)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 8)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 9)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 10)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 11)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 12)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 13)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 14)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 15)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 16)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 17)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 18)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 19)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 20)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 21)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 22)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 23)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 24)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 25)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 26)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 27)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 28)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 29)] = src[tmp];
		tmp += dim;
		dst[(dim_1 + 30)] = src[tmp];
		tmp += dim;
		dst[dim_1+31] = src[tmp];
		tmp -= (31 * dim);
		tmp++;
		dim_1 -= dim;
	}
	dim_1+=dim*dim;
	dim_1+=32;
	tmp += 31 * dim;
    } 
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);   
    add_rotate_function(&rotate, rotate_descr);   
    /* ... Register additional test functions here */
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) 
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	    accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst) 
{
int i, j;
	int tmp;
	dst[0].red = (src[0].red + src[1].red + src[dim].red + src[dim + 1].red)/4;
	dst[0].green = (src[0].green + src[1].green + src[dim].green + src[dim + 1].green) / 4;
	dst[0].blue = (src[0].blue + src[1].blue + src[dim].blue + src[dim + 1].blue) / 4;
	
	dst[dim-1].red = (src[dim - 2].red + src[dim-1].red + src[dim+dim-2].red + src[dim +dim-1].red) / 4;
	dst[dim-1].green = (src[dim - 2].green + src[dim-1].green + src[dim+dim-2].green + src[dim + dim-1].green) / 4;
	dst[dim-1].blue = (src[dim - 2].blue + src[dim-1].blue + src[dim+dim-2].blue + src[dim + dim-1].blue) / 4;
	
	tmp = (dim - 1)*dim;
	dst[tmp].red = (src[tmp-dim].red + src[tmp-dim+1].red + src[tmp].red + src[tmp +1].red)/4;
	dst[tmp].green = (src[tmp-dim].green + src[tmp - dim + 1].green + src[tmp ].green + src[tmp+ 1].green)/4;
	dst[tmp].blue = (src[tmp-dim].blue + src[tmp - dim + 1].blue + src[tmp].blue + src[tmp+ 1].blue)/4;

	tmp = dim*dim-1;
	dst[tmp].red = (src[tmp-dim-1].red + src[tmp -dim].red + src[tmp-1].red + src[tmp].red) / 4;
	dst[tmp].green = (src[tmp-1].green + src[tmp].green + src[tmp - dim-1].green + src[tmp -dim].green) / 4;
	dst[tmp].blue = (src[tmp-dim-1].blue + src[tmp -dim].blue + src[tmp-1].blue + src[tmp].blue) / 4;

	for (j = 1; j < dim - 1; j++) {
		//i == 0;
		tmp = j - 1;
		dst[j].red = (src[tmp].red + src[(tmp + 1)].red + src[(tmp + 2)].red + src[(tmp + dim)].red + src[(tmp + dim + 1)].red + src[(tmp + dim + 2)].red) / 6;
		dst[j].green = (src[tmp].green + src[(tmp + 1)].green + src[(tmp + 2)].green + src[(tmp + dim)].green + src[(tmp + dim + 1)].green + src[(tmp + dim + 2)].green) / 6;
		dst[j].blue = (src[tmp].blue + src[(tmp + 1)].blue + src[(tmp + 2)].blue + src[(tmp + dim)].blue + src[(tmp + dim + 1)].blue + src[(tmp + dim + 2)].blue)/6;
		//i == dim - 1;
		tmp = dim * (dim - 2) + j - 1;
		dst[dim*(dim-1)+j].red = (src[tmp].red + src[(tmp + 1)].red + src[(tmp + 2)].red + src[(tmp + dim)].red + src[(tmp + dim + 1)].red + src[(tmp + dim + 2)].red) / 6;
		dst[dim*(dim - 1) + j].green = (src[tmp].green + src[(tmp + 1)].green + src[(tmp + 2)].green + src[(tmp + dim)].green + src[(tmp + dim + 1)].green + src[(tmp + dim + 2)].green) / 6;
		dst[dim*(dim - 1) + j].blue = (src[tmp].blue + src[(tmp + 1)].blue + src[(tmp + 2)].blue + src[(tmp + dim)].blue + src[(tmp + dim + 1)].blue + src[(tmp + dim + 2)].blue) / 6;
		//j==0
		tmp = dim * (j - 1);
		dst[j*dim].red = (src[tmp].red + src[(tmp + 1)].red + src[(tmp + dim)].red + src[(tmp + dim + 1)].red + src[(tmp + dim + dim)].red + src[(tmp + dim + dim + 1)].red) / 6;
		dst[j*dim].green = (src[tmp].green + src[(tmp + 1)].green + src[(tmp + dim)].green + src[(tmp + dim + 1)].green + src[(tmp + dim + dim)].green + src[(tmp + dim + dim + 1)].green) / 6;
		dst[j*dim].blue = (src[tmp].blue + src[(tmp + 1)].blue + src[(tmp + dim)].blue + src[(tmp + dim + 1)].blue + src[(tmp + dim + dim)].blue + src[(tmp + dim + dim + 1)].blue) / 6;
		//j==dim-1
		tmp = (j*dim)- 2;
		dst[j*dim+dim-1].red = (src[tmp].red + src[(tmp + 1)].red + src[(tmp + dim)].red + src[(tmp + dim + 1)].red + src[(tmp + dim + dim)].red + src[(tmp + dim + dim + 1)].red) / 6;
		dst[j*dim + dim - 1].green = (src[tmp].green + src[(tmp + 1)].green + src[(tmp + dim)].green + src[(tmp + dim + 1)].green + src[(tmp + dim + dim)].green + src[(tmp + dim + dim + 1)].green) / 6;
		dst[j*dim + dim - 1].blue = (src[tmp].blue + src[(tmp + 1)].blue + src[(tmp + dim)].blue + src[(tmp + dim + 1)].blue + src[(tmp + dim + dim)].blue + src[(tmp + dim + dim + 1)].blue) / 6;
	}
	for (i = 1; i < dim-1; i++) {
		for (j = 1; j < dim-1; j++) {
				tmp = i*dim+j;
				dst[tmp].red = (src[tmp - 1 - dim].red + src[tmp - dim].red + src[tmp - dim + 1].red + src[tmp - 1].red + src[tmp].red + src[tmp + 1].red + src[tmp + dim - 1].red + src[tmp + dim].red + src[tmp + dim + 1].red)/9;
				dst[tmp].green = (src[tmp - 1 - dim].green + src[tmp - dim].green + src[tmp - dim + 1].green + src[tmp - 1].green + src[tmp].green + src[tmp + 1].green + src[tmp + dim - 1].green + src[tmp + dim].green + src[tmp + dim + 1].green)/9;
				dst[tmp].blue = (src[tmp - 1 - dim].blue + src[tmp - dim].blue + src[tmp - dim + 1].blue + src[tmp - 1].blue + src[tmp].blue + src[tmp + 1].blue + src[tmp + dim - 1].blue + src[tmp + dim].blue + src[tmp + dim + 1].blue)/9;
		}
	}
}

/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* ... Register additional test functions here */
}

