#include "ScoreService.h"
#include "CardMatchService.h"
#include <algorithm>
#include <cmath>

// 得分配置常量定义
const int ScoreService::BASE_MATCH_SCORE = 10;
const int ScoreService::SPECIAL_CARD_BONUS = 5;
const int ScoreService::SAME_SUIT_BONUS = 3;
const int ScoreService::PERFECT_GAME_MULTIPLIER = 2;
const float ScoreService::COMBO_MULTIPLIER = 1.5f;
const float ScoreService::TIME_BONUS_FACTOR = 0.1f;

// 计算单次匹配得分
int ScoreService::calculateMatchScore(const CardModel& matchedCard, float difficulty) {
    int baseScore = getCardBaseScore(matchedCard);
    int specialBonus = calculateSpecialCardBonus(matchedCard);
    
    // 应用难度系数
    int totalScore = static_cast<int>((baseScore + specialBonus) * difficulty);
    
    return std::max(1, totalScore); // 确保至少得1分
}

// 计算连击奖励
int ScoreService::calculateComboBonus(int comboCount) {
    if (comboCount <= 1) {
        return 0; // 单次匹配无连击奖励
    }
    
    // 连击奖励递增：2连击=2分，3连击=5分，4连击=9分...
    int bonus = static_cast<int>(std::pow(comboCount - 1, 2) * COMBO_MULTIPLIER);
    return std::min(bonus, 50); // 限制最大连击奖励
}

// 计算时间奖励
int ScoreService::calculateTimeBonus(float timeElapsed, float baseTime) {
    if (timeElapsed >= baseTime) {
        return 0; // 超时无奖励
    }
    
    float timeSaved = baseTime - timeElapsed;
    int bonus = static_cast<int>(timeSaved * TIME_BONUS_FACTOR);
    
    return std::max(0, std::min(bonus, 20)); // 限制时间奖励范围
}

// 计算完成游戏的总奖励
int ScoreService::calculateCompletionBonus(int remainingCards, float totalTime, bool perfectMatch) {
    int completionBonus = 0;
    
    // 剩余卡牌越少奖励越高
    if (remainingCards == 0) {
        completionBonus += 100; // 完全清空奖励
    } else if (remainingCards <= 2) {
        completionBonus += 50; // 接近完成奖励
    } else if (remainingCards <= 5) {
        completionBonus += 20; // 部分完成奖励
    }
    
    // 完美匹配奖励
    if (perfectMatch) {
        completionBonus *= PERFECT_GAME_MULTIPLIER;
    }
    
    // 快速完成奖励
    if (totalTime < 60.0f) { // 1分钟内完成
        completionBonus += 30;
    } else if (totalTime < 120.0f) { // 2分钟内完成
        completionBonus += 15;
    }
    
    return completionBonus;
}

// 获取卡牌基础分值
int ScoreService::getCardBaseScore(const CardModel& card) {
    return BASE_MATCH_SCORE;
}

// 计算特殊卡牌奖励
int ScoreService::calculateSpecialCardBonus(const CardModel& card) {
    if (isSpecialCard(card)) {
        return SPECIAL_CARD_BONUS;
    }
    return 0;
}

// 计算花色匹配奖励
int ScoreService::calculateSuitMatchBonus(const CardModel& card1, const CardModel& card2) {
    if (card1.suit == card2.suit) {
        return SAME_SUIT_BONUS;
    }
    return 0;
}

// 判断是否为特殊卡牌
bool ScoreService::isSpecialCard(const CardModel& card) {
    return (card.face == CFT_ACE || 
            card.face == CFT_KING || 
            card.face == CFT_QUEEN || 
            card.face == CFT_JACK);
}