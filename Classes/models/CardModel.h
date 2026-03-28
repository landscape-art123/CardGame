#pragma once
#include"cocos2d.h"
USING_NS_CC;

//！运行时卡牌的数据类型，只存卡牌的基础状态，不处理业务逻辑


enum CardSuitType
{
    CST_NONE = -1,
    CST_CLUBS,
    CST_DIAMONDS,
    CST_HEARTS,
    CST_SPADES,
    CST_NUM_CARD_SUIT_TYPES
};

enum CardFaceType
{
    CFT_NONE = -1,
    CFT_ACE,
    CFT_TWO,
    CFT_THREE,
    CFT_FOUR,
    CFT_FIVE,
    CFT_SIX,
    CFT_SEVEN,
    CFT_EIGHT,
    CFT_NINE,
    CFT_TEN,
    CFT_JACK,
    CFT_QUEEN,
    CFT_KING,
    CFT_NUM_CARD_FACE_TYPES
};

struct CardModel
{
    int cardId = -1;
    CardFaceType face = CFT_NONE;
    CardSuitType suit = CST_NONE;
    Vec2 position = Vec2::ZERO;

    bool isRemoved = false;
    bool isFaceUp = true;
};


