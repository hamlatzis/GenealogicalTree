#include "stdafx.h"
#include "Relations.h"

#include "Person.h"

#include <algorithm>

#include <assert.h>

Relations::Relations()
{
}

Relations::~Relations()
{
}

void Relations::AssignPartners( const std::vector<Person*>& vPartners )
{
	assert ( mvPartners.empty() == true );
	if ( mvPartners.empty() )	// should allow only once: All partners are added at once
		std::copy( vPartners.begin(), vPartners.end(), std::back_inserter(mvPartners) );
}

void Relations::AddChildren( const std::vector<Person*>& vChildren )
{
	assert ( mvChildren.empty() == true );
	if ( mvChildren.empty() )	// should allow only once: All children are added at once
		std::copy( vChildren.begin(), vChildren.end(), std::back_inserter(mvChildren) );
}

Person* Relations::GetPartner(const unsigned int nPartner) const
{
	assert( nPartner < TotalPartners() );
	if ( nPartner < TotalPartners() )
		return mvPartners[nPartner];

	return 0;
}	

Person* Relations::GetChild(const unsigned int nChild) const
{
	assert( nChild < TotalChildren() );
	if ( nChild < TotalChildren() )
		return mvChildren[nChild];

	return 0;
}	
