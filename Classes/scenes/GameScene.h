#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "../models/GameModel.h"
#include "../controllers/GameController.h"
#include "../views/GameView.h"
#include "../managers/UndoManager.h"

// Game scene class
class GameScene : public cocos2d::Scene {
public:
    // Create scene
    static cocos2d::Scene* createScene();
    
    // Initialize
    virtual bool init() override;
    
    // Implement create function
    CREATE_FUNC(GameScene);
    
private:
    GameModel* m_gameModel;           // Game data model
    GameController* m_gameController; // Game controller
    GameView* m_gameView;            // Game view
    UndoManager* m_undoManager;      // Undo manager
    
    // Initialize game components
    bool initGameComponents();
    
    // Create test data
    void createTestData();
    
    // Create default data (fallback)
    void createDefaultData();
    
    // Game end callback
    void onGameEnd(bool isWin);
    
    // Restart game
    void restartGame();
    
    // Create UI elements
    void createUI();
    
    // Back to menu button callback
    void onBackToMenuClicked(cocos2d::Ref* sender);
    
    // Restart button callback
    void onRestartClicked(cocos2d::Ref* sender);
};

#endif // __GAME_SCENE_H__