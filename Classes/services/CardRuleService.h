#pragma once
#include "models/CardModel.h"
USING_NS_CC;

// ！无状态规则服务，负责判断两张牌是否满足匹配条件

class CardRuleService
{
public:
    static bool canMatch(CardFaceType a, CardFaceType b);
};