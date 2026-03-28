#pragma once
#include "models/CardModel.h"
#include <vector>

using namespace std;

// 运行时游戏数据模型，只保存当前局面的动态状态，不处理业务逻辑

struct GameModel
{
    CardModel topCard;
    CardModel handCard;
    CardModel leftStackCard;
    vector<CardModel> playfieldCards;
};