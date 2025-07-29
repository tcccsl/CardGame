#ifndef __CARD_MATCH_SERVICE_H__
#define __CARD_MATCH_SERVICE_H__

#include "../models/CardModel.h"
#include <vector>

/**
 * 卡牌匹配服务 - 专门处理卡牌匹配相关的业务逻辑
 * 特点：
 * - 无状态服务，不持有数据
 * - 专注于卡牌匹配规则和算法
 * - 提供静态方法
 */
class CardMatchService {
public:
    /**
     * 检查两张卡牌是否可以匹配
     * @param card1 第一张卡牌
     * @param card2 第二张卡牌
     * @return 是否可以匹配
     */
    static bool canMatch(const CardModel& card1, const CardModel& card2);
    
    /**
     * 查找所有可以与指定卡牌匹配的卡牌
     * @param targetCard 目标卡牌
     * @param candidateCards 候选卡牌列表
     * @return 可匹配的卡牌ID列表
     */
    static std::vector<int> findMatchableCards(const CardModel& targetCard, 
                                               const std::vector<CardModel>& candidateCards);
    
    /**
     * 检查是否还有可能的匹配
     * @param handCards 手牌列表
     * @param playfieldCards 桌面卡牌列表
     * @return 是否还有可能的匹配
     */
    static bool hasAnyPossibleMatch(const std::vector<CardModel>& handCards,
                                   const std::vector<CardModel>& playfieldCards);
    
    /**
     * 获取匹配难度系数
     * @param card1 第一张卡牌
     * @param card2 第二张卡牌
     * @return 匹配难度系数（用于计分）
     */
    static float getMatchDifficulty(const CardModel& card1, const CardModel& card2);
    
private:
    // 私有构造函数，防止实例化
    CardMatchService() = delete;
    ~CardMatchService() = delete;
    CardMatchService(const CardMatchService&) = delete;
    CardMatchService& operator=(const CardMatchService&) = delete;
    
    /**
     * 计算两张卡牌面值的差值
     * @param card1 第一张卡牌
     * @param card2 第二张卡牌
     * @return 面值差值的绝对值
     */
    static int calculateFaceDifference(const CardModel& card1, const CardModel& card2);
};

#endif // __CARD_MATCH_SERVICE_H__