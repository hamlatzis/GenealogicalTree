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
	void AssignPartners( const Person* pFirstPartner, const Person* pSecondPartner );
	void AddChildren( const std::vector<Person*>& vChildren );

	// Getters
	unsigned int TotalPartners() const;
	const Person* GetPartner(const unsigned int nPartner) const;

	unsigned int TotalChildren() const { return (unsigned int)mvChildren.size(); }
	Person* GetChild(const unsigned int nChild) const;

	// Helper methods
	bool Visited() const { return mbVisited; }

private:
	const Person* mPartners[2];
	std::vector<Person*> mvChildren;

	bool mbVisited;
};

#endif
