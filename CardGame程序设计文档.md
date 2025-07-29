# CardGame 程序设计文档

## 1. 项目概述

### 1.1 项目简介
​	CardGame是一个基于Cocos2d-x引擎开发的卡牌消除游戏。玩家通过点击手牌和牌桌上的卡牌进行匹配消除，目标是清空所有牌桌卡牌获得胜利。游戏采用经典的MVC架构模式，具有良好的代码组织结构和可扩展性。

### 1.2 核心功能
- **卡牌匹配系统**：支持相邻数值卡牌的匹配消除
- **撤销功能**：允许玩家撤销之前的操作
- **关卡系统**：支持多关卡配置和加载
- **动画系统**：流畅的卡牌移动和消除动画


### 1.3 技术栈
- **游戏引擎**：Cocos2d-x 3.17.2
- **编程语言**：C++17
- **架构模式**：MVC (Model-View-Controller)
- **构建系统**：CMake
- **平台支持**：Windows, Android, iOS, macOS, Linux

## 2. 系统架构设计

### 2.1 整体架构

```
┌─────────────────────────────────────────────────────────────┐
│                        Presentation Layer                   │
├─────────────────────────────────────────────────────────────┤
│  Scenes           │  Views           │  UI Components       │
│  - HelloWorldScene│  - GameView      │  - Buttons           │
│  - GameScene      │  - CardView      │  - Labels            │
│                   │                  │  - Dialogs           │
├─────────────────────────────────────────────────────────────┤
│                        Business Layer                       │
├─────────────────────────────────────────────────────────────┤
│  Controllers     │  Services        │  Managers            │
│  - GameController│  - GameService   │  - UndoManager       │
│                  │  - AnimationSvc  │  - LevelConfigMgr    │
│                  │  - ScoreService  │                      │
│                  │  - CardMatchSvc  │                      │
├─────────────────────────────────────────────────────────────┤
│                         Data Layer                          │
├─────────────────────────────────────────────────────────────┤
│  Models          │  Configs         │  Utils               │
│  - GameModel     │  - CardTypes     │  - GameUtils         │
│  - CardModel     │  - LevelConfig   │                      │
│                  │                  │                      │
└─────────────────────────────────────────────────────────────┘
```

### 2.2 MVC架构详解

#### Model层 (数据模型)
- **CardModel**: 单张卡牌的数据表示
- **GameModel**: 游戏整体状态和数据管理
- **GameStateSnapshot**: 游戏状态快照，用于撤销功能

#### View层 (视图表现)
- **GameView**: 游戏主界面视图
- **CardView**: 单张卡牌的视图表示
- **Scene类**: 场景管理和界面切换

#### Controller层 (控制逻辑)
- **GameController**: 游戏核心控制器，协调Model和View
- **UndoManager**: 撤销功能管理器
- **Service类**: 业务逻辑服务层

### 2.3 设计模式应用

#### 2.3.1 单例模式 (Singleton)
```cpp
class LevelConfigManager {
public:
    static LevelConfigManager* getInstance();
private:
    static LevelConfigManager* s_instance;
};
```
**应用场景**: 关卡配置管理器，确保全局唯一的配置访问点。

#### 2.3.2 观察者模式 (Observer)
```cpp
class GameController {
private:
    std::function<void(bool)> m_gameEndCallback;
public:
    void setGameEndCallback(const std::function<void(bool)>& callback);
};
```
**应用场景**: 游戏事件回调机制，实现松耦合的事件通知。

#### 2.3.3 命令模式 (Command)
```cpp
struct GameStateSnapshot {
    std::vector<CardModel> handCards;
    std::vector<CardModel> playfieldCards;
    int score;
};
```
**应用场景**: 撤销功能的状态保存和恢复。

#### 2.3.4 策略模式 (Strategy)
```cpp
class GameService {
public:
    static bool validateCardMatch(const CardModel& card1, const CardModel& card2);
    static int calculateScore(const CardModel& matchedCard);
};
```
**应用场景**: 不同的匹配规则和计分策略。

## 3. 核心模块详解

### 3.1 数据模型层

