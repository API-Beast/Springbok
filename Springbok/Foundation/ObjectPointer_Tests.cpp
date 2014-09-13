#include "ObjectPointer.h"
#include "SSTest.h"

namespace
{
	
void basicUsage()
{
	//! [Basic usage]
	int* x = new int(5);
	ObjectPointer<int> ptrA = x;
	ObjectPointer<int> ptrB = ptrA;
	ObjectPointer<float> ptrC = reinterpret_cast<float*>(x);
	// Calls "delete x;" and sets every ObjectPointer pointing to 'x' to nullptr.
	ptrA.destroy();
	// ptrA, ptrB and ptrC are all nullptr now.
	//! [Basic usage]
	SST_M_ASSERT_START;
	SST_M_ASSERT(!ptrA);
	SST_M_ASSERT(!ptrB);
	SST_M_ASSERT(!ptrC);
	SST_M_ASSERT(ptrA == nullptr);
	SST_M_ASSERT(ptrB == nullptr);
	SST_M_ASSERT(ptrC == nullptr);
	SST_M_ASSERT_END;
}

void replaceWith()
{
	//! [replaceWith]
	int* x = new int(999);
	int* y = new int(1000);
	ObjectPointer<int> ptrA = x;
	ObjectPointer<int> ptrB = x;
	ptrA.replaceWith(y, true);
	// *ptrA == *ptrB == *y == 1000 now
	*ptrB = 2000;
	// *ptrA == *ptrB == *y == 2000 now
	//! [replaceWith]
	SST_M_ASSERT_START;
	SST_M_ASSERT(ptrA != x);
	SST_M_ASSERT(ptrB != x);
	SST_M_ASSERT(ptrA == y);
	SST_M_ASSERT(ptrB == y);
	SST_M_ASSERT((*ptrA) == 2000);
	SST_M_ASSERT((*ptrB) == 2000);
	SST_M_ASSERT_END;
	
	delete y;
}

SST::SimpleTest a("Generic/ObjectPointer", &basicUsage,  SST::Required);
SST::SimpleTest b("Generic/ObjectPointer::replaceWith", &replaceWith, SST::Required);

}
