// Copyright (C) Jonathan Lawder 2001

#ifndef _PAGE_H
#define _PAGE_H

#ifdef DEV
#ifdef __MSDOS__
	#include "..\gendefs.h"
#else
	#include "../gendefs.h"
#endif
#else
	#include "gendefs.h"
#endif

class MED;

/*============================================================================*/
/*                            HEADER	                          	      */
/*============================================================================*/

/* Page data held in the first 'data' element of a PAGE
   sizeof (INFO) MUST be <= sizeof (Hcode) */
typedef struct {
	int lpage;	/* the logical page no. of the page */
	int size;	/* the number of Hcodes on a page: doesn't include INFO */
} pageheader_t;

/*============================================================================*/
/*                            PAGE	                          	      */
/*============================================================================*/
class PAGE {

	friend class DBASE;
	friend class BUFFER;
	friend class BUFF_PAGE;

private:

	PAGE( int dims, int p_entries, MED* );	// constructor (GIVE SECOND PARAM A DEFAULT VALUE ????)
	PAGE( int dims, int p_entries );	// constuctor creates an empty page
	~PAGE();

	pageheader_t	*page_hdr;		// points at start of raw_data
	HU_int		*index;			// pointer to first hcode in raw_data after the header
	HU_int		**data;			// array of pointers into 'raw_data'
	int		p_page_entries;		// no. of hcodes in a page (INCLUDING. index entry - first entry)
	
	int p_find_pageslot( const PU_int* const );	
	void p_merge_pages( PAGE&, PAGE&);
 	void p_split_page( PAGE&, PAGE&, int );
 	int p_shift_from_left( PAGE&, PAGE&, PAGE& );
	int p_shift_from_right( PAGE&, PAGE&, PAGE& );

// private:
	unsigned char 	*raw_data;

	int		dimensions;
	int		p_page_entry_size;	// no. of bytes in an hcode
	int		p_page_bytes;		// no. of bytes on a page
	MED		*M;
	
 	Hcode p_find_median();
	Hcode p_find_median_left( PAGE& );
	Hcode p_find_median_right( PAGE& );
};



#endif	// _PAGE_H