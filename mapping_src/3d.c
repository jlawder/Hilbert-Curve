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
	Hcode v;

	int a,b,c;
    
	for (a = 0; a < DIM; a++)
		for (b = 0; b < DIM; b++)
			for (c = 0; c < DIM; c++)
       				{
					pt.hcode[0] = a;
					pt.hcode[1] = b;
					pt.hcode[2] = c;
					printf("%d\t%d\t%d\n", pt.hcode[0], pt.hcode[1], pt.hcode[2]);
					v = H_encode(pt);
					printf("%d\t%d\t%d\n", v.hcode[2], v.hcode[1], v.hcode[0]);
					pt = H_decode(v);
					printf("%d\t%d\t%d\n\n", pt.hcode[0], pt.hcode[1], pt.hcode[2]);
				}
        
	return 0;
}

/*

....produces the following output....

0       0       0	(coordinates of the original point)
0       0       0	(the point's hilbert curve sequance number, calculated by H_encode())
0       0       0	(coordinates corresponding to the sequence number, calculated by H_decode())

0	0	1
0	0	7
0	0	1

0	0	2
0	0	8
0	0	2

0	1	0
0	0	1
0	1	0

0	1	1
0	0	6
0	1	1

0	1	2
0	0	15
0	1	2

0	2	0
0	0	26
0	2	0

0	2	1
0	0	27
0	2	1

0	2	2
0	0	16
0	2	2

1	0	0
0	0	3
1	0	0

1	0	1
0	0	4
1	0	1

1	0	2
0	0	9
1	0	2

1	1	0
0	0	2
1	1	0

1	1	1
0	0	5
1	1	1

1	1	2
0	0	14
1	1	2

1	2	0
0	0	29
1	2	0

......
........
etc

*/
