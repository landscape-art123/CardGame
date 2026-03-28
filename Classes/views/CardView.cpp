#include "views/CardView.h"
using namespace std;

CardView* CardView::create(CardFaceType face, CardSuitType suit)
{
    CardView* ret = new (nothrow) CardView();
    if (ret && ret->init(face, suit))
    {
        ret->autorelease();
        return ret;
    }

    delete ret;
    ret = nullptr;
    return nullptr;
}




bool CardView::init(CardFaceType face, CardSuitType suit)
{
    if (!Node::init())
    {
        return false;
    }

    auto card = Sprite::create("card_general.png");
    if (!card)
    {
        CCLOG("Failed to load card_general.png");
        return false;
    }

    const float kCardScale = 0.68f;
    card->setScale(kCardScale);
    this->addChild(card);

    auto rawSize = card->getContentSize();
    auto scaledSize = Size(rawSize.width * kCardScale, rawSize.height * kCardScale);

    
    auto number = Sprite::create(getNumberFile(face, suit));
    if (number)
    {
        number->setAnchorPoint(Vec2(0.0f, 1.0f));
        number->setScale(0.32f);
        number->setPosition(Vec2(20.0f, rawSize.height - 14.0f));
        card->addChild(number, 2);
    }

    
    auto centerNumber = Sprite::create(getNumberFile(face, suit));
    if (centerNumber)
    {
        centerNumber->setAnchorPoint(Vec2(0.5f, 0.5f));
        centerNumber->setScale(1.0f);
        centerNumber->setPosition(Vec2(rawSize.width * 0.5f, rawSize.height * 0.45f));
        card->addChild(centerNumber, 1);
    }

   
    auto suitSp = Sprite::create(getSuitFile(suit));
    if (suitSp)
    {
        suitSp->setAnchorPoint(Vec2(1.0f, 1.0f));
        suitSp->setScale(1.02f);
        suitSp->setPosition(Vec2(rawSize.width - 16.0f, rawSize.height - 12.0f));
        card->addChild(suitSp, 2);
    }

    this->setContentSize(scaledSize);

    return true;
}





string CardView::getSuitFile(CardSuitType suit)
{
    switch (suit)
    {
    case CST_CLUBS:    return "suits/club.png";
    case CST_DIAMONDS: return "suits/diamond.png";
    case CST_HEARTS:   return "suits/heart.png";
    case CST_SPADES:   return "suits/spade.png";
    default:           return "";
    }
}

string CardView::getNumberFile(CardFaceType face, CardSuitType suit)
{
    bool isRed = (suit == CST_HEARTS || suit == CST_DIAMONDS);
    string prefix = isRed ? "number/big_red_" : "number/big_black_";

    switch (face)
    {
    case CFT_ACE:   return prefix + "A.png";
    case CFT_JACK:  return prefix + "J.png";
    case CFT_QUEEN: return prefix + "Q.png";
    case CFT_KING:  return prefix + "K.png";
    case CFT_TWO:   return prefix + "2.png";
    case CFT_THREE: return prefix + "3.png";
    case CFT_FOUR:  return prefix + "4.png";
    case CFT_FIVE:  return prefix + "5.png";
    case CFT_SIX:   return prefix + "6.png";
    case CFT_SEVEN: return prefix + "7.png";
    case CFT_EIGHT: return prefix + "8.png";
    case CFT_NINE:  return prefix + "9.png";
    case CFT_TEN:   return prefix + "10.png";
    default:        return "";
    }
}