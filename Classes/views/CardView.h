#ifndef __CARD_VIEW_H__
#define __CARD_VIEW_H__

#include "cocos2d.h"
#include "../models/CardModel.h"

/**
 * @class CardView
 * @brief 卡牌视图类
 * 
 * 负责单张卡牌的可视化显示
 * 继承自cocos2d::Node，提供完整的卡牌渲染功能
 * 支持正面和背面的显示切换
 * 
 * 职责：
 * - 渲染卡牌的视觉外观
 * - 管理卡牌的各个视觉元素（数字、花色、背景等）
 * - 提供卡牌状态更新接口
 * - 维护卡牌的尺寸规范
 * 
 * 使用场景：
 * - 在游戏界面中显示单张卡牌
 * - 卡牌状态变化时更新显示
 * - 作为卡牌动画的载体
 */
class CardView : public cocos2d::Node {
public:
    /**
     * @brief 创建卡牌视图实例
     * 
     * @param card 卡牌数据模型
     * @return 返回创建的CardView对象指针，失败返回nullptr
     */
    static CardView* create(const CardModel& card);
    
    /**
     * @brief 初始化卡牌视图
     * 
     * @param card 卡牌数据模型
     * @return 初始化成功返回true，失败返回false
     */
    virtual bool init(const CardModel& card);
    
    /**
     * @brief 更新卡牌显示
     * 
     * @param card 新的卡牌数据模型
     */
    void updateCard(const CardModel& card);
    
    /**
     * @brief 获取卡牌数据模型
     * 
     * @return 返回当前卡牌的数据模型引用
     */
    const CardModel& getCardModel() const { return m_cardModel; }
    
    static const float CARD_WIDTH;   ///< 卡牌标准宽度
    static const float CARD_HEIGHT;  ///< 卡牌标准高度
    
private:
    CardModel m_cardModel;                  ///< 卡牌数据模型
    cocos2d::Sprite* m_backgroundSprite;    ///< 卡牌背景精灵
    cocos2d::Sprite* m_bigNumberSprite;     ///< 大数字精灵
    cocos2d::Sprite* m_smallNumberSprite;   ///< 小数字精灵
    cocos2d::Sprite* m_suitSprite;          ///< 花色精灵
    cocos2d::Sprite* m_smallSuitSprite;     ///< 小花色精灵
    
    /**
     * @brief 创建卡牌正面显示
     * 
     * 创建并布局卡牌正面的所有视觉元素
     */
    void createCardDisplay();
    
    /**
     * @brief 创建卡牌背面显示
     * 
     * 创建卡牌背面的视觉元素
     */
    void createCardBack();
    
    /**
     * @brief 获取大数字图片路径
     * 
     * @param card 卡牌数据模型
     * @return 大数字图片的资源路径
     */
    std::string getBigNumberImagePath(const CardModel& card);
    
    /**
     * @brief 获取小数字图片路径
     * 
     * @param card 卡牌数据模型
     * @return 小数字图片的资源路径
     */
    std::string getSmallNumberImagePath(const CardModel& card);
    
    /**
     * @brief 获取花色图片路径
     * 
     * @param card 卡牌数据模型
     * @return 花色图片的资源路径
     */
    std::string getSuitImagePath(const CardModel& card);
};

#endif // __CARD_VIEW_H__