// Copyright (C) Jonathan Lawder 2001

#ifndef _DB_H
#define _DB_H

#include <stack>

#ifdef DEV
#ifdef __MSDOS__
	#include "..\gendefs.h"
	#include "..\btree\btree.h"
#else
	#include "../gendefs.h"
	#include "../btree/btree.h"
#endif
#else
	#include "gendefs.h"
	#include "btree.h"
#endif

#include "buffer.h"

#define 	MEDIAN	   		5
#define		INF_SIZE		6

// p_page_entries must be at least EXTRA_RECORDS more than this
#define		THRESHOLD		30
#define		EXTRA_RECORDS		3

// RET_SET values/flags
#define 	_UNSPECIFIED_		0xffffffff
#define		MINTOKEN 		0
#define		MAXTOKEN		0xfffffffe

#ifdef JKLDEBUG
fstream fjunk1;
fstream fjunk2;
fstream fjunk3;
fstream fjunk4;
#endif	

/*============================================================================*/
/*                            MEDIAN_DATA                          	      */
/*============================================================================*/
class MED {

	friend class PAGE;
	
public:
	
	MED( int dims, int d_entries );	// constructor
	~MED();

private:

	int				dimensions;
	vector<Hcode>	MEDdata;
	// used for gaining random access to the hcodes of a page of data for the
	// purpose of finding the approximate median
	vector<int>		MEDmap;

	int p_median_calc_workspace( int );
	void p_shuffle_medmap( int );
};

class DBASE;
/*============================================================================*/
/*                            RET_SET                           	      */
/*============================================================================*/
class RET_SET {

	friend class DBASE;
	
private:

	RET_SET( int dims );
	~RET_SET();
	PU_int	*LB;	// lower bound point
	PU_int	*UB;	// upper bound point - not used in partial match queries
	U_int	Qsaf;	// mask used by partial match queries
	int	numspec;// no. of specified dims (partial matchqueries only)
	int	pos;	// search position on a page
	int	buffslot;
	unsigned char	flags;
};

/*============================================================================*/
/*                            	DBASE  	                        	      */
/*============================================================================*/

/* database object */
class DBASE {

public:

	DBASE( string name, int dims, int bt_n_entries, int b_slots, int p_entries );

	string		dbname;
 	BTree		BT;					// database page index
	MED		dbMED;
	
	int		LastPage;
	int		nextPID;
	int		NumFreePages;		// size of the FreePageList  - free pages in the db
	stack<int>	FreePageList;		// free logical page list
	fstream		fDB;
	
	bool db_create();
	bool db_open();
	bool db_close();
	
	// UPDATING .........................
	// should NOT return bools
	int db_data_insert( PU_int* );
	int db_data_delete( PU_int* );

	// QUERY PROCESSING ..................
	bool db_data_present( PU_int* );
 	bool db_open_set( PU_int *point, int *set_id );
	bool db_range_open_set( PU_int* LB, PU_int *HB, int *set_id );
	bool db_close_set( int set_id );
	bool db_fetch_another( int set_id, PU_int *retval );
	bool db_range_fetch_another( int set_id, PU_int *retval );
	
	// FOR CHECKING PURPOSES ..............
	void db_key_dump( string fname );
	void db_data_dump( string fname, char type );
	
	// FOR TESTING PURPOSES ..............
	void db_batch_update( char type, int num );
	bool db_getquery( PU_int *p, string message );
	bool db_getrange( PU_int *LB, PU_int *UB );
	void db_querytest( void );

	int dbi_get_new_page();
	
private:	
	
	int		dimensions;
	int		page_entries;		// no. of datum-points on a page + index entry
	int		bt_node_entries;	// no. of entries in a btree node + header
	int		num_Bslots;			// no. of buffer slots
	
	BUFFER		Buffer;				// the buffer
	vector<RET_SET*>	Ret_set;	// all members of this vector are 'ACTIVE'
	stack<int>	FreeRet_setList;
	
	void dbi_freepagelist_setup();
	void dbi_freepagelist_save();
	void db_freepagelist_dump();

	bool dbi_create_info();
	bool dbi_open_info();
};

#endif	// #ifndef _DB_H