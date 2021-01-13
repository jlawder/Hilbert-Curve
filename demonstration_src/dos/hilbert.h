#ifndef _HILBERT_H
#define _HILBERT_H

HU_int* ENCODE( HU_int*, const PU_int* const, int );
PU_int* DECODE( PU_int*, HU_int*, int );
bool H_nextmatch_PM( PU_int *query, HU_int *match, HU_int *key, U_int Qsaf, int dimensions );
bool H_nextmatch_RQ( PU_int *LB, PU_int *UB, HU_int *match, HU_int *key, int dimensions );

#endif