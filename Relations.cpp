#include "stdafx.h"
#include "Relations.h"

#include "Person.h"

#include <algorithm>

#include <assert.h>

Relations::Relations()
{
	mPartners[0] = mPartners[1] = 0;
}

Relations::~Relations()
{
}

/*
*			Actions
*/

void Relations::AssignPartners( const Person* pFirstPartner, const Person* pSecondPartner )
{
	bool precondition = ( (mPartners[0] == 0) && (mPartners[1] == 0) && pFirstPartner && pSecondPartner );
	assert ( precondition == true );
	if ( precondition )	// should allow only once: All partners are added at once
	{
		mPartners[0] = pFirstPartner;
		mPartners[1] = pSecondPartner;
	}
}

void Relations::AddChildren( const std::vector<Person*>& vChildren )
{
	assert ( mvChildren.empty() == true );
	if ( mvChildren.empty() )	// should allow only once: All children are added at once
	{
		for ( int nChild = 0; nChild < (int)vChildren.size(); ++nChild )
		{
			Person* pChild = vChildren[nChild];
			pChild->FromRelation(this);
			mvChildren.push_back(pChild);
		}
	}
}

/*
*			Queries
*/

unsigned int Relations::TotalPartners() const
{
	unsigned int nPartners = 0;

	if ( mPartners[0] && mPartners[1] )	// cannot have a relation with only 1 partner or no partner
		nPartners = 2;

	return nPartners;
}

const Person* Relations::GetPartner(const unsigned int nPartner) const
{
	assert( nPartner < TotalPartners() );
	if ( nPartner < TotalPartners() )
		return mPartners[nPartner];

	return 0;
}	

Person* Relations::GetChild(const unsigned int nChild) const
{
	assert( nChild < TotalChildren() );
	if ( nChild < TotalChildren() )
		return mvChildren[nChild];

	return 0;
}	
