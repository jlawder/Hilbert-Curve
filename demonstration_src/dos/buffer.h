// Copyright (C) Jonathan Lawder 2001

#ifndef _BUFFER_H
#define _BUFFER_H

#include <map>
#include <stack>

#ifdef DEV
#ifdef __MSDOS__
	#include "..\gendefs.h"
#else
	#include "../gendefs.h"
#endif
#else
	#include "gendefs.h"
#endif

#include "page.h"

class DBASE;
class MED;

/*============================================================================*/
/*                            BUFF_PAGE                          	      */
/*============================================================================*/

class BUFF_PAGE {

	friend class DBASE;
	friend class BUFFER;

private:

	BUFF_PAGE( int dims, int p_entries, MED *m );
//	~BUFF_PAGE(); not needed

	bool	mod, fix, query;
	U_int	lru;
	PAGE	BPage;
	
	int bp_insert_on_page( const PU_int* const );
	int bp_delete_from_page( PU_int* );

//private:	
	
	int	dimensions;
	int	bp_page_entry_bytes;
};

/*============================================================================*/
/*                            BUFFER                	          	      */
/*============================================================================*/

typedef map<U_int, int>::value_type valTypeB1;

class BUFFER {
	
	friend class DBASE;

private:
	
	BUFFER( int dims, int b_slots, int p_entries, DBASE* );
	~BUFFER();
	
	int			num_Bslots;
	vector<BUFF_PAGE*>	BSlot;

	int b_page_retrieve( int );
	int b_data_insert( PU_int*, int );
	int b_data_delete( PU_int*, int );

// private:		

	DBASE		*DB;
	int		dimensions;
	U_int		LRU;
	int		free_Bslots;	// available buffslots; in the range 0-numBslots-1
	int		b_page_bytes;	// no. of bytes in a page
	
	stack<int>	FreeBufferList;	// free buffer slot list
	map<U_int, int>	LRU_idx;	// < lru, buffslot >
	map<int, int>	Buff_idx;	// < lpage, buffslot >

	void Buff_idx_insert( int, int );
	void Buff_idx_erase( int, int );
	
	inline int in_Buffer( int );
	U_int inc_LRU( int );

	int b_process_overflow( int );
	int b_process_underflow( int );

	inline int b_get_buffer_slot();
	int b_swapout();

	int b_merge_pages( int, int );
	int b_shift_from_left( int, int );
	int b_shift_from_right( int, int );

	int b_admin( int, int, int, int );
};


#endif	// #ifndef _BUFFER_H