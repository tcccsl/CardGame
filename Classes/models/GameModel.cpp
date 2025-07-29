#include "GameModel.h"

USING_NS_CC;

// 构造函数
GameModel::GameModel() 
    : currentLevel(1), score(0), isGameOver(false), isGameWon(false) {
}

// 获取顶部手牌
CardModel* GameModel::getTopHandCard() {
    if (handCards.empty()) {
        return nullptr;
    }
    return &handCards.back();
}

// 根据ID查找牌桌卡牌
CardModel* GameModel::findPlayfieldCardById(int cardId) {
    for (auto& card : playfieldCards) {
        if (card.id == cardId) {
            return &card;
        }
    }
    return nullptr;
}

// 从牌桌移除卡牌
bool GameModel::removePlayfieldCard(int cardId) {
    for (auto it = playfieldCards.begin(); it != playfieldCards.end(); ++it) {
        if (it->id == cardId) {
            playfieldCards.erase(it);
            return true;
        }
    }
    return false;
}

// 重置游戏数据
void GameModel::reset() {
    handCards.clear();
    playfieldCards.clear();
    score = 0;
    isGameOver = false;
    isGameWon = false;
}

// 检查胜利条件
bool GameModel::checkWinCondition() const {
    return playfieldCards.empty();
}

// 检查失败条件
bool GameModel::checkLoseCondition() const {
    return handCards.empty() && !playfieldCards.empty();
}