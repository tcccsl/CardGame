#ifndef __UNDO_MANAGER_H__
#define __UNDO_MANAGER_H__

#include "cocos2d.h"
#include "../models/GameModel.h"
#include <stack>
#include <memory>

/**
 * @struct GameStateSnapshot
 * @brief 游戏状态快照结构体
 * 
 * 用于保存游戏在某个时刻的完整状态
 * 包括手牌、牌桌卡牌和分数等关键信息
 * 支持游戏状态的保存和恢复功能
 */
struct GameStateSnapshot {
    std::vector<CardModel> handCards;        ///< 快照时的手牌状态
    std::vector<CardModel> playfieldCards;   ///< 快照时的牌桌卡牌状态
    int score;                               ///< 快照时的游戏分数
    
    /**
     * @brief 构造函数
     * 
     * @param model 要创建快照的游戏模型
     */
    GameStateSnapshot(const GameModel& model)
        : handCards(model.handCards)
        , playfieldCards(model.playfieldCards)
        , score(model.score) {
    }
};

/**
 * @class UndoManager
 * @brief 撤销管理器类
 * 
 * 负责管理游戏的撤销功能
 * 通过保存游戏状态快照，支持玩家撤销之前的操作
 * 使用栈结构存储历史状态，支持多步撤销
 * 
 * 职责：
 * - 保存游戏状态的历史快照
 * - 提供撤销到之前状态的功能
 * - 管理撤销历史的存储和清理
 * - 控制最大撤销步数限制
 * 
 * 使用场景：
 * - 玩家点击撤销按钮时恢复游戏状态
 * - 在关键操作前自动保存状态
 * - 游戏重置时清理撤销历史
 */
class UndoManager {
public:
    /**
     * @brief 构造函数
     * 
     * 初始化撤销管理器，设置默认参数
     */
    UndoManager();
    
    /**
     * @brief 析构函数
     * 
     * 清理撤销管理器占用的资源
     */
    ~UndoManager();
    
    /**
     * @brief 初始化撤销管理器
     * 
     * @param gameModel 要管理的游戏模型指针
     * @return 初始化成功返回true，失败返回false
     */
    bool init(GameModel* gameModel);
    
    /**
     * @brief 保存当前游戏状态
     * 
     * 将当前游戏状态创建快照并压入撤销栈
     */
    void saveState();
    
    /**
     * @brief 撤销到上一个状态
     * 
     * @return 撤销成功返回true，无可撤销状态返回false
     */
    bool undo();
    
    /**
     * @brief 检查是否可以撤销
     * 
     * @return 有可撤销状态返回true，否则返回false
     */
    bool canUndo() const;
    
    /**
     * @brief 清空撤销历史
     * 
     * 清除所有保存的状态快照
     */
    void clear();
    
    /**
     * @brief 设置最大撤销步数
     * 
     * @param maxSteps 允许的最大撤销步数
     */
    void setMaxUndoSteps(int maxSteps);
    
private:
    GameModel* m_gameModel;                                    ///< 游戏数据模型指针
    std::stack<std::shared_ptr<GameStateSnapshot>> m_undoStack; ///< 撤销状态栈，存储历史快照
    int m_maxUndoSteps;                                        ///< 最大撤销步数限制
    
    /**
     * @brief 应用游戏状态快照
     * 
     * @param snapshot 要应用的状态快照
     */
    void applySnapshot(const GameStateSnapshot& snapshot);
};

#endif // __UNDO_MANAGER_H__