/**********************************************************
 * This file is generated by 20-sim ANSI-C Code Generator
 *
 *  file:  xxsubmod.c
 *  subm:  PositionControllerPan
 *  model: PositionControllerPan
 *  expmt: Jiwy
 *  date:  June 2, 2021
 *  time:  12:30:12 PM
 *  user:  20-sim 4.8 Campus License
 *  from:  Universiteit Twente
 *  build: 4.8.3.10415
 **********************************************************/

/* Standard include files */
#include <stdlib.h>

/* 20-sim include files */
#include "xxmodel.h"
#include "xxinteg.h"
#include "xxfuncs.h"
#include "xxsubmod.h"
#include "motionprofiles.h"
#include "EulerAngles.h"

/* The submodel I/O variables */
XXInteger xx_number_of_inputs = 2;
XXInteger xx_number_of_outputs = 2;

/* the names of the submodel io variables
   uncomment this part if you need these names
XXString xx_input_names[] = {
	"in",
	"position"
,	NULL
};
XXString xx_output_names[] = {
	"corr",
	"out"
,	NULL
};
*/
/* This function sets the input variables from the input vector */
void XXCopyInputsToVariables (XXDouble *u)
{
	/* Copy the input vector to the input variables */
	xx_V[7] = u[0];		/* in */
	xx_V[8] = u[1];		/* position */

}

/* This function uses the output variables to fill the output vector */
void XXCopyVariablesToOutputs (XXDouble *y)
{
	/* Copy the output variables to the output vector */
	y[0] = 	xx_V[6];		/* corr */
	y[1] = 	xx_V[9];		/* out */

}

/* The initialization function for submodel */
void XXInitializeSubmodel (XXDouble *u, XXDouble *y, XXDouble t)
{
	/* Initialization phase (allocating memory) */
	xx_initialize = XXTRUE;
	xx_steps = 0;
	XXModelInitialize ();
	XXDiscreteInitialize ();

	/* Copy the inputs */
	xx_time = t;
	XXCopyInputsToVariables (u);

	/* Calculate the model for the first time */
	XXCalculateInitial ();
	XXCalculateStatic ();
	XXCalculateInput ();
	XXCalculateDynamic ();
	XXCalculateOutput ();

	/* Set the outputs */
	XXCopyVariablesToOutputs (y);

	/* End of initialization phase */
	xx_initialize = XXFALSE;
}

/* The function that calculates the submodel */
void XXCalculateSubmodel (XXDouble *u, XXDouble *y, XXDouble t)
{
	/* Copy the inputs */
	xx_time = t;
	XXCopyInputsToVariables (u);

	/* Calculate the model */
	XXCalculateInput ();
	XXDiscreteStep ();
	XXCalculateOutput ();

	/* Copy the outputs */
	XXCopyVariablesToOutputs (y);
}

/* The termination function for submodel */
void XXTerminateSubmodel (XXDouble *u, XXDouble *y, XXDouble t)
{
	/* Copy the inputs */
	xx_time = t;
	XXCopyInputsToVariables (u);

	/* Calculate the final model equations */
	XXCalculateFinal ();

	/* Set the outputs */
	XXCopyVariablesToOutputs (y);

	/* and terminate the model itself (releasing memory) */
	XXModelTerminate ();
	XXDiscreteTerminate ();
}

