/*
 * File: main.c
 *
 * MATLAB Coder version            : 2.8
 * C/C++ source code generated on  : 26-Nov-2017 14:16:23
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include Files */
#include "rt_nonfinite.h"
#include "distortion.h"
#include "main.h"
#include "distortion_terminate.h"
#include "distortion_initialize.h"

/* Function Declarations */
static long argInit_int32_T(void);
static void main_distortion(void);

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : long
 */
static long argInit_int32_T(void)
{
  return 0L;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_distortion(void)
{
  double Y[57];

  /* Initialize function 'distortion' input arguments. */
  /* Initialize function input argument 'X'. */
  /* Call the entry-point 'distortion'. */
  distortion(argInit_int32_T(), Y);
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  distortion_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_distortion();

  /* Terminate the application.
     You do not need to do this more than one time. */
  distortion_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
