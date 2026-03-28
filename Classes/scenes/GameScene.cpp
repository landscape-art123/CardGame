#include "scenes/GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    _gameView = GameView::create();
    if (!_gameView)
    {
        return false;
    }
    this->addChild(_gameView);

    _gameController.init(_gameView);
    _gameController.startDemoGame();

    return true;
}