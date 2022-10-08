#pragma once

/*
* @brief     the implementation of the translator Class
* @author    David Wang
* @date      06 Oct 2022
*/

#include <string>
#include <vector>

class Translator
{
public:
	Translator();
	~Translator();

	std::string parse(std::string inputLine, std::vector<std::string> &vec_place_param);
	void splitStringByComma(std::vector<std::string>& vec_res, std::string s_target);

private:
	std::vector<std::string> m_vec_place_param;
};

