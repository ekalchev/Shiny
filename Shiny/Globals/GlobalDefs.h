///////////////////////////////////////////////////////////////////////////////
//	File:    GlobalDefs.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////

#ifndef __GLOBALDEFS__
#define __GLOBALDEFS__


#define ShinyVersion 0.001
#define DEFAULT_EPSILON 0.1
#define MAX_REFLECTIVE_DEPTH 4
#define NUM_SAMPLES 1;

//THREADING
#ifdef _DEBUG
	#define NUM_TASKS 1
	#define NUM_THREADS 1
#else
	#define NUM_TASKS 2
	#define NUM_THREADS 2
#endif

class Vector3D;
typedef Vector3D Normal;


#endif