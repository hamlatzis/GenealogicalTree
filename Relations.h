#ifndef _RELATIONS_H_
#define _RELATIONS_H_

#include <vector>

class Person;

class Relations
{
public:
	Relations();
	virtual ~Relations();

public:
	// Actions
	void AssignPartners( const std::vector<Person*>& vPartners );	// accommodate for societies where a person can have more than one spouses/husbands
	void AddChildren( const std::vector<Person*>& vChildren );

	// Getters
	unsigned int TotalPartners() const { return (unsigned int)mvPartners.size(); }
	Person* GetPartner(const unsigned int nPartner) const;

	unsigned int TotalChildren() const { return (unsigned int)mvChildren.size(); }
	Person* GetChild(const unsigned int nChild) const;

	// Helper methods
	bool Visited() const { return mbVisited; }

private:
	std::vector<Person*> mvPartners;
	std::vector<Person*> mvChildren;

	bool mbVisited;
};

#endif
