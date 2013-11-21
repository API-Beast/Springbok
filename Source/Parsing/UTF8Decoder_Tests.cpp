#include "UTF8Decoder.h"
#include "SSTest.h"

namespace
{
	
void test()
{
	std::string test = u8"♀ + ♂ = ⚥";
	std::u32string result;
	std::u32string compare = U"♀ + ♂ = ⚥";
	UTF8Decoder utf(test);
	while(utf.inRange())
		result.push_back(Codepoint(utf++));

	SST_M_ASSERT_START;
	SST_M_ASSERT(result == compare);
	SST_M_ASSERT_END;
}

SST::SimpleTest a("Parsing/UTF8Decoder", &test,  SST::Required);

}
