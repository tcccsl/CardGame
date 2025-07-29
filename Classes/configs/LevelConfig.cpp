#include "LevelConfig.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;

LevelConfigManager* LevelConfigManager::s_instance = nullptr;

LevelConfigManager* LevelConfigManager::getInstance() {
    if (s_instance == nullptr) {
        s_instance = new LevelConfigManager();
    }
    return s_instance;
}

bool LevelConfigManager::loadLevel(const std::string& levelFile) {
    // 读取JSON文件
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(levelFile);
    std::string jsonString = FileUtils::getInstance()->getStringFromFile(fullPath);
    
    if (jsonString.empty()) {
        CCLOG("Failed to load level file: %s", levelFile.c_str());
        return false;
    }
    
    // 解析JSON
    rapidjson::Document document;
    document.Parse(jsonString.c_str());
    
    if (document.HasParseError()) {
        CCLOG("Failed to parse level JSON: %s", levelFile.c_str());
        return false;
    }
    
    // 清空当前配置
    m_currentLevel.playfield.clear();
    m_currentLevel.stack.clear();
    
    // 解析Playfield
    if (document.HasMember("Playfield") && document["Playfield"].IsArray()) {
        const rapidjson::Value& playfield = document["Playfield"];
        for (rapidjson::SizeType i = 0; i < playfield.Size(); i++) {
            const rapidjson::Value& card = playfield[i];
            CardConfig cardConfig;
            cardConfig.cardFace = card["CardFace"].GetInt();
            cardConfig.cardSuit = card["CardSuit"].GetInt();
            cardConfig.position.x = card["Position"]["x"].GetFloat();
            cardConfig.position.y = card["Position"]["y"].GetFloat();
            m_currentLevel.playfield.push_back(cardConfig);
        }
    }
    
    // 解析Stack
    if (document.HasMember("Stack") && document["Stack"].IsArray()) {
        const rapidjson::Value& stack = document["Stack"];
        for (rapidjson::SizeType i = 0; i < stack.Size(); i++) {
            const rapidjson::Value& card = stack[i];
            CardConfig cardConfig;
            cardConfig.cardFace = card["CardFace"].GetInt();
            cardConfig.cardSuit = card["CardSuit"].GetInt();
            cardConfig.position.x = card["Position"]["x"].GetFloat();
            cardConfig.position.y = card["Position"]["y"].GetFloat();
            m_currentLevel.stack.push_back(cardConfig);
        }
    }
    
    CCLOG("Level loaded successfully: %s", levelFile.c_str());
    return true;
}