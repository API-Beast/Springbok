#include "SimpleList.h"
#include "SSTest.h"

namespace
{
	
void list()
{
	int memoryArea[5];
	memoryArea[4] = 999;
	SimpleList<int> b(memoryArea, 4);
	b.pushBack(0);
	b.pushBack(1);
	b.pushBack(2);
	b.pushBack(3);
	
	bool catched = false;
	try{ b.pushBack(4);}
	catch(AllocatedMemoryFull e){ catched = true; }
	b.reallocate(5);
	b.pushBack(4);
	
	SST_M_ASSERT_START;
	SST_M_ASSERT_EQ(b[0], 0);
	SST_M_ASSERT_EQ(b[1], 1);
	SST_M_ASSERT_EQ(b[2], 2);
	SST_M_ASSERT_EQ(b[3], 3);
	SST_M_ASSERT_EQ(b[4], 4);
	SST_M_ASSERT(catched);
	SST_M_ASSERT_EQ(memoryArea[4], 999);
	SST_M_ASSERT_END;
}

void insert()
{
	int memoryArea[6] = {0, 1, 2, 3, 4, 5};
	SimpleList<int> b(memoryArea, 6, 5);
	b.insert(2, 99);

	SST_M_ASSERT_START;
	SST_M_ASSERT_EQ(b[0], 00);
	SST_M_ASSERT_EQ(b[2], 99);
	SST_M_ASSERT_EQ(b[5], 04);
	SST_M_ASSERT_END;
}

void pop()
{
	std::string memoryArea[5] = {"A", "B", "C", "D", "E"};
	SimpleList<std::string> b(memoryArea);

	SST_M_ASSERT_START;
	SST_M_ASSERT_EQ(b.popBack(), "E");
	SST_M_ASSERT_END;
}

void initializer()
{
	SimpleList<std::string> a{"0", "9", "1"};
	
	SST_M_ASSERT_START;
	SST_M_ASSERT_EQ(a[0], "0");
	SST_M_ASSERT_EQ(a[1], "9");
	SST_M_ASSERT_EQ(a[2], "1");
	SST_M_ASSERT_END;
}

struct Object
{
	Object(){};
	Object(int id, char name='Z', int health=100):ID(id),Key(name),Health(health){};
	bool operator==(const Object& other){ return ID == other.ID && Key == other.Key && Health == other.Health; };
	int ID = 0;
	char Key = 'Z';
	int Health = 100;
};

void podMap()
{
	SimpleMap<Object, char, &Object::Key> objects(0);
	objects.insert({  0, 'F'});
	objects.insert({ 90, 'A'});
	objects.insert({100, 'Y'});
	objects.insert({100, 'Z'});
	
	SST_M_ASSERT_START;
	SST_M_ASSERT_EQ(objects['F'].Key, 'F');
	SST_M_ASSERT_EQ(objects['A'].Key, 'A');
	SST_M_ASSERT_EQ(objects['Y'].Key, 'Y');
	SST_M_ASSERT_EQ(objects['Z'].Key, 'Z');
	SST_M_ASSERT_EQ(objects['F'].ID, 0);
	SST_M_ASSERT_EQ(objects['A'].ID, 90);
	SST_M_ASSERT_EQ(objects['Y'].ID, 100);
	SST_M_ASSERT_EQ(objects['Z'].ID, 100);
	SST_M_ASSERT_EQ(objects['F'].Health, 100);
	SST_M_ASSERT_EQ(objects['A'].Health, 100);
	SST_M_ASSERT_EQ(objects['Y'].Health, 100);
	SST_M_ASSERT_EQ(objects['Z'].Health, 100);
	SST_M_ASSERT_END;
}

struct Names
{
	Names& operator=(const std::string& str){ Value = str; return *this; };
	std::string Key;
	std::string Value;
};

void map()
{
	SimpleMap<Names, std::string, &Names::Key> names;
	names["Me"]  = "Nathan";
	names["You"] = "John";
	
	SST_M_ASSERT_START;
	SST_M_ASSERT_EQ(names["Me"].Value, "Nathan");
	SST_M_ASSERT_EQ(names["You"].Value, "John");
	SST_M_ASSERT_END;
}

void mapInitializer()
{
	SimpleMap<Names, std::string, &Names::Key> a{{"0", "a"}, {"9", "c"}, {"1", "b"}};
	
	SST_M_ASSERT_START;
	// Make sure its sorted
	SST_M_ASSERT_EQ(a.Data[0].Key, "0");
	SST_M_ASSERT_EQ(a.Data[1].Key, "1");
	SST_M_ASSERT_EQ(a.Data[2].Key, "9");	
	// And that the access works
	SST_M_ASSERT_EQ(a["0"].Value, "a");
	SST_M_ASSERT_EQ(a["1"].Value, "b");
	SST_M_ASSERT_EQ(a["9"].Value, "c");
	SST_M_ASSERT_END;
}

SST::SimpleTest GSL("Generic/SimpleList", &list,  SST::Required);
SST::SimpleTest GSLi("Generic/SimpleList::insert", &insert,  SST::Required);
SST::SimpleTest GSLpb("Generic/SimpleList::popBack", &pop,  SST::Required);
SST::SimpleTest GSLil("Generic/SimpleList::initializer", &initializer,  SST::Required);
SST::SimpleTest GSMpod("Generic/SimpleMap::plainOldData", &podMap,  SST::Required);
SST::SimpleTest GSMc("Generic/SimpleMap::complex", &map,  SST::Required);

}
