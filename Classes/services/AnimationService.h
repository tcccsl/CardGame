#ifndef __ANIMATION_SERVICE_H__
#define __ANIMATION_SERVICE_H__

#include "cocos2d.h"
#include <functional>

/**
 * 动画服务 - 处理游戏中的动画逻辑
 * 特点：
 * - 无状态服务，不持有数据
 * - 专注于动画效果的计算和配置
 * - 提供静态方法
 */
class AnimationService {
public:
    /**
     * 计算手牌移动到顶部的动画参数
     * @param cardId 卡牌ID
     * @param currentPos 当前位置
     * @param targetPos 目标位置
     * @return 动画持续时间
     */
    static float calculateHandCardMoveToTopDuration(int cardId, 
                                                   const cocos2d::Vec2& currentPos, 
                                                   const cocos2d::Vec2& targetPos);
    
    /**
     * 计算桌面卡牌移动到手牌区的动画参数
     * @param cardId 卡牌ID
     * @param currentPos 当前位置
     * @param targetPos 目标位置
     * @return 动画持续时间
     */
    static float calculatePlayfieldToHandDuration(int cardId, 
                                                  const cocos2d::Vec2& currentPos, 
                                                  const cocos2d::Vec2& targetPos);
    
    /**
     * 创建卡牌移动动画序列
     * @param node 要动画的节点
     * @param targetPos 目标位置
     * @param duration 动画持续时间
     * @param onComplete 完成回调
     * @return 动画动作
     */
    static cocos2d::Action* createCardMoveAnimation(cocos2d::Node* node,
                                                   const cocos2d::Vec2& targetPos,
                                                   float duration,
                                                   const std::function<void()>& onComplete = nullptr);
    
    /**
     * 创建卡牌淡入淡出动画
     * @param node 要动画的节点
     * @param fadeIn 是否淡入（false为淡出）
     * @param duration 动画持续时间
     * @param onComplete 完成回调
     * @return 动画动作
     */
    static cocos2d::Action* createCardFadeAnimation(cocos2d::Node* node,
                                                   bool fadeIn,
                                                   float duration,
                                                   const std::function<void()>& onComplete = nullptr);
    
    /**
     * 创建卡牌缩放动画
     * @param node 要动画的节点
     * @param targetScale 目标缩放比例
     * @param duration 动画持续时间
     * @param onComplete 完成回调
     * @return 动画动作
     */
    static cocos2d::Action* createCardScaleAnimation(cocos2d::Node* node,
                                                    float targetScale,
                                                    float duration,
                                                    const std::function<void()>& onComplete = nullptr);
    
    // 动画配置常量
    static const float DEFAULT_MOVE_DURATION;
    static const float DEFAULT_FADE_DURATION;
    static const float DEFAULT_SCALE_DURATION;
    static const float FAST_ANIMATION_SPEED_MULTIPLIER;
    static const float SLOW_ANIMATION_SPEED_MULTIPLIER;
    
private:
    // 私有构造函数，防止实例化
    AnimationService() = delete;
    ~AnimationService() = delete;
    AnimationService(const AnimationService&) = delete;
    AnimationService& operator=(const AnimationService&) = delete;
    
    /**
     * 计算两点间距离
     * @param pos1 第一个位置
     * @param pos2 第二个位置
     * @return 距离
     */
    static float calculateDistance(const cocos2d::Vec2& pos1, const cocos2d::Vec2& pos2);
};

#endif // __ANIMATION_SERVICE_H__