#### 3.1.1 CardModel (卡牌模型)
```cpp
class CardModel {
public:
    int id;                    // 卡牌唯一标识符
    CardFaceType face;         // 卡牌牌面值 (A-K)
    CardSuitType suit;         // 卡牌花色 (♠♥♦♣)
    bool isFaceUp;            // 卡牌朝向状态
    cocos2d::Vec2 position;   // 卡牌位置坐标
};
```

**职责**:
- 存储单张卡牌的所有属性信息
- 提供卡牌数据的封装和访问接口
- 支持卡牌状态的序列化和反序列化

#### 3.1.2 GameModel (游戏模型)
```cpp
struct GameModel {
    std::vector<CardModel> handCards;      // 手牌列表
    std::vector<CardModel> playfieldCards; // 牌桌卡牌列表
    int currentLevel;                      // 当前关卡
    int score;                            // 游戏分数
    bool isGameOver;                      // 游戏结束标志
    bool isGameWon;                       // 游戏胜利标志
};
```

**职责**:
- 维护游戏的完整状态信息
- 提供游戏数据的查询和修改接口
- 管理游戏进度和胜负判断

### 3.2 视图表现层

#### 3.2.1 GameView (游戏视图)
```cpp
class GameView : public cocos2d::Node {
private:
    cocos2d::Node* m_handCardContainer;     // 手牌容器
    cocos2d::Node* m_playfieldContainer;    // 牌桌容器
    cocos2d::ui::Button* m_undoButton;      // 撤销按钮
    cocos2d::Label* m_scoreLabel;           // 分数标签
    
    std::function<void(int)> m_handCardClickCallback;
    std::function<void(int)> m_playfieldCardClickCallback;
    std::function<void()> m_undoButtonClickCallback;
};
```

**职责**:
- 渲染游戏界面的所有可视元素
- 处理用户的触摸和点击事件
- 播放卡牌动画和视觉效果
- 通过回调函数与控制器通信

#### 3.2.2 CardView (卡牌视图)
```cpp
class CardView : public cocos2d::Node {
public:
    static const float CARD_WIDTH;   // 卡牌宽度常量
    static const float CARD_HEIGHT;  // 卡牌高度常量
    
    static CardView* create(const CardModel& card);
};
```

**职责**:
- 单张卡牌的可视化表示
- 根据卡牌数据渲染对应的图片
- 处理卡牌的显示状态切换

### 3.3 控制逻辑层

#### 3.3.1 GameController (游戏控制器)
```cpp
class GameController {
public:
    bool init(GameModel* model, GameView* view);
    void onHandCardClicked(int cardId);
    void onPlayfieldCardClicked(int cardId);
    void onUndoButtonClicked();
    void refreshView();
    
private:
    GameModel* m_gameModel;
    GameView* m_gameView;
    UndoManager* m_undoManager;
};
```

**职责**:
- 协调Model和View之间的交互
- 处理用户输入事件和游戏逻辑
- 管理游戏状态的更新和同步
- 控制游戏流程和规则执行

#### 3.3.2 UndoManager (撤销管理器)
```cpp
class UndoManager {
public:
    void saveState();           // 保存当前状态
    bool undo();               // 撤销到上一状态
    bool canUndo() const;      // 检查是否可撤销
    void clear();              // 清空撤销历史
    
private:
    std::stack<std::shared_ptr<GameStateSnapshot>> m_undoStack;
    int m_maxUndoSteps;        // 最大撤销步数
};
```

**职责**:
- 管理游戏状态的历史记录
- 提供撤销功能的实现
- 控制撤销步数和内存使用

### 3.4 服务层

#### 3.4.1 GameService (游戏服务)
```cpp
class GameService {
public:
    static bool executeHandCardReplacement(GameModel* gameModel, int cardId);
    static bool executePlayfieldCardMatch(GameModel* gameModel, int cardId);
    static int checkGameEndCondition(const GameModel* gameModel);
    static bool validateCardMatch(const CardModel& card1, const CardModel& card2);
    static int calculateScore(const CardModel& matchedCard);
};
```

**特点**:
- 无状态服务，不持有数据
- 处理核心业务逻辑
- 提供静态方法，便于调用
- 可复用的业务功能模块

