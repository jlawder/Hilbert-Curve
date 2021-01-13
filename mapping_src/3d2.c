#include "mapping.h"

int main() {  
/*    
make sure mapping.h has the following:
#define DIM 3
#define NUMBITS 32
#define WORDBITS 32

make sure mapping.c has the following:
const U_int g_mask[] = {4, 2, 1};
*/

	Point pt;
	Hcode v = {0};

	int i;
    
	for (i = 0; i < 20; i++)
        {
		v.hcode[0] = i;
		v.hcode[1] = 0;
		v.hcode[2] = 0;
		printf("%d\t%d\t%d\n", v.hcode[2], v.hcode[1], v.hcode[0]);
		pt = H_decode(v);
		printf("%d\t%d\t%d\n", pt.hcode[0], pt.hcode[1], pt.hcode[2]);
		v = H_encode(pt);
		printf("%d\t%d\t%d\n\n", v.hcode[2], v.hcode[1], v.hcode[0]);
	}

	return 0;
}

/*

....produces the following output....

0       0       0	(sequence number of first point on Hilbert curve)
0       0       0	(coordinates corresponding to the sequence number, calculated by H_decode())
0       0       0	(the point's sequence number, calculated by H_encode())

0       0       1	(sequence number of second point on Hilbert curve)
0       1       0	(coordinates of second point on curve - NB is adjacent to the first point)
0       0       1

0	0	2
1	1	0
0	0	2

0	0	3
1	0	0
0	0	3

0	0	4
1	0	1
0	0	4

0	0	5
1	1	1
0	0	5

0	0	6
0	1	1
0	0	6

0	0	7
0	0	1
0	0	7

0	0	8
0	0	2
0	0	8

0	0	9
1	0	2
0	0	9

0	0	10
1	0	3
0	0	10

0	0	11
0	0	3
0	0	11

0	0	12
0	1	3
0	0	12

0	0	13
1	1	3
0	0	13

0	0	14
1	1	2
0	0	14

0	0	15
0	1	2
0	0	15

0	0	16
0	2	2
0	0	16

0	0	17
1	2	2
0	0	17

0	0	18
1	2	3
0	0	18

......
........
etc

*/
