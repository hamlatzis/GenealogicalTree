#include "stdafx.h"
#include "Person.h"

#include "Relations.h"

#include <assert.h>

Person::Person()
{
	mpFromRelation = 0;
}

Person::~Person()
{
}
/*
*			Actions
*/

void Person::AddRelation( Relations* pRelation )
{
	assert ( pRelation != 0 );
	if ( pRelation != 0 )
		mvHasRelations.push_back(pRelation);
}

void Person::FromRelation( Relations* pRelation )
{
	assert ( (mpFromRelation == 0) && pRelation );
	if ( (mpFromRelation == 0) && pRelation )
		mpFromRelation = pRelation;
}

/*
*			Queries
*/
Relations* Person::GetRelation(const unsigned int nRelation) const
{
	if ( nRelation < TotalRelations() )
		return mvHasRelations[nRelation];

	return 0;
}
