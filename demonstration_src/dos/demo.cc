// Copyright (C) Jonathan Lawder 2001

#ifdef DEV
#ifdef __MSDOS__
	#include "..\db\db.h"
#else
	#include "../db/db.h"
#endif
#else
	#include "db.h"
#endif

#include <iomanip>


using namespace std;

/*============================================================================*/
/*                            randomi					      */
/*============================================================================*/
/* this is for inserting a lot of randomly generated records at the same time */

int randomi( DBASE *DB )
{
	string	junk;
	int	num;

	cout << "How many records to insert? : ";
	cin >> num;
	getline(cin, junk);

	DB->db_batch_update( 'i', num );
	return 0;
}

/*============================================================================*/
/*                            main					      */
/*============================================================================*/
int main(void)
{
	DBASE	*DB;
	char	c;
	string	name, junk;
	int	DIMS, bt_node_entries, n_bslots, p_entries;

//	U_int x = UINT_MAX;
//	cout << "UINT_MAX = " << x <<endl;

	cout << "Enter database name : ";
	cin >> name;
	getline(cin, junk);
	cout << "\nEnter no. of dimensions : ";
	cin >> DIMS;
	getline(cin, junk);
	cout << "\nEnter no. of BTree node entries : ";
	cin >> bt_node_entries;
	getline(cin, junk);
	cout << "\nEnter size of buffer (pages) : ";
	cin >> n_bslots;
	getline(cin, junk);
	cout << "\nEnter size of page (records) : ";
	cin >> p_entries;
	getline(cin, junk);
	cout << "\n\n";

 	DB = new DBASE( name, DIMS, bt_node_entries, n_bslots, p_entries );
 	string idxdump = DB->dbname + "_idx.dump";
 	string keydump = DB->dbname + "_key.dump";
 	string datadump = DB->dbname + "_data.dump";

	for(;;)
	{
		cout << "\n---- TOP LEVEL MENU ---- " <<
			"What do you want to do? " <<
			"(enter a number or `q' to quit)\n\n" <<
			"  1 : create a new " << DIMS <<"-dimensional data store\n" <<
			"  2 : open an existing data store\n" <<
			"  3 : insert randomly generated data\n" <<
			"  4 : ad hoc updating\n" <<
			"  5 : ad hoc querying\n" <<
			"  6 : dump index to file : " << idxdump << endl <<
			"  7 : dump database keys to file : " << keydump << endl <<
			"  8 : dump database to file : " << datadump << endl;


		cin >> c;
		getline(cin, junk);

		switch (c)
		{
			case '1':  DB->db_create();  break;
			case '2':  DB->db_open();    break;
			case '3':  randomi( DB );   break;	// insert random data
			case '4':  cout << "ad hoc updating - not yet implemented!!\n";    break;
			case '5':  DB->db_querytest();    break;
			case '6':  DB->BT.idx_dump( idxdump );     break;	//
			case '7':  DB->db_key_dump( keydump );     break;	//
			case '8':  DB->db_data_dump( datadump, 'd' );     break;	//

			default :  DB->db_close();  return 0;
		}
	}

	return 0;

}