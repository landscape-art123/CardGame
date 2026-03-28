#include "controllers/StackController.h"
#include "configs/GameLayoutConfig.h"

void StackController::init(GameModel* gameModel, GameView* gameView, UndoManager* undoManager)
{
    _gameModel = gameModel;
    _gameView = gameView;
    _undoManager = undoManager;
}

void StackController::handleHandCardClick()
{
    if (!_gameModel || !_gameView || !_undoManager)
    {
        return;
    }

    if (!_gameView->isHandCardVisible())
    {
        return;
    }

    UndoModel undo;
    undo.movedCardId = _gameModel->handCard.cardId;
    undo.sourceType = UST_HAND;
    undo.oldTopFace = _gameModel->topCard.face;
    undo.oldTopSuit = _gameModel->topCard.suit;
    undo.oldTopPos = _gameModel->topCard.position;
    undo.oldCardPos = _gameModel->handCard.position;
    _undoManager->pushRecord(undo);

    const CardModel matchedCard = _gameModel->handCard;

    _gameView->playHandCardToTop([this, matchedCard]()
        {
            _gameView->hideHandCard();

            _gameModel->topCard = matchedCard;
            _gameModel->topCard.position = GameLayoutConfig::kTopCardPos;
            _gameView->rebuildTopCard(_gameModel->topCard);
        });
}