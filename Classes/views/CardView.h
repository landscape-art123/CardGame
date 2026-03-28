#pragma once
#include "cocos2d.h"
#include "models/CardModel.h"
using namespace std;
USING_NS_CC;

// 只负责一张牌的显示，不处理业务逻辑,继承自 Node

class CardView : public Node
{
public:
    static CardView* create(CardFaceType face, CardSuitType suit);

    bool init(CardFaceType face, CardSuitType suit);

private:
    string getNumberFile(CardFaceType face, CardSuitType suit);
    string getSuitFile(CardSuitType suit);
};