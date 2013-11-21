#include "ConfigFile.h"
#include "SSTest.h"

namespace
{
	
void basicUsage()
{
	std::string configuration;
	configuration = R"(
#include ConfigFile_Sample.scnf
	)";
	ConfigFile configFile;
	configFile.loadFromBuffer(configuration);

	SST_M_ASSERT_START;
	SST_M_ASSERT(configFile["UnnestedValue"] == "ABC");
	SST_M_ASSERT(configFile["SimpleObject.NestedValue"] == "DEF");
	SST_M_ASSERT(configFile["King.Baron.Peasant.Name"] == "Joe");
	SST_M_ASSERT_END;
}

SST::SimpleTest a("Parsing/ConfigFile", &basicUsage,  SST::Required);

}
