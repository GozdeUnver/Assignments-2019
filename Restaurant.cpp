#include "Restaurant.h"

using namespace std;

void Restaurant::execute(const vector<string>& operations) {
    for (const string& op : operations){
        cout << "Operation: " << op << "\t"; 
        
		/* YOU NEED TO IMPLEMENT THIS PART */

		//If the customer comes from the north, the search for the available table will start from the north of the restaurant
		if(op.compare("N")==0){

		    //Checks to find the closest empty table from the beginning of the tables vector.
		    for(Table &t:tables){
		        if(!t.isOccupied()){
		            t.occupy();
		            break;
		        }
		    }

            //If the customer comes from the south, the search for the available table will start from the south of the restaurant
		}else if(op.compare("S")==0){

		    //Checks from the end of the vector whether there is an empty table, since the customer comes from the south
		    for(int i=tables.size()-1;i>=0;i--){
		        if(!tables[i].isOccupied()){
		            tables[i].occupy();
		            break;
		        }
		    }

		    //If the operation is a table number it means the customer at the corresponding table leaves, the table becomes unoccupied
		}else{
		    tables[stoi(op)-1].empty();
		}
        cout << "State: " << *this << endl;
    }
}

Restaurant::Restaurant(unsigned int N)
	: tables{N}
{
    cout << "-Starting- \tState: " << *this << endl;
}

ostream &operator<<(ostream &out, Restaurant &restaurant) {
    for (Table table : restaurant.tables) {
        out << table.isOccupied();
    }
	return out;
}
