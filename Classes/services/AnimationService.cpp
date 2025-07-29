#include "AnimationService.h"
#include <cmath>

USING_NS_CC;

// 动画配置常量定义
const float AnimationService::DEFAULT_MOVE_DURATION = 0.3f;
const float AnimationService::DEFAULT_FADE_DURATION = 0.2f;
const float AnimationService::DEFAULT_SCALE_DURATION = 0.15f;
const float AnimationService::FAST_ANIMATION_SPEED_MULTIPLIER = 0.7f;
const float AnimationService::SLOW_ANIMATION_SPEED_MULTIPLIER = 1.5f;

// 计算手牌移动到顶部的动画参数
float AnimationService::calculateHandCardMoveToTopDuration(int cardId, 
                                                          const Vec2& currentPos, 
                                                          const Vec2& targetPos) {
    float distance = calculateDistance(currentPos, targetPos);
    
    // 基础持续时间根据距离调整
    float baseDuration = DEFAULT_MOVE_DURATION;
    float distanceFactor = distance / 200.0f; // 200像素作为基准距离
    
    // 限制在合理范围内
    float duration = baseDuration * (0.8f + distanceFactor * 0.4f);
    return std::max(0.1f, std::min(duration, 0.8f));
}

// 计算桌面卡牌移动到手牌区的动画参数
float AnimationService::calculatePlayfieldToHandDuration(int cardId, 
                                                        const Vec2& currentPos, 
                                                        const Vec2& targetPos) {
    float distance = calculateDistance(currentPos, targetPos);
    
    // 桌面到手牌的动画稍微快一些
    float baseDuration = DEFAULT_MOVE_DURATION * FAST_ANIMATION_SPEED_MULTIPLIER;
    float distanceFactor = distance / 250.0f; // 250像素作为基准距离
    
    float duration = baseDuration * (0.7f + distanceFactor * 0.5f);
    return std::max(0.08f, std::min(duration, 0.6f));
}

// 创建卡牌移动动画序列
Action* AnimationService::createCardMoveAnimation(Node* node,
                                                 const Vec2& targetPos,
                                                 float duration,
                                                 const std::function<void()>& onComplete) {
    if (!node) {
        return nullptr;
    }
    
    // 创建移动动作，使用缓动效果
    auto moveAction = EaseOut::create(MoveTo::create(duration, targetPos), 2.0f);
    
    if (onComplete) {
        // 添加完成回调
        auto callbackAction = CallFunc::create(onComplete);
        return Sequence::create(moveAction, callbackAction, nullptr);
    }
    
    return moveAction;
}

// 创建卡牌淡入淡出动画
Action* AnimationService::createCardFadeAnimation(Node* node,
                                                 bool fadeIn,
                                                 float duration,
                                                 const std::function<void()>& onComplete) {
    if (!node) {
        return nullptr;
    }
    
    GLubyte targetOpacity = fadeIn ? 255 : 0;
    auto fadeAction = FadeTo::create(duration, targetOpacity);
    
    if (onComplete) {
        auto callbackAction = CallFunc::create(onComplete);
        return Sequence::create(fadeAction, callbackAction, nullptr);
    }
    
    return fadeAction;
}

// 创建卡牌缩放动画
Action* AnimationService::createCardScaleAnimation(Node* node,
                                                  float targetScale,
                                                  float duration,
                                                  const std::function<void()>& onComplete) {
    if (!node) {
        return nullptr;
    }
    
    // 使用缓动效果的缩放动画
    auto scaleAction = EaseBackOut::create(ScaleTo::create(duration, targetScale));
    
    if (onComplete) {
        auto callbackAction = CallFunc::create(onComplete);
        return Sequence::create(scaleAction, callbackAction, nullptr);
    }
    
    return scaleAction;
}

// 计算两点间距离
float AnimationService::calculateDistance(const Vec2& pos1, const Vec2& pos2) {
    float dx = pos2.x - pos1.x;
    float dy = pos2.y - pos1.y;
    return std::sqrt(dx * dx + dy * dy);
}