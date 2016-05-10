#ifndef _INI_FILE_H
#define _INI_FILE_H

#include <string>
#include <vector>
#include <algorithm>
#include <functional>

class CIniFile
{
public:
	struct Record
	{
		std::string Comments;
		char Commented;
		std::string Section;
		std::string Key;
		std::string Value;
	};

	enum CommentChar
	{
		Pound = '#',
		SemiColon = ';'
	};

	CIniFile(void);
	virtual ~CIniFile(void);

	bool LoadAll(const char* FileName);

	std::string Content();

	bool DeleteRecord(std::string KeyName, std::string SectionName);
	bool DeleteSection(std::string SectionName);
	std::vector<Record> GetRecord(std::string KeyName, std::string SectionName);
	std::vector<Record> GetSection(std::string SectionName);
	std::vector<std::string> GetSectionNames();
	std::string GetValue(std::string KeyName, std::string SectionName);
	bool RecordExists(std::string KeyName, std::string SectionName);
	bool SectionExists(std::string SectionName);

	int GetIntValue(std::string KeyName, std::string SectionName, int nDefault);
	int GetStringValue(std::string SectionName, std::string KeyName, const std::string& default_val, std::string& buffer);

private:
	std::vector<Record> GetSections();

	struct RecordSectionIs : std::unary_function<Record, bool>
	{
		std::string section_;

		RecordSectionIs(const std::string& section): section_(section){}

		bool operator()( const Record& rec ) const
		{
			return rec.Section == section_;
		}
	};

	struct RecordSectionKeyIs : std::unary_function<Record, bool>
	{
		std::string section_;
		std::string key_;

		RecordSectionKeyIs(const std::string& section, const std::string& key): section_(section),key_(key){}

		bool operator()( const Record& rec ) const
		{
			return ((rec.Section == section_)&&(rec.Key == key_));
		}
	};

	struct AscendingSectionSort
	{
		bool operator()(Record& Start, Record& End)
		{
			return Start.Section < End.Section;
		}
	};

	struct DescendingSectionSort
	{
		bool operator()(Record& Start, Record& End)
		{
			return Start.Section > End.Section;
		}
	};

	struct AscendingRecordSort
	{
		bool operator()(Record& Start, Record& End)
		{
			return Start.Key < End.Key;
		}
	};

	struct DescendingRecordSort
	{
		bool operator()(Record& Start, Record& End)
		{
			return Start.Key > End.Key;
		}
	};

	std::vector<Record> mvContent;
};

#endif
