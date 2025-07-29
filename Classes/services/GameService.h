#ifndef __GAME_SERVICE_H__
#define __GAME_SERVICE_H__

#include "../models/CardModel.h"
#include "../models/GameModel.h"
#include <vector>
#include <functional>

/**
 * 游戏服务层 - 处理游戏业务逻辑
 * 特点：
 * - 无状态服务，不持有数据
 * - 处理业务逻辑，不管理数据生命周期
 * - 可以加工数据但不持有数据
 * - 提供静态方法
 */
class GameService {
public:
    /**
     * 执行手牌替换逻辑
     * @param gameModel 游戏数据模型
     * @param cardId 被点击的卡牌ID
     * @return 是否成功执行替换
     */
    static bool executeHandCardReplacement(GameModel* gameModel, int cardId);
    
    /**
     * 执行桌面卡牌匹配逻辑
     * @param gameModel 游戏数据模型
     * @param cardId 被点击的桌面卡牌ID
     * @return 是否成功执行匹配
     */
    static bool executePlayfieldCardMatch(GameModel* gameModel, int cardId);
    
    /**
     * 检查游戏是否结束
     * @param gameModel 游戏数据模型
     * @return 游戏结束状态：0-继续，1-胜利，-1-失败
     */
    static int checkGameEndCondition(const GameModel* gameModel);
    
    /**
     * 验证卡牌匹配规则
     * @param card1 第一张卡牌
     * @param card2 第二张卡牌
     * @return 是否可以匹配
     */
    static bool validateCardMatch(const CardModel& card1, const CardModel& card2);
    
    /**
     * 计算得分
     * @param matchedCard 匹配的卡牌
     * @return 获得的分数
     */
    static int calculateScore(const CardModel& matchedCard);
    
private:
    // 私有构造函数，防止实例化
    GameService() = delete;
    ~GameService() = delete;
    GameService(const GameService&) = delete;
    GameService& operator=(const GameService&) = delete;
};

#endif // __GAME_SERVICE_H__