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

	Point pt1, pt2;

	int a,b,c;
    
	for (a = 0; a < DIM; a++)
		for (b = 0; b < DIM; b++)
			for (c = 0; c < DIM; c++)
       				{
					pt1.hcode[0] = a;
					pt1.hcode[1] = b;
					pt1.hcode[2] = c;
					printf("%d\t%d\t%d\n", pt1.hcode[0], pt1.hcode[1], pt1.hcode[2]);
					pt2 = H_decode(H_encode(pt1));
					printf("%d\t%d\t%d\n\n", pt2.hcode[0], pt2.hcode[1], pt2.hcode[2]);
				}
        
	return 0;
}

/*
....produces the following output....

0       0       0	(coordinates of the original point)
0       0       0	(coordinates of the original point, having been 'encoded' and 'decoded' again)

0       0       1
0       0       1

0       0       2
0       0       2

0       1       0
0       1       0

0       1       1
0       1       1

0       1       2
0       1       2

0       2       0
0       2       0

0       2       1
0       2       1

0       2       2
0       2       2
                                                                                                                                                                   
1       0       0                                                                                                                                                  
1       0       0                                                                                                                                                  
                                                                                                                                                                   
1       0       1                                                                                                                                                  
1       0       1                                                                                                                                                  

1       0       2
1       0       2

1       1       0
1       1       0

1       1       1
1       1       1

1       1       2
1       1       2

1       2       0
1       2       0

1       2       1
1       2       1

1       2       2
1       2       2

2       0       0
2       0       0

......
........
etc

*/
