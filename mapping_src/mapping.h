#include <stdio.h>
#include <stdlib.h>

/*
 * 'DIM' is the number of dimensions in space through which the
 * Hilbert Curve passes.
 * Don't use this implementation with values for DIM of > 31! 
 * Also, make sure you use a 32 bit compiler!
 */
#define	DIM 3

typedef unsigned int U_int;

/*
 * An Hcode holds the Hilbert Curve sequence number of a point as an array
 * of unsigned ints. The least significant bit of hcode[0] is the least
 * significant bit of the sequence number.
 */
typedef struct {
	U_int	hcode[DIM];
}Hcode;

typedef Hcode Point;

/*
 * retained for historical reasons: the number of bits in an attribute value:
 * effectively the order of a curve
 */
#define		NUMBITS			32

/*
 * the number of bits in a word used to store an hcode (or in an element of
 * an array that's used)
 */
#define		WORDBITS		32


Hcode H_encode(Point);

Point H_decode (Hcode);
