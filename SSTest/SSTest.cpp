/*
 * Copyright (C) 2013 Manuel Riecke <m.riecke@mrbeast.org>
 *
 * TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 * 0. You just DO WHAT THE FUCK YOU WANT TO.
 */

#include "SSTest.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <unistd.h>
#include <signal.h>

using namespace std;

SST::TestCollector* SST::TestCollector::gInstance = nullptr;

struct ThrownSignal
{
	const char* signal;
};

void HandleSignal(int signal)
{
	if(signal == SIGSEGV)
		throw ThrownSignal{"Memory Access Violation"};
	if(signal == SIGFPE)
		throw ThrownSignal{"Floating Point Exception"};
	if(signal == SIGILL)
		throw ThrownSignal{"Illegal Instruction"};
	if(signal == SIGABRT)
		throw ThrownSignal{"Abort"};
}

SST::TestCollector::TestCollector()
{
	signal(SIGSEGV, &HandleSignal);
	signal(SIGFPE, &HandleSignal);
	signal(SIGILL, &HandleSignal);
	//signal(SIGABRT, &HandleSignal);
}

bool SST::SimpleTest::run(ostream& out, bool catchExceptions)
{
	bool result = true;
	std::string clReset = "";
	std::string clHighlight = "";
	std::string clAccent = "";
	if(false)
	{
		clReset = "\033[0m";
		clHighlight = "\033[1m";
		clAccent = "\033[1;31m";
	}
	auto printAssert = [&](SST::AssertFailure& a)
	{
		out << clHighlight << "Asserts failed: '" << clReset << a.Expression << "' in " << a.File << "::" << a.Line << " in function " << a.Function << endl;
		if(!a.ExtraInfo.empty())
			out << "   -> " << clAccent << a.ExtraInfo << clReset << endl;
	};
	
	if(catchExceptions)
	{
		try
		{
			if(mFunc) mFunc();
			else
			{
				out << "Can't run, test is misconfigured." << endl;
				result = false;
			}
		}
		catch(std::out_of_range& e)
		{
			out << "Exception: out_of_range " << e.what() << endl;
			result = false;
		}
		catch(std::exception& e)
		{
			out << "Exception: " << e.what() << endl;
			result = false;
		}
		catch(SST::AssertFailure& a)
		{
			printAssert(a);
			result = false;
		}
		catch(std::vector<SST::AssertFailure>& vec)
		{
			for(SST::AssertFailure& a : vec)
				printAssert(a);
			result = false;
		}
		catch(ThrownSignal& s)
		{
			out << "Signal: " << s.signal << endl;
			result = false;
		}
		catch(...)
		{
			out << "Unhandled and unknown exception catched." << endl;
			result = false;
		}
	}
	else
	{
		if(mFunc) mFunc();
		else
		{
			out << "Can't run, test is misconfigured." << endl;
			result = false;
		}
	}
	if(result) out << "SUCESS" << endl;
	else out << "FAIL" << endl;
	return result;
}

SST::SimpleTest::SimpleTest(const char* ident, function< void()> fun, SST::Category cat)
{
	mIdent = ident;
	mFunc = fun;
	mCategory = cat;
	SST::TestCollector::GetInstance().addTest(this);
}


void SST::TestCollector::addTest(SST::AbstractTest* test)
{
	mAllTests.push_back(test);
	mTestByName[test->getIdentifier()] = test;
	switch(test->getCategory())
	{
		case Required:
			mRequiredTests.push_back(test);
			break;
		case Optional:
			mOptionalTests.push_back(test);
			break;
		case Loose:
			mLooseTests.push_back(test);
			break;
	}
}

SST::AssertFailure::AssertFailure(const string& expression, const char* file, const char* function, int line)
{
	Expression = expression;
	File = file;
	Function = function;
	Line = line;
}

SST::AssertFailure::AssertFailure(const string& expression, const string& extra, const char* file, const char* function, int line)
{
	Expression = expression;
	ExtraInfo = extra;
	File = file;
	Function = function;
	Line = line;
}

bool SST::TestCollector::runTests(int argc, char* argv[])
{
	if(argc == 1) return runAllTests();
	else if(argc == 2)
	{
		if(std::string(argv[1]) == "-l") return listTests();
		if(std::string(argv[1]) == "-d") return runAllTests(false);
	}
	bool returnVal = true;
	try
	{
		while(argc--)
		{
			std::string test = argv[argc];
			returnVal = returnVal && mTestByName.at(test)->run(cerr);
		}
	}
	catch(...){};
	return returnVal;
}

struct TestCategory
{
	std::string Name;
	std::vector<SST::AbstractTest*>& Container;
	int FailedTests;
	bool Required;
};

bool SST::TestCollector::runAllTests(bool catchExceptions)
{
	TestCategory testCategories[2] = {{"Required", mRequiredTests, 0, true}, {"Optional", mOptionalTests, 0, false}};
	
	std::vector<SST::AbstractTest*> failedTests(0);
	bool requiredTestFailed = false;
	for(TestCategory& cat : testCategories)
	{
		int currentTest = 0;
		cout << "Running test category: " << cat.Name << endl;
		for(SST::AbstractTest* test : cat.Container)
		{
			std::stringstream status;
			std::string buffer;
			
			currentTest++;
			
			std::stringstream tempBuffer;
			tempBuffer << right << "["<< setfill('0') << setw(3) << currentTest << "/" << setw(3) << cat.Container.size() << "] ";
			std::string prepend = tempBuffer.str();
			cout << prepend << "Running test " << test->getIdentifier() << endl;
			
			bool sucess = (test->run(status, catchExceptions));
			if(!sucess)
			{
				failedTests.push_back(test);
				cat.FailedTests++;
				if(cat.Required) requiredTestFailed = true;
			}
			while(!status.eof())
			{
				getline(status, buffer);
				if(buffer.empty()) continue;
				cerr << prepend << buffer << endl;
			}
			cout << prepend << "~~~~~~~~~~~~~~" << endl;
		}
	}
	
	if(!failedTests.empty())
	{
		for(TestCategory& cat : testCategories)
		{
			cout << "From category " << cat.Name << " " << cat.FailedTests << " Tests have failed" << endl;
		}
		cout << endl;
		cout << "The following tests have failed:" << endl;
		for(SST::AbstractTest* test : failedTests)
			cout << "  " << test->getIdentifier() << endl;
	}
	else
		cout << "All tests were sucessful." << endl;
	return !requiredTestFailed;
}

bool SST::TestCollector::listTests()
{
	bool before=false;
	for(SST::AbstractTest* test : mAllTests){ if(before) cout << ";"; cout << test->getIdentifier(); before = true;}
	cout << endl;
	return true;
}

// From http://www.cygnus-software.com/papers/comparingfloats/Comparing%20floating%20point%20numbers.htm#_Toc135149455
bool SST::AlmostEqual(float A, float B, int maxUlps)
{
	// Make sure maxUlps is non-negative and small enough that the
	// default NAN won't compare as equal to anything.
	assert(maxUlps > 0 && maxUlps < 4 * 1024 * 1024);
	int aInt = *(int*)&A;
	// Make aInt lexicographically ordered as a twos-complement int
	if (aInt < 0)
			aInt = 0x80000000 - aInt;
	// Make bInt lexicographically ordered as a twos-complement int
	int bInt = *(int*)&B;
	if (bInt < 0)
			bInt = 0x80000000 - bInt;
	int intDiff = abs(aInt - bInt);
	if (intDiff <= maxUlps)
			return true;
	return false;
}

