#ifndef CRICKETTEAM_H
#define CRICKETTEAM_H

#include <string>

typedef std::string CricketType;


class CricketTeam
{
private:
	struct Node {
		CricketType value;
		Node* next;
		Node* prev;
		std::string firstName;
		std::string lastName;
	};
	Node* head;

public:
	CricketTeam();

	CricketTeam(const CricketTeam& rhs);

	const CricketTeam& operator=(const CricketTeam& rhs);

	~CricketTeam();	

	bool noTeam() const; 


	int cricketerCount() const; 


	bool addCricketer(const std::string& firstName, const std::string&
		lastName, const CricketType& value);


	bool substituteCricketer(const std::string & firstName, const
			std::string & lastName, const CricketType & value);



	bool addOrSubstitute(const std::string& firstName, const
		std::string& lastName, const CricketType& value);
	


	bool releaseCricketer(const std::string& firstName, const
		std::string& lastName);



	bool rosteredOnCricketTeam(const std::string& firstName, const
		std::string& lastName) const;
	


	bool searchForCricketer(const std::string& firstName, const
		std::string& lastName, CricketType& value) const;
	


	bool checkTeamForCricketer(int i, std::string& firstName,
		std::string& lastName, CricketType& value) const;
	


	void tradeCricketTeams(CricketTeam & other);

};

bool mergeCricketers(const CricketTeam& odOne,
	const CricketTeam& odTwo,
	CricketTeam& odJoined);


void checkCricketers(const std::string& fsearch,
	const std::string& lsearch,
	const CricketTeam& odOne,
	CricketTeam& odResult);

#endif
