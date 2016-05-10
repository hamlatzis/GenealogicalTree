#include "inifile.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>

CIniFile::CIniFile(void)													// Default constructor
{
}

CIniFile::~CIniFile(void)
{
}

// A function to trim whitespace from both sides of a given string
void Trim(std::string& str, const std::string & ChrsToTrim = " \t\n\r", int TrimDir = 0)
{
    size_t startIndex = str.find_first_not_of(ChrsToTrim);
    if (startIndex == std::string::npos){str.erase(); return;}
    if (TrimDir < 2) str = str.substr(startIndex, str.size()-startIndex);
    if (TrimDir!=1) str = str.substr(0, str.find_last_not_of(ChrsToTrim) + 1);
}

//inline void TrimRight(std::string& str, const std::string & ChrsToTrim = " \t\n\r")
//{
//    Trim(str, ChrsToTrim, 2);
//}

//inline void TrimLeft(std::string& str, const std::string & ChrsToTrim = " \t\n\r")
//{
//    Trim(str, ChrsToTrim, 1);
//}

// A function to transform a string to uppercase if neccessary
//void UCase(string& str, bool ucase)
//{
//	if(ucase) transform(str.begin(), str.end(), str.begin(), toupper);
//}

bool CIniFile::LoadAll(const char* filename)
{
	std::string FileName = std::string(filename);

	mvContent.clear();															// Clear the content vector

	std::string s;																// Holds the current line from the ini file
	std::string CurrentSection;													// Holds the current section name

	std::ifstream inFile (FileName.c_str());										// Create an input filestream
	if (!inFile.is_open())
		return false;														// If the input file doesn't open, then return

	std::string comments = "";													// A string to store comments in

	while(!std::getline(inFile, s).eof())									// Read until the end of the file
	{
		Trim(s);															// Trim whitespace from the ends
		if(!s.empty())														// Make sure its not a blank line
		{
			Record r;														// Define a new record

			if((s[0]=='#')||(s[0]==';'))									// Is this a commented line?
			{
				if ((s.find('[')==std::string::npos)&&							// If there is no [ or =
					(s.find('=')==std::string::npos))							// Then it's a comment
				{
					comments += s + '\n';									// Add the comment to the current comments string
				} else {
					r.Commented = s[0];										// Save the comment character
					s.erase(s.begin());										// Remove the comment for further processing
					Trim(s);
				}// Remove any more whitespace
			} else r.Commented = ' ';										// else mark it as not being a comment

			if(s.find('[')!=std::string::npos)									// Is this line a section?
			{
				s.erase(s.begin());											// Erase the leading bracket
				s.erase(s.find(']'));										// Erase the trailing bracket
				r.Comments = comments;										// Add the comments string (if any)
				comments = "";												// Clear the comments for re-use
				r.Section = s;												// Set the Section value
				r.Key = "";													// Set the Key value
				r.Value = "";												// Set the Value value
				CurrentSection = s;
			}
			Trim(r.Comments);
			Trim(r.Section);
			Trim(r.Key);
			Trim(r.Value);

			if(s.find('=')!=std::string::npos)									// Is this line a Key/Value?
			{
				r.Comments = comments;										// Add the comments string (if any)
				comments = "";												// Clear the comments for re-use
				r.Section = CurrentSection;									// Set the section to the current Section
				r.Key = s.substr(0,s.find('='));							// Set the Key value to everything before the = sign
				r.Value = s.substr(s.find('=')+1);							// Set the Value to everything after the = sign
			}

			Trim(r.Comments);
			Trim(r.Section);
			Trim(r.Key);
			Trim(r.Value);

			if(comments == "")												// Don't add a record yet if its a comment line
				mvContent.push_back(r);										// Add the record to content
		}
	}

	inFile.close();															// Close the file

	return true;
}

