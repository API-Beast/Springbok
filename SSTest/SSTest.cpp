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

using namespace std;

SST::TestCollector* SST::TestCollector::gInstance = nullptr;

bool SST::SimpleTest::run(ostream& out)
{
	out << "Running test " << getIdentifier() << endl;
	bool result = true;
	try
	{
		if(mFunc) mFunc();
		else
		{
			out << "Can't run, test is misconfigured." << endl;
			result = false;
		}
	}
	catch(std::exception& e)
	{
		out << "Exception: " << e.what() << endl;
		result = false;
	}
	catch(SST::AssertFailure& a)
	{
		out << "Assert failed: '" << a.Expression << "' in " << a.File << "::" << a.Line << " in function " << a.Function << endl;
		result = false;
	}
	catch(std::vector<SST::AssertFailure>& vec)
	{
		for(SST::AssertFailure& a : vec)
			out << "Assert failed: '" << a.Expression << "' in " << a.File << "::" << a.Line << " in function " << a.Function << endl;
		result = false;
	}
	catch(...)
	{
		out << "Unhandled and unknown exception catched." << endl;
		result = false;
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

bool SST::TestCollector::runTests(int argc, char* argv[])
{
	if(argc == 1) return runAllTests();
	else if(argc == 2) if(std::string(argv[1]) == "-l") return listTests();
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

bool SST::TestCollector::runAllTests()
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
			bool sucess = (test->run(status));
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
				cerr << right << "["<< setfill('0') << setw(3) << currentTest << "/" << setw(3) << cat.Container.size() << "] " << buffer << endl;
			}
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
