#include "GameUtils.h"
#include <cmath>

USING_NS_CC;

// 静态变量初始化
int GameUtils::s_nextCardId = 1;

// 检查两张卡牌是否可以匹配
bool GameUtils::canMatch(const CardModel& card1, const CardModel& card2) {
    int face1 = static_cast<int>(card1.face);
    int face2 = static_cast<int>(card2.face);
    
    // 牌面值相差1可以匹配
    return std::abs(face1 - face2) == 1;
}

// 获取卡牌名称字符串
std::string GameUtils::getCardName(const CardModel& card) {
    return getFaceName(card.face) + " of " + getSuitName(card.suit);
}

// 获取花色名称
std::string GameUtils::getSuitName(CardSuitType suit) {
    switch (suit) {
        case CST_HEARTS:
            return "Hearts";
        case CST_DIAMONDS:
            return "Diamonds";
        case CST_CLUBS:
            return "Clubs";
        case CST_SPADES:
            return "Spades";
        default:
            return "Unknown";
    }
}

// 获取牌面名称
std::string GameUtils::getFaceName(CardFaceType face) {
    switch (face) {
        case CFT_ACE:
            return "A";
        case CFT_TWO:
            return "2";
        case CFT_THREE:
            return "3";
        case CFT_FOUR:
            return "4";
        case CFT_FIVE:
            return "5";
        case CFT_SIX:
            return "6";
        case CFT_SEVEN:
            return "7";
        case CFT_EIGHT:
            return "8";
        case CFT_NINE:
            return "9";
        case CFT_TEN:
            return "10";
        case CFT_JACK:
            return "J";
        case CFT_QUEEN:
            return "Q";
        case CFT_KING:
            return "K";
        default:
            return "Unknown";
    }
}

// 生成唯一卡牌ID
int GameUtils::generateUniqueCardId() {
    return s_nextCardId++;
}

// 获取卡牌图片资源名称
std::string GameUtils::getCardImageName(const CardModel& card) {
    std::string colorPrefix;
    if (card.suit == CST_HEARTS || card.suit == CST_DIAMONDS) {
        colorPrefix = "big_red_";
    } else {
        colorPrefix = "big_black_";
    }
    
    return "res/number/" + colorPrefix + getFaceName(card.face) + ".png";
}

// 获取卡牌背面图片资源名称
std::string GameUtils::getCardBackImageName() {
    return "res/card_general.png";
}