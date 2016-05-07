#include "stdafx.h"
#include "Person.h"

#include "Relations.h"

#include <assert.h>

Person::Person()
{
	mbVisited = false;
}

Person::~Person()
{
}

void Person::AddRelation( Relations* pRelation )
{
	assert ( pRelation != 0 );
	if ( pRelation != 0 )
		mvRelations.push_back(pRelation);
}

Relations* Person::GetRelation(const unsigned int nRelation) const
{
	if ( nRelation < TotalRelations() )
		return mvRelations[nRelation];

	return 0;
}
