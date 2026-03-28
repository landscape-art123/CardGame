#include "views/GameView.h"
#include "configs/GameLayoutConfig.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;


bool GameView::init()
{
    if (!Node::init())
    {
        return false;
    }

    createBackground();
    return true;
}

void GameView::buildFromGameModel(const GameModel& gameModel)
{
    if (_topCardNode)
    {
        _topCardNode->removeFromParent();
        _topCardNode = nullptr;
    }

    if (_handCardNode)
    {
        _handCardNode->removeFromParent();
        _handCardNode = nullptr;
    }

    if (_leftStackCardNode)
    {
        _leftStackCardNode->removeFromParent();
        _leftStackCardNode = nullptr;
    }

    if (_undoTouchArea)
    {
        _undoTouchArea->removeFromParent();
        _undoTouchArea = nullptr;
    }

    clearPlayfieldNodes();

    createTopCardNode(gameModel.topCard);
    createPlayfieldNodes(gameModel.playfieldCards);
    createStackNodes(gameModel);
    createUndoButton();
}

void GameView::setOnPlayfieldCardClick(const function<void(int)>& callback)
{
    _onPlayfieldCardClick = callback;
}

void GameView::setOnHandCardClick(const function<void()>& callback)
{
    _onHandCardClick = callback;
}

void GameView::setOnUndoClick(const function<void()>& callback)
{
    _onUndoClick = callback;
}

void GameView::createBackground()
{
    if (!_playfieldArea)
    {
        _playfieldArea = LayerColor::create(
            Color4B(177, 128, 72, 255),
            GameLayoutConfig::kSceneWidth,
            GameLayoutConfig::kPlayfieldHeight
        );
        _playfieldArea->setAnchorPoint(Vec2::ZERO);
        _playfieldArea->setPosition(Vec2(0.0f, GameLayoutConfig::kStackHeight));
        this->addChild(_playfieldArea, 0);
    }

    if (!_stackArea)
    {
        _stackArea = LayerColor::create(
            Color4B(160, 38, 168, 255),
            GameLayoutConfig::kSceneWidth,
            GameLayoutConfig::kStackHeight
        );
        _stackArea->setAnchorPoint(Vec2::ZERO);
        _stackArea->setPosition(Vec2::ZERO);
        this->addChild(_stackArea, 0);
    }
}

void GameView::createTopCardNode(const CardModel& topCard)
{
    _topCardNode = CardView::create(topCard.face, topCard.suit);
    if (!_topCardNode)
    {
        return;
    }

    _topCardNode->setPosition(topCard.position);
    _stackArea->addChild(_topCardNode, 5);
}

void GameView::clearPlayfieldNodes()
{
    for (auto& pair : _playfieldCardNodes)
    {
        if (pair.second)
        {
            pair.second->removeFromParent();
        }
    }
    _playfieldCardNodes.clear();
}

void GameView::createPlayfieldNodes(const vector<CardModel>& playfieldCards)
{
    for (const auto& card : playfieldCards)
    {
        auto node = CardView::create(card.face, card.suit);
        if (!node)
        {
            continue;
        }

        node->setPosition(card.position);
        node->setVisible(!card.isRemoved);
        _playfieldArea->addChild(node);
        _playfieldCardNodes[card.cardId] = node;

        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);

        listener->onTouchBegan = [this, node, card](Touch* touch, Event* event)
            {
                if (isTouchInsideCard(node, touch))
                {
                    if (_onPlayfieldCardClick)
                    {
                        _onPlayfieldCardClick(card.cardId);
                    }
                    return true;
                }
                return false;
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, node);
    }
}

void GameView::createStackNodes(const GameModel& gameModel)
{
    _leftStackCardNode = CardView::create(
        gameModel.leftStackCard.face,
        gameModel.leftStackCard.suit
    );
    if (_leftStackCardNode)
    {
        _leftStackCardNode->setPosition(gameModel.leftStackCard.position);
        _stackArea->addChild(_leftStackCardNode, 3);
    }

    _handCardNode = CardView::create(
        gameModel.handCard.face,
        gameModel.handCard.suit
    );
    if (_handCardNode)
    {
        _handCardNode->setPosition(gameModel.handCard.position);
        _stackArea->addChild(_handCardNode, 4);

        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);

        listener->onTouchBegan = [this](Touch* touch, Event* event)
            {
                if (isTouchInsideCard(_handCardNode, touch))
                {
                    if (_onHandCardClick)
                    {
                        _onHandCardClick();
                    }
                    return true;
                }

                return false;
            };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _handCardNode);
    }
}

