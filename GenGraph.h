#ifndef _GEN_GRAPH_
#define _GEN_GRAPH_

#include <vector>

class Relations;
class Person;

class GenGraph
{
public:
	GenGraph();
	virtual ~GenGraph();

public:
	// Actions
	void ConnectPeople( const Person* pFirstPerson, const Person* pSecondPerson, const std::vector<Person*>& vChildren );

	// Getters
	typedef std::vector<Relations*> branch;
	bool GetFamilyTree( std::vector<branch>& vBranches, const std::string& strDescendantName, const std::string& strAscendantName );

	// Helper methods
	void GetAscendants( branch& vRelations, const Person* pPerson, const std::string& strAscendantName );

private:
	std::vector<Relations*> mvRelations;
	std::vector<Person*> mvPersons;
};

#endif