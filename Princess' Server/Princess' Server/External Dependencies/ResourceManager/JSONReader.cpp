
#include "JSONReader.h"

////////////////////////////////////////////////////////////
JSONReader::JSONReader(std::string const & filename)
{
	loadJSONData(filename);
	m_value = JSON::Parse(m_JSONData.c_str());
	if (NULL == m_value)
	{
		std::string s("Could not parse json in " + filename);
		return;
	}
}

////////////////////////////////////////////////////////////
JSONReader::~JSONReader() {
	delete m_value;
}

////////////////////////////////////////////////////////////
int JSONReader::load(std::string const & filename)
{
	loadJSONData(filename);
	m_value = JSON::Parse(m_JSONData.c_str());
	if (NULL == m_value)
	{
		std::string s("Could not parse json in " + filename);
		return 0;
	}
	return 1;
}

////////////////////////////////////////////////////////////
void JSONReader::loadJSONData(std::string const & filename)
{
	m_JSONData.clear();

	// Loads all the data in the file into a std::string.
	std::ifstream myfile(filename);
	std::string line;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			m_JSONData.append(line);
		}
		myfile.close();
	}
	else
	{
		std::string errorMessage = "Could not open " + filename + " exiting!";
		std::cout << "Could not open " + filename + " exiting!" << std::endl;
		return;
	}
}

////////////////////////////////////////////////////////////
JSONObject JSONReader::getTopLevelJSONObject() {
	// Retrieve the main (root) object
	JSONObject root;

	if (m_value->IsObject() == false)
	{
		throw std::exception("Problem with root element in json file, exiting");
	}
	root = m_value->AsObject();

	return root;
}

////////////////////////////////////////////////////////////
std::string JSONReader::wStringToString(std::wstring const & wstr)
{
	std::string s(wstr.begin(), wstr.end());
	return s;
}


std::vector<std::vector<std::string>> JSONReader::loadLevel()
{
	std::vector<std::vector<std::string>> map;
	JSONObject root = getTopLevelJSONObject();
	std::string sizeTemp("SizeX");
	std::wstring sizeTemp2;
	sizeTemp2.assign(sizeTemp.begin(), sizeTemp.end());
	int sizeX = std::stoi(root[sizeTemp2]->AsString());
	sizeTemp = "SizeY";
	sizeTemp2.assign(sizeTemp.begin(), sizeTemp.end());
	int sizeY = std::stoi(root[sizeTemp2]->AsString());
	for (int i = 0; i < sizeX; i++)
	{
		std::string word("Row" + std::to_string(i));
		std::wstring wWord;
		wWord.assign(word.begin(), word.end());
		JSONObject row = root[wWord]->AsObject();
		std::vector<std::string> mapRow;
		mapRow.clear();
		for (int j = 0; j < sizeY; j++)
		{
			std::string word2(std::to_string(j));
			std::wstring wWord2;
			wWord2.assign(word2.begin(), word2.end());
			std::wstring holder(row[wWord2]->AsString());
			std::string holderString(holder.begin(), holder.end());
			mapRow.push_back(holderString);
			std::cout << " " << holderString;
		}
		map.push_back(mapRow);
		std::cout << "" << std::endl;
	}
	return map;
}

std::string JSONReader::ElementGetter(std::string x)
{
	JSONObject root = getTopLevelJSONObject();
	std::string temp(x);
	std::wstring temp2;
	temp2.assign(temp.begin(), temp.end());
	std::wstring holder = root[temp2]->AsString();
	return std::string(holder.begin(), holder.end());
}
