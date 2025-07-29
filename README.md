# CardGame

基于Cocos2d-x开发的卡牌消除游戏，采用MVC架构设计。

## 项目简介

CardGame是一个卡牌消除类游戏，玩家通过点击手牌和牌桌上的卡牌进行匹配消除，目标是清空所有牌桌卡牌获得胜利。

## 核心功能

- **卡牌匹配系统**：支持相邻数值卡牌的匹配消除
- **撤销功能**：允许玩家撤销之前的操作
- **关卡系统**：支持多关卡配置和加载
- **动画系统**：流畅的卡牌移动和消除动画
- **分数系统**：实时计分和游戏状态管理

## 技术栈

- **游戏引擎**：Cocos2d-x 3.17.2
- **编程语言**：C++17
- **架构模式**：MVC (Model-View-Controller)
- **构建系统**：CMake
- **平台支持**：Windows, Android, iOS, macOS, Linux

## 项目结构

```
CardGame/
├── Classes/                 # 源代码目录
│   ├── models/             # 数据模型层
│   ├── views/              # 视图表现层
│   ├── controllers/        # 控制逻辑层
│   ├── services/           # 业务服务层
│   ├── managers/           # 管理器类
│   ├── configs/            # 配置文件
│   ├── utils/              # 工具类
│   └── scenes/             # 场景类
├── Resources/              # 游戏资源
│   ├── res/               # 图片资源
│   ├── fonts/             # 字体文件
│   └── levels/            # 关卡配置
├── cocos2d/               # Cocos2d-x引擎
├── proj.win32/            # Windows项目文件
├── proj.android/          # Android项目文件
├── proj.ios_mac/          # iOS/macOS项目文件
└── proj.linux/            # Linux项目文件
```

## 构建说明

### Windows

1. 确保已安装Visual Studio 2019或更高版本
2. 打开 `proj.win32/CardGame.sln`
3. 选择Debug或Release配置
4. 构建并运行项目

### Android

1. 确保已安装Android Studio和NDK
2. 进入 `proj.android` 目录
3. 运行 `./gradlew assembleDebug`

### iOS/macOS

1. 确保已安装Xcode
2. 打开 `proj.ios_mac/CardGame.xcodeproj`
3. 选择目标平台并构建

## 游戏玩法

1. 点击手牌中的卡牌，将其移动到牌桌顶部
2. 点击牌桌上的卡牌，如果与手牌顶部卡牌相邻（差值为1），则可以消除
3. 消除所有牌桌卡牌即可获胜
4. 可以使用撤销功能回退上一步操作

## 开发文档

详细的开发文档请参考项目根目录下的 `CardGame程序设计文档.md`，包含：

- 系统架构设计
- 核心模块详解
- 扩展开发指南
- 性能优化建议

## 许可证

本项目采用MIT许可证，详情请参考LICENSE文件。

## 贡献

欢迎提交Issue和Pull Request来改进项目。

## 联系方式

如有问题或建议，请通过GitHub Issues联系。
