/*
 * Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
 *
 * TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 * 0. You just DO WHAT THE FUCK YOU WANT TO.
 */

#ifndef SSTEST_H
#define SSTEST_H

#include <vector>
#include <functional>
#include <exception>
#include <cassert>
#include <ostream>
#include <string>
#include <map>

namespace SST
{

enum Category
{
	Required,
	Optional,
	Loose
};

class AbstractTest
{
public:
	virtual bool run(std::ostream& out){};
	virtual Category getCategory(){ return Loose; };
	virtual const char* getIdentifier(){ return "!Missing!"; };
};

class SimpleTest : public AbstractTest
{
public:
	SimpleTest(const char* ident, std::function<void()> fun, Category cat);
	virtual bool run(std::ostream& out);
	virtual Category getCategory(){ return mCategory;};
	virtual const char* getIdentifier(){ return mIdent; };
private:
	std::function<void()> mFunc;
	const char* mIdent;
	Category mCategory;
};

class TestCollector
{
public:
	static TestCollector* gInstance;
	static TestCollector& GetInstance(){ if(!gInstance) gInstance = new TestCollector; return *gInstance; };
public:
	void addTest(AbstractTest* test);
	bool runTests(int argc, char* argv[]);
	bool runAllTests();
	bool runTest(SST::AbstractTest* test, std::ostream& out);
	bool listTests();
private:
	std::map<std::string, AbstractTest*> mTestByName;
	std::vector<AbstractTest*> mAllTests;
	std::vector<AbstractTest*> mRequiredTests;
	std::vector<AbstractTest*> mOptionalTests;
	std::vector<AbstractTest*> mLooseTests;
};

inline int RunTests(int argc, char* argv[]){ return TestCollector::GetInstance().runTests(argc, argv); };

class AssertFailure
{
public:
	AssertFailure(const std::string& expression, const char* file, const char* function, int line);
	std::string Expression;
	const char* File;
	const char* Function;
	int Line;
};

#define SST_S_ASSERT(x) if(!(x)) throw SST::AssertFailure(#x , __FILE__, __PRETTY_FUNCTION__, __LINE__)
#define SST_M_ASSERT_START { std::vector<SST::AssertFailure> __asserts__
#define SST_M_ASSERT(x) if(!(x)) __asserts__.push_back(SST::AssertFailure(#x , __FILE__, __PRETTY_FUNCTION__, __LINE__));
#define SST_M_ASSERT_END if(!__asserts__.empty()) throw __asserts__; }

}

#endif // SSTEST_H
