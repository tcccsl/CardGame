#ifndef __CARD_MODEL_H__
#define __CARD_MODEL_H__

#include "cocos2d.h"
#include "../configs/CardTypes.h"

/**
 * @class CardModel
 * @brief 卡牌数据模型类
 * 
 * 负责存储和管理单张卡牌的所有属性信息
 * 包括卡牌的ID、牌面值、花色、朝向状态和位置等
 * 用于游戏逻辑中的卡牌数据表示和传递
 * 
 * 使用场景：
 * - 游戏中所有卡牌对象的数据载体
 * - 卡牌状态的持久化和序列化
 * - 卡牌匹配和移动逻辑的数据基础
 */
class CardModel {
public:
    int id;                    ///< 卡牌唯一标识符，用于区分不同卡牌实例
    CardFaceType face;         ///< 卡牌牌面值，决定卡牌的数值
    CardSuitType suit;         ///< 卡牌花色，决定卡牌的花色类型
    bool isFaceUp;            ///< 卡牌朝向状态，true为正面朝上，false为背面朝上
    cocos2d::Vec2 position;   ///< 卡牌在游戏场景中的位置坐标
    
    /**
     * @brief 默认构造函数
     * 
     * 创建一个空的卡牌模型，所有属性使用默认值初始化
     */
    CardModel();
    
    /**
     * @brief 带参数的构造函数
     * 
     * @param cardId 卡牌ID
     * @param cardFace 卡牌牌面值
     * @param cardSuit 卡牌花色
     * @param faceUp 是否正面朝上，默认为true
     */
    CardModel(int cardId, CardFaceType cardFace, CardSuitType cardSuit, bool faceUp = true);
    
    /**
     * @brief 拷贝构造函数
     * 
     * @param other 要拷贝的卡牌模型对象
     */
    CardModel(const CardModel& other);
    
    /**
     * @brief 赋值运算符重载
     * 
     * @param other 要赋值的卡牌模型对象
     * @return 返回当前对象的引用
     */
    CardModel& operator=(const CardModel& other);
    
    /**
     * @brief 析构函数
     * 
     * 清理卡牌模型占用的资源
     */
    ~CardModel();
};

#endif // __CARD_MODEL_H__