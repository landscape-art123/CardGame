#include "services/GameModelFromLevelGenerator.h"
#include "configs/GameLayoutConfig.h"

#include <random>
#include <ctime>
#include <vector>

using namespace std;

namespace
{
    mt19937& rng()
    {
        static mt19937 gen(static_cast<unsigned int>(time(nullptr)));
        return gen;
    }

    CardSuitType randomSuit()
    {
        uniform_int_distribution<int> dist(0, 3);
        return static_cast<CardSuitType>(dist(rng()));
    }

    CardFaceType randomFace()
    {
        uniform_int_distribution<int> dist(static_cast<int>(CFT_ACE),
            static_cast<int>(CFT_KING));
        return static_cast<CardFaceType>(dist(rng()));
    }

    int faceToValue(CardFaceType face)
    {
        return static_cast<int>(face);
    }

    CardFaceType valueToFace(int value)
    {
        if (value < static_cast<int>(CFT_ACE))
        {
            value = static_cast<int>(CFT_ACE);
        }
        if (value > static_cast<int>(CFT_KING))
        {
            value = static_cast<int>(CFT_KING);
        }
        return static_cast<CardFaceType>(value);
    }

    CardFaceType randomNeighborFace(CardFaceType baseFace)
    {
        const int base = faceToValue(baseFace);
        vector<int> candidates;

        if (base - 1 >= static_cast<int>(CFT_ACE))
        {
            candidates.push_back(base - 1);
        }
        if (base + 1 <= static_cast<int>(CFT_KING))
        {
            candidates.push_back(base + 1);
        }

        if (candidates.empty())
        {
            return randomFace();
        }

        uniform_int_distribution<int> dist(0, static_cast<int>(candidates.size()) - 1);
        return valueToFace(candidates[dist(rng())]);
    }
}

GameModel GameModelFromLevelGenerator::generateRandomGameModel()
{
    GameModel model;

    // 顶部牌
    model.topCard.cardId = 100;
    model.topCard.face = randomFace();
    model.topCard.suit = randomSuit();
    model.topCard.position = GameLayoutConfig::kTopCardPos;
    model.topCard.isFaceUp = true;
    model.topCard.isRemoved = false;

    // 左边牌
    model.leftStackCard.cardId = 200;
    model.leftStackCard.face = randomFace();
    model.leftStackCard.suit = randomSuit();
    model.leftStackCard.position = GameLayoutConfig::kLeftStackCardPos;
    model.leftStackCard.isFaceUp = true;
    model.leftStackCard.isRemoved = false;

    // 手牌
    model.handCard.cardId = 201;
    model.handCard.face = randomFace();
    model.handCard.suit = randomSuit();
    model.handCard.position = GameLayoutConfig::kHandCardPos;
    model.handCard.isFaceUp = true;
    model.handCard.isRemoved = false;

    // 主牌区 6 张
    model.playfieldCards.resize(6);

    model.playfieldCards[0].cardId = 0;
    model.playfieldCards[0].position = GameLayoutConfig::kPlayfieldCardPos0;

    model.playfieldCards[1].cardId = 1;
    model.playfieldCards[1].position = GameLayoutConfig::kPlayfieldCardPos1;

    model.playfieldCards[2].cardId = 2;
    model.playfieldCards[2].position = GameLayoutConfig::kPlayfieldCardPos2;

    model.playfieldCards[3].cardId = 3;
    model.playfieldCards[3].position = GameLayoutConfig::kPlayfieldCardPos3;

    model.playfieldCards[4].cardId = 4;
    model.playfieldCards[4].position = GameLayoutConfig::kPlayfieldCardPos4;

    model.playfieldCards[5].cardId = 5;
    model.playfieldCards[5].position = GameLayoutConfig::kPlayfieldCardPos5;

    // 先全部随机
    for (auto& card : model.playfieldCards)
    {
        card.face = randomFace();
        card.suit = randomSuit();
        card.isRemoved = false;
        card.isFaceUp = true;
    }

    // 保证开局至少一张能匹配顶部牌
    uniform_int_distribution<int> idxDist(0, 5);
    const int guaranteedIndex = idxDist(rng());

    model.playfieldCards[guaranteedIndex].face = randomNeighborFace(model.topCard.face);
    model.playfieldCards[guaranteedIndex].suit = randomSuit();

    return model;
}