#ifndef _BTREE_H
#define _BTREE_H

#ifdef DEV
#ifdef __MSDOS__
	#include "..\gendefs.h"
#else
	#include "../gendefs.h"
#endif
#else
#include "gendefs.h"
#endif

class BTnode;

/* used by idxi_setup_nextptrs() */
typedef struct ListNode {
	BTnode *node;
	struct ListNode *next;
} ListNode;

/*============================================================================*/
/*                            #defines	                          	      */
/*============================================================================*/
// aliases to distinguish inner nodes from leaf nodes
#define lf_HDR			btnodehdr
#define in_HDR			btnodehdr
#define lf_ENTRY		XX
#define in_ENTRY		XX
#define nextptr			btnodeptr // within a lf_ENTRY
#define firstptr		btnodeptr // within a in_ENTRY

#define	isLEAF			0x1
#define	isROOT			0x2

#define lf_FANOUT		(node_entries - 2)
#define in_FANOUT		(node_entries - 2)
#define lf_minFANOUT	((node_entries - 2) / 2)
#define in_minFANOUT	((node_entries - 2) / 2)

/*============================================================================*/
/*                            BTnode	                          	      */
/*============================================================================*/

typedef struct {
	BTnode		*parent;
	u2BYTES 	flags;
	u2BYTES 	size;			// the number of keys (not pointers) in a node
	BTnode  	*btnodeptr;		// aliased to nextptr (leaf) and firstptr (inner)
} BTnodehdr;

// NB the size of one of these is assumed to be the size of a U_int
// and if it isn't this is a problem!!!
typedef union {
	int		lpage;
	BTnode		*downptr;
} X;

/* this comment is out of date

 One of these occupies a page of size idx_PAGE_SIZE (or a little less)
   ientry[] elements 1 to inFANOUT are used for storing Hcodes.
   ientry[0] is used for storing info (in 'lf' or 'in')
   ientry[MAX_INNER - 1] is for overflow data: as soon as it is filled,
	 in.size exceeds inFANOUT and a node split is triggered */

// Hkey[0] points at btnodehdr.
// when an entry is placed in Hkey[node_entries - 1], this triggers a split
// - ie, this element doesn't normally hold an entry.
class BTnode {
	friend class BTree;
public:
	BTnode( int dims, int n_entries );		// constructor
	~BTnode();					// destructor

	BTnodehdr	*btnodehdr;		// aliased to lf_HDR and in_HDR
	X 			**XX;			// aliased to lf_ENTRY and in_ENTRY
	BTnode* idxi_find_leaf( HU_int *key );

private:
	U_int		**Hkey;
	int dimensions;
	int node_entries;			// no. of elements in a node (inc. header)
	int node_entry_size;		// no. of bytes in a node element
	unsigned char *raw_data;

	int idxi_find_slot( HU_int *key );
	int idxi_find_prev( HU_int *key, int lpage, BTnode *left );
	int idxi_merge_nodes( BTnode *right );	// called by left node
	int idxi_shift_from_left( BTnode *left, BTnode *anchor );
	int idxi_shift_from_right( BTnode *right, BTnode *anchor );
	int idxi_process_underflow( BTnode *left, BTnode *right, BTnode *LAnchor, BTnode *RAnchor );
	int idxi_delete_from_node( HU_int *key, int lpage, BTnode *left, BTnode *right, BTnode *LAnchor, BTnode *RAnchor );
	BTnode* idxi_read_file( fstream&, int, int, int );
	void idxi_append( ListNode *tail );
	int idxi_setup_parents();
	int idxi_setup_nextptrs();
	void idxi_free_btree();
} ;


/*============================================================================*/
/*                            BTree	                          	      */
/*============================================================================*/

class BTree {
public:
	BTree();
	BTree( string name, int dims, int n_entries );			// constructor
	~BTree();							// destructor
	BTnode	*root;
	
	int idx_insert_key( HU_int *key, int lpage );
	int idx_delete_key( HU_int *key, int lpage );
	int idx_search( HU_int *key );
	void idx_dump( string );
	int idx_write( string fname = "" );
	int idx_read( string fname = "" );
	void free_root();					// for freeing root created in db_create()
	int idx_get_next( HU_int *key, int lpage );
	int idx_get_prev( HU_int *key, int lpage );
	HU_int* idx_get_next_key( HU_int *key, int lpage );

private:
	string name;
	int dimensions;
	int node_entries;					// no. of elements in a node (inc. header)
	int node_entry_size;				// no. of bytes in a node element
	fstream idxfile;

	void idxi_make_new_root( BTnode *right, HU_int *newkey );
	void idxi_split_leaf( BTnode *p );
	void idxi_split_inner( BTnode *p );
	void idxi_insert_in_node( BTnode *p, HU_int *key, int lpage, BTnode *q );
	int idxi_write_file( BTnode *node );
	int idx_get_last_page();
};

#endif // _BTREE_H