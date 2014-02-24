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
#include <sstream>
#include <type_traits>
#include <locale>
#include <iomanip>
#include <limits>
#include <Source/Parsing/ConfigFile.h>

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
	virtual bool run(std::ostream& out, bool catchExceptions = true){};
	virtual Category getCategory(){ return Loose; };
	virtual const char* getIdentifier(){ return "!Missing!"; };
};

class SimpleTest : public AbstractTest
{
public:
	SimpleTest(const char* ident, std::function<void()> fun, Category cat);
	virtual bool run(std::ostream& out, bool catchExceptions = true);
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
	TestCollector();
	void addTest(AbstractTest* test);
	bool runTests(int argc, char* argv[]);
	bool runAllTests(bool catchExceptions = true);
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
	AssertFailure(const std::string& expression, const std::string& extra, const char* file, const char* function, int line);
	std::string Expression;
	std::string ExtraInfo;
	const char* File;
	const char* Function;
	int Line;
};

template <typename T>
inline void decorateVal(std::ostream& str, T val)
{
	str.precision(std::numeric_limits<float>::digits10+2);
	
	//std::string herpusderpus = herpus;

#pragma message("FIX ME! error: invalid operands to binary expression ('std::ostream' (aka 'basic_ostream<char>') and 'ConfigFile::PossibleArray')")
	//error: invalid operands to binary expression ('std::ostream' (aka 'basic_ostream<char>') and 'ConfigFile::PossibleArray')

	str << std::fixed;
}

template <>
inline void decorateVal(std::ostream& str, char val)
{
	str << '\'' << val << '\'';
}

template <>
inline void decorateVal(std::ostream& str, char16_t val)
{
	str << "u" << '\'' << val << '\'';
}

template <>
inline void decorateVal(std::ostream& str, char32_t val)
{
	str << "U" << '\'' << val << '\'';
}

template <>
inline void decorateVal(std::ostream& str, std::string val)
{
	str << '"' << val << '"';
}

template<typename T>
void decorateVal(std::ostream& str, const std::vector<T>& val)
{
	str << '{';
	bool isFirst = true;
	for(auto Z : val)
	{
		if(!isFirst)
			str << ", ";
		decorateVal(str, Z);
		isFirst = false;
	};
	str << '}';
};

template <typename T>
typename std::enable_if<std::is_convertible<T, std::string>::value, std::string>::type ToString(T value)
{
	return  "\"" + std::string(value) +  "\""; 
};

template <typename T>
typename std::enable_if<!std::is_convertible<T, std::string>::value, std::string>::type ToString(T value)
{
   std::stringstream ss;
   decorateVal(ss, value);
   return ss.str();
};

template <typename T>
typename std::enable_if<!std::is_convertible<std::basic_string<T>, std::string>::value, std::string>::type ToString(std::basic_string<T> value)
{
	std::stringstream ss;
	if(sizeof(T) == 2)
		ss << 'u';
	else if(sizeof(T) == 4)
		ss << 'U';
	ss << '\"';
	for(auto c : value)
	{
		if(c < 127)
			ss << char(c);
		else
			ss << "\\U" << std::hex << int(c);
	}
	ss << '\"';
	return ss.str();
};

template <typename To, typename T>
typename std::enable_if<std::is_convertible<T, To>::value, To>::type ToType(const T& value)
{
	return static_cast<To>(value);
};

template <typename To, typename T>
typename std::enable_if<!std::is_convertible<T, To>::value, T>::type ToType(const T& value)
{
	return value;
};

bool AlmostEqual(float A, float B, int maxUlps);

#define SST_S_ASSERT(x) if(!(x)) throw SST::AssertFailure(#x , __FILE__, __PRETTY_FUNCTION__, __LINE__)
#define SST_S_ASSERT_EQ(x, y) { auto ass__a = (x); auto ass__b = (y); if(!(ass__a == ass__b)) throw SST::AssertFailure( std::string(#x " == " #y), SST::ToString(SST::ToType<decltype(ass__b)>(ass__a)) + " != " + SST::ToString(ass__b), __FILE__, __PRETTY_FUNCTION__, __LINE__); }
#define SST_M_ASSERT_START { std::vector<SST::AssertFailure> __asserts__
#define SST_M_ASSERT(x) if(!(x)) __asserts__.push_back(SST::AssertFailure(#x , __FILE__, __PRETTY_FUNCTION__, __LINE__));
#define SST_M_ASSERT_EQ(x, y) { auto ass__a = (x); auto ass__b = (y); if(!(ass__a == ass__b)) __asserts__.push_back(SST::AssertFailure( std::string(#x " == " #y), SST::ToString(SST::ToType<decltype(ass__b)>(ass__a)) + " != " + SST::ToString(ass__b), __FILE__, __PRETTY_FUNCTION__, __LINE__)); }
#define SST_M_ASSERT_GT(x, y) { auto ass__a = (x); auto ass__b = (y); if(!(ass__a  > ass__b)) __asserts__.push_back(SST::AssertFailure( std::string(#x " > " #y), SST::ToString(SST::ToType<decltype(ass__b)>(ass__a)) + " <= " + SST::ToString(ass__b), __FILE__, __PRETTY_FUNCTION__, __LINE__)); }
#define SST_M_ASSERT_ST(x, y) { auto ass__a = (x); auto ass__b = (y); if(!(ass__a  < ass__b)) __asserts__.push_back(SST::AssertFailure( std::string(#x " < " #y), SST::ToString(SST::ToType<decltype(ass__b)>(ass__a)) + " >= " + SST::ToString(ass__b), __FILE__, __PRETTY_FUNCTION__, __LINE__)); }
#define SST_M_ASSERT_SIM(x, y, z) { auto ass__a = (x); auto ass__b = (y); auto ass__c = (z); if(Abs(ass__a - ass__b) > ass__c) __asserts__.push_back(SST::AssertFailure( std::string(#x " ~~ " #y), SST::ToString(SST::ToType<decltype(ass__b)>(ass__a)) + " !~~ " + SST::ToString(ass__b), __FILE__, __PRETTY_FUNCTION__, __LINE__)); }
#define SST_M_ASSERT_EQf(x, y) { auto ass__a = (x); auto ass__b = (y); if(!SST::AlmostEqual(float(ass__a), float(ass__b), 20)) __asserts__.push_back(SST::AssertFailure( std::string(#x " == " #y), SST::ToString(SST::ToType<decltype(ass__b)>(ass__a)) + " != " + SST::ToString(ass__b), __FILE__, __PRETTY_FUNCTION__, __LINE__)); }
#define SST_M_ASSERT_ALMOST_EQ(x, y, i) { auto ass__a = (x); auto ass__b = (y); if(!SST::AlmostEqual(float(ass__a), float(ass__b), (i))) __asserts__.push_back(SST::AssertFailure( std::string(#x " == " #y), SST::ToString(SST::ToType<decltype(ass__b)>(ass__a)) + " != " + SST::ToString(ass__b), __FILE__, __PRETTY_FUNCTION__, __LINE__)); }
#define SST_M_ASSERT_END if(!__asserts__.empty()) throw __asserts__; }

}

#endif // SSTEST_H
