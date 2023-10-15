#include "CricketTeam.h"

#include <iostream>


using namespace std;

//constructor
CricketTeam::CricketTeam() {
	head = nullptr;
}

//copy constructor
CricketTeam::CricketTeam(const CricketTeam& rhs) {
	if (rhs.head == nullptr) {
		return;
	}

	//if the list being copied from is not null
	//make the head of the new list be a node
	head = new Node;
	head->prev = nullptr;
	head->next = nullptr;
	head->value = rhs.head->value;
	head->firstName = rhs.head->firstName;
	head->lastName = rhs.head->lastName;

	Node* copyList = rhs.head;
	Node* newList = head;

	while (copyList->next != nullptr) {	//while the list being copied from is not null 
		newList->next = new Node;		//make a new node and accordingly connect to prev
										//and next node
		newList->next->prev = newList;

		newList = newList->next;
		copyList = copyList->next;
		newList->value = copyList->value;
		newList->firstName = copyList->firstName;
		newList->lastName = copyList->lastName;
	}
	newList->next = nullptr;
}

//assignment operator
const CricketTeam& CricketTeam::operator=(const CricketTeam& rhs) {
	if (this == & rhs) {	//if the existing list is being copied from the same list
		return *this;		//return the original list
	}
	else {
		CricketTeam temp(rhs);	//otherwise, put the list into a temp list
		tradeCricketTeams(temp);	//then trade the list with temp
	}
	return *this;
}

CricketTeam::~CricketTeam() {
	Node* p = head;

	while (p != nullptr) {
		Node* n = p->next;
		delete p;
		p = n;
	}
}


// Return true if the CricketTeam list
// is empty, otherwise false.
bool CricketTeam::noTeam() const {
	if (head == nullptr) {
		return true;
	} else {
		return false;
	}
}

// Return the number of matches
// on the CricketTeam list.
int CricketTeam::cricketerCount() const {
	int count = 0;

	Node* p = head;		
	while (p != nullptr) {	//while the pointer to head is not null
		count++;			//iterate through the list and increase
		p = p->next;		//count for every node
	}
	return count;
}


// If the full name (both the first and last name) is not equal 
 // to any full name currently in the list then add it and return 
 // true. Elements should be added according to their last name. 
 // Elements with the same last name should be added according to
 // their first names. Otherwise, make no change to the list and
 // return false (indicating that the name is already in the 
 // list)
bool CricketTeam::addCricketer(const std::string& firstName, const std::string&
	lastName, const CricketType& value) {


	bool samePersonNotFound = true;	//create a bool value and set it to true 
									//in order to test later if the list has same
									//first name and last name or not

	//if the list is empty just add to front
	//by making head a new node
	if (head == nullptr) {
		head = new Node;
		head->firstName = firstName;
		head->lastName = lastName;
		head->value = value;
		head->next = nullptr;
		head->prev = nullptr;

		return samePersonNotFound;

	}
	//first check that the cricket team has no duplicate first and last names
	//create a pointer to iterate thru the list
	Node* ptr = head;
	while (ptr != nullptr) {
		if (ptr->firstName == firstName && ptr->lastName == lastName) {		//if same person found, make samePersonNotFound become false
			samePersonNotFound = false;										//and return it

			return samePersonNotFound;
		}
		ptr = ptr->next;
	}

	Node* p = head;
	//now, if it is true that samePersonNotFound then run this by creating a new pointer
	//since same pointers cannot be initialized
	if (samePersonNotFound) {
		while (p != nullptr) {
			if (p->lastName == lastName) {	//if lastName of head is equal to the given lastName
				if (p->firstName > firstName && p->lastName == lastName) { //check if the firstName is greater than the given firstName
					Node* tmptr = p->prev;
					p->prev = new Node;

					p->prev->value = value;							//create a new node to the previous since given firstName is less than head's firstName
					p->prev->firstName = firstName;					//and appropriately link the previous and next pointers
					p->prev->lastName = lastName;
					p->prev->next = p;

					p->prev->prev = tmptr;

					tmptr != nullptr ? tmptr->next = p->prev : head = p->prev;	//insert to front case: if the tmptr is not a nullptr && the firstName of head is greater than given 
																				//firstName tmptr's next is the head's previous
					return samePersonNotFound;
				}
				else if (p->next == nullptr) {	//otherwise if we are at the end of the list then add accordingly by inserting to rear
					p->next = new Node;

					p->next->value = value;
					p->next->lastName = lastName;
					p->next->firstName = firstName;
					p->next->next = nullptr;
					p->next->prev = p;

					return samePersonNotFound;
				}
			}
			else if (p->lastName > lastName && p->lastName != lastName) {		//else if the head's lastName is greater than lastName given insert the new node to previous of head
				Node* tmptr = p->prev;
				p->prev = new Node;

				p->prev->value = value;
				p->prev->firstName = firstName;
				p->prev->lastName = lastName;
				p->prev->next = p;

				p->prev->prev = tmptr;

				tmptr != nullptr ? tmptr->next = p->prev : head = p->prev;		//same logic applies here

				return samePersonNotFound;
			}
			else if (p->next == nullptr) {										//same logic applies here
				p->next = new Node;

				p->next->value = value;
				p->next->lastName = lastName;
				p->next->firstName = firstName;
				p->next->next = nullptr;
				p->next->prev = p;

				return samePersonNotFound;
			}
			p = p->next;
		}
	}
	return samePersonNotFound;
}
						


