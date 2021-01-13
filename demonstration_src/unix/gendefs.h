#ifndef _GENDEFS_H
#define _GENDEFS_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <limits.h>		// defines UINT_MAX

using namespace std;

/*============================================================================*/
/*                            TYPEDEFS	                          	      */
/*============================================================================*/
typedef unsigned char	u1BYTE;
typedef unsigned short	u2BYTES;
typedef unsigned int	U_int;
#define HU_int			U_int	// a HU_int* is a hilbert code
#define PU_int			U_int	// a PU_int* is a 'point' (array of coordinates)

/*============================================================================*/
/*                            Hcode	                          	      */
/*============================================================================*/
class Hcode{
public:
	Hcode( int dims );
	~Hcode() { hcode.erase( hcode.begin(), hcode.end() ); }; // not needed?

	vector<U_int> hcode;
};

/*============================================================================*/
/*                            #defines	                          	      */
/*============================================================================*/

#define		WORDBITS		32
#define		NUMBITS			32
#ifndef NO_EXTRA_TOKENS
	#define NO_EXTRA_TOKENS		0
#endif
	
// #define JKLDEBUG

#endif // _GENDEFS_H