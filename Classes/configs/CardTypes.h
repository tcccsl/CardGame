#ifndef __CARD_TYPES_H__
#define __CARD_TYPES_H__

/**
 * @file CardTypes.h
 * @brief 卡牌类型定义文件
 * 
 * 定义了游戏中使用的卡牌花色和牌面类型枚举
 * 用于标识和区分不同类型的扑克牌
 * 支持标准52张扑克牌的完整牌组
 */

/**
 * @enum CardSuitType
 * @brief 卡牌花色类型枚举
 * 
 * 定义扑克牌的四种花色类型
 * 用于区分不同花色的卡牌，影响卡牌的显示和匹配规则
 */
enum CardSuitType
{
    CST_NONE = -1,              ///< 无效花色，用于错误处理
    CST_CLUBS,                  ///< 梅花花色
    CST_DIAMONDS,               ///< 方块花色
    CST_HEARTS,                 ///< 红桃花色
    CST_SPADES,                 ///< 黑桃花色
    CST_NUM_CARD_SUIT_TYPES     ///< 花色类型总数，用于遍历和验证
};

/**
 * @enum CardFaceType
 * @brief 卡牌牌面类型枚举
 * 
 * 定义扑克牌的牌面值，从A到K
 * 用于标识卡牌的数值，影响卡牌匹配和游戏逻辑
 */
enum CardFaceType
{
    CFT_NONE = -1,              ///< 无效牌面，用于错误处理
    CFT_ACE,                    ///< A牌
    CFT_TWO,                    ///< 2牌
    CFT_THREE,                  ///< 3牌
    CFT_FOUR,                   ///< 4牌
    CFT_FIVE,                   ///< 5牌
    CFT_SIX,                    ///< 6牌
    CFT_SEVEN,                  ///< 7牌
    CFT_EIGHT,                  ///< 8牌
    CFT_NINE,                   ///< 9牌
    CFT_TEN,                    ///< 10牌
    CFT_JACK,                   ///< J牌
    CFT_QUEEN,                  ///< Q牌
    CFT_KING,                   ///< K牌
    CFT_NUM_CARD_FACE_TYPES     ///< 牌面类型总数，用于遍历和验证
};

#endif // __CARD_TYPES_H__