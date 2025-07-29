#include "CardModel.h"

USING_NS_CC;

// 默认构造函数
CardModel::CardModel() 
    : id(0), face(CFT_ACE), suit(CST_HEARTS), isFaceUp(true), position(Vec2::ZERO) {
}

// 参数构造函数
CardModel::CardModel(int cardId, CardFaceType cardFace, CardSuitType cardSuit, bool faceUp)
    : id(cardId), face(cardFace), suit(cardSuit), isFaceUp(faceUp), position(Vec2::ZERO) {
}

// 拷贝构造函数
CardModel::CardModel(const CardModel& other)
    : id(other.id), face(other.face), suit(other.suit), isFaceUp(other.isFaceUp), position(other.position) {
}

// 赋值运算符
CardModel& CardModel::operator=(const CardModel& other) {
    if (this != &other) {
        id = other.id;
        face = other.face;
        suit = other.suit;
        isFaceUp = other.isFaceUp;
        position = other.position;
    }
    return *this;
}

// 析构函数
CardModel::~CardModel() {
}