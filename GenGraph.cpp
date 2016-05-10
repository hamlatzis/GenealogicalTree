#include "stdafx.h"
#include "GenGraph.h"

#include "Relations.h"
#include "Person.h"

#include <stack>

#include <assert.h>

GenGraph::GenGraph()
{
}

GenGraph::~GenGraph()
{
	for ( int nRelation = 0; nRelation < (int)mvRelations.size(); ++nRelation )
		delete mvRelations[nRelation];
	mvRelations.clear();

	std::set<Person*>::iterator it = mPersons.begin();
	while ( it != mPersons.end() )
	{
		delete *it;
		++it;
	}
	mPersons.clear();
}

/*
*			Actions
*/
void GenGraph::ConnectPeople( Person* pFirstPerson, Person* pSecondPerson, const std::vector<Person*>& vChildren )
{
	bool precondition ( pFirstPerson && pSecondPerson );
	assert ( precondition == true );
	if ( precondition )
	{
		Relations* pRelation = new Relations();
		pRelation->AssignPartners(pFirstPerson, pSecondPerson);

		if ( !vChildren.empty() )
			pRelation->AddChildren(vChildren);

		mvRelations.push_back(pRelation);
		mPersons.insert(pFirstPerson);
		mPersons.insert(pSecondPerson);
		for ( int nChild = 0; nChild < (int)vChildren.size(); ++nChild )
			mPersons.insert(vChildren[nChild]);
	}
}

/*
*			Queries
*/

bool GenGraph::GetFamilyTree( std::vector<relations>& vRelations, const std::string& strDescendantName, const std::string& strAscendantName )
{
	bool precondition = ( !strDescendantName.empty() && !strAscendantName.empty() && vRelations.empty() );
	assert ( precondition == true );
	if ( !precondition )
		return false;

	mvRelationsPath.clear();

	std::set<Person*>::iterator it = mPersons.begin();
	while ( it != mPersons.end() )
	{
		Person* pPerson = *it;
		if ( pPerson->GetName() == strDescendantName )
		{
			relations vRelationsPath;
			GetAscendants(vRelationsPath, pPerson);
		}

		++it;
	}

	CleanupAscendants(strAscendantName);

	std::copy( mvRelationsPath.begin(), mvRelationsPath.end(), std::back_inserter(vRelations) );

	return !mvRelationsPath.empty();
}

void GenGraph::GetAscendants( relations& vRelations, const Person* pPerson )
{
	if ( pPerson == NULL ) 
		return;
	if ( pPerson->FromRelation() == NULL )
		return;

	/* append this node to the relations vector */
	vRelations.push_back( std::make_pair(pPerson->FromRelation(), pPerson) );

	const Person* p0 = pPerson->FromRelation()->GetPartner(0);
	const Person* p1 = pPerson->FromRelation()->GetPartner(1);

	if ( (p0->FromRelation() == NULL) && (p1->FromRelation() == NULL) )
	{	/* there is no information regarding their ancestors  */
		mvRelationsPath.push_back(vRelations);

		/* we will backtrack one step so remove last ascendant otherwise we will have duplicate*/
		vRelations.erase( vRelations.begin()+ vRelations.size()-1 );
	}
	else
	{
		/* try both partners */
		GetAscendants(vRelations, p0);
		GetAscendants(vRelations, p1);
	}
}

void GenGraph::CleanupAscendants( const std::string& strAscendantName )
{
	for ( int nPath = 0; nPath < (int)mvRelationsPath.size(); ++nPath )
	{
		relations vRelations = mvRelationsPath[nPath];

		bool bFound = false;

		while ( !bFound && !vRelations.empty() )
		{
			relations::reverse_iterator it = vRelations.rbegin();
			Relations* pRelation = it->first;

			const Person* p0 = pRelation->GetPartner(0);
			const Person* p1 = pRelation->GetPartner(1);

			bFound = ( (p0->GetName() == strAscendantName) || (p1->GetName() == strAscendantName) );

			if ( !bFound )
				vRelations.pop_back();
		}

		mvRelationsPath[nPath].swap(vRelations);

		if ( mvRelationsPath[nPath].empty() ) 
			mvRelationsPath.erase( mvRelationsPath.begin() + nPath );
	}
}