#pragma once
#include "managers/UndoManager.h"
#include "models/GameModel.h"
#include "views/GameView.h"

USING_NS_CC;
using namespace std;

// 负责桌面牌点击匹配逻辑,判断是否可匹配、记录 Undo、更新 Model、通知 View 播放动画

class PlayFieldController
{
public:
    void init(GameModel* gameModel, GameView* gameView, UndoManager* undoManager);
    void handleCardClick(int cardId);

private:
    GameModel* _gameModel = nullptr;
    GameView* _gameView = nullptr;
    UndoManager* _undoManager = nullptr;
};