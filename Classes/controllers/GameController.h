#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "cocos2d.h"
#include "../models/GameModel.h"
#include <functional>

// 前向声明
class GameView;
class UndoManager;

/**
 * @class GameController
 * @brief 游戏控制器类
 * 
 * 负责协调游戏模型和视图之间的交互
 * 处理用户输入事件，更新游戏状态，控制游戏流程
 * 实现MVC架构中的控制器角色
 * 
 * 职责：
 * - 处理用户的卡牌点击事件
 * - 管理游戏逻辑和状态转换
 * - 协调模型数据更新和视图刷新
 * - 控制游戏的开始、重置和结束
 * - 管理撤销功能和游戏回调
 * 
 * 使用场景：
 * - 作为游戏场景的核心控制组件
 * - 连接用户界面事件和游戏逻辑
 * - 管理游戏状态和流程控制
 */
class GameController {
public:
    /**
     * @brief 构造函数
     * 
     * 初始化游戏控制器，设置默认状态
     */
    GameController();
    
    /**
     * @brief 析构函数
     * 
     * 清理控制器占用的资源
     */
    ~GameController();
    
    /**
     * @brief 初始化控制器
     * 
     * @param model 游戏数据模型指针
     * @param view 游戏视图指针
     * @return 初始化成功返回true，失败返回false
     */
    bool init(GameModel* model, GameView* view);
    
    /**
     * @brief 处理手牌点击事件
     * 
     * @param cardId 被点击的手牌ID
     */
    void onHandCardClicked(int cardId);
    
    /**
     * @brief 处理牌桌卡牌点击事件
     * 
     * @param cardId 被点击的牌桌卡牌ID
     */
    void onPlayfieldCardClicked(int cardId);
    
    /**
     * @brief 处理撤销按钮点击事件
     */
    void onUndoButtonClicked();
    
    /**
     * @brief 刷新游戏视图
     * 
     * 根据当前游戏模型状态更新视图显示
     */
    void refreshView();
    
    /**
     * @brief 设置撤销管理器
     * 
     * @param undoManager 撤销管理器指针
     */
    void setUndoManager(UndoManager* undoManager);
    
    /**
     * @brief 设置游戏结束回调函数
     * 
     * @param callback 游戏结束时的回调函数，参数为是否获胜
     */
    void setGameEndCallback(const std::function<void(bool)>& callback);
    
    /**
     * @brief 开始新游戏
     * 
     * 初始化游戏状态，开始新的游戏回合
     */
    void startNewGame();
    
    /**
     * @brief 重置游戏
     * 
     * 将游戏恢复到初始状态
     */
    void resetGame();
    
private:
    GameModel* m_gameModel;                           ///< 游戏数据模型指针
    GameView* m_gameView;                            ///< 游戏视图指针
    UndoManager* m_undoManager;                      ///< 撤销管理器指针
    std::function<void(bool)> m_gameEndCallback;     ///< 游戏结束回调函数
    
    /**
     * @brief 刷新手牌视图
     * 
     * 更新手牌区域的显示
     */
    void refreshHandView();
    
    /**
     * @brief 刷新牌桌视图
     * 
     * 更新牌桌区域的显示
     */
    void refreshPlayfieldView();
    
    /**
     * @brief 检查游戏结束条件
     * 
     * 判断游戏是否结束并触发相应的处理
     */
    void checkGameEnd();
};

#endif // __GAME_CONTROLLER_H__