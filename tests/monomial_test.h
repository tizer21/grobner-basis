#pragma once

#include "../src/monomial.h"

void TestMonomial()
{
    using namespace NLibPoly;

    TMonomial e = TMonomial();
    TMonomial a = TMonomial({0, 1, 2, 3, 4});
    TMonomial b = TMonomial({0, 1, 2, 3, 4, 0, 0, 0});

    assert(a == b);
    assert(e != a);

    for (unsigned i = 0; i != 5; ++i)
    {
        assert(a.GetDegreeOf(i) == i);
    }
    assert(a.GetDegreeOf(5) == 0);
    assert(a.GetDegreeOf(100) == 0);

    assert(a.GetEndIndex() == 5);
    assert(e.GetEndIndex() == 0);

    assert(e.GetDegree() == 0);
    assert(a.GetDegree() == 10);

    TMonomial c = {1, 0, 0, 1, 0, 1, 1, 1};
    assert((a * c) == TMonomial({1, 1, 2, 4, 4, 1, 1, 1}));
    assert((c * e) == TMonomial({1, 0, 0, 1, 0, 1, 1, 1}));
    assert((e * c) == TMonomial({1, 0, 0, 1, 0, 1, 1, 1}));

    TMonomial d = {1, 2, 2, 3, 4};
    assert((d / a) == TMonomial({1, 1}));
    assert((d / e) == TMonomial({1, 2, 2, 3, 4}));
    assert((d / d) == TMonomial());
}
