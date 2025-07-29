#ifndef __LEVEL_CONFIG_H__
#define __LEVEL_CONFIG_H__

#include "cocos2d.h"
#include "CardTypes.h"
#include <vector>
#include <string>

struct CardConfig {
    int cardFace;
    int cardSuit;
    cocos2d::Vec2 position;
};

struct LevelConfig {
    std::vector<CardConfig> playfield;
    std::vector<CardConfig> stack;
};

class LevelConfigManager {
public:
    static LevelConfigManager* getInstance();
    
    // 加载关卡配置
    bool loadLevel(const std::string& levelFile);
    
    // 获取当前关卡配置
    const LevelConfig& getCurrentLevel() const { return m_currentLevel; }
    
private:
    LevelConfigManager() = default;
    ~LevelConfigManager() = default;
    
    static LevelConfigManager* s_instance;
    LevelConfig m_currentLevel;
};

#endif // __LEVEL_CONFIG_H__