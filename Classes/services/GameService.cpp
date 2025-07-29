#include "GameService.h"
#include "CardMatchService.h"
#include "ScoreService.h"
#include "../utils/GameUtils.h"
#include <algorithm>

// 执行手牌替换逻辑
bool GameService::executeHandCardReplacement(GameModel* gameModel, int cardId) {
    if (!gameModel || gameModel->handCards.empty()) {
        return false;
    }
    
    // 查找被点击的卡牌
    auto it = std::find_if(gameModel->handCards.begin(), gameModel->handCards.end(),
        [cardId](const CardModel& card) { return card.id == cardId; });
    
    if (it != gameModel->handCards.end()) {
        // 将被点击的卡牌移动到顶部位置（向量末尾）
        CardModel clickedCard = *it;
        gameModel->handCards.erase(it);
        gameModel->handCards.push_back(clickedCard);
        return true;
    }
    
    return false;
}

// 执行桌面卡牌匹配逻辑
bool GameService::executePlayfieldCardMatch(GameModel* gameModel, int cardId) {
    if (!gameModel) {
        return false;
    }
    
    // 获取桌面卡牌
    CardModel* playfieldCard = gameModel->findPlayfieldCardById(cardId);
    CardModel* topHandCard = gameModel->getTopHandCard();
    
    if (!playfieldCard || !topHandCard) {
        return false;
    }
    
    // 验证匹配规则
    if (!CardMatchService::canMatch(*playfieldCard, *topHandCard)) {
        return false;
    }
    
    // 执行匹配：用桌面卡牌替换顶部手牌
    if (!gameModel->handCards.empty()) {
        gameModel->handCards.back() = *playfieldCard;
    }
    
    // 移除桌面卡牌
    gameModel->removePlayfieldCard(cardId);
    
    // 增加分数
    gameModel->score += calculateScore(*playfieldCard);
    
    return true;
}

// 检查游戏是否结束
int GameService::checkGameEndCondition(const GameModel* gameModel) {
    if (!gameModel) {
        return 0; // 继续游戏
    }
    
    // 检查胜利条件：所有桌面卡牌都被清除
    if (gameModel->playfieldCards.empty()) {
        return 1; // 胜利
    }
    
    // 检查失败条件：无法进行任何匹配
    if (gameModel->handCards.empty()) {
        return -1; // 失败
    }
    
    const CardModel* topHandCard = &gameModel->handCards.back();
    if (!topHandCard) {
        return -1; // 失败
    }
    
    // 检查是否还有可匹配的桌面卡牌
    if (CardMatchService::hasAnyPossibleMatch(gameModel->handCards, gameModel->playfieldCards)) {
        return 0; // 还可以继续游戏
    }
    
    // 如果没有可匹配的卡牌，检查手牌是否还有其他选择
    if (gameModel->handCards.size() > 1) {
        return 0; // 还可以切换手牌
    }
    
    return -1; // 失败
}

// 验证卡牌匹配规则
bool GameService::validateCardMatch(const CardModel& card1, const CardModel& card2) {
    // 使用CardMatchService中的匹配逻辑
    return CardMatchService::canMatch(card1, card2);
}

// 计算得分
int GameService::calculateScore(const CardModel& matchedCard) {
    // 使用ScoreService计算得分
    return ScoreService::calculateMatchScore(matchedCard);
}