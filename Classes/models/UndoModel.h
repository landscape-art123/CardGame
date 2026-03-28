#pragma once
#include "cocos2d.h"
#include "models/CardModel.h"
USING_NS_CC;



enum UndoSourceType
{
    UST_NONE = 0,
    UST_PLAYFIELD,
    UST_HAND
};

struct UndoModel
{
    int movedCardId = -1;
    UndoSourceType sourceType = UST_NONE;

    CardFaceType oldTopFace = CFT_NONE;
    CardSuitType oldTopSuit = CST_NONE;

    Vec2 oldTopPos = Vec2::ZERO;
    Vec2 oldCardPos = Vec2::ZERO;
};