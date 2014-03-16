#include "UTF8.h"
#include "SSTest.h"
#include <Springbok/Generic/Logic.h>

namespace
{
	
void test()
{
	std::string test = u8"♀ + ♂ = ⚥";
	std::u32string result;
	std::u32string compare = U"♀ + ♂ = ⚥";
	int i = 0;
	Codepoint cur = UTF8::DecodeAt(test, i);
	while(i < test.size())
	{
		result.push_back(cur);
		cur = UTF8::DecodeNext(test, &i);
	}

	SST_M_ASSERT_START;
	SST_M_ASSERT_EQ(result, compare);
	SST_M_ASSERT_END;
}

void strip()
{
	SST_M_ASSERT_START;
	SST_M_ASSERT_EQ(UTF8::StripLeft("__Test__", EqualTo('_')), "Test__");
	SST_M_ASSERT_EQ(UTF8::StripRight("__Test__", EqualTo('_')), "__Test");
	SST_M_ASSERT_EQ(UTF8::Strip("__Test__", EqualTo('_')), "Test");
	SST_M_ASSERT_END;	
}

SST::SimpleTest a("Parsing/UTF8", &test,  SST::Required);
SST::SimpleTest b("Parsing/UTF8::Strip", &strip,  SST::Required);

}
