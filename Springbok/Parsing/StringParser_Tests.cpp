#include "StringParser.h"
#include "SSTest.h"

namespace
{
	
void test()
{
	std::string a = "Test.ABC";
	StringParser p(a);
	SST_M_ASSERT_START;
	SST_M_ASSERT_EQ(p.peek(), 'T');
	SST_M_ASSERT_EQ(p.next(), 'e');
	SST_M_ASSERT_EQ(p.next(), 's');
	SST_M_ASSERT_EQ(p.peek(), 's');
	p.reset();
	SST_M_ASSERT_EQ(p.advanceTo(U'.'), "Test");
	SST_M_ASSERT_EQ(p.advanceTo(U'€'), "ABC");
	SST_M_ASSERT_END;
}

SST::SimpleTest a("Parsing/StringParser", &test,  SST::Required);

}
