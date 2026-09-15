# reVC

**简体中文** | [English](README.en.md)

## 本次整合的功能与修复

- **过场动画可动手指**：原生移植 Xbox Hands VC，包含配套模型、纹理、动画和 XML；必要资源缺失时保留原手部。见 [安装与兼容说明](docs/XBOX_HANDS.md)。
- **任务重试血量**：修复重试后显示 255，恢复当前有效最高血量，并兼容已知旧存档异常血量上限。
- **Classic Axis**：在 Standard Controls 中加入居中准星、越肩第三人称瞄准；Free Cam 仍独立控制普通移动的自由环绕。根据 VC 原生动画、武器与载具特性适配，不照搬 III。
- **GInput 第五套风格手柄布局**：LT 瞄准、RT 开火，A 奔跑、X 跳跃、Y 上车、LS 蹲下；驾驶时 RT 油门、LT 刹车/倒车、A 手刹、B 载具开火、LB/RB 左右观察，组合向后看。
- **目标锁定**：LT 半按自由瞄准、全按锁定；十字键左右切换目标，击杀后选择附近最近的有效目标。推动右摇杆进入自由瞄准，保持到松开 LT。
- **瞄准与蹲姿修复**：锁定时不再叠加自由瞄准准星；修复车库镜头多余准星、取消瞄准丢失蹲姿，支持自定义步行键。
- **中文按键图标**：左上角提示随当前输入设备和设置中的手柄类型显示对应图标；修复方向提示多出的 L3。
- **大地图**：左摇杆/十字键平移，LT/RT 缩放，X/方块标点，LB/L1 开关图例；修复鼠标与手柄争抢、拖动跳动和旧光标坐标。所有缩放下均可到达四边与四角。
- **菜单与焦点**：B/圆圈返回上一级，暂停首页 B 返回游戏，Start 恢复游戏；修复过场切到桌面后鼠标被拉回，不新增过场暂停菜单。

配置见 [ClassicAxisVC.ini](gamefiles/data/ClassicAxisVC.ini)，完整操作与验证范围见 [Classic Axis VC](docs/CLASSIC_AXIS_VC.md)。本次已通过 Windows x64、librw D3D9、OpenAL、C++17 编译与隔离逻辑检查，完整游戏及实体手柄测试仍需继续。

当前仓库克隆命令：

```sh
git clone --recursive --branch miami https://github.com/LeoLu1226/reVC_CHS_FIX.git reVC
```

**旧版说明保留在下方**：历史下载地址与上游兼容性说明不代表本分支最新状态。本分支要求 **C++17（不是 C17）**，已配置 Premake；下文旧版“不要使用 C++11”是上游历史要求。CLEO 以本分支的支持与限制为准，并非全部脚本兼容，也不表示已同步全部最新版 SilentPatch。

