/**
 * \file      exp0.h
 * \brief     Differentiable exponential/logarithmic functions that intersect
 *            the origin
 * \author    Josh Klodnicki
 * \date      Created:  2024-07-15
 * \copyright (c) 2024 Josh Klodnicki.
 *            Distributed under terms of the MIT license.
 */

#ifndef EXP0_H
#define EXP0_H

#include <stdint.h>

/******** Configuration ********/

#ifndef EXP0_INCLUDE_CONFIG
# define EXP0_INCLUDE_CONFIG     0
#endif

#if EXP0_INCLUDE_CONFIG
# include "exp0_config.h"
#endif

#ifndef EXP0_DEFAULT_TYPE
# define EXP0_DEFAULT_TYPE       double
#endif

#ifndef EXP0_PROVIDE_GENERICS
# define EXP0_PROVIDE_GENERICS   0
#endif

#ifndef EXP0_USE_DOUBLE
# define EXP0_USE_DOUBLE         1
#endif

/******** Macros ********/

#define EXP0_VERSION_MAJOR   0
#define EXP0_VERSION_MINOR   1
#define EXP0_VERSION_BUILD   0

#if (EXP0_USE_DOUBLE && EXP0_PROVIDE_GENERICS)
# define exp0_func(x0, y0, slope) \
	_Generic((x0)*(y0)*(slope), \
		double:    exp0_func_double, \
		float:     exp0_func_float, \
		default:   exp0_func \
	)(x0, y0, slope)

# define exp0_eval(func, x) \
	_Generic((func), \
		exp0_func_double_st:   exp0_eval_double, \
		exp0_func_float_st:    exp0_eval_float \
	)(func, x)
#endif

/******** Typedefs ********/

#if EXP0_USE_DOUBLE
typedef EXP0_DEFAULT_TYPE   exp0_default_kt;
#else
typedef float               exp0_default_kt;
#endif

typedef struct exp0_func {
	exp0_default_kt   a;
	exp0_default_kt   b;
} exp0_func_st;

#if EXP0_USE_DOUBLE
typedef struct exp0_func_float {
	float   a;
	float   b;
} exp0_func_float_st;

typedef struct exp0_func_double {
	double   a;
	double   b;
} exp0_func_double_st;
#endif

typedef struct exp0_version {
	uint8_t    major;
	uint8_t    minor;
	uint16_t   build;
} exp0_version_st;

/******** Function Prototypes ********/

exp0_func_st
exp0_func (exp0_default_kt x0, exp0_default_kt y0, exp0_default_kt slope);

#if EXP0_USE_DOUBLE
exp0_func_float_st    exp0_func_float    (float  x0, float  y0, float  slope);
exp0_func_double_st   exp0_func_double   (double x0, double y0, double slope);
#endif

#if !(EXP0_USE_DOUBLE && EXP0_PROVIDE_GENERICS)
exp0_default_kt exp0_eval (exp0_func_st func, exp0_default_kt x);
#endif

#if EXP0_USE_DOUBLE
float    exp0_eval_float    (exp0_func_float_st    func, float    x);
double   exp0_eval_double   (exp0_func_double_st   func, double   x);
#endif

/******** Inline Function Definitions ********/

inline exp0_version_st exp0_version (void) {
	return (exp0_version_st){
		EXP0_VERSION_MAJOR,
		EXP0_VERSION_MINOR,
		EXP0_VERSION_BUILD,
	};
}

#endif // EXP0_H

// vim: ft=c.doxygen
