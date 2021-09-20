#include "monomial_test.h"
#include "term_test.h"

void TestAll()
{
    TestMonomial();
    TestTerm();
}

int main()
{
    TestAll();

    return 0;
}
