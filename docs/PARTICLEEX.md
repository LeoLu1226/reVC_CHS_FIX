# ParticleEx for reVC / 原生粒子系统移植

**简体中文** | [English](#english)

本分支按 [Fire_Head / ParticleEx](https://github.com/Fire-Head/ParticleEx) 的 **VCParticleRE** 实现移植，源码快照为 `d4a816d24877dcb6c6781197636df42650576dea`。默认保持 PC 粒子，不需要安装 ASI。

## 安装与切换

将 `gamefiles/ParticleEx` 整个目录复制到游戏根目录，与 `reVC.exe` 同级。原有 `models/particle.txd` 和 `data/particle.cfg` 仍需保留。

退出游戏后，在游戏实际使用的 `reVC.ini` 中设置：

```ini
[ParticleEx]
System=0
```

| System | 模式 |
| --- | --- |
| 0 | PC（默认，原有实现） |
| 1 | PS2（VC） |
| 2 | Xbox（VC） |
| 3 | Xbox+III（上游 VC Xbox 火焰与 GTA III Xbox 爆炸组合） |

修改后重新启动游戏。这里的 `3` 是上游 VC 的 **Xbox+III**，不是 re3 分支的 PS2+Xbox 模式。所选模式的配置或纹理缺失、配置损坏、必要纹理缺失时，启动回退到 PC，并记录日志。PC 本身仍需要原版游戏资源。

## 效果与适配

- 三套 VC 专用的粒子配置、纹理、创建、更新和渲染逻辑。PS2 83 种粒子；两套 Xbox 各 84 种，额外支持移动车辆火焰。
- PS2 的烟雾、蒸汽、扬尘等效果；场景 2dfx／粒子对象使用所选引擎，保留 VC 自己的生成逻辑。
- Xbox 的地面、人物、车辆火焰，移动火焰及对应的烟雾调整。燃烧瓶火焰围绕实际火源分布；静止车辆火焰使用各自的游戏计时，避免车辆共享计时器。
- Xbox+III 的额外爆炸效果。喷火器仍按 VC 的生成逻辑使用所选粒子效果，不套用 GTA III 专有的喷射代码。
- VC 的屏幕水滴／血滴、热浪、远景船只、可射击海鸥、弹壳音效和录像粒子类型映射。
- 消防栓：PC／PS2 5 秒，Xbox／Xbox+III 15 秒。修正远处到期的粒子对象被再次加入活动列表的问题。
- Console 粒子动画、旋转、淡出按 30 Hz 更新，场景发射器每步更新一次；PC 保留分支现有帧率修复。
- 使用 reVC 原生粒子对象和指针，不依赖原版 EXE 的地址或二进制布局；支持 C++17、32／64 位构建。
- 每套 console 引擎保留 1000 个粒子的容量；只加载所选 console 资源。配置采用完整条目校验，渲染帧索引按实际纹理数组限制。

原仓库已有的爆炸地面焦痕修复继续保留。没有将 GTA III 独有的船只、水洼、车轮等分支强行套用到 VC。

## 可选设置

以下选项同样位于 `[ParticleEx]`，修改后重启生效，布尔值使用 `0`／`1`：

```ini
DisableVanillaWaterDrop=0
DisableVanillaBloodDrop=0
RestoreXboxHydrantWaterSpray=1
FixWaterDropsInInteriors=1
FixFlame5Bug=0
```

- `DisableVanillaWaterDrop`／`DisableVanillaBloodDrop`：在 console 模式隐藏原生屏幕水滴／血滴，默认显示。
- `RestoreXboxHydrantWaterSpray`：恢复 Xbox 模式消防栓额外的喷水绘制，默认开启；不改变持续时间。
- `FixWaterDropsInInteriors`：console 模式允许室内水景产生屏幕水滴，默认开启。PC 模式保留原行为。
- `FixFlame5Bug`：允许使用原本被 `flame1` 替代的 `flame5` 纹理；默认关闭以保持上游通常效果。对使用 Xbox 动画火焰的类型没有替换作用。

本移植读取 `reVC.ini`，不读取上游 `VCParticleEx.ini`。原版 EXE 地址补丁、调试编辑器、`.pobj` 导入导出、外部 Waterdrops 插件钩子及游戏内即时切换不包含在本次移植内。切换需重启，避免销毁仍被场景对象引用的粒子。

## 验证范围

三套配置均通过独立 C++17 读取测试：正常输入、空文件、错误类型名、过长行、截断、额外条目、缺文件、无末尾换行；失败不会覆盖当前有效配置。已核对随附 TXD 中的必要纹理。Windows x64 D3D9/OpenAL、x86 D3D9/Miles Release 编译通过。

尚未进行真实游戏画面测试。建议分别检查三套模式的烟雾、雨水、起火车辆、燃烧瓶、喷火器、爆炸、消防栓、室内水景、海鸥、录像及存档／任务重试，并比较 30／60 FPS。

## English

Native adaptation of **VCParticleRE** from [Fire_Head / ParticleEx](https://github.com/Fire-Head/ParticleEx), revision `d4a816d24877dcb6c6781197636df42650576dea`. PC remains the default. Copy `gamefiles/ParticleEx` beside `reVC.exe`, retaining the original PC assets, then set `[ParticleEx] System` in `reVC.ini`:

- `0`: PC; `1`: PS2 VC; `2`: Xbox VC; `3`: Xbox+III (the upstream VC/Xbox and GTA III/Xbox explosion combination).
- Restart to apply. **Mode 3 differs from re3's PS2+Xbox mode.** Missing/invalid selected console resources fall back to PC.

Includes the three console engines and assets, VC-specific smoke/scene effects, Xbox stationary/moving fire, centred molotov fire, Xbox+III explosions, screen droplets, heat haze, distant ships, shootable birds and replay type conversion. VC's flamethrower emission logic is retained. Hydrants last 5 seconds in PC/PS2 and 15 seconds in Xbox/Xbox+III. Existing scorch fixes remain intact.

Console engines use native reVC particle objects, 1000-particle pools and 30 Hz animation/fade/rotation ticks. Only the selected console resources are loaded. Config validation and raster bounds checks avoid unsafe original executable assumptions; C++17 and 32/64-bit builds are supported.

Optional startup settings in the same section: `DisableVanillaWaterDrop=0`, `DisableVanillaBloodDrop=0`, `RestoreXboxHydrantWaterSpray=1`, `FixWaterDropsInInteriors=1`, `FixFlame5Bug=0`. Droplet visibility/interior options apply to console modes; the hydrant spray option affects Xbox drawing, not duration. The flame5 option retains its upstream default of off.

The original `VCParticleEx.ini`, EXE hooks, external Waterdrops hooks, developer editors, `.pobj` tools and live switching are not included. Invalid resources do not replace the original game's required assets. Validation covers real config-parser cases, texture completeness and x64 OpenAL/x86 Miles Release builds; actual gameplay remains to be tested.

Credit and resource provenance: Fire_Head; assets from the same revision's `Release/VC/ParticleEx` directories. The upstream snapshot has no separate LICENSE file; this port does not assert an additional license for upstream code or assets.
