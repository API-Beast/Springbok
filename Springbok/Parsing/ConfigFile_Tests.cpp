#include "ConfigFile.h"
#include "SSTest.h"

namespace
{
	
void basicUsage()
{
	std::string configuration;
	configuration = u8R"(
UnnestedValue = ABC
EnclosedString = " <- Whitespace"
Array = [a, b, c]

; Single line object
Object: Value = Great

[SimpleObject]
NestedValue = DEF

King
{
	Name = Joffrey
  Baron
  {
		Name = Baratheon
		
		[Peasant]
		Name = Joe
  }
  
  Baron
  {
		Name = Beartastic
  
		Peasant: Name = Jeff
  }
}
	)";
	ConfigFile configFile;
	configFile.loadFromBuffer(configuration);

	SST_M_ASSERT_START;
	SST_M_ASSERT_EQ(configFile["UnnestedValue"], "ABC");
	SST_M_ASSERT_EQ(configFile["Object.Value"], "Great");
	SST_M_ASSERT_EQ(configFile["SimpleObject.NestedValue"], "DEF");
	SST_M_ASSERT_EQ(configFile["King.Baron.Peasant.Name"], "Joe");
	SST_M_ASSERT_EQ(configFile.getObject("King").Children[1]["Name"], "Beartastic");
	SST_M_ASSERT_EQ(configFile["EnclosedString"], " <- Whitespace");
	std::vector<std::string> result = {"a", "b", "c"};
	SST_M_ASSERT_EQ(configFile["Array"], result);
	SST_M_ASSERT_END;
}

SST::SimpleTest a("Parsing/ConfigFile", &basicUsage,  SST::Required);
}
