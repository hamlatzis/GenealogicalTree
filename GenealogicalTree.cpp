// GenealogicalTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "GenGraph.h"
#include "Person.h"
#include "Relations.h"

#include "inifile.h"

#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

int _tmain(int argc, _TCHAR* argv[])
{
	CIniFile testDataFile;
	bool bOK = testDataFile.LoadAll("TestData.txt");

	std::string strDescendantName;
	std::string strAscendantName;

	testDataFile.GetStringValue("INFO", "Descendant", "Bob", strDescendantName);
	testDataFile.GetStringValue("INFO", "Ascendant", "Will", strAscendantName);

	std::vector<Person*> vPersons;

	bool bSectionExists = true;
	char buffer[100];

	int nPerson = 0;
	while ( bSectionExists )
	{
		sprintf( buffer, "Person_%d", nPerson );
		std::string strSectionName(buffer);
		bSectionExists = testDataFile.SectionExists(strSectionName);
		if ( bSectionExists )
		{
			std::string strName = "";
			std::string strLastName = "";
			std::string strLocation = "";
			std::string strDateOfBirth = "";

			testDataFile.GetStringValue(strSectionName, "Name", "***", strName);
			testDataFile.GetStringValue(strSectionName, "Lastname", "***", strLastName);
			testDataFile.GetStringValue(strSectionName, "Location", "***", strLocation);
			testDataFile.GetStringValue(strSectionName, "DateOfBirth", "***", strDateOfBirth);

			Person* pPerson = new Person();
			pPerson->SetName(strName);
			pPerson->SetLastName(strLastName);
			pPerson->SetLocation(strLocation);
			pPerson->SetDateOfBirth(strDateOfBirth);

			vPersons.push_back(pPerson);
		}
		++nPerson;
	}

	GenGraph genGraph;

	bSectionExists = true;
	int nRelation = 0;

	while ( bSectionExists )
	{
		sprintf( buffer, "Relation_%d", nRelation );
		std::string strSectionName(buffer);
		bSectionExists = testDataFile.SectionExists(strSectionName);
		if ( bSectionExists )
		{
			int nPartner0 = testDataFile.GetIntValue("Partner_0", strSectionName, -1);
			int nPartner1 = testDataFile.GetIntValue("Partner_1", strSectionName, -1);

			std::vector<Person*> vChildren;
			bool bChildExist = true;
			int nChild = 0;
			while ( bChildExist )
			{
				sprintf( buffer, "Child_%d", nChild );
				std::string strChild(buffer);

				bChildExist = testDataFile.RecordExists(strChild, strSectionName);
				if ( bChildExist )
				{
					int nChildID = testDataFile.GetIntValue(strChild, strSectionName, -1);
					vChildren.push_back(vPersons[nChildID]);
				}

				++nChild;
			}

			genGraph.ConnectPeople( vPersons[nPartner0], vPersons[nPartner1], vChildren );
		}

		++nRelation;
	}

	std::vector<GenGraph::relations> vBranches;
	bool bFound = genGraph.GetFamilyTree( vBranches, strDescendantName, strAscendantName );
	if ( bFound )
	{
		assert ( vBranches.empty() == false );

		for ( int nBranch = 0; nBranch < (int)vBranches.size(); ++nBranch )
		{
			GenGraph::relations vRelations = vBranches[nBranch];
			for ( int nRelation = 0; nRelation < (int)vRelations.size(); ++nRelation )
			{
				std::pair<Relations*, const Person*> relation = vRelations[nRelation];
				const Person* pChild = relation.second;
				Relations* pRelation = relation.first;

				const Person* p0 = pRelation->GetPartner(0);
				const Person* p1 = pRelation->GetPartner(1);

				std::cout <<	pChild->GetName().c_str() << " " <<
								pChild->GetLastName().c_str() << std::endl <<
								pChild->GetDateOfBirth().c_str() << std::endl <<
								pChild->GetLocation().c_str() << std::endl << std::endl <<
								" is child of " << std::endl << std::endl;

				std::cout <<	p0->GetName().c_str() << " " <<
								p0->GetLastName().c_str() << std::endl <<
								p0->GetDateOfBirth().c_str() << std::endl <<
								p0->GetLocation().c_str() << std::endl << std::endl <<
								" AND " << std::endl << std::endl;
				std::cout <<	p1->GetName().c_str() << " " <<
								p1->GetLastName().c_str() << std::endl <<
								p1->GetDateOfBirth().c_str() << std::endl <<
								p1->GetLocation().c_str() << std::endl << std::endl;
			}
			std::cout << "--------------------------------------------------" << std::endl << std::endl;
		}
	}
	else
		std::cout << "Either no " << strDescendantName.c_str() << " found or doesn't have an ascendant named " << strAscendantName.c_str() << std::endl;

	getchar();

	return 0;
}

