#ifndef _UTILS_H
#define _UTILS_H

void	*getstorage( int );
void	errorexit( string );
void	keycopy( HU_int*, const HU_int* const, const int );
void	keycopy( HU_int*, const Hcode& );
void	keycopy( Hcode&, const HU_int* const );
char	*int2bins( unsigned int, int );

#endif