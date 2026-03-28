#pragma once
#include "managers/UndoManager.h"
#include "models/GameModel.h"
#include "views/GameView.h"

USING_NS_CC;
using namespace std;

// 负责手牌区点击逻辑,记录 Undo、播放手牌到顶部牌动画、更新顶部牌

class StackController
{
public:
    void init(GameModel* gameModel, GameView* gameView, UndoManager* undoManager);
    void handleHandCardClick();

private:
    GameModel* _gameModel = nullptr;
    GameView* _gameView = nullptr;
    UndoManager* _undoManager = nullptr;
};