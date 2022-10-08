/*
* @brief     the implementation of the unit test for translator
* @author    David Wang
* @date      07 Oct 2022
*/

#include "gtest/gtest.h"
#include "Translator.h"
#include <string>
#include <vector>

using namespace std;

TEST(testTranslator, TestparseFunction)
{
	vector<string> vec_place_param;
	Translator translator;
	//input some correct values
	string sRes = translator.parse("MOVE", vec_place_param);
	EXPECT_TRUE("MOVE" == sRes);

	sRes = translator.parse("LEFT", vec_place_param);
	EXPECT_TRUE("LEFT" == sRes);

	sRes = translator.parse("RIGHT", vec_place_param);
	EXPECT_TRUE("RIGHT" == sRes);

	sRes = translator.parse("REPORT", vec_place_param);
	EXPECT_TRUE("REPORT" == sRes);

	sRes = translator.parse("PLACE 3,3,NORTH", vec_place_param);
	EXPECT_TRUE("PLACE" == sRes);
	EXPECT_TRUE("3" == vec_place_param[0]);
	EXPECT_TRUE("3" == vec_place_param[1]);
	EXPECT_TRUE("NORTH" == vec_place_param[2]);

	//input some incorrect values
	sRes = translator.parse("WESTERN", vec_place_param);
	EXPECT_TRUE("" == sRes);

	sRes = translator.parse("1415926", vec_place_param);
	EXPECT_TRUE("" == sRes);

	sRes = translator.parse("PLACE 3,3,5,EARTH", vec_place_param);
	EXPECT_TRUE("" == sRes);

	sRes = translator.parse("PLACE 4,4,WEST", vec_place_param);
	EXPECT_TRUE("PLACE" == sRes);
	EXPECT_TRUE("4" == vec_place_param[0]);
	EXPECT_TRUE("4" == vec_place_param[1]);
	EXPECT_TRUE("WEST" == vec_place_param[2]);
}

TEST(testTranslator, TestSplitStringByCommaFunction)
{
	vector<string> vec_place_param;
	Translator translator;

	translator.splitStringByComma(vec_place_param, "3,4,NORTH,5,6,SOUTH");
	EXPECT_TRUE("3" == vec_place_param[0]);
	EXPECT_TRUE("4" == vec_place_param[1]);
	EXPECT_TRUE("NORTH" == vec_place_param[2]);
	EXPECT_TRUE("5" == vec_place_param[3]);
	EXPECT_TRUE("6" == vec_place_param[4]);
	EXPECT_TRUE("SOUTH" == vec_place_param[5]);

	vec_place_param.clear();
	translator.splitStringByComma(vec_place_param, ",,,");
	EXPECT_TRUE("" == vec_place_param[0]);
	EXPECT_TRUE("" == vec_place_param[1]);
	EXPECT_TRUE("" == vec_place_param[2]);
	EXPECT_TRUE("" == vec_place_param[3]);

	vec_place_param.clear();
	translator.splitStringByComma(vec_place_param, "1,2,3,4,5,6,7,8,9,10");
	for (size_t i = 0; i < 10; ++i)
	{
		string temp = to_string(i+1);
		EXPECT_TRUE( temp == vec_place_param[i]);
	}
}