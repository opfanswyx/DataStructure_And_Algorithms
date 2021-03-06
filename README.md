# 数据结构与算法

[《数据结构与算法》](http://www.tup.tsinghua.edu.cn/booksCenter/book_06931402.html)学习记录 :pushpin: :pushpin:

计划：
1. 巩固之前所学习的，同时对代码进行详细注释
2. 对一些系统性的知识写文章，进行系统性的总结，按章节来
3. 矩阵、广义表、图的知识学习
4. 剑指offer一书的习题
5. 刷leetcode题

## 线性表
* * [x] 顺序存储
* * [x] 链式存储
* * [x] 双向链表
* * [x] 循环链表(约瑟夫环)
* * [ ] 静态链表
* * [ ] 双向循环链表
## 栈
* * [x] 顺序栈
* * [x] 链式栈
* * [x] 栈递归
## 队列
* * [x] 顺序队列
* * [x] 链式队列
* * [x] 循环队列
## 串
* * [x] 串结构
* * [x] 模式匹配
  + * [x] 朴素匹配
  + * [x] kmp算法
  + * [ ] BF算法
  + * [x] AC自动机
## 数组和广义表
* * [ ] 矩阵
  * * [ ] 特殊矩阵(对称矩阵,三角矩阵,对角矩阵)
  * * [ ] 稀疏矩阵(转置,十字链表)
* * [ ] 广义表
## 树
* * [x] 二叉树
* * [ ] 线索二叉树
* * [ ] 赫夫曼树
## 图
* * [ ] 遍历
  * * [ ] 广度优先BFS
  * * [ ] 深度优先DFS
* * [ ] 最小生成树
  * * [ ] Prim(普里姆)算法
  * * [ ] Kruskal(克鲁斯卡尔)算法
* * [ ] 最短路径
* * [ ] 拓扑排序
* * [ ] 关键路径
## 查找
* * [x] 顺序表查找-监视哨兵
* * [x] 有序表查找
  * * [x] 折半查找
  * * [x] 插值查找
  * * [x] 斐波那契查找
* * [x] 索引顺序查找
* * [x] 二叉排序树
* * [x] 平衡二叉树
* * [ ] 红黑二叉树
* * [ ] B/B-/B+树
* * [x] 字典树
* * [x] 哈希表
## 排序
* * [x] 交换排序
  * * [x] 冒泡
  * * [x] 快速排序
* * [x] 插入排序
  * * [x] 直接插入排序
  * * [x] 折半插入排序
  * * [x] 希尔排序
* * [x] 选择排序
  * * [x] 简单选择排序
  * * [x] 堆排序
* * [x] 归并排序
  * * [x] 多线程归并排序
* * [x] 基数排序
* * [x] 磁盘外部排序
  * * [x] 多路平衡归并
## 其他
* * [x] 缓存淘汰算法
* * [x] 跳跃表
* * [x] 位图法

# 算法复杂度
## 对数阶O(logn)
```c
int number=1;
while(number<n){
number=number*2;
...
}
```
## 平方阶O(n^2)
```c
for(int i=0;i<n;i++){   
      for(int j=0;j<n;j++){
         ... 
      }
  }
```