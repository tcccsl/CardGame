#include "UndoManager.h"

USING_NS_CC;

// 构造函数
UndoManager::UndoManager()
    : m_gameModel(nullptr), m_maxUndoSteps(10) {
}

// 析构函数
UndoManager::~UndoManager() {
    clear();
}

// 初始化
bool UndoManager::init(GameModel* gameModel) {
    if (!gameModel) {
        return false;
    }
    
    m_gameModel = gameModel;
    return true;
}

// 保存当前游戏状态
void UndoManager::saveState() {
    if (!m_gameModel) {
        return;
    }
    
    // 创建当前状态快照
    auto snapshot = std::make_shared<GameStateSnapshot>(*m_gameModel);
    m_undoStack.push(snapshot);
    
    // 限制撤销栈大小
    while (m_undoStack.size() > static_cast<size_t>(m_maxUndoSteps)) {
        m_undoStack.pop();
    }
}

// 撤销到上一状态
bool UndoManager::undo() {
    if (!canUndo()) {
        return false;
    }
    
    // 获取上一状态
    auto snapshot = m_undoStack.top();
    m_undoStack.pop();
    
    // 应用快照
    applySnapshot(*snapshot);
    
    return true;
}

// 检查是否可以撤销
bool UndoManager::canUndo() const {
    return !m_undoStack.empty() && m_gameModel != nullptr;
}

// 清除撤销历史
void UndoManager::clear() {
    while (!m_undoStack.empty()) {
        m_undoStack.pop();
    }
}

// 设置最大撤销步数
void UndoManager::setMaxUndoSteps(int maxSteps) {
    m_maxUndoSteps = maxSteps;
    
    // 如果当前栈大小超过新限制，移除多余元素
    while (m_undoStack.size() > static_cast<size_t>(m_maxUndoSteps)) {
        m_undoStack.pop();
    }
}

// 应用游戏状态快照
void UndoManager::applySnapshot(const GameStateSnapshot& snapshot) {
    if (!m_gameModel) {
        return;
    }
    
    m_gameModel->handCards = snapshot.handCards;
    m_gameModel->playfieldCards = snapshot.playfieldCards;
    m_gameModel->score = snapshot.score;
    
    // 重新检查游戏状态
    m_gameModel->isGameOver = false;
    m_gameModel->isGameWon = false;
}