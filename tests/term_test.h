<<<<<<< HEAD
#pragma once

#include "../src/term.h"

void TestTerm()
{
    using namespace NLibPoly;

    TMonomial monomialA = TMonomial({0, 1, 2, 3, 4});

    TTerm<int> termZero = TTerm<int>();
    TTerm<int> termZeroExtra = TTerm<int>(0, {1, 0, 1});
    TTerm<int> termA = TTerm<int>(2, monomialA);
    TTerm<int> termB = TTerm<int>(2, {0, 1, 2, 3, 4});

    assert(termA == termB);
    assert(termZero == termZeroExtra);
    assert(termZero != termA);

    TTerm<int> termC = TTerm<int>(14, {1, 2, 2, 3, 4, 0, 0, 1});
    assert((termC * termA) == TTerm<int>(28, {1, 3, 4, 6, 8, 0, 0, 1}));
    assert((termC / termA) == TTerm<int>(7, {1, 1, 0, 0, 0, 0, 0, 1}));
    assert((termC / termC) == TTerm<int>(1, {}));
}
=======
>>>>>>> 8ac035541fef5b20aff637e8f520e776e43c73c3
