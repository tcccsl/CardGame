#include "CardMatchService.h"
#include "../utils/GameUtils.h"
#include <algorithm>
#include <cmath>

// 检查两张卡牌是否可以匹配
bool CardMatchService::canMatch(const CardModel& card1, const CardModel& card2) {
    // 使用现有的GameUtils匹配逻辑
    return GameUtils::canMatch(card1, card2);
}

// 查找所有可以与指定卡牌匹配的卡牌
std::vector<int> CardMatchService::findMatchableCards(const CardModel& targetCard, 
                                                     const std::vector<CardModel>& candidateCards) {
    std::vector<int> matchableCardIds;
    
    for (const auto& candidate : candidateCards) {
        if (canMatch(targetCard, candidate)) {
            matchableCardIds.push_back(candidate.id);
        }
    }
    
    return matchableCardIds;
}

// 检查是否还有可能的匹配
bool CardMatchService::hasAnyPossibleMatch(const std::vector<CardModel>& handCards,
                                          const std::vector<CardModel>& playfieldCards) {
    // 检查每张手牌是否能与任何桌面卡牌匹配
    for (const auto& handCard : handCards) {
        for (const auto& playfieldCard : playfieldCards) {
            if (canMatch(handCard, playfieldCard)) {
                return true;
            }
        }
    }
    
    return false;
}

// 获取匹配难度系数
float CardMatchService::getMatchDifficulty(const CardModel& card1, const CardModel& card2) {
    int faceDiff = calculateFaceDifference(card1, card2);
    
    // 基础难度系数
    float baseDifficulty = 1.0f;
    
    // 面值差越小，难度越高（需要更精确的判断）
    if (faceDiff == 1) {
        baseDifficulty = 1.5f; // 相邻值匹配难度较高
    }
    
    // 特殊牌匹配难度调整
    bool hasSpecialCard = (card1.face == CFT_ACE || card1.face == CFT_KING || 
                          card1.face == CFT_QUEEN || card1.face == CFT_JACK ||
                          card2.face == CFT_ACE || card2.face == CFT_KING || 
                          card2.face == CFT_QUEEN || card2.face == CFT_JACK);
    
    if (hasSpecialCard) {
        baseDifficulty *= 1.2f; // 特殊牌增加难度
    }
    
    return baseDifficulty;
}

// 计算两张卡牌面值的差值
int CardMatchService::calculateFaceDifference(const CardModel& card1, const CardModel& card2) {
    return std::abs(static_cast<int>(card1.face) - static_cast<int>(card2.face));
}