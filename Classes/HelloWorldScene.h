/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

/**
 * @class HelloWorld
 * @brief Hello World场景类
 * 
 * 继承自cocos2d::Scene，提供游戏的欢迎场景
 * 这是cocos2d-x项目的默认示例场景
 * 通常用作项目的起始场景或测试场景
 * 
 * 职责：
 * - 创建和初始化Hello World场景
 * - 处理场景中的UI交互事件
 * - 提供场景的基础功能演示
 * 
 * 使用场景：
 * - 作为游戏的启动场景
 * - 用于测试基础功能
 * - 作为其他场景的参考模板
 */
class HelloWorld : public cocos2d::Scene
{
public:
    /**
     * @brief 创建Hello World场景
     * 
     * 静态工厂方法，用于创建场景实例
     * 
     * @return 返回创建的场景对象指针
     */
    static cocos2d::Scene* createScene();

    /**
     * @brief 初始化场景
     * 
     * 设置场景的基础元素和UI组件
     * 
     * @return 初始化成功返回true，失败返回false
     */
    virtual bool init();
    
    /**
     * @brief 菜单关闭按钮回调函数
     * 
     * 处理关闭按钮的点击事件
     * 
     * @param pSender 触发事件的发送者对象
     */
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    /**
     * @brief 创建函数宏
     * 
     * 手动实现静态create()方法
     * 用于简化对象的创建和初始化过程
     */
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
