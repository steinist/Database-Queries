#include "intermediate.h"
#include "table.h"

#include <iostream>
using namespace std;



Intermediate::Intermediate(const Table &table){
	attrs = table.attrs;
	numAttrs = table.numAttrs;


	if (table.entries == nullptr){
		head = nullptr;
		tail = nullptr;
	}


	else {
		head = new EntryNode;
		head->prev = nullptr;
		head->entry = table.entries[0];

		EntryNode* en = head;

		for (int i = 1; i < table.numEntries; ++i, en = en->next){
			en->next = new EntryNode;
			en->next->entry = table.entries[i];
			en->next->prev = en;

			if (i == table.numEntries-1){
				tail = en->next;
			}
		}

		tail->next = nullptr;
	}

}

Intermediate::~Intermediate(){
	attrs = nullptr;

	if (head != nullptr){
		for (EntryNode* en = head; en != tail; ){
			en->entry = nullptr;
			en = en->next;
			en->prev->next = nullptr;
			delete en->prev;
			en->prev = nullptr;
		}
		tail->entry = nullptr;
		delete tail;
		tail = nullptr;
		head = nullptr;
	}
}


Intermediate& Intermediate::where(const string &attr, enum compare mode, const string &value){
	//SEARCHING FOR ATTRS COL
	int a = -1;
	for (int i = 0; i < this->numAttrs; ++i){
		if (attr == this->attrs[i]){
			a = i;
			break;
		}
	}
	//If we dont find the attr
	if (a == -1)
		return *this;




	//IF WE HAVE 1 ENTRY
	if (this->head == this->tail){
		bool same;
		if (mode == EQ){
			same = (this->head->entry[a] == value);
		}
		else {
			same = (this->head->entry[a].find(value));
		}
		//Return as it is.. if it is the same
		if (same){
			return *this;
		}
		//Delete entry and return only the attrs
		else {
			this->head->entry = nullptr;
			delete this->head;
			this->head = nullptr;

			this->tail->entry = nullptr;
			delete this->tail;
			this->tail = nullptr;
			return *this;
		}
	}

	//IF WE HAVE >1 ENTRY


	//Searching for the right head
	while (true){

		bool same;
		if (mode == EQ){
			same = (this->head->entry[a] == value);
		}
		if (mode == CONTAINS) {
			same = (this->head->entry[a].find(value) != string::npos);
		}

		//if we found the first value return
		if (same){
			break;
		}

		//if we are at the end of the line, we cant found anything delete all
		if (this->head == this->tail){
			for (EntryNode* en = this->head; en != this->tail; ){
				en->entry = nullptr;
				en = en->next;
				en->prev->next = nullptr;
				delete en->prev;
				en->prev = nullptr;
			}
			this->tail->entry = nullptr;
			delete this->tail;
			this->tail = nullptr;
			this->head = nullptr;
			return *this;
		}

		//if we dont find anything, delete current head and move
		//move
		this->head = this->head->next;
		//delete the prev

		this->head->prev->entry = nullptr;
		this->head->prev->next = nullptr;
		delete this->head->prev;
		this->head->prev = nullptr;
	}

	//Count how many is the same
	int count = 1;
	for (EntryNode* i = this->head; i != tail; i = i->next){
		if(i->next->entry[a].find(value) != string::npos){
			count++;

		}
	}




	//Assuming head is has the value because head must have the value
	//Searching for the next partner
	for (EntryNode* i = this->head; i->next != nullptr; ){
		//Checking compare mode
		bool same;

		if (mode == EQ)
			same = (i->next->entry[a] == value);
		else
			same = (i->next->entry[a].find(value) != string::npos);


		if(same){
			i = i->next;
		}

		//delete
		if(!same) {
			i->next->entry = nullptr;

			if(i->next->next != nullptr){
				i->next->prev = nullptr;
				i->next = i->next->next;
				i->next->prev->next = nullptr;
				delete i->next->prev;
				i->next->prev = i;

			}

			else{
				i->next->prev = nullptr;
				delete i->next;
				i->next = nullptr;
				this->tail = i;
				break;
			}
		}
	}
	return *this;
}


Intermediate& Intermediate::orderBy(const string &attr, enum order order){
	//SEARCHING FOR ATTRS COL
	int a = -1;
	for (int i = 0; i < this->numAttrs; ++i){
		if (attr == this->attrs[i]){
			a = i;
			break;
		}
	}
	//If we dont find the attr
	if (a == -1)
		return *this;


	bool ordered = false;

	while(!ordered){

		//Checking if already ordered
		int count1 = 0;
		int count2 = 0;
		for (EntryNode* i = this->head; i->next != nullptr; i = i->next, ++count1){
			if (order == ASCENDING && (i->entry[a].compare(i->next->entry[a]) <= 0)){
				++count2;
			}
			if (order == DESCENDING && (i->entry[a].compare(i->next->entry[a]) >= 0)){
				++count2;
			}
		}

		//if ordered break loop
		if (count1 == count2)
			break;

		//Bubble sort
		for(EntryNode*i = this->head; i->next != nullptr; ){
			//if not order SWAP


			if ((order == ASCENDING && (i->entry[a].compare(i->next->entry[a]) > 0)) ||
					(order == DESCENDING && (i->entry[a].compare(i->next->entry[a]) < 0))){
				EntryNode* j = i->next;

				//SWAPPING NEXT
				//if i is head

				if (i->prev != nullptr)
					i->prev->next = j;
				else
					this->head = j;

				i->next = j->next;
				j->next = i;

				//SWAPPING PREV
				//if j->next is tail
				if (i->next != nullptr)
					i->next->prev = i;
				else
					this->tail = i;

				j->prev = i->prev;
				i->prev = j;

				j = nullptr;
			}

			else
				i = i->next;

		}

	}

	return *this;
}

