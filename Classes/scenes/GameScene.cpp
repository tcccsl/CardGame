#include "GameScene.h"
#include "HelloWorldScene.h"
#include "../utils/GameUtils.h"
#include "../configs/LevelConfig.h"
#include "../configs/CardTypes.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

// 创建场景
Scene* GameScene::createScene() {
    return GameScene::create();
}

// 初始化
bool GameScene::init() {
    if (!Scene::init()) {
        return false;
    }
    
    // 初始化游戏组件
    if (!initGameComponents()) {
        return false;
    }
    
    // 创建UI
    createUI();
    
    // 创建测试数据
    createTestData();
    
    return true;
}

// 初始化游戏组件
bool GameScene::initGameComponents() {
    // 创建游戏数据模型
    m_gameModel = new (std::nothrow) GameModel();
    if (!m_gameModel) {
        return false;
    }
    
    // 创建游戏视图
    m_gameView = GameView::create();
    if (!m_gameView) {
        return false;
    }
    this->addChild(m_gameView);
    
    // 创建游戏控制器
    m_gameController = new (std::nothrow) GameController();
    if (!m_gameController || !m_gameController->init(m_gameModel, m_gameView)) {
        return false;
    }
    
    // 创建撤销管理器
    m_undoManager = new (std::nothrow) UndoManager();
    if (!m_undoManager || !m_undoManager->init(m_gameModel)) {
        return false;
    }
    
    // 设置控制器的撤销管理器
    m_gameController->setUndoManager(m_undoManager);
    
    // 设置游戏结束回调
    m_gameController->setGameEndCallback([this](bool isWin) {
        onGameEnd(isWin);
    });
    
    // 设置视图回调
    m_gameView->setHandCardClickCallback([this](int cardId) {
        m_gameController->onHandCardClicked(cardId);
    });
    
    m_gameView->setPlayfieldCardClickCallback([this](int cardId) {
        m_gameController->onPlayfieldCardClicked(cardId);
    });
    
    m_gameView->setUndoButtonClickCallback([this]() {
        m_gameController->onUndoButtonClicked();
    });
    
    return true;
}

// 创建测试数据
void GameScene::createTestData() {
    if (!m_gameModel) {
        return;
    }
    
    // 清除现有数据
    m_gameModel->reset();
    
    // 加载关卡配置
    auto levelManager = LevelConfigManager::getInstance();
    if (!levelManager->loadLevel("levels/level1.json")) {
        CCLOG("Failed to load level configuration, using default data");
        createDefaultData();
        return;
    }
    
    const auto& levelConfig = levelManager->getCurrentLevel();
    
    // 从堆叠配置创建手牌
    for (const auto& cardConfig : levelConfig.stack) {
        CardModel card;
        card.id = GameUtils::generateUniqueCardId();
        card.face = static_cast<CardFaceType>(cardConfig.cardFace);
        card.suit = static_cast<CardSuitType>(cardConfig.cardSuit);
        card.isFaceUp = true;
        m_gameModel->handCards.push_back(card);
    }
    
    // 从牌桌配置创建牌桌卡牌
    for (const auto& cardConfig : levelConfig.playfield) {
        CardModel card;
        card.id = GameUtils::generateUniqueCardId();
        card.face = static_cast<CardFaceType>(cardConfig.cardFace);
        card.suit = static_cast<CardSuitType>(cardConfig.cardSuit);
        card.isFaceUp = true;
        card.position = cardConfig.position;
        m_gameModel->playfieldCards.push_back(card);
    }
    
    // 刷新视图
    m_gameController->refreshView();
}

// 创建默认数据（回退）
void GameScene::createDefaultData() {
    // 创建手牌
    for (int i = 0; i < 5; i++) {
        CardModel card;
        card.id = GameUtils::generateUniqueCardId();
        card.face = static_cast<CardFaceType>(i + 1);
        card.suit = CST_HEARTS;
        card.isFaceUp = true;
        m_gameModel->handCards.push_back(card);
    }
    
    // 创建牌桌卡牌
    for (int i = 0; i < 3; i++) {
        CardModel card;
        card.id = GameUtils::generateUniqueCardId();
        card.face = static_cast<CardFaceType>(i + 2);
        card.suit = CST_SPADES;
        card.isFaceUp = true;
        card.position = Vec2(i * 120, 0);
        m_gameModel->playfieldCards.push_back(card);
    }
}

// 游戏结束回调
void GameScene::onGameEnd(bool isWin) {
    if (m_gameView) {
        m_gameView->showGameEndDialog(isWin);
    }
}

// 重启游戏
void GameScene::restartGame() {
    if (m_gameView) {
        m_gameView->hideGameEndDialog();
    }
    
    if (m_undoManager) {
        m_undoManager->clear();
    }
    
    createTestData();
}

// 创建UI元素
void GameScene::createUI() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // 返回按钮背景
    auto backBg = LayerColor::create(Color4B(50, 150, 50, 200), 200, 60);
    backBg->setPosition(Vec2(origin.x + 50, origin.y + visibleSize.height - 100));
    this->addChild(backBg);
    
    // 返回菜单按钮
    auto backButton = ui::Button::create();
    backButton->setTitleText("Back");
    backButton->setTitleFontSize(32);
    backButton->setTitleColor(Color3B::WHITE);
    backButton->setPosition(Vec2(origin.x + 150, origin.y + visibleSize.height - 70));
    backButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            onBackToMenuClicked(sender);
        }
    });
    this->addChild(backButton);
    
    // 重启按钮背景
    auto restartBg = LayerColor::create(Color4B(150, 50, 50, 200), 150, 60);
    restartBg->setPosition(Vec2(origin.x + visibleSize.width - 200, origin.y + visibleSize.height - 100));
    this->addChild(restartBg);
    
    // 重启按钮
    auto restartButton = ui::Button::create();
    restartButton->setTitleText("Restart");
    restartButton->setTitleFontSize(32);
    restartButton->setTitleColor(Color3B::WHITE);
    restartButton->setPosition(Vec2(origin.x + visibleSize.width - 125, origin.y + visibleSize.height - 70));
    restartButton->addTouchEventListener([this](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            onRestartClicked(sender);
        }
    });
    this->addChild(restartButton);
}

// 返回菜单按钮回调
void GameScene::onBackToMenuClicked(Ref* sender) {
    auto scene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
}

// 重启按钮回调
void GameScene::onRestartClicked(Ref* sender) {
    restartGame();
}