#### 3.4.2 AnimationService (动画服务)
```cpp
class AnimationService {
public:
    static cocos2d::Action* createCardMoveAnimation(cocos2d::Node* card, 
                                                   const cocos2d::Vec2& targetPos, 
                                                   float duration);
    static float calculateHandCardMoveToTopDuration(int cardId, 
                                                    const cocos2d::Vec2& from, 
                                                    const cocos2d::Vec2& to);
};
```

**职责**:
- 创建和管理游戏动画效果
- 计算动画时长和轨迹
- 提供统一的动画接口

### 3.5 配置和工具层

#### 3.5.1 CardTypes (卡牌类型定义)
```cpp
enum CardSuitType {
    CST_CLUBS,     // 梅花
    CST_DIAMONDS,  // 方块
    CST_HEARTS,    // 红桃
    CST_SPADES     // 黑桃
};

enum CardFaceType {
    CFT_ACE, CFT_TWO, CFT_THREE, ..., CFT_KING
};
```

#### 3.5.2 LevelConfig (关卡配置)
```cpp
struct CardConfig {
    int cardFace;
    int cardSuit;
    cocos2d::Vec2 position;
};

struct LevelConfig {
    std::vector<CardConfig> playfield;  // 牌桌卡牌配置
    std::vector<CardConfig> stack;      // 手牌堆配置
};
```

#### 3.5.3 GameUtils (游戏工具)
```cpp
class GameUtils {
public:
    static bool canMatch(const CardModel& card1, const CardModel& card2);
    static std::string getCardName(const CardModel& card);
    static int generateUniqueCardId();
    static std::string getCardImageName(const CardModel& card);
};
```

## 4. 数据流和交互流程

### 4.1 游戏初始化流程
```
1. AppDelegate::applicationDidFinishLaunching()
   ↓
2. HelloWorldScene::createScene()
   ↓
3. 用户点击"开始游戏"
   ↓
4. GameScene::createScene()
   ↓
5. GameScene::initGameComponents()
   ├── 创建GameModel
   ├── 创建GameView
   ├── 创建GameController
   └── 创建UndoManager
   ↓
6. GameScene::createTestData()
   ├── LevelConfigManager::loadLevel()
   └── 初始化卡牌数据
   ↓
7. GameController::refreshView()
```

### 4.2 卡牌点击处理流程
```
1. 用户点击卡牌
   ↓
2. GameView::onHandCardTouched() 或 onPlayfieldCardTouched()
   ↓
3. 触发回调函数
   ↓
4. GameController::onHandCardClicked() 或 onPlayfieldCardClicked()
   ↓
5. UndoManager::saveState() (保存当前状态)
   ↓
6. GameService::executeHandCardReplacement() 或 executePlayfieldCardMatch()
   ↓
7. 更新GameModel数据
   ↓
8. GameController::refreshView()
   ↓
9. GameView::updateHandCards() 和 updatePlayfieldCards()
   ↓
10. 播放动画效果
    ↓
11. GameController::checkGameEnd()
```

### 4.3 撤销操作流程
```
1. 用户点击撤销按钮
   ↓
2. GameView::onUndoButtonClicked()
   ↓
3. GameController::onUndoButtonClicked()
   ↓
4. UndoManager::undo()
   ├── 检查是否可撤销
   ├── 从栈中弹出上一状态
   └── 应用状态快照
   ↓
5. GameController::refreshView()
   ↓
6. 更新界面显示
```

## 5. 扩展开发指南

### 5.1 如何添加新的卡牌类型

#### 步骤1: 扩展卡牌类型枚举
在 `CardTypes.h` 中添加新的牌面类型：

```cpp
enum CardFaceType {
    CFT_NONE = -1,
    CFT_ACE,
    // ... 现有类型
    CFT_KING,
    
    // 新增特殊卡牌类型
    CFT_JOKER_RED,      // 红色小丑
    CFT_JOKER_BLACK,    // 黑色小丑
    CFT_WILD_CARD,      // 万能牌
    
    CFT_NUM_CARD_FACE_TYPES
};
```

#### 步骤2: 更新工具类方法
在 `GameUtils.cpp` 中添加新卡牌的处理逻辑：

