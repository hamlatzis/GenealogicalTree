#ifndef _GEN_GRAPH_
#define _GEN_GRAPH_

#include <vector>
#include <set>
#include <utility>

class Relations;
class Person;

class GenGraph
{
public:
	GenGraph();
	virtual ~GenGraph();

public:
	// Actions
	void ConnectPeople( Person* pFirstPerson, Person* pSecondPerson, const std::vector<Person*>& vChildren );

	// Getters
	typedef std::vector< std::pair<Relations*, const Person*> > relations;
	bool GetFamilyTree( std::vector<relations>& vRelations, const std::string& strDescendantName, const std::string& strAscendantName );

private:
	// Helper methods
	void GetAscendants( relations& vRelations, const Person* pPerson );
	void CleanupAscendants( const std::string& strAscendantName );

private:
	std::vector<Relations*> mvRelations;
	std::set<Person*> mPersons;

	std::vector<relations> mvRelationsPath;
};

#endif