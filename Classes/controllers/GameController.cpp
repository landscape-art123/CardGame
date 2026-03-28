#include "controllers/GameController.h"
#include "services/GameModelFromLevelGenerator.h"
#include "configs/GameLayoutConfig.h"

void GameController::init(GameView* gameView)
{
    _gameView = gameView;
    _undoManager.init();

    initSubControllers();
    bindViewCallbacks();
}

void GameController::initSubControllers()
{
    _playFieldController.init(&_gameModel, _gameView, &_undoManager);
    _stackController.init(&_gameModel, _gameView, &_undoManager);
}

void GameController::bindViewCallbacks()
{
    if (!_gameView)
    {
        return;
    }

    _gameView->setOnPlayfieldCardClick([this](int cardId)
        {
            _playFieldController.handleCardClick(cardId);
        });

    _gameView->setOnHandCardClick([this]()
        {
            _stackController.handleHandCardClick();
        });

    _gameView->setOnUndoClick([this]()
        {
            handleUndo();
        });
}

void GameController::startDemoGame()
{
    _gameModel = GameModelFromLevelGenerator::generateRandomGameModel();

    if (_gameView)
    {
        _gameView->buildFromGameModel(_gameModel);
    }
}

void GameController::handleUndo()
{
    if (!_gameView)
    {
        return;
    }

    UndoModel undo;
    if (!_undoManager.popRecord(undo))
    {
        CCLOG("No undo record");
        return;
    }

   
    _gameModel.topCard.face = undo.oldTopFace;
    _gameModel.topCard.suit = undo.oldTopSuit;
    _gameModel.topCard.position = undo.oldTopPos;
    _gameView->rebuildTopCard(_gameModel.topCard);

  
    if (undo.sourceType == UST_PLAYFIELD)
    {
        _gameView->restorePlayfieldCard(
            undo.movedCardId,
            undo.oldTopPos,
            undo.oldCardPos
        );

        for (auto& model : _gameModel.playfieldCards)
        {
            if (model.cardId == undo.movedCardId)
            {
                model.isRemoved = false;
                break;
            }
        }
    }
    else if (undo.sourceType == UST_HAND)
    {
        _gameView->restoreHandCard(
            undo.oldTopPos,
            undo.oldCardPos
        );
    }
}