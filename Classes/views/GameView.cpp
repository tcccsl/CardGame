#include "GameView.h"
#include "../utils/GameUtils.h"
#include "ui/CocosGUI.h"
#include "CardView.h"
#include "../services/AnimationService.h"

USING_NS_CC;

// 创建游戏视图
GameView* GameView::create() {
    GameView* ret = new (std::nothrow) GameView();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

// 初始化
bool GameView::init() {
    if (!Node::init()) {
        return false;
    }
    
    createUI();
    
    return true;
}

// 更新手牌显示
void GameView::updateHandCards(const std::vector<CardModel>& handCards) {
    if (!m_handCardContainer) {
        return;
    }
    
    // 清除现有手牌
    m_handCardContainer->removeAllChildren();
    
    if (handCards.empty()) {
        return;
    }
    
    // 以堆叠布局显示卡牌，顶部卡牌分离
    float cardOffset = 25.0f; // 堆叠卡牌间的偏移
    float topCardGap = 60.0f; // 顶部卡牌与堆叠的间隙
    
    // 计算所有卡牌所需的总宽度
    float stackWidth = (handCards.size() - 1) * cardOffset;
    float totalWidth = stackWidth + topCardGap + CardView::CARD_WIDTH;
    float startX = -totalWidth / 2.0f;
    
    for (size_t i = 0; i < handCards.size(); ++i) {
        const CardModel& card = handCards[i];
        auto cardNode = createCardSprite(card);
        if (cardNode) {
            float posX = 0;
            float posY = 0;
            
            if (i == handCards.size() - 1) {
                // 顶部卡牌（向量中的最后一张）- 用间隙分离
                posX = startX + stackWidth + topCardGap;
            } else {
                // 其他卡牌 - 从左侧堆叠
                posX = startX + (float)i * cardOffset;
            }
            
            cardNode->setPosition(Vec2(posX, posY));
            m_handCardContainer->addChild(cardNode);
            
            // 添加点击事件
            auto button = ui::Button::create();
            button->setContentSize(Size(CardView::CARD_WIDTH, CardView::CARD_HEIGHT));
            button->setPosition(Vec2(posX, posY));
            button->setTag(card.id);
            // 设置完全透明背景以确保触摸事件工作
            button->loadTextureNormal("res/card_general.png");
            button->setOpacity(0); // 设为完全透明
            button->addTouchEventListener(CC_CALLBACK_2(GameView::onHandCardTouched, this));
            m_handCardContainer->addChild(button);
            CCLOG("Created hand card button with tag: %d at position (%f, %f)", card.id, posX, posY);
        }
    }
}

// 更新牌桌卡牌显示
void GameView::updatePlayfieldCards(const std::vector<CardModel>& playfieldCards) {
    if (!m_playfieldContainer) {
        return;
    }
    
    // 清除现有卡牌
    m_playfieldContainer->removeAllChildren();
    
    // 显示所有牌桌卡牌
    for (const auto& card : playfieldCards) {
        auto cardNode = createCardSprite(card);
        if (cardNode) {
            cardNode->setPosition(card.position);
            m_playfieldContainer->addChild(cardNode);
            
            
            auto button = ui::Button::create();
            button->setContentSize(Size(CardView::CARD_WIDTH, CardView::CARD_HEIGHT));
            button->setPosition(card.position);
            button->setTag(card.id);
            
            button->loadTextureNormal("res/card_general.png");
            button->setOpacity(0); 
            button->addTouchEventListener(CC_CALLBACK_2(GameView::onPlayfieldCardTouched, this));
            m_playfieldContainer->addChild(button);
            CCLOG("Created playfield card button with tag: %d at position (%f, %f)", card.id, card.position.x, card.position.y);
        }
    }
}

// 设置手牌点击回调
void GameView::setHandCardClickCallback(const std::function<void(int)>& callback) {
    m_handCardClickCallback = callback;
}

// 设置牌桌卡牌点击回调
void GameView::setPlayfieldCardClickCallback(const std::function<void(int)>& callback) {
    m_playfieldCardClickCallback = callback;
}

// 设置撤销按钮点击回调
void GameView::setUndoButtonClickCallback(const std::function<void()>& callback) {
    m_undoButtonClickCallback = callback;
}

// 显示游戏结束对话框
void GameView::showGameEndDialog(bool isWin) {
    if (m_gameEndDialog) {
        m_gameEndDialog->setVisible(true);
        
        // 更新对话框内容
        auto label = m_gameEndDialog->getChildByName<Label*>("result_label");
        if (label) {
            label->setString(isWin ? "You Win!" : "Game Over");
        }
    }
}

// 隐藏游戏结束对话框
void GameView::hideGameEndDialog() {
    if (m_gameEndDialog) {
        m_gameEndDialog->setVisible(false);
    }
}

// 创建UI元素
void GameView::createUI() {
    createHandCardArea();
    createPlayfieldArea();
    createControlButtons();
    createScoreDisplay();
    createGameInstructions();
    createGameEndDialog();
}

// 创建游戏说明
void GameView::createGameInstructions() {
    // 在牌桌右下角创建半透明背景
    auto background = LayerColor::create(Color4B(0, 0, 0, 128), 280, 180);
    background->setPosition(Vec2(800, 50)); // 右下角
    m_playfieldContainer->addChild(background);
    
    // 创建说明文本
    auto instructionLabel = Label::createWithTTF(
        "Game Rules:\n1. Click two cards to select\n2. Selected cards to match\n3. Adjacent values can match\n4. Clear all cards to win!",
        "fonts/arial.ttf", 14);
    instructionLabel->setPosition(Vec2(940, 140)); // 在背景中居中
    instructionLabel->setColor(Color3B::WHITE);
    m_playfieldContainer->addChild(instructionLabel);
}

// 创建手牌区域（堆牌区 1080*580）
void GameView::createHandCardArea() {
    // 手牌区域背景
    auto handBg = LayerColor::create(Color4B(0, 100, 200, 100), 1080, 580);
    handBg->setPosition(Vec2(0, 0));
    this->addChild(handBg);
    
    // 手牌区域标签
    auto handLabel = Label::createWithSystemFont("Deck", "Arial", 36);
    handLabel->setPosition(Vec2(540, 520));
    handLabel->setColor(Color3B::WHITE);
    this->addChild(handLabel);
    
    m_handCardContainer = Node::create();
    m_handCardContainer->setPosition(Vec2(540, 290));
    this->addChild(m_handCardContainer);
}

// 创建牌桌区域（主牌区 1080*1500）
void GameView::createPlayfieldArea() {
    // 牌桌区域背景
    auto playfieldBg = LayerColor::create(Color4B(100, 200, 100, 100), 1080, 1500);
    playfieldBg->setPosition(Vec2(0, 580));
    this->addChild(playfieldBg);
    
    // 牌桌区域标签
    auto playfieldLabel = Label::createWithSystemFont("Field", "Arial", 36);
    playfieldLabel->setPosition(Vec2(540, 1950));
    playfieldLabel->setColor(Color3B::WHITE);
    this->addChild(playfieldLabel);
    
    m_playfieldContainer = Node::create();
    m_playfieldContainer->setPosition(Vec2(0, 580));
    this->addChild(m_playfieldContainer);
}

// 创建控制按钮
void GameView::createControlButtons() {
    m_undoButton = ui::Button::create();
    m_undoButton->setTitleText("Undo");
    m_undoButton->setTitleFontName("Arial");
    m_undoButton->setTitleFontSize(32);
    m_undoButton->setPosition(Vec2(200, 200));
    
    // 为撤销按钮添加背景
    auto undoBg = LayerColor::create(Color4B(128, 128, 128, 255), 150, 60);
    undoBg->setPosition(Vec2(125, 170));
    this->addChild(undoBg);
    
    m_undoButton->setTitleColor(Color3B::WHITE);
    m_undoButton->addTouchEventListener(CC_CALLBACK_2(GameView::onUndoButtonClicked, this));
    this->addChild(m_undoButton);
}

// 创建分数显示
void GameView::createScoreDisplay() {
    m_scoreLabel = Label::createWithSystemFont("Score: 0", "Arial", 36);
    m_scoreLabel->setPosition(Vec2(800, 100));
    m_scoreLabel->setColor(Color3B::WHITE);
    this->addChild(m_scoreLabel);
}

// 创建游戏结束对话框
void GameView::createGameEndDialog() {
    m_gameEndDialog = Node::create();
    m_gameEndDialog->setVisible(false);
    
    // 背景
    auto bg = LayerColor::create(Color4B(0, 0, 0, 128));
    m_gameEndDialog->addChild(bg);
    
    // 结果标签
    auto resultLabel = Label::createWithTTF("Game Over", "fonts/arial.ttf", 48);
    resultLabel->setName("result_label");
    resultLabel->setPosition(Vec2(400, 300));
    m_gameEndDialog->addChild(resultLabel);
    
    this->addChild(m_gameEndDialog);
}

// 创建卡牌精灵
Node* GameView::createCardSprite(const CardModel& card) {
    // 使用CardView创建完整的卡牌显示
    auto cardView = CardView::create(card);
    if (cardView) {
        // 直接返回CardView
        return cardView;
    }
    
    // 如果CardView创建失败，回退到原来的方式
    std::string imageName;
    if (card.isFaceUp) {
        imageName = GameUtils::getCardImageName(card);
    } else {
        imageName = GameUtils::getCardBackImageName();
    }
    
    auto sprite = Sprite::create(imageName);
    return sprite;
}

// 手牌触摸事件处理器
void GameView::onHandCardTouched(Ref* sender, ui::Widget::TouchEventType type) {
    CCLOG("Hand card touched, type: %d", (int)type);
    if (type == ui::Widget::TouchEventType::BEGAN) {
        CCLOG("Touch began on hand card");
    }
    if (type == ui::Widget::TouchEventType::ENDED) {
        auto button = dynamic_cast<ui::Button*>(sender);
        if (button) {
            CCLOG("Button found, tag: %d", button->getTag());
            if (m_handCardClickCallback) {
                CCLOG("Calling hand card callback with cardId: %d", button->getTag());
                m_handCardClickCallback(button->getTag());
            } else {
                CCLOG("Hand card callback is null!");
            }
        } else {
            CCLOG("Button cast failed!");
        }
    }
}

// 牌桌卡牌触摸事件处理器
void GameView::onPlayfieldCardTouched(Ref* sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
        auto button = dynamic_cast<ui::Button*>(sender);
        if (button && m_playfieldCardClickCallback) {
            m_playfieldCardClickCallback(button->getTag());
        }
    }
}