Intermediate& Intermediate::limit (unsigned int limit){
	int i = 1;
	EntryNode* en = this->head;
	for (; (en->next != nullptr) && (i < limit); en = en->next, ++i){
	}

	//DELETE after J
	if (en->next == nullptr)
		return *this;

	en->next->prev = nullptr;
	EntryNode* del = en->next;
	en->next = nullptr;

	for (; del != tail; ){
		del->entry = nullptr;
		del = del->next;
		del->prev->next = nullptr;
		delete del->prev;
		del->prev = nullptr;
	}
	this->tail->entry = nullptr;
	delete this->tail;
	this->tail = en;

	return *this;
}


void Intermediate::update(const string &attr, const string &new_value) const{
	int a = -1;
	for (int i = 0; i < this->numAttrs; ++i){
		if (attr == this->attrs[i]){
			a = i;
			break;
		}
	}
	//If we dont find the attr
	if (a == -1)
		return;

	for (EntryNode* en = this->head; en != nullptr; en = en->next){
		en->entry[a] = new_value;
	}

}

void Intermediate::select(const string *attrs, int numAttrs) const{
	if (this->attrs == nullptr)
		return;


	//We need to print everything
	if (attrs == nullptr){
		numAttrs = this->numAttrs;

		int* len = new int[numAttrs];

		//Find the length of ATTRS
		for (int i = 0; i < numAttrs; ++i){
			len[i] = this->attrs[i].length();
		}

		//Find the longest length on Entries if it exist
		if (this->head != nullptr){

			for (EntryNode* en = this->head; en != nullptr; en = en->next){
				for (int i = 0; i < numAttrs; ++i){
					if (en->entry[i].length() > len[i]){
						len[i] = en->entry[i].length();
					}
				}
			}
		}


		//PRINT ATTRS
		for (int i = 0; i < this->numAttrs; ++i){
			if (i == this->numAttrs-1) {
				cout << _left_pad_until(this->attrs[i], len[i]);
			}
			else{
				cout << _left_pad_until(this->attrs[i], len[i]) << " | ";
			}
		}
		cout << endl;

		//PRINT Entries
		if (this->head != nullptr){
			for (EntryNode* i = this->head; i != nullptr; i = i->next){
				for (int j = 0; j < this->numAttrs; ++j){
					if (j == this->numAttrs-1)
						cout << _left_pad_until(i->entry[j], len[j]);
					else
						cout << _left_pad_until(i->entry[j], len[j]) << " | ";
				}
				cout << endl;
			}
		}


		delete [] len;
	} // End of PRINT ALL

	else {
		int* len = new int[numAttrs];
		int* index = new int[numAttrs];

		//Searching for the attrs index
		for (int i = 0; i < numAttrs; ++i){
			for (int j = 0;  j < this->numAttrs; ++j){
				if (this->attrs[j].compare(attrs[i]) == 0)
					index[i] = j;
			}
		}

		//Find the length of ATTRS
		for (int i = 0; i < numAttrs; ++i){
			len[i] = this->attrs[index[i]].length();
		}

		//Find the longest length on Entries if it exist
		if (this->head != nullptr){

			for (EntryNode* en = this->head; en != nullptr; en = en->next){
				for (int i = 0; i < numAttrs; ++i){
					if (en->entry[index[i]].length() > len[i])
						len[i] = en->entry[index[i]].length();
				}
			}
		}


		//PRINT

		//PRINT ATTRS
		for (int i = 0; i < numAttrs; ++i){
			if (i == numAttrs-1) {
				cout << _left_pad_until(this->attrs[index[i]], len[i]);
			}
			else{
				cout << _left_pad_until(this->attrs[index[i]], len[i]) << " | ";
			}
		}
		cout << endl;


		//PRINT Entries
		if (this->head != nullptr){
			for (EntryNode* i = this->head; i != nullptr; i = i->next){
				for (int j = 0; j < numAttrs; ++j){
					if (j == numAttrs-1)
						cout << _left_pad_until(i->entry[index[j]], len[j]);
					else
						cout << _left_pad_until(i->entry[index[j]], len[j]) << " | ";
				}
				cout << endl;
			}
		}




		delete[] len;
		delete[] index;

	}


}
