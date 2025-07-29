#ifndef __GAME_VIEW_H__
#define __GAME_VIEW_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../models/CardModel.h"
#include <vector>
#include <functional>

/**
 * @class GameView
 * @brief 游戏视图类
 * 
 * 负责游戏界面的显示和用户交互
 * 继承自cocos2d::Node，实现游戏的可视化界面
 * 包括卡牌显示、用户界面元素和动画效果
 * 
 * 职责：
 * - 渲染游戏中的所有可视元素
 * - 处理用户的触摸和点击事件
 * - 显示游戏状态和信息
 * - 播放卡牌移动和游戏动画
 * - 管理游戏界面布局和样式
 * 
 * 使用场景：
 * - 作为游戏场景的主要视图组件
 * - 响应控制器的视图更新请求
 * - 向控制器传递用户交互事件
 */
class GameView : public cocos2d::Node {
public:
    /**
     * @brief 创建游戏视图实例
     * 
     * @return 返回创建的GameView对象指针，失败返回nullptr
     */
    static GameView* create();
    
    /**
     * @brief 初始化游戏视图
     * 
     * @return 初始化成功返回true，失败返回false
     */
    virtual bool init() override;
    
    /**
     * @brief 更新手牌显示
     * 
     * @param handCards 手牌卡牌列表
     */
    void updateHandCards(const std::vector<CardModel>& handCards);
    
    /**
     * @brief 更新牌桌卡牌显示
     * 
     * @param playfieldCards 牌桌卡牌列表
     */
    void updatePlayfieldCards(const std::vector<CardModel>& playfieldCards);
    
    /**
     * @brief 设置手牌点击回调函数
     * 
     * @param callback 手牌点击时的回调函数，参数为卡牌ID
     */
    void setHandCardClickCallback(const std::function<void(int)>& callback);
    
    /**
     * @brief 设置牌桌卡牌点击回调函数
     * 
     * @param callback 牌桌卡牌点击时的回调函数，参数为卡牌ID
     */
    void setPlayfieldCardClickCallback(const std::function<void(int)>& callback);
    
    /**
     * @brief 设置撤销按钮点击回调函数
     * 
     * @param callback 撤销按钮点击时的回调函数
     */
    void setUndoButtonClickCallback(const std::function<void()>& callback);
    
    /**
     * @brief 显示游戏结束对话框
     * 
     * @param isWin 是否获胜，true为胜利，false为失败
     */
    void showGameEndDialog(bool isWin);
    
    /**
     * @brief 隐藏游戏结束对话框
     */
    void hideGameEndDialog();
    
    /**
     * @brief 播放手牌移动到顶部的动画
     * 
     * @param cardId 要移动的卡牌ID
     */
    void animateHandCardToTop(int cardId);
    
    /**
     * @brief 播放牌桌卡牌移动到手牌区的动画
     * 
     * @param cardId 要移动的卡牌ID
     */
    void animatePlayfieldCardToHand(int cardId);
    
private:
    cocos2d::Node* m_handCardContainer;                    ///< 手牌容器节点，用于管理手牌显示
    cocos2d::Node* m_playfieldContainer;                  ///< 牌桌容器节点，用于管理牌桌卡牌显示
    cocos2d::ui::Button* m_undoButton;                    ///< 撤销按钮，用于撤销上一步操作
    cocos2d::Label* m_scoreLabel;                         ///< 分数标签，显示当前游戏分数
    cocos2d::Node* m_gameEndDialog;                       ///< 游戏结束对话框节点
    
    std::function<void(int)> m_handCardClickCallback;     ///< 手牌点击回调函数
    std::function<void(int)> m_playfieldCardClickCallback; ///< 牌桌卡牌点击回调函数
    std::function<void()> m_undoButtonClickCallback;      ///< 撤销按钮点击回调函数
    
    /**
     * @brief 创建用户界面元素
     * 
     * 初始化所有UI组件，包括卡牌区域、按钮和标签等
     */
    void createUI();
    
    /**
     * @brief 创建手牌区域
     * 
     * 设置手牌显示区域的背景和布局
     */
    void createHandCardArea();
    
    /**
     * @brief 创建牌桌区域
     * 
     * 设置牌桌显示区域的背景和布局
     */
    void createPlayfieldArea();
    
    /**
     * @brief 创建控制按钮
     * 
     * 创建撤销等游戏控制按钮
     */
    void createControlButtons();
    
    /**
     * @brief 创建分数显示
     * 
     * 创建显示游戏分数的标签
     */
    void createScoreDisplay();
    
    /**
     * @brief 创建游戏说明
     * 
     * 创建显示游戏规则和操作说明的界面元素
     */
    void createGameInstructions();
    
    /**
     * @brief 创建游戏结束对话框
     * 
     * 创建显示游戏结果的对话框界面
     */
    void createGameEndDialog();
    
    /**
     * @brief 创建卡牌精灵
     * 
     * @param card 卡牌模型数据
     * @return 返回创建的卡牌节点指针
     */
    cocos2d::Node* createCardSprite(const CardModel& card);
    
    /**
     * @brief 手牌触摸事件处理器
     * 
     * @param sender 事件发送者
     * @param type 触摸事件类型
     */
    void onHandCardTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    
    /**
     * @brief 牌桌卡牌触摸事件处理器
     * 
     * @param sender 事件发送者
     * @param type 触摸事件类型
     */
    void onPlayfieldCardTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    
    /**
     * @brief 撤销按钮点击事件处理器
     * 
     * @param sender 事件发送者
     * @param type 触摸事件类型
     */
    void onUndoButtonClicked(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
};

#endif // __GAME_VIEW_H__