// 撤销按钮点击事件处理器
void GameView::onUndoButtonClicked(Ref* sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
        if (m_undoButtonClickCallback) {
            m_undoButtonClickCallback();
        }
    }
}

// 手牌移动到顶部位置的动画
void GameView::animateHandCardToTop(int cardId) {
    if (!m_handCardContainer) {
        return;
    }
    
    // 通过标签查找卡牌节点
    Node* cardNode = nullptr;
    for (auto child : m_handCardContainer->getChildren()) {
        if (child->getTag() == cardId) {
            cardNode = child;
            break;
        }
    }
    
    if (cardNode) {
        // 计算顶部卡牌位置（与updateHandCards中相同）
        Vec2 currentPos = cardNode->getPosition();
        Vec2 topPos = Vec2(0, 0); // 当前布局中的顶部卡牌位置
        
        // 使用AnimationService创建动画
        float duration = AnimationService::calculateHandCardMoveToTopDuration(cardId, currentPos, topPos);
        auto moveAction = AnimationService::createCardMoveAnimation(cardNode, topPos, duration);
        
        if (moveAction) {
            cardNode->runAction(moveAction);
        }
    }
}

// 牌桌卡牌移动到手牌区域的动画
void GameView::animatePlayfieldCardToHand(int cardId) {
    if (!m_playfieldContainer || !m_handCardContainer) {
        return;
    }
    
    // 通过标签查找牌桌卡牌节点
    Node* cardNode = nullptr;
    for (auto child : m_playfieldContainer->getChildren()) {
        if (child->getTag() == cardId) {
            cardNode = child;
            break;
        }
    }
    
    if (cardNode) {
        // 计算目标位置（手牌区域的顶部卡牌位置）
        Vec2 currentPos = cardNode->getPosition();
        Vec2 handAreaPos = m_handCardContainer->getPosition();
        Vec2 targetPos = Vec2(handAreaPos.x, handAreaPos.y - 580); // 调整容器偏移
        
        // Use AnimationService to create animation
        float duration = AnimationService::calculatePlayfieldToHandDuration(cardId, currentPos, targetPos);
        auto moveAction = AnimationService::createCardMoveAnimation(cardNode, targetPos, duration);
        
        // 动画后移除卡牌
        auto removeAction = CallFunc::create([cardNode]() {
            cardNode->removeFromParent();
        });
        
        if (moveAction) {
            auto finiteAction = dynamic_cast<FiniteTimeAction*>(moveAction);
            if (finiteAction) {
                auto sequence = Sequence::create(finiteAction, removeAction, nullptr);
                cardNode->runAction(sequence);
            }
        }
    }
}