移植来源：[Classic Axis](https://github.com/gennariarmando/classic-axis)、[Xbox Hands VC](https://github.com/gennariarmando/gtavc-xbox-hands)、[GInput VC](https://cookieplmonster.github.io/mods/gta-vc/#ginput)。中文术语参考 [GTAMODX 的 re3 介绍译文](https://gtamodx.com/mods/BmUYhBABACsQ)。原有署名、截图、链接、配置、构建说明、历史和许可均保留；[未经改写的旧 README](docs/README_LEGACY.md) 可供对照。


---

<img src="https://github.com/mrxenginner/reVC/blob/miami/res/images/logo_1024.png?raw=true" alt="reVC logo" width="200">

[![Build Status](https://img.shields.io/endpoint.svg?url=https%3A%2F%2Factions-badge.atrox.dev%2FGTAmodding%2Fre3%2Fbadge%3Fref%3Dmiami&style=flat)](https://actions-badge.atrox.dev/GTAmodding/re3/goto?ref=miami)
<a href="https://discord.gg/ERYg58ttcE"><img src="https://img.shields.io/badge/discord-join-7289DA.svg?logo=discord&longCache=true&style=flat" /></a>


本Fork基于reVC_CHS修复了以下问题：

1.修复汽车发动机的启动声音播放异常的问题
2.补全CHS版缺失的autoconf文件夹
3.修复CHS版护甲数字错位的问题
4.修复CHS版左上角提示信息背景颜色不正确的问题
5.补全CHS版缺失的shaders
6.删除CHS版多余源码副本
7.恢复了原版VC的血液屏幕效果
8.修复了霰弹枪换弹声音播放异常的问题
9.修复了开始新游戏时会重置鼠标灵敏度的问题
10.修复了鼠标水平竖直灵敏度不一致的问题
11.启用了PS2加载动画
12.启用任务重试
13.将全屏模式更改为无边框全屏
14.修复粒子物理由于帧数过高导致的BUG
15.修复切出游戏时鼠标被锁定的问题
&nbsp;
编译时记得右键解决方案资源管理器中的reVC，并将C语言调整为17版，否则会编译错误
&nbsp;
如果需要OpenGL方案请下载3.3.2的SDK https://github.com/glfw/glfw/releases/tag/3.3.2
确保目录如下: reVC/vendor/glfw-3.3.2.bin.WIN64
&nbsp;
如果方案中有OpenAL(oal)请将:
vendor/openal-soft/dist/Win64(或32，取决于你编译版本)/OpenAL32.dll
vendor/mpg123/dist/Win64(或32，取决于你编译版本)/libmpg123-0.dll
vendor/libsndfile/dist/Win64(或32，取决于你编译版本)/libsndfile-1.dll
这三个文件复制到游戏根目录中，否则游戏无法启动
 &nbsp;
************************************************************************
&nbsp;
# reVC的中文化支持和CLEO支持

汉化作者：Ova1122（gamefiles 中文文本与贴图来自无名汉化组）

中文已经支持，gamefiles文件夹里面已包含无名的文本和贴图，请复制到游戏目录。
CLEO已经支持，部分涉及读写内存的暂未实现，因为和原版不兼容。有需要的可以根据CLEO的源码自行添加，其他的应该都支持了。

## 汉化特性（CHSFont）

* 动态字库：任意中文 + 扩展平面（生僻字 U+30EDE「𰻞」、Emoji）都能显示，永不缺字
* 三种文本渲染模式（[Fonts] `TextRenderer=1/2/3`）：静态 CHINESE.TXD / GDI 动态字库 / DirectWrite（默认，最完善）
* 彩色表情符号（COLR/CPAL）与 emoji 右剪修复
* 可变字重：`NormalWeight` / `SlantWeight` / `RareWeight`（100–900，可自动保存回写 reVC.ini）
* GXT 热重载：修改任意语言文本约 1 秒自动生效（开发调试用）

## 文本渲染模式与字体配置（GDI / DirectWrite）

所有字体相关配置都在游戏目录的 `reVC.ini` 的 `[Fonts]` 段，**改完需重启游戏生效**（启动时读取）。

### 三种渲染模式

| `TextRenderer` | 模式 | 说明 |
|---|---|---|
| `3` | **DirectWrite（默认，推荐）** | 动态字库。任意中文 + 生僻字（𰻞 U+30EDE 等扩展平面）+ 彩色 Emoji（COLR/CPAL）+ 可变字重，全部支持 |
| `2` | **GDI** | GDI `GetGlyphOutlineW` 动态字库，兼容老机器；不支持彩色 Emoji 与可变字重轴 |
| `1` | **TXD（最老）** | 静态 `MODELS\CHINESE.TXD` + `Chinese.dat` 贴图字库（即 gamefiles/chinese_text_file 里那套），无动态能力 |

也兼容旧写法的字符串值（`TXD` / `GDI`），写错或缺失时自动回退到 DirectWrite。

> 以下示例中的 `<…>` 均为占位符，请替换为你**本机已安装**或**有权分发**的字体。本仓库不捆绑任何字体文件；只额外列了 Windows 自带字体作为"开箱可用"的参考。

### DirectWrite 模式（推荐配置示例）

```ini
[Fonts]
TextRenderer=3
NormalFonts=<主字体名>          ; 系统已安装的字体名，或 models 目录下的 .ttf（如微软雅黑填 msyh）
NormalBold=1                    ; 1 = 默认用粗体字重（700）
SlantFontFile=models\<斜体字体>.ttf   ; 斜体（意大利体）字体；可不配，缺省用主字体的伪斜体
SlantBold=0
GlyphHeight=56                  ; 字格高度（像素），越大笔画越细
RareFontFile=<主字体文件>,<补充字体…>  ; 兜底字体链（见下）
```

- **`RareFontFile` 兜底链**：逗号分隔多个字体文件，从左到右依次尝试。主字体**缺字形的任何码位**（生僻字、Emoji、韩文、BMP 缺字）都会按链查找，第一个能画出该字的字体生效——所以"永不缺字"靠的就是它。按需补充 Windows **自带**字体即可：
  - 彩色 Emoji：`C:\Windows\Fonts\seguiemj.ttf`（COLR/CPAL 彩色，Win8.1+ 自带）
  - 韩文：`C:\Windows\Fonts\malgun.ttf`
  - 生僻字（如 𰻞）：`C:\Windows\Fonts\SimsunExtG.ttf`
  - 主字体缺的简中字形：`C:\Windows\Fonts\msyh.ttc`（微软雅黑）
- **可变字重**：`NormalWeight=100~900`（对应 NormalFonts 的粗细，默认 400），`SlantWeight`、`RareWeight` 同理；`NormalBold=1` 时默认字重为 700。这些键会自动写回 `reVC.ini`（不需要手动补）。

### GDI 模式

```ini
[Fonts]
TextRenderer=2
NormalFonts=<主字体名>
SlantFontFile=models\<斜体字体>.ttf
GlyphHeight=56
RareFontFile=<主字体文件>,<补充字体…>
```

GDI 模式也能显示全部码位（超出 BMP 的走 stb_truetype 兜底链），只是没有彩色 Emoji 和字重轴。

### TXD 模式

```ini
[Fonts]
TextRenderer=1
```

需要把 `gamefiles/chinese_text_file/` 下的 `MODELS\CHINESE.TXD` 与 `Chinese.dat` 放进游戏目录对应位置（其余两种模式不需要它们）。

### GXT 热重载（开发调试）

改完 GXT 文本不用重启：游戏运行中保存 `TEXT\xx.GXT`（xx = 当前语言），约 1 秒后自动生效；切换语言会自动跟随新的语言文件；GXT 损坏时自动回滚不崩溃。仅影响文本，不影响 `[Fonts]`（字体配置仍要重启生效）。

### 调试日志

启动时会在游戏 exe 旁生成 `chsfont.log`，记录字体加载/渲染回退过程；字显示不出来时先看它。字体文件版权归各自作者所有，本仓库不包含任何字体文件。





## 简介

旧上游仓库提供 GTA III（[master](https://github.com/GTAmodding/re3/tree/master/)）和 GTA Vice City（[miami](https://github.com/GTAmodding/re3/tree/miami/)）的完整逆向源代码。

原项目曾在 Windows、Linux、FreeBSD 以及 x86、amd64、ARM、ARM64 上测试运行。图形可使用原版 RenderWare（D3D8），或重新实现的 [librw](https://github.com/aap/librw)（D3D9、OpenGL 2.1+、OpenGL ES 2.0+）；音频可使用 MSS（原版 GTA DLL）或 OpenAL。

旧版说明指出尚不能构建 PS2 或 Xbox 版本，有意参与者可联系原开发者。

## 安装

- reVC 需要 PC 原版游戏资源才能运行，必须拥有一份正版 GTA Vice City。以下保留旧版商店与构建链接（历史地址）：
- [原游戏商店链接](https://store.steampowered.com/app/12110/Grand_Theft_Auto_Vice_City/)。编译 reVC，或参考旧版列出的构建包：
  - [Windows D3D9 MSS 32 位](https://nightly.link/GTAmodding/re3/workflows/reVC_msvc_x86/miami/reVC_Release_win-x86-librw_d3d9-mss.zip)
  - [Windows D3D9 64 位](https://nightly.link/GTAmodding/re3/workflows/reVC_msvc_amd64/miami/reVC_Release_win-amd64-librw_d3d9-oal.zip)
  - [Windows OpenGL 64 位](https://nightly.link/GTAmodding/re3/workflows/reVC_msvc_amd64/miami/reVC_Release_win-amd64-librw_gl3_glfw-oal.zip)
  - [Linux 64 位](https://nightly.link/GTAmodding/re3/workflows/build-cmake-conan/miami/ubuntu-latest-gl3.zip)
  - [macOS 64 位](https://nightly.link/GTAmodding/re3/workflows/build-cmake-conan/miami/macos-latest-gl3.zip)
- 将下载的运行包解压到 GTA Vice City 游戏目录并运行 reVC。原说明中的 ZIP 包含可执行文件、更新与额外资源；OpenAL 版本还包含必需 DLL。源码 ZIP 本身不含已编译程序。


## 截图

![screen_ 1613087332](https://user-images.githubusercontent.com/1521437/107714111-f84f3200-6ccc-11eb-902e-d757481d579a.png)
![screen_ 1613086852](https://user-images.githubusercontent.com/1521437/107714115-fa18f580-6ccc-11eb-9de5-eb4cd04865d3.png)
![screen_ 1613086989](https://user-images.githubusercontent.com/1521437/107714103-f38a7e00-6ccc-11eb-88a3-c8c2033c51d6.png)
![screen_ 1613087193](https://user-images.githubusercontent.com/1521437/107714106-f4bbab00-6ccc-11eb-96a9-13821d9b9684.png)


## 改进

我们对原版游戏进行了多项修改和改进，可在 `src/core/config.h` 中配置；部分可在运行时切换，其他需要编译时选择。

* 修复大量大小 Bug。
* 用户文件（存档和设置）存放在 GTA 游戏根目录。
* 增加调试菜单（Ctrl-M），用于执行或修改各种内容。
* 增加调试摄像机（Ctrl-B 切换）。
* 支持旋转摄像机。
* Windows 支持 XInput 手柄。
* 岛屿间可取消加载画面（菜单中的“地图内存使用量”）。
* 渲染：
  * 宽屏支持，正确缩放 HUD、菜单与 FOV。
  * PS2 MatFX 车辆反射。
  * PS2 Alpha Test，改善透明材质。
  * Xbox 车辆渲染。
  * Xbox 世界光照贴图（需要 Xbox 地图）。
  * Xbox 行人边缘光。
  * Xbox 屏幕雨滴。
  * 更自由的颜色滤镜设置。
* 菜单：更多选项、手柄配置菜单等。
* 可加载其他平台的 DFF 和 TXD，但可能有性能损失。
* ……

## 待办事项

以下为原版 README 的开发方向，不表示本分支已经完成：

* 修复高帧率物理问题。
* 改善低端设备性能，尤其是 Raspberry Pi 的 OpenGL 图形层；欢迎有经验的开发者参与。
* [PS2 移植](https://github.com/GTAmodding/re3/wiki/PS2-port)。
* Xbox 移植（优先级较低）。
* 逆向剩余未使用与调试函数。
* 将 CodeWarrior 编译结果与原始二进制对比，提高还原准确性（工作繁琐）。

## Mod 支持

模型、纹理、操控参数、脚本等资源修改，在大多数情况下与原版 GTA 的 Mod 制作方式相同。

修改原版程序代码的 DLL/ASI、限制调整器通常不能直接使用。它们的部分功能已在 re3 中实现，例如 SkyGFX、GInput、SilentPatch、Widescreen Fix 的部分功能；其他功能可以通过 `config.h` 提高限制，或重写后直接集成到源码中。对于这种不便，原项目表示歉意。

原版此处将 CLEO 与不兼容代码 Mod 一并列出；本中文分支已加入 CLEO 支持，直接操作原版内存或地址的脚本仍存在兼容限制。

## 从源代码编译

使用 Premake 时，可将 `GTA_VC_RE_DIR` 环境变量指向游戏根目录，通过编译后脚本复制可执行程序。

旧版上游克隆命令：`git clone --recursive -b miami https://github.com/GTAmodding/re3.git reVC`。然后 `cd reVC` 进入目录。本分支地址请使用本页开头的新命令。

<details><summary>Linux Premake</summary>

Linux 使用 Premake 请参考：[在 Linux 上编译](https://github.com/GTAmodding/re3/wiki/Building-on-Linux)

</details>

<details><summary>Linux Conan</summary>

安装 Python 与 Conan，然后执行旧版构建命令（依赖版本以工程要求为准）：
```
conan export vendor/librw librw/master@
mkdir build
cd build
conan install .. reVC/master@ -if build -o reVC:audio=openal -o librw:platform=gl3 -o librw:gl3_gfxlib=glfw --build missing -s reVC:build_type=RelWithDebInfo -s librw:build_type=RelWithDebInfo
conan build .. -if build -bf build -pf package
```
</details>

<details><summary>FreeBSD</summary>

FreeBSD 使用 Premake 请参考：[在 FreeBSD 上编译](https://github.com/GTAmodding/re3/wiki/Building-on-FreeBSD)

</details>

<details><summary>Windows</summary>

旧版以 Visual Studio 2015/2017/2019 为例；当前新增代码应使用符合工程要求的工具集：
- 运行根目录对应的 `premake-vsXXXX.cmd`。
- 在 Visual Studio 中打开 `build/reVC.sln` 并编译解决方案。

旧文记载微软已停止提供 DX9 SDK 下载，可参考归档版本： https://archive.org/details/dxsdk_jun10

**Windows 选择 OpenAL 时**，请阅读 [在 Windows 上运行 OpenAL 构建](https://github.com/GTAmodding/re3/wiki/Running-OpenAL-build-on-Windows).
</details>

> :information_source: Premake 的 `--lto` 选项用于链接时优化（LTO）。

> :information_source: 各种配置开关见 [config.h](https://github.com/GTAmodding/re3/tree/miami/src/core/config.h)，建议查阅。

> :information_source: 项目使用自行开发的 RenderWare 替代引擎 [librw](https://github.com/aap/librw/)。它作为 Git 子模块提供，也可以通过 `LIBRW` 环境变量指定自己的 librw 路径。

如有需要，也可使用 CodeWarrior 7 与 `codewarrior/reVC.mcp` 工程编译，需要原版 RW34 库和 DX8 SDK。相比 MSVC，此构建方式不稳定，主要用作参考。


## 贡献代码

以下保留原项目的贡献约定：除 Linux／跨平台框架／兼容层代码外，未放在预处理条件（如 `FIX_BUGS`）内的代码，均来自原始二进制的逆向。自定义代码应由预处理条件封装，或属于上述跨平台部分。

原项目接受的 PR 类型：

- 至少在一部 GTA 中存在的新功能；若 III/VC 原本没有，不要求来自反编译。
- 游戏、界面或体验修复；原始游戏代码的 Bug 修复应位于 `FIX_BUGS` 条件下。
- 尚未逆向的平台专用代码及未使用代码。
- 使逆向代码更易理解、更准确，例如更接近原始汇编生成方式。
- 新的跨平台框架／兼容层及其改进。
- 原游戏支持语言的翻译修复。
- 提高代码可维护性的修改。

原项目提供 [代码风格说明](https://github.com/GTAmodding/re3/blob/master/CODING_STYLE.md)，但执行并不严格。

旧版要求“不要使用 C++11 或更新特性”。这是保留的历史要求；当前分支的构建要求和已集成代码以本页开头及工程配置为准。

## 历史

re3 始于 2018 年春，最初用于在游戏内测试逆向得到的碰撞与物理代码，通过 DLL 将原游戏的单个函数替换成逆向实现。

项目开发一段时间后停滞约一年，于 2019 年 5 月恢复并上传 GitHub。当时 aap 已逆向约一万行，估计完整游戏约有 20 万至 25 万行代码。Fire_Head、shfil、erorcun、Nick007J 依次加入，Serge 稍后加入；2019 年夏进展迅速，此后速度放缓。

疫情初期大家居家，有更多时间参与。2020 年 4 月，项目终于生成独立可执行程序，当时代码约 18 万行。继续修复和完善后，2020 年 5 月初开始 reVC：它直接基于 re3，而不是重新从 DLL 替换函数起步。经过数月稳定开发，团队于当年 12 月认为 reVC 已完成。

旧版 README 随后记载开始了 reLCS，且当时仍在开发；此处保留其历史描述，不代表当前进度。

## 许可

原项目表示不认为自己有权为这些代码授予许可。代码仅用于教育、文档和 Mod 制作目的；不鼓励盗版或商业用途。请让衍生作品保持开源，并保留适当署名。
