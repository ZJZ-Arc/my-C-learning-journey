# my-C-learning-journey

我的 C 语言学习记录。每学完一周课程，就在对应目录里放上练习代码。

## 目录结构

| 路径 | 内容 |
| --- | --- |
| `week1/` | 入门：第一个程序、变量、`printf`、基本运算符 |
| `week2/` | 计算：变量与初始化、`scanf` 输入、常量、`/` 与 `%` |
| `week3/` | 条件与函数：`if` / `else`、关系与逻辑运算、奇偶与闰年判断、把重复计算写成函数 |
| `week4/` | 数组与函数拆分：下标、遍历、求和 / 平均 / 最大、把统计逻辑拆成函数 |
| `week5/` | 字符与字符串、指针入门：`char`、`\0`、`fgets`、`&` / `*`、指针参数、用指针遍历数组 |
| `tools/gcc-gbk.c` | gcc 转发器的源码（见下文，可选但推荐） |

各周文件：

- `week1/hello.c` — Hello World
- `week1/111.c` — 后来改成的传参小实验：`change(value)` 改不到外面，只有指针才能改原变量
- `week1/d.c` — 取余运算符 `%` 的尝试（`372 % 72`）
- `week1/calculate.c`、`week1/change.c` — 找零计算 + 输入校验 + 暂停
- `week2/temperature.c` — 摄氏度 → 华氏度
- `week2/time.c` — 秒数拆成时 / 分 / 秒
- `week2/average.c` — 三科成绩平均分（保留两位小数）
- `week2/discount.c` — 常量单价 + 折扣：算总价和折后价
- `week2/time2.c` — 两个时刻的时 / 分差：分钟不够减时向小时借 1
- `week3/relationship.c` — 关系运算符的结果：`5 >= 3` 打印出 1
- `week3/test.c` — 优先级实验：`i<j==j<k` 实际算的是 `(i<j)==(j<k)`
- `week3/bijiao.c` — 比较两个整数取较大者
- `week3/jiou.c` — 判断奇偶，并检查 `scanf` 的返回值
- `week3/nianfen.c` — 闰年判断（`%4`、`%100`、`%400`）
- `week3/addition.c` — 三位数拆成百 / 十 / 个位再求和
- `week3/change2.c` — 找零：票面大于金额才找钱，否则提示钱不够
- `week3/time2.c` — 时间差那题的副本（内容与 `week2/time2.c` 相同）
- `week3/maxhour.c` — 第一个自制函数：`calculate_maxnum` 返回较大数
- `week3/jilu.c` — 学习时长记录：`calculate_average` / `calculate_max_hours` 两个函数 + 时长范围校验
- `week4/shuzu.c` — 学习时长记录：天数与每小时时长都做输入校验，最后输出总时长、平均、最长
- `week4/shuzu2.c` — 同一题换个写法：把「求总时长」「求最长」抽成 `calculate_total` / `calculate_max_hours`
- `week4/purchse.c` — 购物小票：价格数组求总价、均价、最高价，并统计不低于 100 元的件数
- `week5/zifu.c` — 读入 3 个字符再逐个打印（`scanf(" %c")` 里的空格用来吃掉换行）
- `week5/shuzu2.c` — 用 `scanf("%19s %19s")` 读两个单词当姓和名
- `week5/zifuchuan.c` — `fgets` 读一整行名字，再手动把结尾的 `\n` 改成 `\0`
- `week5/zifuchuan2.c` — 文本统计：数出小写字母、大写字母、数字各有几个
- `week5/xinxin.c` — 嵌套循环打印倒三角星号
- `week5/zhizheng.c` — 指针第一课：`&` 取地址、`*` 读写变量（`set_zero` 还没写）
- `week5/zhizhen2.c` — 指针和数组：用 `*(nums + i)` 遍历、求和、原地每个元素加 5
- `week5/zhizhen3.c` — 指针参数：`swap(&a, &b)` 通过地址修改调用者的变量
- `week5/zhizhen4.c` — 指针版求最大值（求法还有边界问题，待改）

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
- [x] 第 3 周：`if` / `else`、关系与逻辑条件、奇偶 / 闰年 / 找零判断，函数拆分入门
- [x] 第 4 周：数组下标与遍历、求和 / 平均 / 最大值、把统计拆成函数
- [x] 第 5 周：`char` 与字符数组、字符串结束符 `\0`、`fgets`、指针的 `&` / `*` 与指针参数
