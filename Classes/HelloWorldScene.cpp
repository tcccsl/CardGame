/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "scenes/GameScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// 当文件不存在时打印有用的错误信息而不是段错误
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// 在"init"中需要初始化实例
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. 首先调用父类初始化
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. 添加带"X"图像的菜单项，点击退出程序
    //    可以修改它

    // 添加"关闭"图标退出程序，这是一个自动释放对象
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // 创建菜单，这是一个自动释放对象
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. 在下面添加你的代码...

    // 添加显示"Hello World"的标签
    // 创建并初始化标签

    auto label = Label::createWithTTF("Card Elimination Game", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // 将标签定位在屏幕中心
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // 将标签作为子节点添加到此层
        this->addChild(label, 1);
    }
    
    // 创建开始游戏按钮
    auto startGameButton = ui::Button::create();
    startGameButton->setTitleText("Start Game");
    startGameButton->setTitleFontSize(48);
    startGameButton->setTitleColor(Color3B::WHITE);
    startGameButton->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y - 200));
    
    // 为按钮添加渐变效果背景
    auto buttonBg = LayerColor::create(Color4B(50, 150, 250, 255), 400, 120);
    buttonBg->setPosition(Vec2(visibleSize.width/2 + origin.x - 200, visibleSize.height/2 + origin.y - 260));
    this->addChild(buttonBg, 2);
    
    // 为按钮添加边框
    auto buttonBorder = LayerColor::create(Color4B(255, 255, 255, 255), 404, 124);
    buttonBorder->setPosition(Vec2(visibleSize.width/2 + origin.x - 202, visibleSize.height/2 + origin.y - 262));
    this->addChild(buttonBorder, 1);
    
    startGameButton->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto gameScene = GameScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, gameScene));
        }
    });
    this->addChild(startGameButton, 3);
    
    // 添加游戏标题
    auto titleLabel = Label::createWithSystemFont("Card Elimination Game", "Arial", 72);
    titleLabel->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 200));
    titleLabel->setColor(Color3B::WHITE);
    this->addChild(titleLabel, 3);
    
    // 添加副标题
    auto subtitleLabel = Label::createWithSystemFont("Match adjacent cards to clear the field!", "Arial", 36);
    subtitleLabel->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 100));
    subtitleLabel->setColor(Color3B(200, 200, 200));
    this->addChild(subtitleLabel, 3);

    // 添加"HelloWorld"启动画面
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // 将精灵定位在屏幕中心
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // 将精灵作为子节点添加到此层
        this->addChild(sprite, 0);
    }
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    // 关闭cocos2d-x游戏场景并退出应用程序
    Director::getInstance()->end();

    /* 要导航回原生iOS屏幕（如果存在）而不退出应用程序，不要使用上面的Director::getInstance()->end()，而是触发在RootViewController.mm中创建的自定义事件，如下所示 */

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
