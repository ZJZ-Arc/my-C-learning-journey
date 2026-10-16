# my-C-learning-journey

我的 C 语言学习记录。每学完一周课程，就在对应目录里放上练习代码。

## 目录结构

| 路径 | 内容 |
| --- | --- |
| `week1/` | 入门：第一个程序、变量、`printf`、基本运算符 |
| `week2/` | 计算：变量与初始化、`scanf` 输入、常量、`/` 与 `%` |
| `.vscode/` | VS Code 的编译 / 调试 / 运行配置 |
| `tools/gcc-gbk.c` | gcc 转发器的源码（见下文，可选但推荐） |

各周文件：

- `week1/hello.c` — Hello World
- `week1/111.c` — 最简单的一行输出
- `week1/d.c` — 取余运算符 `%` 的尝试（`372 % 72`）
- `week1/calculate.c`、`week1/change.c` — 找零计算 + 输入校验 + 暂停
- `week2/temperature.c` — 摄氏度 → 华氏度
- `week2/time.c` — 秒数拆成时 / 分 / 秒
- `week2/average.c` — 三科成绩平均分（保留两位小数）

## 怎么编译运行

### 方式 1：VS Code（推荐）

打开本目录作为工作区，然后：

| 操作 | 效果 |
| --- | --- |
| `Ctrl+Shift+B` | 只编译当前文件 |
| `F5` | 编译并调试（会弹出独立控制台窗口，可输入、中文正常） |
| Code Runner 的 ▶ | 编译后在终端里运行 |

编译产物（`.exe`）与源文件同目录，已被 `.gitignore` 排除。

### 方式 2：命令行

```powershell
cd week2
gcc average.c -o average.exe      # 注意：见下文的编码与路径限制
.\average.exe
```

## 开发环境与 gcc 转发器

- 系统：Windows，中文用户名，控制台代码页 **936 (GBK)**
- 编译器：MSYS2 UCRT64 的 **gcc 16.2.0**（`C:\msys64\ucrt64\bin\gcc.exe`）
- 实际调用的是转发器 `gcc-gbk.exe`（源码在 `tools/gcc-gbk.c`），
  它把参数转发给真正的 gcc，并额外处理四件事：

| # | 它做的事 | 不这么做会怎样 |
| --- | --- | --- |
| 1 | 补 `-finput-charset=UTF-8 -fexec-charset=GBK` | exe 里存 UTF-8 字节，在 936 控制台下中文乱码 |
| 2 | 补 `-static` | exe 依赖 MSYS2 的 DLL，拷到别处打不开 |
| 3 | 把 `PATH` 前置 `C:\msys64\ucrt64\bin` | gcc 的子程序 `cc1.exe` 找不到 DLL，**静默退出 1、无任何报错** |
| 4 | 把 `TEMP/TMP` 指向 `C:\msys64\tmp`（纯 ASCII） | 汇编器报 `can't create ...\ccXXXX.o`（中文路径问题） |
| 5 | `-o` 指向中文路径时，先输出到 ASCII 临时目录再搬回 | 链接器报 `cannot open output file ...: No such file or directory` |

自己编译转发器：

```powershell
gcc -O2 -static -o gcc-gbk.exe gcc-gbk.c -lshell32
```

## 编码：为什么 exe 里必须是 GBK

**输出的字节编码，必须和"最终读它的那一方"一致。**

| 运行方式 | 谁在解码输出 | 期望的编码 |
| --- | --- | --- |
| 双击 exe | 控制台（代码页 936） | GBK ✅ |
| VS Code 终端 / PowerShell | 控制台（代码页 936） | GBK ✅ |
| F5 调试（`externalConsole: false`） | 调试器管道（UTF-8） | UTF-8 ⚠️ |
| F5 调试（`externalConsole: true`） | 独立控制台窗口（936） | GBK ✅ |

所以本项目统一用 **GBK**，并且 `.vscode/launch.json` 里设了
`"externalConsole": true`，让 F5 也走真实控制台窗口（既能输入，中文也正常）。

判断一个 exe 是什么编码：

```powershell
.\你的程序.exe | Format-Hex | Select-Object -First 2
```

- 首字节 `E4`/`E5`/`E8` 开头 → UTF-8（在 936 控制台下会乱码）
- 首字节 `C7`/`CA`/`B0` 这类成对高位字节 → GBK ✅

## 常见坑速查

| 现象 | 原因 | 解决 |
| --- | --- | --- |
| 中文乱码 | exe 与解码方编码不一致 | 用转发器编译（GBK） |
| 双击后窗口一闪而过 | 程序结束，窗口随之关闭 | 结尾加暂停（见下） |
| 加了 `getchar()` 仍然一闪而过 | `scanf` 残留的回车被立刻读走 | 先清缓冲再等按键 |
| 程序"算对了但没输出" | 语句顺序错（例如暂停放在输出之前） | 按执行顺序从上到下排列 |
| 程序输出 0 或怪值 | 变量未初始化 / `scanf` 失败未检查 | 初始化变量 + 检查 `scanf` 返回值 |
| `%lf` 配 `int`、`%d` 配 `double` 却"能编译" | 类型与格式符不匹配 | 打开 `-Wall`，看 `-Wformat` 警告 |
| F5 时敲键盘程序没反应 | 输入接在调试器管道上 | `"externalConsole": true` |
| 输出到中文目录报 `cannot open output file` | 链接器无法处理非 ASCII 路径 | 用转发器，或改用 ASCII 目录 |

### 暂停的标准写法

```c
/* 先清掉当前行残留（scanf 留下的回车），再等一次真正的回车 */
int c;
while ((c = getchar()) != '\n' && c != EOF) { }
printf("按回车键退出...");
getchar();
```

**放在所有输出之后、`return 0;` 之前。**

### 输入校验的标准写法

```c
if (scanf("%d", &n) != 1) {
    printf("输入无效\n");
    return 1;
}
```

`scanf` 返回**成功读到的项数**，不检查的话失败时会拿未初始化的垃圾值继续算，
输出看起来"正常"但结果是假的。

## 进度

- [x] 第 1 周：变量、`printf`、基本运算
- [x] 第 2 周：变量与初始化、`scanf`、常量、整数除法与取余
- [ ] 第 3 周
