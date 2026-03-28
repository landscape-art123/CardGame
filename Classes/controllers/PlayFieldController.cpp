#include "controllers/PlayFieldController.h"
#include "configs/GameLayoutConfig.h"
#include "services/CardRuleService.h"

void PlayFieldController::init(GameModel* gameModel, GameView* gameView, UndoManager* undoManager)
{
    _gameModel = gameModel;
    _gameView = gameView;
    _undoManager = undoManager;
}

void PlayFieldController::handleCardClick(int cardId)
{
    if (!_gameModel || !_gameView || !_undoManager)
    {
        return;
    }

    for (auto& card : _gameModel->playfieldCards)
    {
        if (card.cardId != cardId)
        {
            continue;
        }

        if (card.isRemoved)
        {
            CCLOG("cardId=%d already removed", cardId);
            return;
        }

        const bool canMatch = CardRuleService::canMatch(card.face, _gameModel->topCard.face);
        if (!canMatch)
        {
            return;
        }

        UndoModel undo;
        undo.movedCardId = card.cardId;
        undo.sourceType = UST_PLAYFIELD;
        undo.oldTopFace = _gameModel->topCard.face;
        undo.oldTopSuit = _gameModel->topCard.suit;
        undo.oldTopPos = _gameModel->topCard.position;
        undo.oldCardPos = card.position;
        _undoManager->pushRecord(undo);

        const CardModel matchedCard = card;

        _gameView->playPlayfieldCardToTop(card.cardId, [this, cardId, matchedCard]()
            {
                _gameView->hidePlayfieldCard(cardId);

                for (auto& model : _gameModel->playfieldCards)
                {
                    if (model.cardId == cardId)
                    {
                        model.isRemoved = true;
                        break;
                    }
                }

                _gameModel->topCard = matchedCard;
                _gameModel->topCard.position = GameLayoutConfig::kTopCardPos;
                _gameView->rebuildTopCard(_gameModel->topCard);
            });

        return;
    }
}