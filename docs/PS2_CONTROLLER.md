# PS2 手柄作弊码与模拟油门

## 使用方法

- 使用 XInput 兼容手柄；PlayStation 手柄经 XInput 映射后也可使用。
- 在游戏过程中依次按下作弊码，每个按键按下后松开。方向使用十字键。
- 按键按手柄实际位置识别，不随 Standard / Classic 操作布局改变。
- Xbox 对应关系：△ = Y、○ = B、× = A、□ = X、L1 = LB、L2 = LT、R1 = RB、R2 = RT。
- LT / RT 超过 30/255 才计为按下，按住不会重复录入；暂停菜单内不录入，进入暂停会清空未完成的序列。
- 在 Standard Controls 下，RT 为模拟油门、LT 为模拟刹车／倒车。前 30/255 行程为死区，剩余行程线性映射到 0～255；半按不再变成全油门。键盘按键仍输出全量，Classic 布局保持原有油门按键。
- 使用现有游戏内作弊效果与提示；这不是 ASI 插件，无需另装 GInput。

## 按键表

参考 [GInput 官方说明](https://silentsblog.com/mods/gta-vc/)及其下载包中的 `docs/cheat_list_ps3.html`。以下为本分支接入的序列。

| 效果 | 依次按下 |
| --- | --- |
| Weapons set 1 | R1 R2 L1 R2 ← ↓ → ↑ ← ↓ → ↑ |
| Weapons set 2 | R1 R2 L1 R2 ← ↓ → ↑ ← ↓ ↓ ← |
| Weapons set 3 | R1 R2 L1 R2 ← ↓ → ↑ ← ↓ ↓ ↓ |
| Health cheat | R1 R2 L1 ○ ← ↓ → ↑ ← ↓ → ↑ |
| Armour cheat | R1 R2 L1 × ← ↓ → ↑ ← ↓ → ↑ |
| Remove Wanted Level | R1 R1 ○ R2 ↑ ↓ ↑ ↓ ↑ ↓ |
| Raise Wanted Level | R1 R1 ○ R2 ← → ← → ← → |
| Sunny weather | R2 × L1 L1 L2 L2 L2 △ |
| Extra Sunny weather | R2 × L1 L1 L2 L2 L2 ↓ |
| Cloudy weather | R2 × L1 L1 L2 L2 L2 □ |
| Rainy weather | R2 × L1 L1 L2 L2 L2 ○ |
| Foggy weather | R2 × L1 L1 L2 L2 L2 × |
| Faster clock | ○ ○ L1 □ L1 □ □ □ L1 △ ○ △ |
| Explode all vehicles | R2 L2 R1 L1 L2 R2 □ △ ○ △ L2 L1 |
| Pedestrians fight | ↓ ← ↑ ← × R2 R1 L2 L1 |
| Pedestrians attack the player | ↑ ↓ ↑ ↑ × R2 R1 L2 L2 |
| All pedestrians carry weapons | R2 R1 × △ × △ ↑ ↓ |
| Increase gameplay speed | △ ↑ → ↓ L2 L1 □ |
| Decrease gameplay speed | △ ↑ → ↓ □ R2 R1 |
| Wheels only | △ L1 △ R2 □ L1 L1 |
| Cars fly | → R2 ○ R1 L2 ↓ L1 R1 |
| Perfect handling | △ R1 R1 ← R1 L1 R2 L1 |
| Show Media Attention stat | ○ L1 ↓ L2 ← × R1 L1 → × |
| Vercetti's gang becomes girls with M4 | → L1 ○ L2 ← × R1 L1 L1 × |
| Commit suicide | → L2 ↓ R1 ← ← R1 L1 L2 L1 |
| All traffic lights are green | → R1 ↑ L2 L2 ← R1 L1 R1 R1 |
| Crazy traffic | R2 ○ R1 L2 ← R1 L1 R2 L2 |
| All cars are pink | ○ L1 ↓ L2 ← × R1 L1 → ○ |
| All cars are black | ○ L2 ↑ R2 ← × R1 L1 ← ○ |
| Spawn Rhino | ○ ○ L1 ○ ○ ○ L1 L2 R1 △ ○ △ |
| Spawn Bloodring Banger #1 | ↓ R1 ○ L2 L2 × R1 L1 ← ← |
| Spawn Bloodring Banger #2 | ↑ → → L1 → ↑ □ L2 |
| Spawn Romero's Hearse | ↓ R2 ↓ R1 L2 ← R1 L1 ← → |
| Spawn Love Fist's Limo | R2 ↑ L2 ← ← R1 L1 ○ → |
| Spawn Trashmaster | ○ R1 ○ R1 ← ← R1 L1 ○ → |
| Spawn Sabre Turbo | → L2 ↓ L2 L2 × R1 L1 ○ ← |
| Spawn Caddy | ○ L1 ↑ R1 L2 × R1 L1 ○ × |
| Spawn Hotring Racer #1 | R2 L1 ○ → L1 R1 → ↑ ○ R2 |
| Spawn Hotring Racer #2 | R1 ○ R2 → L1 L2 × × □ R1 |
| Change appearance | → → ← ↑ L1 L2 ← ↑ ↓ → |
| Play as Lance Vance | ○ L2 ← × R1 L1 × L1 |
| Play as Candy Suxxx | ○ R2 ↓ R1 ← → R1 L1 × L2 |
| Play as Ken Rosenberg | → L1 ↑ L2 L1 → R1 L1 × R1 |
| Play as Hilary King | R1 ○ R2 L1 → R1 L1 × R2 |
| Play as Jezz Torent | R1 L2 R2 L1 → R2 ← × □ L1 |
| Play as Phil Cassidy | → R1 ↑ R2 L1 → R1 L1 → ○ |
| Play as Sonny Forelli | ○ L1 ○ L2 ← × R1 L1 × × |
| Play as Mercedes Cortez | R2 L1 ↑ L1 → R1 → ↑ ○ △ |
| Play as Dick | ↓ L1 ↓ L2 ← × R1 L1 × × |
| Play as Ricardo Diaz | L1 L2 R1 R2 ↓ L1 R2 L2 |
| Cars drive on water | → R2 ○ R1 L2 □ R1 R2 |
| Changes several vehicles' attributes | R1 × △ → R2 □ ↑ ↓ □ |
| Pedestrians get in your car | ○ → ↑ L1 □ R1 |
| Boats fly | R2 ○ ↑ L1 → R1 → ↑ □ △ |
| Women follow Tommy | ○ × L1 L1 R2 × × ○ △ |
| Tommy smokes a cigarette | △ □ × ○ R1 R2 R1 R2 |
| Fat Tommy | L2 △ L2 × ↑ ↓ ← → |
| Skinny Tommy | L2 △ L2 × ← → ↑ ↓ |

前 55 项为 PS2 序列，最后三项是 GInput 为 PC 效果提供的手柄扩展序列。
原 reVC 中误用的 GTA III 按键表已替换；不添加 Vice City 原版没有的金钱作弊码。

## 复活血量

新游戏基础上限保持 100。读取旧存档和死亡／被捕复活时，将遗留的 250、255 上限恢复为 100；旧 255 上限获得奖励后溢出的 49、99 继续分别恢复为 150、200。
正常的 150／200 奖励和其他自定义上限保留。存档结构不变，修正后的上限会在下次正常保存时写入。

## 实现与验证

- 合并键盘、鼠标、手柄输入时保留 L2/R2 压力值，避免被按钮逻辑提升为 255。
- 作弊码使用合并前的手柄状态；暂停、新游戏清理输入状态，回放不触发手柄作弊。
- `tests/test_pad_input.py` 从实际 `Pad.cpp` 提取输入合并、油门、刹车、边沿识别和序列匹配方法编译运行。作弊效果使用桩函数，测试不替代游戏场景验证。
- 在 Visual Studio x64 开发者命令行运行 `python tests/test_pad_input.py`；其他平台可设置 `CXX` 使用 C++17 编译器。
- 本次通过 Release x64 D3D9/OpenAL 修改文件编译及完整程序链接，以及输入与血量回归测试。MSBuild 文件跟踪组件在当前受限环境报权限错误，使用已有构建参数直接调用 MSVC 编译器／链接器完成增量构建。
- 尚未进行实体手柄驾驶、全部作弊效果、旧存档死亡复活的游戏内实测。
