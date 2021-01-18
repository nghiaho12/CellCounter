#ifndef __DEFINES_H__
#define __DEFINES_H__

#define VERSION_MAJOR 2021
#define VERSION_MINOR 1
#define VERSION_SUB 17

#ifndef M_PI
#define M_PI		3.14159265358979323846	/* pi */
#endif

#ifndef M_PI_2
#define M_PI_2		1.57079632679489661923	/* pi/2 */
#endif

#ifdef _WIN32
	#ifndef GL_BGR
	#define GL_BGR                            0x80E0
	#endif
#endif

#endif
