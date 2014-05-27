#include "List.h"
#include <Springbok/Types/Vec2.h>
#include "SSTest.h"

namespace
{
	
void list()
{
	SST_M_ASSERT_START;
	int memoryArea[5];
	memoryArea[4] = 999;
	List<int> b(memoryArea, 4);
	b.pushBack(0);
	b.pushBack(1);
	b.pushBack(2);
	b.pushBack(3);
	SST_M_ASSERT_EQ(b.UsedLength, 4);
	
	bool catched = false;
	try{ b.pushBack(4);}
	catch(AllocatedMemoryFull e){ catched = true; }
	b.reallocate(5);
	SST_M_ASSERT_EQ(b.UsedLength, 4);
	b.pushBack(4);
	SST_M_ASSERT_EQ(b.UsedLength, 5);
	
	
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
	List<int> b(memoryArea, 6, 5);
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
	List<std::string> b(memoryArea);

	SST_M_ASSERT_START;
	SST_M_ASSERT_EQ(b.popBack(), "E");
	SST_M_ASSERT_END;
}

void initializer()
{
	List<std::string> a{"0", "9", "1", "12", "15"};
	
	SST_M_ASSERT_START;
	SST_M_ASSERT_EQ(a[0], "0");
	SST_M_ASSERT_EQ(a[1], "9");
	SST_M_ASSERT_EQ(a[2], "1");
	SST_M_ASSERT_EQ(a[3], "12");
	SST_M_ASSERT_EQ(a[4], "15");
	SST_M_ASSERT_EQ(a.UsedLength, 5);
	SST_M_ASSERT_END;
}

void listCold()
{
	List<int> a;
	a.pushBack(1);
	a.pushBack(2);
	a.pushBack(3);
	
	List<int> b(2);
	b.pushBack(1);
	b.pushBack(2);
	b.pushBack(3);
	b.pushBack(4);
	
	SST_M_ASSERT_START;
	SST_M_ASSERT_EQ(a[0], 1);
	SST_M_ASSERT_EQ(a[1], 2);
	SST_M_ASSERT_EQ(a[2], 3);
	SST_M_ASSERT_EQ(b[0], 1);
	SST_M_ASSERT_EQ(b[1], 2);
	SST_M_ASSERT_EQ(b[2], 3);
	SST_M_ASSERT_EQ(b[3], 4);
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
	Map<Object, char, &Object::Key> objects(0);
	objects.insert({  1, 'F'});
	objects.insert({  2, 'A'});
	objects.insert({  3, 'Y'});
	objects.insert({  4, 'Z'});
	
	SST_M_ASSERT_START;
	SST_M_ASSERT_EQ(objects['F'].Key, 'F');
	SST_M_ASSERT_EQ(objects['A'].Key, 'A');
	SST_M_ASSERT_EQ(objects['Y'].Key, 'Y');
	SST_M_ASSERT_EQ(objects['Z'].Key, 'Z');
	SST_M_ASSERT_EQ(objects['F'].ID, 1);
	SST_M_ASSERT_EQ(objects['A'].ID, 2);
	SST_M_ASSERT_EQ(objects['Y'].ID, 3);
	SST_M_ASSERT_EQ(objects['Z'].ID, 4);
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
	Map<Names, std::string, &Names::Key> names;
	names["Me"]  = "Nathan";
	names["You"] = "John";
	
	SST_M_ASSERT_START;
	SST_M_ASSERT_EQ(names["Me"].Value, "Nathan");
	SST_M_ASSERT_EQ(names["You"].Value, "John");
	SST_M_ASSERT_END;
}

void mapInitializer()
{
	Map<Names, std::string, &Names::Key> a{{"0", "a"}, {"9", "c"}, {"1", "b"}};
	
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

SST::SimpleTest GSL("Generic/List", &list,  SST::Required);
SST::SimpleTest GSLcold("Generic/List::coldStart", &listCold,  SST::Required);
SST::SimpleTest GSLi("Generic/List::insert", &insert,  SST::Required);
SST::SimpleTest GSLpb("Generic/List::popBack", &pop,  SST::Required);
SST::SimpleTest GSLil("Generic/List::initializer", &initializer,  SST::Required);
SST::SimpleTest GSMpod("Generic/Map::plainOldData", &podMap,  SST::Required);
SST::SimpleTest GSMc("Generic/Map::complex", &map,  SST::Required);
SST::SimpleTest GSMil("Generic/Map::maxInitializer", &mapInitializer,  SST::Required);

struct Sector
{
	int Position;
	bool Initialized = false;
};

void _indexInsert()
{	
	Map<Sector, int, &Sector::Position> map;
	
	auto check = [&](int index)
	{
		auto& entry = map[index];
		bool wasInitialized = entry.Initialized;
		entry.Initialized = true;
		return wasInitialized;
	};
	
	SST_M_ASSERT_START;
	
	SST_M_ASSERT_EQ(check(2), false);
	SST_M_ASSERT_EQ(check(2), true);
	SST_M_ASSERT_EQ(check(1), false);
	SST_M_ASSERT_EQ(check(0), false);
	SST_M_ASSERT_EQ(check(1), true);
	SST_M_ASSERT_EQ(check(1), true);
	SST_M_ASSERT_EQ(check(2), true);
	SST_M_ASSERT_EQ(check(1), true);
	SST_M_ASSERT_EQ(check(0), true);
	SST_M_ASSERT_EQ(check(0), true);
	SST_M_ASSERT_EQ(check(0), true);
	SST_M_ASSERT_EQ(check(1), true);
	SST_M_ASSERT_EQ(check(2), true);
	SST_M_ASSERT_EQ(check(2), true);
	SST_M_ASSERT_EQ(check(0), true);
	SST_M_ASSERT_EQ(check(1), true);
	SST_M_ASSERT_EQ(check(0), true);
	SST_M_ASSERT_EQ(check(2), true);
	SST_M_ASSERT_EQ(check(2), true);
	SST_M_ASSERT_EQ(check(1), true);
	SST_M_ASSERT_EQ(check(2), true);
	SST_M_ASSERT_EQ(check(1), true);
	
	SST_M_ASSERT_END;
}

SST::SimpleTest _Map_indexInsert("Containers/Map::indexInsert", &_indexInsert, SST::Required);

#include <cstdlib>
#include <climits>

typedef Vec2I ToTest;

struct SingleVal
{
	ToTest Val;
	operator ToTest()
	{
		return Val;
	};
};

void _insertReliability()
{	
	SST_M_ASSERT_START;
	Map<SingleVal, ToTest, &SingleVal::Val> map;
	srand(549834035);
	for(int i = 0; i < 1600; ++i)
	{
		map.insert({{rand()%16, rand()%16}});
		bool isSorted = true;
		ToTest lastItem=map.Data[0];
		for(ToTest item : map.Data)
		{
			if(item >= lastItem)
				continue;
			isSorted = false;
			break;
		}
		SST_M_ASSERT(isSorted);
	}
	SST_M_ASSERT_END;
}

SST::SimpleTest _List_insertReliability("Containers/List::insertReliability", &_insertReliability, SST::Required);


}
