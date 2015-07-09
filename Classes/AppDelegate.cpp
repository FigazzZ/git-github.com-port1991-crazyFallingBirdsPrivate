#include "AppDelegate.h"
#include "MainMenu.h"
#include "Constants.h"

using namespace cocos2d;

static Size designResolutionSize = Size(2048, 1536);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }

    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::FIXED_WIDTH);
    
    std::vector <std::string> searchPaths;
    
    float screenRelation = glview->getFrameSize().width / glview->getFrameSize().height;
    if (screenRelation < 0.75)
    {
        log("iPhone");
        searchPaths.push_back("iPhoneBacks");
    }
    else
    {
        log("iPad");
        searchPaths.push_back("iPadBacks");
    }

    cocos2d::FileUtils::getInstance()->setSearchPaths(searchPaths);
    
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    register_all_packages();

    this->loadSheets();
    singleton->loginGameCenter();
    
    // create a scene. it's an autorelease object
    auto scene = MainMenu::create();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    singleton->loginGameCenter();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::loadSheets()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_objects.plist", "game_objects.png");
}
