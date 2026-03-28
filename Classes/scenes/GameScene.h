#pragma once
#include "controllers/GameController.h"
#include "managers/UndoManager.h"
#include "models/GameModel.h"
#include "views/GameView.h"

USING_NS_CC;
using namespace std;

// 当前项目的主场景

class GameScene : public Scene
{
public:
    static Scene* createScene();
    virtual bool init();

    CREATE_FUNC(GameScene);

private:
    void initDemoGameModel();

    void handlePlayfieldCardClick(int cardId);
    void handleHandCardClick();
    void handleUndoClick();

    void replaceTopCard(const CardModel& newTopCard);
    void replaceTopCardFromHand(const CardModel& newTopCard);

    int faceToDisplayValue(CardFaceType face) const;

private:
    GameView* _gameView = nullptr;

    UndoManager _undoManager;
    GameModel _gameModel;
    GameController _gameController;
};