// If 0 <= i < size(), copy into firstName, lastName and value 
// parameters the corresponding information of the element at 
// position i in the list and return true. Otherwise, leave the 
// parameters unchanged and return false. (See below for details 
// about this function.)

bool CricketTeam::checkTeamForCricketer(int i, std::string& firstName,
	std::string& lastName, CricketType& value) const {

	if (i >= 0 && i < cricketerCount()) {					//given the user entered a valid int of 0 or greater and less than the cricketerCount of the cricketTeam
		Node* p = head;										//create a pointer to head

		for (int k = 0; k < i; k++) {				//iterate thru the list until the ith value is found
			p = p->next;
		}

		firstName = p->firstName;					//change the parameters
		lastName = p->lastName;
		value = p->value;

		return true;
	}
	return false;
}



// If the full name is equal to a full name currently in the 
// list, then make that full name no longer map to the value it 
// currently maps to, but instead map to the value of the third 
// parameter; return true in this case. Otherwise, make no 
// change to the list and return false.


bool CricketTeam::substituteCricketer(const std::string& firstName, const
	std::string& lastName, const CricketType& value) {

	bool samePersonFound = false;			//create a bool value and set to false

	Node* p = head;

	while (p != nullptr) {
		if (p->firstName == firstName && p->lastName == lastName) {	//if same full name found in list
			samePersonFound = true;
			break;
		}
		p = p->next;
	}
	return samePersonFound;

	if (samePersonFound) {			//if samePersonFound the the parameter changes to the value in the list
		p->value = value;
	}
	return samePersonFound;
}


// If full name is equal to a name currently in the list, then
// make that full name no longer map to the value it currently 
// maps to, but instead map to the value of the third parameter; 
// return true in this case. If the full name is not equal to 
// any full name currently in the list then add it and return 
// true. In fact, this function always returns true.
bool CricketTeam::addOrSubstitute(const std::string& firstName, const
	std::string& lastName, const CricketType& value) {

	bool samePersonFound = false;

	Node* p = head;

	while (p != nullptr) {
		if (p->firstName == firstName && p->lastName == lastName) {  //if samePersonFound
			samePersonFound = true;
			break;
		}
		p = p->next;
	}
	return samePersonFound;

	if (samePersonFound) {					//if samePersonFound is true then the change the value of the list itself to the given param
		p->value = value;
	} else {
		addCricketer(firstName, lastName, value);	//otherwise if not found then just add accordingly
	}
	return samePersonFound;
}



// If the full name is equal to a full name currently in the 
// list, remove the full name and value from the list and return 
// true. Otherwise, make no change to the list and return 
// false.

bool CricketTeam::releaseCricketer(const std::string& firstName, const
	std::string& lastName) {

	bool samePersonFound = false;		

	if (head == nullptr) {			//if the list is empty then return
		return samePersonFound;
	}


	if (head->firstName == firstName && head->lastName == lastName) {		//if same person found and it's head
		Node* killMe = head;												//make a kill pointer on head
		head = killMe->next;

		delete killMe;														//make head go to next and delete previous value


		samePersonFound = true;
		return samePersonFound;
	}

	Node* p = head;

	while (p->next != nullptr) {
		if (p->next->firstName == firstName && p->next->lastName == lastName) {	
			samePersonFound = true;
			break;
		}
		p = p->next;
	}

	if (samePersonFound && p->next->next != nullptr) {		//not at head: if same person found and the next next value is not null
		Node* killMe = p->next;								//make kill me go to the actual deleting value
		p->next = killMe->next;
		killMe->next->prev = p;								//store the previous to kill me's next
		delete killMe;										//appropriately delete killme
	}
	else {
		Node* killMe = p->next;
		p->next = nullptr;
		delete killMe;
	}
	return samePersonFound;
}



