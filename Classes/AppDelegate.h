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

#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

/**
 * @class AppDelegate
 * @brief 应用程序委托类
 * 
 * 继承自cocos2d::Application，负责管理应用程序的生命周期
 * 处理应用程序的启动、暂停、恢复等关键事件
 * 通过私有继承隐藏Director接口的部分功能
 * 
 * 职责：
 * - 初始化OpenGL上下文属性
 * - 配置游戏场景和导演
 * - 处理应用程序前后台切换
 * - 管理应用程序资源的加载和释放
 * 
 * 使用场景：
 * - 应用程序启动时的初始化
 * - 应用程序生命周期事件处理
 * - 游戏引擎的基础配置
 */
class  AppDelegate : private cocos2d::Application
{
public:
    /**
     * @brief 构造函数
     * 
     * 创建应用程序委托实例
     */
    AppDelegate();
    
    /**
     * @brief 析构函数
     * 
     * 清理应用程序委托资源
     */
    virtual ~AppDelegate();

    /**
     * @brief 初始化OpenGL上下文属性
     * 
     * 配置OpenGL渲染上下文的各种属性
     * 如颜色缓冲区、深度缓冲区、多重采样等
     */
    virtual void initGLContextAttrs();

    /**
     * @brief 应用程序启动完成回调
     * 
     * 实现导演和场景的初始化代码
     * 在此方法中进行游戏的基础设置和首个场景的创建
     * 
     * @return true 初始化成功，应用程序继续运行
     * @return false 初始化失败，应用程序终止
     */
    virtual bool applicationDidFinishLaunching();

    /**
     * @brief 应用程序进入后台回调
     * 
     * 当应用程序切换到后台时调用
     * 用于暂停游戏逻辑、保存游戏状态等操作
     */
    virtual void applicationDidEnterBackground();

    /**
     * @brief 应用程序重新进入前台回调
     * 
     * 当应用程序从后台恢复到前台时调用
     * 用于恢复游戏逻辑、重新加载资源等操作
     */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

