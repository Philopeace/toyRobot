#include "Translator.h"

using namespace std;

Translator::Translator()
{
	m_vec_place_param.clear();
}

Translator::~Translator()
{
}

void Translator::splitStringByComma(vector<string>& vec_res, string s_target)
{
	size_t pos = s_target.find(',');
	while (string::npos != pos)
	{
		vec_res.push_back(s_target.substr(0, pos));
		s_target.erase(0, pos + 1);
		pos = s_target.find(',');
	}

	vec_res.push_back(s_target);
}

string Translator::parse(string inputLine, vector<string> &vec_place_param)
{
	string res = "";
	string sub_string = "";
	int index = -1;
	vec_place_param.clear();

	if ("MOVE" == inputLine)
	{
		res = "MOVE";
	}
	else if ("LEFT" == inputLine)
	{
		res = "LEFT";
	}
	else if ("RIGHT" == inputLine)
	{
		res = "RIGHT";
	}
	else if ("REPORT" == inputLine)
	{
		res = "REPORT";
	}
	else if (-1 != inputLine.find("PLACE"))
	{
		index = inputLine.find("PLACE");
		if (index != 0)
			return res;

		sub_string = inputLine.substr(6);
		splitStringByComma(vec_place_param, sub_string);
		if (vec_place_param.size() != 3)
			return res;

		res = "PLACE";		
	}
	else if ("QUIT" == inputLine)
	{
		res = "QUIT";
	}

	return res;
}