// Return true if the full name is equal to a full name 
// currently in the list, otherwise false.

bool CricketTeam::rosteredOnCricketTeam(const std::string& firstName, const
	std::string& lastName) const {
	
	if (head == nullptr) {
		return false;
	}

	Node* p = head;
	while (p != nullptr) {
		if (p->firstName == firstName && p->lastName == lastName) {		//if same person found return true since they are rostered on the team
			return true;												//otherwise, return false
		}
		p = p->next;
	}
	return false;
}


// If the full name is equal to a full name currently in the 
// list, set value to the value in the list that that full name 
// maps to, and return true. Otherwise, make no change to the 
// value parameter of this function and return false.
bool CricketTeam::searchForCricketer(const std::string& firstName, const
	std::string& lastName, CricketType& value) const {

	if (head == nullptr) {
		return false;
	}

	Node* p = head;
	while (p != nullptr) {
		if (firstName == p->firstName && lastName == p->lastName) {		//while searching for cricketer if found, change the value to the value in list
			value = p->value;
			return true;
		}
		p = p->next;
	}
	return false;
}


// Exchange the contents of this list with the other one.
void CricketTeam::tradeCricketTeams(CricketTeam& other) {
	Node* temp = head;							//create a temp pointer to the head 
	head = other.head;							//head points to other head
	other.head = temp;							//other head now points to temp which is head

	temp = nullptr;
}



//if a fullname appears in exactly ONE of odOne and odTwo, then odJoined must
//contain an element consisting of that fullname and corresponding value.

//if a full name appears in BOTH odOne and odTwo, with the SAME corresponding value in BOTH,
//then odJoined must contain an element with that full name

