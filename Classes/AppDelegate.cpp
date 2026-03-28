#include "AppDelegate.h"
#include "scenes/GameScene.h"

USING_NS_CC;


// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1


#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

namespace
{
    const Size kDesignResolutionSize(1080.0f, 2080.0f);
    const Size kSmallResolutionSize(480.0f, 320.0f);
    const Size kMediumResolutionSize(1024.0f, 768.0f);
    const Size kLargeResolutionSize(2048.0f, 1536.0f);
}

// if you want to use the package manager to install more packages,
// don't modify or remove this function
static int register_all_packages()
{
    return 0; // flag for packages manager
}

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // red, green, blue, alpha, depth, stencil, multisamplesCount
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    if (!glview)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || \
    (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)   || \
    (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)

        glview = GLViewImpl::createWithRect(
            "CardGame",
            Rect(0, 0, kDesignResolutionSize.width, kDesignResolutionSize.height),
            0.5f
        );
#else
        glview = GLViewImpl::create("CardGame");
#endif
        director->setOpenGLView(glview);
    }

    glview->setDesignResolutionSize(
        kDesignResolutionSize.width,
        kDesignResolutionSize.height,
        ResolutionPolicy::FIXED_WIDTH
    );

    // close FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60.0f);

    const Size frameSize = glview->getFrameSize();

    if (frameSize.height > kMediumResolutionSize.height)
    {
        director->setContentScaleFactor(
            MIN(kLargeResolutionSize.height / kDesignResolutionSize.height,
                kLargeResolutionSize.width / kDesignResolutionSize.width)
        );
    }
    else if (frameSize.height > kSmallResolutionSize.height)
    {
        director->setContentScaleFactor(
            MIN(kMediumResolutionSize.height / kDesignResolutionSize.height,
                kMediumResolutionSize.width / kDesignResolutionSize.width)
        );
    }
    else
    {
        director->setContentScaleFactor(
            MIN(kSmallResolutionSize.height / kDesignResolutionSize.height,
                kSmallResolutionSize.width / kDesignResolutionSize.width)
        );
    }

    register_all_packages();

    auto scene = GameScene::createScene();
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive.
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}