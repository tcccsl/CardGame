#include "CardView.h"
#include "../utils/GameUtils.h"

USING_NS_CC;

// 卡牌尺寸常量
const float CardView::CARD_WIDTH = 120.0f;
const float CardView::CARD_HEIGHT = 168.0f;

CardView* CardView::create(const CardModel& card) {
    CardView* ret = new (std::nothrow) CardView();
    if (ret && ret->init(card)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool CardView::init(const CardModel& card) {
    if (!Node::init()) {
        return false;
    }
    
    m_cardModel = card;
    m_backgroundSprite = nullptr;
    m_bigNumberSprite = nullptr;
    m_smallNumberSprite = nullptr;
    m_suitSprite = nullptr;
    m_smallSuitSprite = nullptr;
    
    if (card.isFaceUp) {
        createCardDisplay();
    } else {
        createCardBack();
    }
    
    return true;
}

void CardView::updateCard(const CardModel& card) {
    m_cardModel = card;
    
    // 清除现有显示
    this->removeAllChildren();
    
    if (card.isFaceUp) {
        createCardDisplay();
    } else {
        createCardBack();
    }
}

void CardView::createCardDisplay() {
    // 创建卡牌背景
    m_backgroundSprite = Sprite::create("res/card_general.png");
    if (m_backgroundSprite) {
        m_backgroundSprite->setContentSize(Size(CARD_WIDTH, CARD_HEIGHT));
        m_backgroundSprite->setColor(Color3B::WHITE); // 设为白色
        this->addChild(m_backgroundSprite, 0);
    }
    
    // 创建大数字（卡牌中心）
    std::string bigNumberPath = getBigNumberImagePath(m_cardModel);
    m_bigNumberSprite = Sprite::create(bigNumberPath);
    if (m_bigNumberSprite) {
        m_bigNumberSprite->setPosition(Vec2(0, 0)); // 居中位置
        m_bigNumberSprite->setScale(0.6f); // 中心显示的合适缩放
        this->addChild(m_bigNumberSprite, 1);
    }
    
    // 创建花色（左上角）
    std::string suitPath = getSuitImagePath(m_cardModel);
    m_suitSprite = Sprite::create(suitPath);
    if (m_suitSprite) {
        m_suitSprite->setPosition(Vec2(-CARD_WIDTH/2 + 20, CARD_HEIGHT/2 - 30));
        m_suitSprite->setScale(0.6f);
        this->addChild(m_suitSprite, 1);
    }
    
    // 创建小数字（左上角）
    std::string smallNumberPath = getSmallNumberImagePath(m_cardModel);
    m_smallNumberSprite = Sprite::create(smallNumberPath);
    if (m_smallNumberSprite) {
        m_smallNumberSprite->setPosition(Vec2(-CARD_WIDTH/2 + 15, CARD_HEIGHT/2 - 15));
        m_smallNumberSprite->setScale(0.5f);
        this->addChild(m_smallNumberSprite, 1);
    }
    
    // 创建小花色（右下角，旋转）
    m_smallSuitSprite = Sprite::create(suitPath);
    if (m_smallSuitSprite) {
        m_smallSuitSprite->setPosition(Vec2(CARD_WIDTH/2 - 20, -CARD_HEIGHT/2 + 50));
        m_smallSuitSprite->setRotation(180); // 旋转180度
        m_smallSuitSprite->setScale(0.4f);
        this->addChild(m_smallSuitSprite, 1);
    }
}

void CardView::createCardBack() {
    // 创建卡牌背面
    m_backgroundSprite = Sprite::create("res/card_general.png");
    if (m_backgroundSprite) {
        m_backgroundSprite->setContentSize(Size(CARD_WIDTH, CARD_HEIGHT));
        this->addChild(m_backgroundSprite, 0);
    }
}

std::string CardView::getBigNumberImagePath(const CardModel& card) {
    std::string colorPrefix;
    if (card.suit == CST_HEARTS || card.suit == CST_DIAMONDS) {
        colorPrefix = "big_red_";
    } else {
        colorPrefix = "big_black_";
    }
    
    return "res/number/" + colorPrefix + GameUtils::getFaceName(card.face) + ".png";
}

std::string CardView::getSmallNumberImagePath(const CardModel& card) {
    std::string colorPrefix;
    if (card.suit == CST_HEARTS || card.suit == CST_DIAMONDS) {
        colorPrefix = "small_red_";
    } else {
        colorPrefix = "small_black_";
    }
    
    return "res/number/" + colorPrefix + GameUtils::getFaceName(card.face) + ".png";
}

std::string CardView::getSuitImagePath(const CardModel& card) {
    switch (card.suit) {
        case CST_HEARTS:
            return "res/suits/heart.png";
        case CST_DIAMONDS:
            return "res/suits/diamond.png";
        case CST_CLUBS:
            return "res/suits/club.png";
        case CST_SPADES:
            return "res/suits/spade.png";
        default:
            return "res/suits/heart.png";
    }
}