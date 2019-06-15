# 树 (tree)

树的表现方法很多，人的思维里天然存在着各种树结构。

### 树的最基本构成元素：

1.  vertex: 或者叫 node, 就是最基本的可以附带信息的对象。

2.  edge: 两个 vertices 之间的连接。

3.  path: 一个 vertex 的 list, 相邻vertex 之间必须有边相连。一棵树的任意两个节点之间有且仅有一个 path。
4.  internal node: 有子节点的节点。
5.  external node: 没有子节点的节点。



#### 二叉树

重要定义： 

二叉树， 可以是一个 external node;

​				或者是一个有一对二叉树子节点的 internal node。分别叫做左子二叉树和右子二叉树。

二叉树最便捷的三个操作：

1.  在底部添加一个新 node;
2.  删除一片叶子；
3.  合并两棵树，我们只需要创建一个新 root， 然后左右link 分别指向两棵树。

二叉树的数学性质：

1.  有 N 个 internal nodes 的二叉树 有 N + 1 个 external nodes;

2.  有 N 个 internal nodes 的二叉树 有 2N 个 单向边。N-1 条边指向 internal nodes, N+1 条边指向 external nodes。

从而有几个数量上的定义：

1. level: 从 node 到 root 需要经过几条边？
2. heigth: max( level(any node));
3. path length = sum( length( any node));

再多几条数学性质：

3. 有 N 个 internal nodes 的二叉树，其 path_length (external nodes ) = path_length(internal nodes) + 2N。
4.  lg( N ) <= height ( BinTree(internal nodes == N)) <=  N - 1;
5.  for bin tree with N internal nodes, N(log(N/4)) < path_length(internal nodes) < N(N-1)/2;