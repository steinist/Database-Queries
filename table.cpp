#include "table.h"

#include <iostream>
#include <cstring>
using namespace std;


//CONSTRUCTOR & DESTRUCTOR
Table::Table(){
	attrs = nullptr;
	entries = nullptr;
	numAttrs = 0;
	numEntries = 0;
}

Table::Table(const Table &another){
	numAttrs = another.numAttrs;
	numEntries = another.numEntries;

//	copy attrs
	if (another.attrs != nullptr){

		attrs = new string[numAttrs];

		for (int i = 0; i < numAttrs; ++i){
			attrs[i] = another.attrs[i];
		}
	}
	else
		attrs = nullptr;

	//copy entries
	if (another.entries != nullptr){

		entries = new string*[numEntries];

		for (int i = 0; i < numEntries; ++i){
			entries[i] = new string[numAttrs];
		}

		for (int i = 0; i < numEntries; ++i){
			for (int j = 0; j < numAttrs; ++j){
				entries[i][j] = another.entries[i][j];
			}
		}
	}
	else
		entries = nullptr;

}


Table::~Table(){
	if (attrs != nullptr) {
		delete[] attrs;
		attrs = nullptr;
	}

	if (entries != nullptr){
		for (int i = 0; i < numEntries; ++i){
			delete[] entries[i];
			entries[i] = nullptr;
		}
		delete[] entries;
		entries = nullptr;
	}
}



//MEMBER FUNCTIONS

bool Table::addAttribute(const string &attr, int index, const string &default_value){
	if (index > numAttrs || index < -1){
		return false;
	}

	//If still blank sheet
	if (attrs == nullptr){

		attrs = new string[1];
		*attrs = attr;
		++numAttrs;
	}


	//Adding
	else {

		//Create a copy to copy back to original
		Table cpy(*this);

		//delete original attrs and prepare a bigger place
		delete[] attrs;


		//adjust index
		if (index == -1)
			index = numAttrs;
		++numAttrs;

		//create and assign back attrs copy to origin
		attrs = new string[numAttrs];

		for(int i = 0; i < numAttrs; ++i){
			if (i < index){
				attrs[i] = cpy.attrs[i];
			}
			else if(i == index){
				attrs[i] = attr;
			}
			else{
				attrs[i] = cpy.attrs[i-1];
			}
		}


		//adjust entries
		if (entries != nullptr){
			//delete the original entries and create a bigger place
			for (int i = 0; i < numEntries; ++i){
				delete[] entries[i];
				entries[i] = nullptr;
			}
			delete[] entries;

			entries = new string*[numEntries];

			for (int i = 0; i < numEntries; ++i){
				entries[i] = new string[numAttrs];

				for (int j = 0; j < numAttrs; ++j){

					if(j < index){
						entries[i][j] = cpy.entries[i][j];
					}
					else if (j == index){
						entries[i][j] = default_value;
					}
					else{
						entries[i][j] = cpy.entries[i][j-1];
					}
				}
			}
		}
	}

	return true;

}


bool Table::addEntry(const string *entry, int index){
	if (index > numEntries || index < -1){
		return false;
	}



	if (entries == nullptr){

		entries = new string*[1];
		entries[0] = new string[numAttrs];

		for (int i = 0; i < numAttrs; ++i){
			entries[0][i] = entry[i];
		}
		++numEntries;
	}



	//Addition
	else{
		//Create a copy
		Table cpy(*this);

		//delete original
		for (int i = 0; i < numEntries; ++i){
			delete[] entries[i];
		}
		delete[] entries;

		//adjust index
		if (index == -1)
			index = numEntries;
		++numEntries;

		//create and assign back entries copy to origin
		entries = new string*[numEntries];

		for (int i = 0; i < numEntries; ++i){

			entries[i] = new string[numAttrs];

			for (int j = 0; j < numAttrs; ++j){
				if (i < index){
					entries[i][j] = cpy.entries[i][j];
				}

				else if (i == index){
					entries[i][j] = entry[j];
				}

				else {
					entries[i][j] = cpy.entries[i-1][j];
				}
			}
		}

	}

	return true;

}

bool Table::deleteAttribute(int index){
	if (index > numAttrs-1 || index < 0)
		return false;

	//if numAttrs == 1 delete all
	if (numAttrs == 1){
		delete[] attrs;
		attrs = nullptr;

		for(int i = 0; i < numEntries; ++i){
			delete[] entries[i];
			entries[i] = nullptr;
		}
		delete[] entries;
		entries = nullptr;

		numAttrs = 0;
		numEntries = 0;
	}


	else{
		//Copy the original
		Table cpy(*this);

		//delete ATTRS and ENTRIES
		if (attrs != nullptr) {
			delete[] attrs;
			attrs = nullptr;
		}

		if (entries != nullptr){
			for (int i = 0; i < numEntries; ++i){
				delete[] entries[i];
				entries[i] = nullptr;
			}
			delete[] entries;
			entries = nullptr;
		}

		//ATTRS create a smaller space and assign
		--numAttrs;
		attrs = new string[numAttrs];
		for(int i = 0; i < numAttrs; ++i){
			if (i < index)
				attrs[i] = cpy.attrs[i];
			else
				attrs[i] = cpy.attrs[i+1];
		}

		//ENTRIES create a smaller space and assign
		if (numEntries != 0){
			entries = new string*[numEntries];
			for (int i = 0; i < numEntries; ++i){
				entries[i] = new string[numAttrs];

				for(int j = 0; j < numAttrs; ++j){
					if (j < index){
						entries[i][j] = cpy.entries[i][j];
					}
					else{
						entries[i][j] = cpy.entries[i][j+1];
					}
				}
			}
		}

	}

	return true;
}

bool Table::deleteEntry(int index){

	if (index > numEntries-1 || index < 0)
		return false;

	if (numEntries == 1){
		delete[] entries[0];
		entries[0] = nullptr;

		delete[] entries;
		entries = nullptr;
		numEntries = 0;
	}

	else {
		//Copy the original
		Table cpy(*this);

		//delete ENTRIES
		if (entries != nullptr){
			for (int i = 0; i < numEntries; ++i){
 				delete[] entries[i];
				entries[i] = nullptr;
			}
			delete[] entries;
			entries = nullptr;
		}

		//ENTRIES create a smaller space and assign
		--numEntries;
		entries = new string*[numEntries];

		for (int i = 0; i < numEntries; ++i){
			entries[i] = new string[numAttrs];

			for (int j = 0; j < numAttrs; ++j){
				if (i < index)
					entries[i][j] = cpy.entries[i][j];
				else
					entries[i][j] = cpy.entries[i+1][j];
			}
		}

	}

	return true;
}

bool Table::append(const Table& another){
	if (numAttrs != another.numAttrs)
		return false;

	for (int i = 0; i < numAttrs; ++i){
		if (attrs[i] != another.attrs[i])
			return false;
	}

	if (another.entries == nullptr)
		return true;

	//copy the origin
	Table cpy(*this);


	//delete entries
	if (entries != nullptr){
		for (int i = 0; i < numEntries; ++i){
			delete[] entries[i];
			entries[i] = nullptr;
		}
		delete[] entries;
		entries = nullptr;
	}

	//create a bigger entries
	numEntries += another.numEntries;
	entries = new string*[numEntries];

	for (int i = 0; i < numEntries; ++i){
		entries[i] = new string[numAttrs];

		for (int j = 0; j < numAttrs; ++j){
			if (i < cpy.numEntries)
				entries[i][j] = cpy.entries[i][j];
			else
				entries[i][j] = another.entries[i-cpy.numEntries][j];
		}
	}

	return true;
}







