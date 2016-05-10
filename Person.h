#ifndef _PERSON_H_
#define _PERSON_H_

#include <vector>
#include <string>

class Relations;

class Person
{
public:
	Person();
	virtual ~Person();

public:
	// Actions
	void SetName( const std::string& strFirstName ) { mstrFirstName = strFirstName; }
	void SetLastName( const std::string& strLastName ) { mstrLastName = strLastName; }
	void SetDateOfBirth( const std::string& strDateOfBirth ) { mstrDateOfBirth = strDateOfBirth; }
	void SetLocation( const std::string& strLocation ) { mstrLocation = strLocation; }

	void AddRelation( Relations* pRelation ); // allow for re-marriage and/or societies were more than one spouse/husband are allowed
	void FromRelation( Relations* pRelation );

	// Queries
	unsigned int TotalRelations() const { return (unsigned int)mvHasRelations.size(); }
	Relations* GetRelation(const unsigned int nRelation) const;
	Relations* FromRelation() const { return mpFromRelation; }

	std::string GetName() const { return mstrFirstName; }
	std::string GetLastName() const { return mstrLastName; }
	std::string GetDateOfBirth() const { return mstrDateOfBirth; }
	std::string GetLocation() const { return mstrLocation; }

private:
	std::string mstrFirstName;
	std::string mstrLastName;
	std::string mstrDateOfBirth;
	std::string mstrLocation;

	std::vector<Relations*> mvHasRelations;
	Relations* mpFromRelation;
};
#endif