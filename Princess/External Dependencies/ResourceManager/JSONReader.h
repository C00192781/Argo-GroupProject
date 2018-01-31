#ifndef _JSONREADER_H
#define _JSONREADER_H

#include <JSON.h>
#include <fstream>
#include <iostream>

////////////////////////////////////////////////////////////
///Reads JSON data using SimpleJSON
////////////////////////////////////////////////////////////

class JSONReader {
public:
	JSONReader(std::string const & filename);
	~JSONReader();

	int load(std::string const & filename);
	std::vector<std::vector<std::string>> loadLevel();
	std::string ElementGetter(std::string x);

private:
	JSONValue *m_value;
	std::string m_JSONData;

	void loadJSONData(std::string const & filename);

	//LevelData m_levelData;

	// Utility methods.
	JSONObject getTopLevelJSONObject();
	std::string wStringToString(std::wstring const & wstr);
};

#endif