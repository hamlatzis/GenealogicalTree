// GenealogicalTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "GenGraph.h"
#include "Person.h"

#include <vector>
#include <string>
#include <assert.h>

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<GenGraph::branch> vBranches;
	std::string strDescendantName = "";
	std::string strAscendantName = "";

	GenGraph genGraph;
	bool bFound = genGraph.GetFamilyTree( vBranches, strDescendantName, strAscendantName );
	if ( bFound )
	{
		assert ( vBranches.empty() == false );
	}

	return 0;
}

