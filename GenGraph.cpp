#include "stdafx.h"
#include "GenGraph.h"

#include "Relations.h"
#include "Person.h"

#include <assert.h>

GenGraph::GenGraph()
{
}

GenGraph::~GenGraph()
{
	for ( int nRelation = 0; nRelation < (int)mvRelations.size(); ++nRelation )
		delete mvRelations[nRelation];
	mvRelations.clear();

	for ( int nPerson = 0; nPerson < (int)mvPersons.size(); ++nPerson )
		delete mvPersons[nPerson];
	mvPersons.clear();
}

/*
*			Actions
*/
void GenGraph::ConnectPeople( const Person* pFirstPerson, const Person* pSecondPerson, const std::vector<Person*>& vChildren )
{
	bool precondition ( pFirstPerson && pSecondPerson );
	assert ( precondition == true );
	if ( precondition )
	{
		Relations* pRelation = new Relations();
		pRelation->AssignPartners(pFirstPerson, pSecondPerson);

		if ( !vChildren.empty() )
			pRelation->AddChildren(vChildren);
	}
}

/*
*			Queries
*/

bool GenGraph::GetFamilyTree( std::vector<branch>& vBranches, const std::string& strDescendantName, const std::string& strAscendantName )
{
	bool precondition = ( !strDescendantName.empty() && !strAscendantName.empty() && vBranches.empty() );
	assert ( precondition == true );
	if ( !precondition )
		return false;

	for ( int nPerson = 0; nPerson < (int)mvPersons.size(); ++nPerson )
	{
		Person* pPerson = mvPersons[nPerson];
		if ( pPerson->GetName() == strDescendantName )
		{
			branch vRelations;
			GetAscendants(vRelations, pPerson, strAscendantName);
			if ( !vRelations.empty() )
				vBranches.push_back(vRelations);
		}
	}

	return !vBranches.empty();
}
/*
*			Helper methods
*/

void GenGraph::GetAscendants( branch& vRelations, const Person* pPerson, const std::string& strAscendantName )
{
}