void GameView::createUndoButton()
{
    const Vec2 kUndoTextPos = GameLayoutConfig::kUndoButtonPos;
    const Size kTouchSize(170.0f, 90.0f);

    auto touchArea = Layout::create();
    touchArea->setContentSize(kTouchSize);
    touchArea->setAnchorPoint(Vec2(0.5f, 0.5f));
    touchArea->setPosition(kUndoTextPos);
    touchArea->setTouchEnabled(true);
    touchArea->setBackGroundColorType(Layout::BackGroundColorType::NONE);
    _stackArea->addChild(touchArea, 10);
    _undoTouchArea = touchArea;

    auto shadow = Label::createWithTTF(u8"»ØÍË", "simhei.ttf", 50);
    if (shadow)
    {
        shadow->setTextColor(Color4B(120, 60, 140, 180));
        shadow->setPosition(Vec2(kTouchSize.width * 0.5f + 2.0f, kTouchSize.height * 0.5f - 2.0f));
        touchArea->addChild(shadow, 1);
    }

    auto label = Label::createWithTTF(u8"»ØÍË", "simhei.ttf", 50);
    if (label)
    {
        label->setTextColor(Color4B::WHITE);
        label->enableOutline(Color4B(210, 170, 230, 160), 1);
        label->setPosition(Vec2(kTouchSize.width * 0.5f, kTouchSize.height * 0.5f));
        touchArea->addChild(label, 2);
    }

    touchArea->addTouchEventListener([this, label, shadow](Ref*, Widget::TouchEventType type)
        {
            switch (type)
            {
            case Widget::TouchEventType::BEGAN:
                if (label)  label->setScale(0.96f);
                if (shadow) shadow->setScale(0.96f);
                break;

            case Widget::TouchEventType::CANCELED:
                if (label)  label->setScale(1.0f);
                if (shadow) shadow->setScale(1.0f);
                break;

            case Widget::TouchEventType::ENDED:
                if (label)  label->setScale(1.0f);
                if (shadow) shadow->setScale(1.0f);
                if (_onUndoClick)
                {
                    _onUndoClick();
                }
                break;

            default:
                break;
            }
        });
}

bool GameView::isTouchInsideCard(CardView* node, Touch* touch) const
{
    if (!node || !touch || !node->isVisible())
    {
        return false;
    }

    Vec2 localPos = node->convertToNodeSpace(touch->getLocation());
    Size size = node->getContentSize();
    Rect rect(-size.width * 0.5f, -size.height * 0.5f, size.width, size.height);

    return rect.containsPoint(localPos);
}

void GameView::rebuildTopCard(const CardModel& topCard)
{
    if (_topCardNode)
    {
        _topCardNode->removeFromParent();
        _topCardNode = nullptr;
    }

    _topCardNode = CardView::create(topCard.face, topCard.suit);
    if (!_topCardNode)
    {
        return;
    }

    _topCardNode->setPosition(topCard.position);
    _stackArea->addChild(_topCardNode, 5);
}

Vec2 GameView::getTopCardWorldPosition() const
{
    if (!_topCardNode)
    {
        return Vec2::ZERO;
    }
    return _stackArea->convertToWorldSpace(_topCardNode->getPosition());
}

bool GameView::isHandCardVisible() const
{
    return _handCardNode && _handCardNode->isVisible();
}

void GameView::playPlayfieldCardToTop(int cardId, const function<void()>& onFinish)
{
    auto it = _playfieldCardNodes.find(cardId);
    if (it == _playfieldCardNodes.end() || !it->second)
    {
        return;
    }

    auto node = it->second;
    Vec2 targetWorldPos = getTopCardWorldPosition();
    Vec2 targetLocalPos = _playfieldArea->convertToNodeSpace(targetWorldPos);

    auto move = MoveTo::create(GameLayoutConfig::kMoveDuration, targetLocalPos);

    if (onFinish)
    {
        node->runAction(Sequence::create(move, CallFunc::create(onFinish), nullptr));
    }
    else
    {
        node->runAction(move);
    }
}

void GameView::playHandCardToTop(const function<void()>& onFinish)
{
    if (!_handCardNode)
    {
        return;
    }

    Vec2 targetPos = _stackArea->convertToNodeSpace(getTopCardWorldPosition());
    auto move = MoveTo::create(GameLayoutConfig::kMoveDuration, targetPos);

    if (onFinish)
    {
        _handCardNode->runAction(Sequence::create(move, CallFunc::create(onFinish), nullptr));
    }
    else
    {
        _handCardNode->runAction(move);
    }
}

void GameView::hidePlayfieldCard(int cardId)
{
    auto it = _playfieldCardNodes.find(cardId);
    if (it != _playfieldCardNodes.end() && it->second)
    {
        it->second->setVisible(false);
    }
}

void GameView::hideHandCard()
{
    if (_handCardNode)
    {
        _handCardNode->setVisible(false);
    }
}

void GameView::restorePlayfieldCard(int cardId, const Vec2& oldTopPos, const Vec2& oldCardPos)
{
    auto it = _playfieldCardNodes.find(cardId);
    if (it == _playfieldCardNodes.end() || !it->second)
    {
        return;
    }

    auto node = it->second;

    Vec2 startWorld = _stackArea->convertToWorldSpace(oldTopPos);
    Vec2 startLocal = _playfieldArea->convertToNodeSpace(startWorld);

    node->setVisible(true);
    node->setPosition(startLocal);
    node->runAction(MoveTo::create(GameLayoutConfig::kMoveDuration, oldCardPos));
}

void GameView::restoreHandCard(const Vec2& oldTopPos, const Vec2& oldCardPos)
{
    if (!_handCardNode)
    {
        return;
    }

    _handCardNode->setVisible(true);
    _handCardNode->setPosition(oldTopPos);
    _handCardNode->runAction(MoveTo::create(GameLayoutConfig::kMoveDuration, oldCardPos));
}