```cpp
std::string GameUtils::getFaceName(CardFaceType face) {
    switch (face) {
        // ... 现有case
        case CFT_JOKER_RED: return "红色小丑";
        case CFT_JOKER_BLACK: return "黑色小丑";
        case CFT_WILD_CARD: return "万能牌";
        default: return "未知";
    }
}

std::string GameUtils::getCardImageName(const CardModel& card) {
    if (card.face == CFT_JOKER_RED) {
        return "res/special/joker_red.png";
    }
    if (card.face == CFT_JOKER_BLACK) {
        return "res/special/joker_black.png";
    }
    if (card.face == CFT_WILD_CARD) {
        return "res/special/wild_card.png";
    }
    // ... 现有逻辑
}
```

#### 步骤3: 扩展匹配规则
在 `GameService.cpp` 中更新匹配逻辑：

```cpp
bool GameService::validateCardMatch(const CardModel& card1, const CardModel& card2) {
    // 万能牌可以与任何卡牌匹配
    if (card1.face == CFT_WILD_CARD || card2.face == CFT_WILD_CARD) {
        return true;
    }
    
    // 小丑牌之间可以匹配
    if ((card1.face == CFT_JOKER_RED || card1.face == CFT_JOKER_BLACK) &&
        (card2.face == CFT_JOKER_RED || card2.face == CFT_JOKER_BLACK)) {
        return true;
    }
    
    // 原有匹配规则
    return GameUtils::canMatch(card1, card2);
}
```

#### 步骤4: 添加图片资源
在 `Resources/res/special/` 目录下添加新卡牌的图片文件：
- `joker_red.png`
- `joker_black.png`
- `wild_card.png`

#### 步骤5: 更新关卡配置
在关卡JSON文件中可以使用新的卡牌类型：

```json
{
    "playfield": [
        {
            "CardFace": 14,  // CFT_JOKER_RED
            "CardSuit": 0,
            "Position": {"x": 100, "y": 200}
        }
    ]
}
```

### 5.2 如何添加新的撤销功能类型

#### 步骤1: 定义新的撤销操作类型
创建新的撤销操作枚举和数据结构：

```cpp
// 在UndoManager.h中添加
enum class UndoActionType {
    CARD_MATCH,           // 卡牌匹配操作
    CARD_REPLACEMENT,     // 卡牌替换操作
    SPECIAL_ABILITY,      // 特殊能力使用
    POWER_UP_ACTIVATION,  // 道具激活
    HINT_USAGE           // 提示使用
};

struct UndoAction {
    UndoActionType type;
    int cardId;
    cocos2d::Vec2 fromPosition;
    cocos2d::Vec2 toPosition;
    int scoreChange;
    std::map<std::string, std::string> extraData; // 扩展数据
};
```

#### 步骤2: 扩展游戏状态快照
增强 `GameStateSnapshot` 结构以支持更多状态信息：

```cpp
struct GameStateSnapshot {
    std::vector<CardModel> handCards;
    std::vector<CardModel> playfieldCards;
    int score;
    
    // 新增状态信息
    int hintsRemaining;              // 剩余提示次数
    std::vector<int> activePowerUps; // 激活的道具列表
    int comboCount;                  // 连击数
    float timeRemaining;             // 剩余时间
    
    // 最后执行的操作信息
    UndoAction lastAction;
    
    GameStateSnapshot(const GameModel& model, const UndoAction& action)
        : handCards(model.handCards)
        , playfieldCards(model.playfieldCards)
        , score(model.score)
        , lastAction(action) {
        // 初始化新增字段
    }
};
```

#### 步骤3: 实现特定撤销逻辑
在 `UndoManager` 中添加针对不同操作类型的撤销处理：

```cpp
class UndoManager {
public:
    // 保存特定类型的操作状态
    void saveStateWithAction(const UndoAction& action);
    
    // 撤销特定类型的操作
    bool undoSpecificAction(UndoActionType actionType);
    
private:
    // 撤销卡牌匹配操作
    void undoCardMatch(const UndoAction& action);
    
    // 撤销道具使用
    void undoPowerUpActivation(const UndoAction& action);
    
    // 撤销提示使用
    void undoHintUsage(const UndoAction& action);
};

// 实现示例
void UndoManager::undoPowerUpActivation(const UndoAction& action) {
    // 恢复道具状态
    auto powerUpId = std::stoi(action.extraData.at("powerUpId"));
    
    // 将道具重新添加到可用列表
    // 恢复道具使用前的游戏状态
    // 更新UI显示
}
```