std::string CIniFile::Content()
{
	std::string s="";															// Hold our return string

	for (int i=0;i<(int)mvContent.size();i++)								// Loop through the content
	{
		if(mvContent[i].Comments != "") s += mvContent[i].Comments;			// Add the comments
		if(mvContent[i].Commented != ' ') s += mvContent[i].Commented;		// If this is commented, then add it
		if((mvContent[i].Key == ""))										// Is this a section?
			s += '[' + mvContent[i].Section + ']';						// Add the section
		else s += mvContent[i].Key + '=' + mvContent[i].Value;				// Or the Key value to the return srting

		if (i != (int)mvContent.size()) s += '\n';								// If this is not the last line, add a CrLf
	}
	return s;															// Return the contents
}
std::vector<std::string> CIniFile::GetSectionNames()
{
	std::vector<std::string> data;													// Holds the return data

	for (int i=0;i<(int)mvContent.size();i++)								// Loop through the content
	{
		if(mvContent[i].Key =="")											// If there is no key value, then its a section
			data.push_back(mvContent[i].Section);							// Add the section to the return data
	}

	return data;															// Return the data
}
std::vector<CIniFile::Record> CIniFile::GetSection(std::string SectionName)
{
	std::vector<Record> data;													// Holds the return data

	for (int i=0;i<(int)mvContent.size();i++)								// Loop through the content
	{
		if((mvContent[i].Section == SectionName) &&						// If this is the section name we want
			(mvContent[i].Key != ""))										// but not the section name itself
			data.push_back(mvContent[i]);									// Add the record to the return data
	}

	return data;															// Return the data
}

bool CIniFile::RecordExists(std::string KeyName, std::string SectionName)
{
	std::vector<Record>::iterator iter = std::find_if(mvContent.begin(),
			mvContent.end(),
			RecordSectionKeyIs(SectionName,KeyName));			// Locate the Section/Key

	if (iter == mvContent.end()) return false;							// The Section/Key was not found

	return true;															// The Section/Key was found
}

bool CIniFile::SectionExists(std::string SectionName)
{
	std::vector<Record>::iterator iter = std::find_if(mvContent.begin(),
			mvContent.end(),
			RecordSectionIs(SectionName));					// Locate the Section

	if (iter == mvContent.end()) return false;							// The Section was not found

	return true;															// The Section was found
}

std::vector<CIniFile::Record> CIniFile::GetRecord(std::string KeyName, std::string SectionName)
{
	std::vector<Record> data;													// Holds the return data

	std::vector<Record>::iterator iter = std::find_if(mvContent.begin(),
			mvContent.end(),
			RecordSectionKeyIs(SectionName,KeyName));			// Locate the Record

	if (iter == mvContent.end()) return data;								// The Record was not found

	data.push_back (*iter);												// The Record was found

	return data;															// Return the Record
}

std::string CIniFile::GetValue(std::string KeyName, std::string SectionName)
{
	std::vector<Record> content = GetRecord(KeyName,SectionName);		// Get the Record

	if(!content.empty())													// Make sure there is a value to return
		return content[0].Value;											// And return the value

	return "";																// No value was found
}
int CIniFile::GetIntValue(std::string KeyName, std::string SectionName, int nDefault)
{
	std::string strVal = GetValue(KeyName, SectionName);

	if ( strVal.empty() )
		return nDefault;

	std::stringstream strStream(strVal);

	int nRet = -1;
	strStream >> nRet;

	return nRet;
}

int CIniFile::GetStringValue(std::string SectionName, std::string KeyName, const std::string& default_val, std::string& buffer)
{
	std::string strVal = GetValue(KeyName, SectionName);

	if ( strVal.empty() )
	{
		buffer = default_val;
		return 0;
	}

	buffer = strVal;
	return (int)buffer.size();
}

std::vector<CIniFile::Record> CIniFile::GetSections()
{
	std::vector<Record> data;													// Holds the return data

	for (int i=0;i<(int)mvContent.size();i++)								// Loop through the content
	{
		if(mvContent[i].Key == "")										// If this is a section
			data.push_back(mvContent[i]);									// Add the record to the return data
	}

	return data;															// Return the data
}
