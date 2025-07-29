#ifndef __SCORE_SERVICE_H__
#define __SCORE_SERVICE_H__

#include "../models/CardModel.h"
#include <vector>

/**
 * 得分服务 - 处理游戏得分计算逻辑
 * 特点：
 * - 无状态服务，不持有数据
 * - 专注于得分规则的计算
 * - 提供静态方法
 */
class ScoreService {
public:
    /**
     * 计算单次匹配得分
     * @param matchedCard 被匹配的卡牌
     * @param difficulty 匹配难度系数
     * @return 得分
     */
    static int calculateMatchScore(const CardModel& matchedCard, float difficulty = 1.0f);
    
    /**
     * 计算连击奖励
     * @param comboCount 连击次数
     * @return 奖励分数
     */
    static int calculateComboBonus(int comboCount);
    
    /**
     * 计算时间奖励
     * @param timeElapsed 已用时间（秒）
     * @param baseTime 基准时间（秒）
     * @return 时间奖励分数
     */
    static int calculateTimeBonus(float timeElapsed, float baseTime);
    
    /**
     * 计算完成游戏的总奖励
     * @param remainingCards 剩余卡牌数量
     * @param totalTime 总用时
     * @param perfectMatch 是否完美匹配（无错误）
     * @return 完成奖励分数
     */
    static int calculateCompletionBonus(int remainingCards, float totalTime, bool perfectMatch);
    
    /**
     * 获取卡牌基础分值
     * @param card 卡牌
     * @return 基础分值
     */
    static int getCardBaseScore(const CardModel& card);
    
    /**
     * 计算特殊卡牌奖励
     * @param card 卡牌
     * @return 特殊奖励分数
     */
    static int calculateSpecialCardBonus(const CardModel& card);
    
    /**
     * 计算花色匹配奖励
     * @param card1 第一张卡牌
     * @param card2 第二张卡牌
     * @return 花色奖励分数
     */
    static int calculateSuitMatchBonus(const CardModel& card1, const CardModel& card2);
    
    // 得分配置常量
    static const int BASE_MATCH_SCORE;
    static const int SPECIAL_CARD_BONUS;
    static const int SAME_SUIT_BONUS;
    static const int PERFECT_GAME_MULTIPLIER;
    static const float COMBO_MULTIPLIER;
    static const float TIME_BONUS_FACTOR;
    
private:
    // 私有构造函数，防止实例化
    ScoreService() = delete;
    ~ScoreService() = delete;
    ScoreService(const ScoreService&) = delete;
    ScoreService& operator=(const ScoreService&) = delete;
    
    /**
     * 判断是否为特殊卡牌
     * @param card 卡牌
     * @return 是否为特殊卡牌
     */
    static bool isSpecialCard(const CardModel& card);
};

#endif // __SCORE_SERVICE_H__