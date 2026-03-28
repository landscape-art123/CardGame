#pragma once
#include "controllers/PlayFieldController.h"
#include "controllers/StackController.h"
#include "managers/UndoManager.h"
#include "models/GameModel.h"
#include "views/GameView.h"

USING_NS_CC;
using namespace std;

// 主控制器,负责初始化 GameModel / GameView / 子控制器,处理全局 Undo。

class GameController
{
public:
    void init(GameView* gameView);
    void startDemoGame();
    void handleUndo();

private:
    void bindViewCallbacks();
    void initSubControllers();
    void initDemoGameModel();

private:
    GameModel _gameModel;
    GameView* _gameView = nullptr;
    UndoManager _undoManager;

    PlayFieldController _playFieldController;
    StackController _stackController;
};