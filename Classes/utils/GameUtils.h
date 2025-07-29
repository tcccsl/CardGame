#ifndef __GAME_UTILS_H__
#define __GAME_UTILS_H__

#include "cocos2d.h"
#include "../models/CardModel.h"
#include <string>

/**
 * @class GameUtils
 * @brief 游戏工具类
 * 
 * 提供游戏中常用的静态工具方法
 * 包括卡牌匹配判断、名称获取、ID生成和资源路径等功能
 * 作为游戏逻辑的辅助工具集合
 * 
 * 职责：
 * - 提供卡牌匹配规则的判断逻辑
 * - 处理卡牌名称和描述的字符串转换
 * - 生成唯一的卡牌标识符
 * - 管理卡牌图片资源的路径映射
 * 
 * 使用场景：
 * - 游戏逻辑中需要判断卡牌匹配时
 * - 界面显示需要卡牌名称时
 * - 创建新卡牌需要唯一ID时
 * - 加载卡牌图片资源时
 */
class GameUtils {
public:
    /**
     * @brief 检查两张卡牌是否可以匹配
     * 
     * 匹配规则：牌面值相差1
     * @param card1 第一张卡牌
     * @param card2 第二张卡牌
     * @return 可以匹配返回true，否则返回false
     */
    static bool canMatch(const CardModel& card1, const CardModel& card2);
    
    /**
     * @brief 获取卡牌名称字符串
     * 
     * @param card 卡牌对象
     * @return 卡牌的完整名称字符串
     */
    static std::string getCardName(const CardModel& card);
    
    /**
     * @brief 获取花色名称
     * 
     * @param suit 花色类型
     * @return 花色的中文名称
     */
    static std::string getSuitName(CardSuitType suit);
    
    /**
     * @brief 获取牌面名称
     * 
     * @param face 牌面类型
     * @return 牌面的名称字符串
     */
    static std::string getFaceName(CardFaceType face);
    
    /**
     * @brief 生成唯一的卡牌ID
     * 
     * @return 新的唯一卡牌标识符
     */
    static int generateUniqueCardId();
    
    /**
     * @brief 获取卡牌图片资源名称
     * 
     * @param card 卡牌对象
     * @return 对应的图片资源文件名
     */
    static std::string getCardImageName(const CardModel& card);
    
    /**
     * @brief 获取卡牌背面图片资源名称
     * 
     * @return 卡牌背面的图片资源文件名
     */
    static std::string getCardBackImageName();
    
private:
    static int s_nextCardId; ///< 用于生成唯一ID的静态计数器
};

#endif // __GAME_UTILS_H__