//you MAY NOT assume odJoined is empty when passed into the function
//if there exists a full name that appears in both odOne and odTwo with DIFFERENT
//values, then the function returns false.
//if there is no full name like this, the function returns true
bool mergeCricketers(const CricketTeam& odOne,
	const CricketTeam& odTwo,
	CricketTeam& odJoined) {

	string firstName;
	string lastName;
	CricketType value;

	bool boolVal = true;

	if (odOne.cricketerCount() == 0 && odTwo.cricketerCount() == 0) {		//if both lists are empty, just return
		return boolVal;
	}

	if (odJoined.cricketerCount() != 0 && (&odJoined != &odOne) && (&odJoined != &odTwo)) {		//check for the odJoined not being empty and odOne and odTwo not being aliased
		//use copy constructor to make odJoined equal to odOne

		odJoined = odOne;

		for (int i = 0; i < odJoined.cricketerCount(); i++) {			//add same name and same value peeps
			odJoined.checkTeamForCricketer(i, firstName, lastName, value);	//get the first item in odOne

			for (int k = 0; k < odTwo.cricketerCount(); k++) {			//then compare it against every value in odTwo

				CricketType comp;

				if (odTwo.checkTeamForCricketer(k, firstName, lastName, comp) && comp == value) {
					odJoined.addCricketer(firstName, lastName, value);			//if same then add
				}
			}
		}
		for (int i = 0; i < odTwo.cricketerCount(); i++) {				//also add values of odTwo that are not yet in odJoined
			odTwo.checkTeamForCricketer(i, firstName, lastName, value);

			if (odJoined.rosteredOnCricketTeam(firstName, lastName)) {
				boolVal = false;
			}
			else {
				odJoined.addCricketer(firstName, lastName, value);
			}
		}
		return boolVal;

	}
	else if (&odJoined == &odOne || &odJoined == &odTwo || (&odJoined == &odOne && &odJoined == &odTwo)) {	//aliasing check if odJoined is equal to either params
		if (&odJoined == &odOne) {		//specifically for odJoined being equal to odOne

			CricketTeam temp = odOne;				//create temp cricketteam

			for (int i = 0; i < odOne.cricketerCount(); i++) { //add same peeps in odOne and odTwo into 'temp'
				odOne.checkTeamForCricketer(i, firstName, lastName, value);	

				for (int k = 0; k < odTwo.cricketerCount(); k++) {

					CricketType comp;

					if (odTwo.checkTeamForCricketer(k, firstName, lastName, comp) && comp == value) {
						temp.addCricketer(firstName, lastName, value);
					}
				}
			}
			for (int i = 0; i < odTwo.cricketerCount(); i++) { //add peeps from odTwo into temp that are NOT in odOne
				odTwo.checkTeamForCricketer(i, firstName, lastName, value);

				if (odOne.rosteredOnCricketTeam(firstName, lastName)) {
					boolVal = false;
				}
				else {
					temp.addCricketer(firstName, lastName, value);
				}
			}
			for (int i = 0; i < odJoined.cricketerCount(); i++) { //add peeps from odJoined that are NOT in temp
				odJoined.checkTeamForCricketer(i, firstName, lastName, value);

				if (temp.rosteredOnCricketTeam(firstName, lastName)) {
					boolVal = false;
				}
				else {
					temp.addCricketer(firstName, lastName, value);
				}
				odJoined = temp;
			}
			return boolVal;
		}
		else if (&odJoined == &odTwo) {			//check for odJoined being equal to odTwo

			CricketTeam temp = odTwo;

			for (int i = 0; i < odOne.cricketerCount(); i++) { //add same peeps in odOne and odTwo into 'temp'
				odOne.checkTeamForCricketer(i, firstName, lastName, value);

				for (int k = 0; k < odTwo.cricketerCount(); k++) {

					CricketType comp;

					if (odTwo.checkTeamForCricketer(k, firstName, lastName, comp) && comp == value) {
						temp.addCricketer(firstName, lastName, value);
					}
				}
			}
			for (int i = 0; i < odOne.cricketerCount(); i++) { //add peeps from odOne into temp that are NOT in temp
				odOne.checkTeamForCricketer(i, firstName, lastName, value);

				if (odTwo.rosteredOnCricketTeam(firstName, lastName)) {
					boolVal = false;
				}
				else {
					temp.addCricketer(firstName, lastName, value);
				}
			}
			for (int i = 0; i < odJoined.cricketerCount(); i++) { //add peeps from odJoined that are NOT in temp
				odJoined.checkTeamForCricketer(i, firstName, lastName, value);

				if (temp.rosteredOnCricketTeam(firstName, lastName)) {
					boolVal = false;
				}
				else {
					temp.addCricketer(firstName, lastName, value);
				}
				odJoined = temp;
			}
			return boolVal;
		}
		else if (&odJoined == &odTwo && &odJoined == &odOne) {		//check for odJoined being equal to odTwo and odOne

			return boolVal;											//just return the list since they are all equal
		}
	}
	else {			//if none of the conditions of the ifs have been met then run this
		for (int i = 0; i < odOne.cricketerCount(); i++) {
			odOne.checkTeamForCricketer(i, firstName, lastName, value);

			for (int k = 0; k < odTwo.cricketerCount(); k++) {

				CricketType comp;

				if (odTwo.checkTeamForCricketer(k, firstName, lastName, comp) && comp == value) {
					odJoined.addCricketer(firstName, lastName, value);
				}
			}
		}
		for (int i = 0; i < odOne.cricketerCount(); i++) {
			odOne.checkTeamForCricketer(i, firstName, lastName, value);

			if (odTwo.rosteredOnCricketTeam(firstName, lastName)) {
				boolVal = false;
			}
			else {
				odJoined.addCricketer(firstName, lastName, value);
			}

		}
		for (int i = 0; i < odTwo.cricketerCount(); i++) {
			odTwo.checkTeamForCricketer(i, firstName, lastName, value);

			if (odOne.rosteredOnCricketTeam(firstName, lastName)) {
				boolVal = false;
			}
			else {
				odJoined.addCricketer(firstName, lastName, value);
			}

		}
		return boolVal;
	}
	return boolVal;
}


void checkCricketers(const std::string& fsearch,
	const std::string& lsearch,
	const CricketTeam& odOne,
	CricketTeam& odResult) {

	string firstName;
	string lastName;
	CricketType value;

	if ((fsearch == "*") && (lsearch == "*")) {			//if for both fsearch and lsearch, wild card is used, return the original entire list
		odResult = odOne;
	}


	if ((fsearch == "*")) {		//if fsearch has the wildcard
		for (int i = 0; i < odOne.cricketerCount(); i++) {		//iterate over odOne and check the cricketer
			odOne.checkTeamForCricketer(i, firstName, lastName, value);
			if (lastName == lsearch) {							//if lastName is equal to given lsearch param add the cricketer
				odResult.addCricketer(firstName, lastName, value);
			}
		}
	} else if (lsearch == "*") {			//else if lsearch has the wildcard
		for (int k = 0; k < odOne.cricketerCount(); k++) {			//iterate over odOne and check the cricketer
			odOne.checkTeamForCricketer(k, firstName, lastName, value);		// if the firstName is equal to given fsearch param add the cricketer
			if (firstName == fsearch) {
				odResult.addCricketer(firstName, lastName, value);
			}
		}
	}
}



