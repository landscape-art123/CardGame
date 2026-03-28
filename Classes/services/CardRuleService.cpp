#include "services/CardRuleService.h"
#include <cmath>
using namespace std;

bool CardRuleService::canMatch(CardFaceType a, CardFaceType b)
{
    return abs((int)a - (int)b) == 1;
}