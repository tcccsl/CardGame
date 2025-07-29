#ifndef __GAME_MODEL_H__
#define __GAME_MODEL_H__

#include "cocos2d.h"
#include "CardModel.h"
#include <vector>

/**
 * @struct GameModel
 * @brief 游戏数据模型结构体
 * 
 * 负责管理整个游戏的核心数据状态
 * 包括手牌、牌桌卡牌、关卡信息、分数和游戏状态等
 * 作为游戏逻辑的数据中心，为控制器和视图提供数据支持
 * 
 * 职责：
 * - 维护游戏中所有卡牌的状态和位置
 * - 管理游戏进度和分数统计
 * - 提供游戏状态查询和修改接口
 * - 处理游戏胜负条件判断
 * 
 * 使用场景：
 * - 游戏控制器获取和更新游戏数据
 * - 游戏视图根据模型数据更新显示
 * - 游戏状态的保存和恢复
 */
struct GameModel {
    std::vector<CardModel> handCards;      ///< 手牌列表，存储玩家当前持有的卡牌
    std::vector<CardModel> playfieldCards; ///< 牌桌卡牌列表，存储场上的所有卡牌
    int currentLevel;                      ///< 当前游戏关卡等级
    int score;                            ///< 当前游戏得分
    bool isGameOver;                      ///< 游戏结束标志，true表示游戏已结束
    bool isGameWon;                       ///< 游戏胜利标志，true表示玩家获胜
    
    /**
     * @brief 构造函数
     * 
     * 初始化游戏模型，设置默认的游戏状态
     */
    GameModel();
    
    /**
     * @brief 获取顶部手牌
     * 
     * @return 返回手牌堆顶的卡牌指针，如果手牌为空则返回nullptr
     */
    CardModel* getTopHandCard();
    
    /**
     * @brief 根据ID查找牌桌卡牌
     * 
     * @param cardId 要查找的卡牌ID
     * @return 返回找到的卡牌指针，如果未找到则返回nullptr
     */
    CardModel* findPlayfieldCardById(int cardId);
    
    /**
     * @brief 移除牌桌卡牌
     * 
     * @param cardId 要移除的卡牌ID
     * @return 移除成功返回true，失败返回false
     */
    bool removePlayfieldCard(int cardId);
    
    /**
     * @brief 重置游戏状态
     * 
     * 将游戏模型恢复到初始状态，清空所有卡牌和重置分数
     */
    void reset();
    
    /**
     * @brief 检查游戏胜利条件
     * 
     * @return 满足胜利条件返回true，否则返回false
     */
    bool checkWinCondition() const;
    
    /**
     * @brief 检查游戏失败条件
     * 
     * @return 满足失败条件返回true，否则返回false
     */
    bool checkLoseCondition() const;
};

#endif // __GAME_MODEL_H__