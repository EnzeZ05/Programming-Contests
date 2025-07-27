P2292 [HNOI2004] L 语言
https://www.luogu.com.cn/problem/P2292

## 状压 bitset‑DP 思路（字典串长度 < 20）

设  
* `dp_i`：当前处理到 **索引 `i`（0‑based）** 时，要求子串 `[0, i‑1]` 均已完全匹配；  
* `mask`：滑动窗口 `[i‑20, i‑1]` 内的匹配状态（20 bit）；  
* `p_i`：把 `s[i]` 沿 AC 自动机转移后，**可一次性结束的字典词集合**（bitset）。

转移规则  

1. **存在匹配：**  
   $$\bigl((\text{mask} \ll 1) \mid p_i \bigr) > 0$$  
   则  mask = (mask << 1) | 1, 滑窗右移并把当前位标 1

2. **不存在匹配：**
    $$mask <<= 1$$, 仅滑窗右移
    << 为左移，| 为按位或。窗口恒长 20，所以 mask 随时保持 20 bit。
