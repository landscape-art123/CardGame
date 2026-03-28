#pragma once
#include "cocos2d.h"

USING_NS_CC;

// 只存放界面布局与动画相关静态常量  不放业务逻辑



namespace GameLayoutConfig
{
    // 场景尺寸
    static const float kSceneWidth = 1080.0f;
    static const float kPlayfieldHeight = 1500.0f;
    static const float kStackHeight = 580.0f;

    // 底部区域
    static const Vec2 kTopCardPos(620.0f, 255.0f);
    static const Vec2 kLeftStackCardPos(190.0f, 255.0f);
    static const Vec2 kHandCardPos(315.0f, 255.0f);
    static const Vec2 kUndoButtonPos(915.0f, 245.0f);

    // 主牌区 6 张牌
    static const Vec2 kPlayfieldCardPos0(250.0f, 1030.0f);
    static const Vec2 kPlayfieldCardPos1(300.0f, 835.0f);
    static const Vec2 kPlayfieldCardPos2(350.0f, 640.0f);
    static const Vec2 kPlayfieldCardPos3(850.0f, 1030.0f);
    static const Vec2 kPlayfieldCardPos4(800.0f, 835.0f);
    static const Vec2 kPlayfieldCardPos5(750.0f, 640.0f);

    // 动画
    static const float kMoveDuration = 0.25f;
}