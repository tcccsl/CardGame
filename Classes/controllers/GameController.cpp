#include "GameController.h"
#include "../views/GameView.h"
#include "../managers/UndoManager.h"
#include "../services/GameService.h"
#include "../utils/GameUtils.h"
#include <algorithm>

USING_NS_CC;

// 构造函数
GameController::GameController()
    : m_gameModel(nullptr), m_gameView(nullptr), m_undoManager(nullptr) {
}

// 析构函数
GameController::~GameController() {
}

// 初始化控制器
bool GameController::init(GameModel* model, GameView* view) {
    if (!model || !view) {
        return false;
    }
    
    m_gameModel = model;
    m_gameView = view;
    
    return true;
}

// 处理手牌点击
void GameController::onHandCardClicked(int cardId) {
    if (!m_gameModel || m_gameModel->isGameOver) {
        return;
    }
    
    // 保存状态用于撤销
    if (m_undoManager) {
        m_undoManager->saveState();
    }
    
    // 使用GameService处理业务逻辑
    if (GameService::executeHandCardReplacement(m_gameModel, cardId)) {
        // 触发动画
        if (m_gameView) {
            m_gameView->animateHandCardToTop(cardId);
        }
        refreshView();
        checkGameEnd();
    }
}

// 处理牌桌卡牌点击
void GameController::onPlayfieldCardClicked(int cardId) {
    if (!m_gameModel || m_gameModel->isGameOver) {
        return;
    }
    
    // Save state for undo
    if (m_undoManager) {
        m_undoManager->saveState();
    }
    
    // 使用GameService处理业务逻辑
    if (GameService::executePlayfieldCardMatch(m_gameModel, cardId)) {
        // 触发动画
        if (m_gameView) {
            m_gameView->animatePlayfieldCardToHand(cardId);
        }
        refreshView();
        checkGameEnd();
    }
}

// 处理撤销按钮点击
void GameController::onUndoButtonClicked() {
    if (m_undoManager && m_undoManager->canUndo()) {
        m_undoManager->undo();
        refreshView();
    }
}

// 刷新视图
void GameController::refreshView() {
    refreshHandView();
    refreshPlayfieldView();
}

// 设置撤销管理器
void GameController::setUndoManager(UndoManager* undoManager) {
    m_undoManager = undoManager;
}

// 设置游戏结束回调
void GameController::setGameEndCallback(const std::function<void(bool)>& callback) {
    m_gameEndCallback = callback;
}

// 开始新游戏
void GameController::startNewGame() {
    if (m_gameModel) {
        m_gameModel->reset();
        // TODO: 加载关卡数据
        refreshView();
    }
}

// 重置游戏
void GameController::resetGame() {
    startNewGame();
}

// 刷新手牌视图
void GameController::refreshHandView() {
    if (m_gameView) {
        m_gameView->updateHandCards(m_gameModel->handCards);
    }
}

// 刷新牌桌视图
void GameController::refreshPlayfieldView() {
    if (m_gameView) {
        m_gameView->updatePlayfieldCards(m_gameModel->playfieldCards);
    }
}

// 检查游戏结束
void GameController::checkGameEnd() {
    if (!m_gameModel) {
        return;
    }
    
    // 使用GameService检查游戏结束条件
    int gameEndStatus = GameService::checkGameEndCondition(m_gameModel);
    
    if (gameEndStatus == 1) {
        // 胜利
        m_gameModel->isGameOver = true;
        m_gameModel->isGameWon = true;
        if (m_gameEndCallback) {
            m_gameEndCallback(true);
        }
    } else if (gameEndStatus == -1) {
        // 失败
        m_gameModel->isGameOver = true;
        m_gameModel->isGameWon = false;
        if (m_gameEndCallback) {
            m_gameEndCallback(false);
        }
    }
    // gameEndStatus == 0 时继续游戏
}