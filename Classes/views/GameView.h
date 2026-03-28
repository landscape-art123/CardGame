#pragma once
#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/CardView.h"

#include <functional>
#include <unordered_map>
#include <vector>

USING_NS_CC;
using namespace std;

// GameView：只负责游戏界面的创建、展示、输入监听和动画表现

class GameView : public Node
{
public:
    CREATE_FUNC(GameView);

    virtual bool init() override;

    void buildFromGameModel(const GameModel& gameModel);

    void setOnPlayfieldCardClick(const function<void(int)>& callback);
    void setOnHandCardClick(const function<void()>& callback);
    void setOnUndoClick(const function<void()>& callback);

    void rebuildTopCard(const CardModel& topCard);

    Vec2 getTopCardWorldPosition() const;
    bool isHandCardVisible() const;

    void playPlayfieldCardToTop(int cardId, const function<void()>& onFinish);
    void playHandCardToTop(const function<void()>& onFinish);

    void hidePlayfieldCard(int cardId);
    void hideHandCard();

    void restorePlayfieldCard(int cardId, const Vec2& oldTopPos, const Vec2& oldCardPos);
    void restoreHandCard(const Vec2& oldTopPos, const Vec2& oldCardPos);

private:
    void createBackground();
    void createTopCardNode(const CardModel& topCard);
    void createPlayfieldNodes(const vector<CardModel>& playfieldCards);
    void createStackNodes(const GameModel& gameModel);
    void createUndoButton();

    void clearPlayfieldNodes();
    bool isTouchInsideCard(CardView* node, Touch* touch) const;

private:
    LayerColor* _playfieldArea = nullptr;
    LayerColor* _stackArea = nullptr;

    CardView* _topCardNode = nullptr;
    CardView* _handCardNode = nullptr;
    CardView* _leftStackCardNode = nullptr;
    Node* _undoTouchArea = nullptr;

    unordered_map<int, CardView*> _playfieldCardNodes;

    function<void(int)> _onPlayfieldCardClick;
    function<void()> _onHandCardClick;
    function<void()> _onUndoClick;
};