#### 步骤4: 集成到游戏控制器
在 `GameController` 中集成新的撤销功能：

```cpp
class GameController {
public:
    // 使用道具时保存状态
    void onPowerUpUsed(int powerUpId, const std::string& powerUpType);
    
    // 使用提示时保存状态
    void onHintUsed(int hintType);
    
private:
    // 创建撤销操作记录
    UndoAction createUndoAction(UndoActionType type, int cardId = -1);
};

// 实现示例
void GameController::onPowerUpUsed(int powerUpId, const std::string& powerUpType) {
    // 创建撤销操作记录
    UndoAction action;
    action.type = UndoActionType::POWER_UP_ACTIVATION;
    action.extraData["powerUpId"] = std::to_string(powerUpId);
    action.extraData["powerUpType"] = powerUpType;
    action.scoreChange = 0; // 道具使用通常不直接影响分数
    
    // 保存状态
    if (m_undoManager) {
        m_undoManager->saveStateWithAction(action);
    }
    
    // 执行道具效果
    // ...
}
```

#### 步骤5: 扩展UI支持
在 `GameView` 中添加对新撤销类型的UI支持：

```cpp
class GameView {
public:
    // 显示撤销操作的详细信息
    void showUndoPreview(const UndoAction& action);
    
    // 更新撤销按钮状态
    void updateUndoButtonState(bool canUndo, UndoActionType lastActionType);
    
private:
    cocos2d::Label* m_undoInfoLabel;  // 显示撤销信息的标签
};

// 实现示例
void GameView::showUndoPreview(const UndoAction& action) {
    std::string undoText;
    switch (action.type) {
        case UndoActionType::POWER_UP_ACTIVATION:
            undoText = "撤销道具使用: " + action.extraData.at("powerUpType");
            break;
        case UndoActionType::HINT_USAGE:
            undoText = "撤销提示使用";
            break;
        default:
            undoText = "撤销上一步操作";
            break;
    }
    
    if (m_undoInfoLabel) {
        m_undoInfoLabel->setString(undoText);
    }
}
```

### 5.3 性能优化建议

#### 5.3.1 内存管理
- 使用对象池管理卡牌视图对象
- 及时释放不再使用的纹理资源
- 限制撤销历史的最大数量

#### 5.3.2 渲染优化
- 使用批量渲染减少Draw Call
- 实现视锥剔除，只渲染可见卡牌
- 使用纹理图集减少纹理切换

#### 5.3.3 逻辑优化
- 缓存频繁计算的结果
- 使用事件驱动减少轮询
- 异步加载关卡数据

## 6. 测试策略

### 6.1 单元测试
- 测试卡牌匹配逻辑
- 测试撤销功能的正确性
- 测试分数计算算法

### 6.2 集成测试
- 测试MVC各层之间的交互
- 测试关卡加载和切换
- 测试游戏状态的保存和恢复

### 6.3 性能测试
- 内存使用情况监控
- 帧率稳定性测试
- 长时间运行稳定性测试

## 7. 部署和维护

### 7.1 构建配置
- 使用CMake管理跨平台构建
- 配置不同平台的编译选项
- 设置资源打包和压缩

### 7.2 版本管理
- 使用语义化版本号
- 维护详细的变更日志
- 建立代码审查流程

### 7.3 监控和日志
- 实现游戏崩溃报告
- 添加性能监控点
- 记录用户行为数据

## 8. 总结

CardGame项目采用了清晰的MVC架构设计，具有良好的代码组织结构和扩展性。通过合理的模块划分和设计模式应用，项目能够支持快速的功能迭代和维护。

### 8.1 项目优势
- **架构清晰**: MVC模式确保了代码的可维护性
- **扩展性强**: 模块化设计支持功能的快速扩展
- **代码质量高**: 完整的注释和文档
- **跨平台支持**: 基于Cocos2d-x的多平台部署能力

### 8.2 未来发展方向
- 添加更多卡牌类型和游戏模式
- 实现网络多人对战功能
- 增加更丰富的动画和特效
- 支持自定义关卡编辑器
- 集成数据分析和用户行为追踪
