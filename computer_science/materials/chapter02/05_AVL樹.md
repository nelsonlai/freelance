# AVL 樹 (AVL Tree)

## 學習目標
- 理解 AVL 樹的定義和平衡性質
- 掌握 AVL 樹的插入操作和旋轉機制
- 掌握 AVL 樹的刪除操作
- 理解四種旋轉類型（左旋、右旋、左右旋、右左旋）
- 能夠實作 AVL 樹的基本操作

## 1. AVL 樹的基本概念

### 1.1 為什麼需要 AVL 樹？

**問題**: 普通的二元搜尋樹 (BST) 在插入已排序資料時會退化成鏈表，搜尋時間變成 O(n)。

**解決方案**: **AVL 樹**是一種**自平衡**的二元搜尋樹，透過旋轉操作保持樹的平衡。

### 1.2 定義

**AVL 樹**是一種二元搜尋樹，滿足以下性質：
- 是二元搜尋樹（滿足 BST 性質）
- **平衡性質**: 對於樹中的任意節點，其**左子樹和右子樹的高度差**（平衡因子）的絕對值不超過 1

### 1.3 平衡因子 (Balance Factor)

**平衡因子 (BF)** = 左子樹高度 - 右子樹高度

**AVL 樹要求**: |BF| ≤ 1

**範例**:
```
節點 A:
  左子樹高度 = 2
  右子樹高度 = 1
  BF = 2 - 1 = 1  ✓ (|1| ≤ 1)

節點 B:
  左子樹高度 = 3
  右子樹高度 = 1
  BF = 3 - 1 = 2  ✗ (|2| > 1，不平衡)
```

### 1.4 範例

以下是一個 AVL 樹：
```
        10
       /  \
      5    15
     / \   / \
    3   7 12  18
   /
  1
```

**驗證平衡因子**:
- 節點 10: 左高度=3, 右高度=2, BF=1 ✓
- 節點 5: 左高度=2, 右高度=1, BF=1 ✓
- 節點 15: 左高度=1, 右高度=1, BF=0 ✓
- 節點 3: 左高度=1, 右高度=0, BF=1 ✓

## 2. AVL 樹的旋轉操作

當插入或刪除節點導致不平衡時，需要進行**旋轉**來恢復平衡。

### 2.1 左旋 (Left Rotation)

#### 適用情況

當節點的右子樹比左子樹高 2 層以上時（BF < -1）。

#### 操作過程

```
不平衡情況:
      A (BF = -2)
       \
        B (BF = -1 或 0)
       / \
      BL  C
         / \
        CL  CR

左旋後:
        B
       / \
      A   C
     / \ / \
    AL BL CL CR
```

#### 步驟

1. 將 B 提升為新的根節點
2. A 成為 B 的左子節點
3. B 的原左子樹 (BL) 成為 A 的右子樹

#### C 語言實作

```c
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;
    
    // 執行旋轉
    y->left = x;
    x->right = T2;
    
    // 更新高度
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    
    // 返回新的根節點
    return y;
}
```

### 2.2 右旋 (Right Rotation)

#### 適用情況

當節點的左子樹比右子樹高 2 層以上時（BF > 1）。

#### 操作過程

```
不平衡情況:
        A (BF = 2)
       /
      B (BF = 1 或 0)
     / \
    C   BR
   / \
  CL  CR

右旋後:
      B
     / \
    C   A
   / \ / \
  CL CR BR AR
```

#### 步驟

1. 將 B 提升為新的根節點
2. A 成為 B 的右子節點
3. B 的原右子樹 (BR) 成為 A 的左子樹

#### C 語言實作

```c
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;
    
    // 執行旋轉
    x->right = y;
    y->left = T2;
    
    // 更新高度
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    
    // 返回新的根節點
    return x;
}
```

### 2.3 左右旋 (Left-Right Rotation)

#### 適用情況

當節點的左子樹的右子樹較高時（左-右不平衡）。

#### 操作過程

```
不平衡情況:
      A (BF = 2)
     /
    B (BF = -1)
     \
      C
     / \
    CL  CR

先對 B 左旋，再對 A 右旋:
步驟 1 (左旋 B):
      A
     /
    C
   /
  B
   \
   CL

步驟 2 (右旋 A):
      C
     / \
    B   A
   / \ / \
  BL CL CR AR
```

#### C 語言實作

```c
struct Node* leftRightRotate(struct Node* z) {
    z->left = leftRotate(z->left);
    return rightRotate(z);
}
```

### 2.4 右左旋 (Right-Left Rotation)

#### 適用情況

當節點的右子樹的左子樹較高時（右-左不平衡）。

#### 操作過程

```
不平衡情況:
    A (BF = -2)
     \
      B (BF = 1)
     /
    C
   / \
  CL  CR

先對 B 右旋，再對 A 左旋:
步驟 1 (右旋 B):
    A
     \
      C
       \
        B
       /
      CR

步驟 2 (左旋 A):
      C
     / \
    A   B
   / \ / \
  AL CL CR BR
```

#### C 語言實作

```c
struct Node* rightLeftRotate(struct Node* z) {
    z->right = rightRotate(z->right);
    return leftRotate(z);
}
```

## 3. AVL 樹的插入操作

### 3.1 基本步驟

1. **標準 BST 插入**: 按照 BST 的規則插入新節點
2. **更新高度**: 更新從插入點到根節點路徑上所有節點的高度
3. **計算平衡因子**: 計算每個節點的平衡因子
4. **檢查不平衡**: 如果發現不平衡（|BF| > 1），進行旋轉
5. **返回新根**: 返回（可能旋轉後的）根節點

### 3.2 插入演算法

```
Insert(node, key):
    1. 如果 node 為空，建立新節點並返回
    2. 如果 key < node.data:
        node.left = Insert(node.left, key)
    3. 否則如果 key > node.data:
        node.right = Insert(node.right, key)
    4. 否則返回 node (重複值)
    
    5. 更新 node 的高度
    6. 計算平衡因子 balance = height(node.left) - height(node.right)
    
    7. 如果 balance > 1 且 key < node.left.data:
        右旋 (Right Rotation)
    8. 如果 balance < -1 且 key > node.right.data:
        左旋 (Left Rotation)
    9. 如果 balance > 1 且 key > node.left.data:
        左右旋 (Left-Right Rotation)
    10. 如果 balance < -1 且 key < node.right.data:
        右左旋 (Right-Left Rotation)
    
    11. 返回 node
```

### 3.3 插入範例

**插入序列**: 10, 20, 30, 40, 50, 25

#### 步驟 1: 插入 10
```
    10
```

#### 步驟 2: 插入 20
```
    10
     \
     20
```

#### 步驟 3: 插入 30（需要左旋）
```
插入後（不平衡）:
    10 (BF = -2)
     \
     20 (BF = -1)
       \
       30

左旋後:
       20
      /  \
    10   30
```

#### 步驟 4: 插入 40
```
       20
      /  \
    10   30
          \
          40
```

#### 步驟 5: 插入 50（需要左旋）
```
插入後（不平衡）:
       20 (BF = -2)
      /  \
    10   30 (BF = -1)
          \
          40
           \
           50

左旋後:
       20
      /  \
    10   40
        /  \
      30   50
```

#### 步驟 6: 插入 25（需要右左旋）
```
插入後（不平衡）:
       20 (BF = -2)
      /  \
    10   40 (BF = 1)
        /  \
      30   50
     /
   25

先右旋 40，再左旋 20:
       30
      /  \
    20   40
   /  \    \
 10   25   50
```

### 3.4 C 語言實作

```c
// 獲取節點高度
int height(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// 獲取兩個數的最大值
int max(int a, int b) {
    return (a > b) ? a : b;
}

// 建立新節點
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  // 新節點的高度為 1
    return node;
}

// 插入節點
struct Node* insert(struct Node* node, int key) {
    // 1. 標準 BST 插入
    if (node == NULL)
        return newNode(key);
    
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;  // 重複值，不插入
    
    // 2. 更新高度
    node->height = 1 + max(height(node->left), height(node->right));
    
    // 3. 計算平衡因子
    int balance = height(node->left) - height(node->right);
    
    // 4. 檢查不平衡並旋轉
    
    // 左左情況（右旋）
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    
    // 右右情況（左旋）
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    
    // 左右情況（左右旋）
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    // 右左情況（右左旋）
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    // 返回未改變的節點指標
    return node;
}
```

## 4. AVL 樹的刪除操作

### 4.1 基本步驟

1. **標準 BST 刪除**: 按照 BST 的規則刪除節點
2. **更新高度**: 更新從刪除點到根節點路徑上所有節點的高度
3. **計算平衡因子**: 計算每個節點的平衡因子
4. **檢查不平衡**: 如果發現不平衡，進行旋轉
5. **返回新根**: 返回（可能旋轉後的）根節點

### 4.2 刪除演算法

```
Delete(node, key):
    1. 如果 node 為空，返回 node
    2. 如果 key < node.data:
        node.left = Delete(node.left, key)
    3. 否則如果 key > node.data:
        node.right = Delete(node.right, key)
    4. 否則（找到要刪除的節點）:
        a. 如果沒有左子節點或右子節點:
           返回另一個子節點
        b. 如果有兩個子節點:
           找到右子樹的最小值節點
           用該值取代當前節點
           刪除右子樹的最小值節點
    
    5. 更新 node 的高度
    6. 計算平衡因子 balance
    
    7. 如果 balance > 1 且左子樹平衡因子 >= 0:
        右旋
    8. 如果 balance > 1 且左子樹平衡因子 < 0:
        左右旋
    9. 如果 balance < -1 且右子樹平衡因子 <= 0:
        左旋
    10. 如果 balance < -1 且右子樹平衡因子 > 0:
        右左旋
    
    11. 返回 node
```

### 4.3 刪除範例

**刪除節點 20**（從以下 AVL 樹）:
```
       30
      /  \
    20   40
   /  \    \
 10   25   50
```

**刪除過程**:
1. 找到節點 20
2. 節點 20 有兩個子節點，找到右子樹最小值 25
3. 用 25 取代 20
4. 刪除原來的 25（葉節點）
5. 檢查平衡（可能需要旋轉）

**刪除後**:
```
       30
      /  \
    25   40
   /       \
 10        50
```

### 4.4 C 語言實作

```c
// 找到最小值節點
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// 刪除節點
struct Node* deleteNode(struct Node* root, int key) {
    // 1. 標準 BST 刪除
    if (root == NULL)
        return root;
    
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // 找到要刪除的節點
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node* temp = root->left ? root->left : root->right;
            
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            
            free(temp);
        } else {
            // 有兩個子節點
            struct Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }
    
    if (root == NULL)
        return root;
    
    // 2. 更新高度
    root->height = 1 + max(height(root->left), height(root->right));
    
    // 3. 計算平衡因子
    int balance = height(root->left) - height(root->right);
    
    // 4. 檢查不平衡並旋轉
    
    // 左左情況
    if (balance > 1 && height(root->left->left) >= height(root->left->right))
        return rightRotate(root);
    
    // 左右情況
    if (balance > 1 && height(root->left->left) < height(root->left->right)) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    
    // 右右情況
    if (balance < -1 && height(root->right->right) >= height(root->right->left))
        return leftRotate(root);
    
    // 右左情況
    if (balance < -1 && height(root->right->right) < height(root->right->left)) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    
    return root;
}
```

## 5. AVL 樹的複雜度分析

### 5.1 時間複雜度

- **搜尋**: O(log n) - 因為樹是平衡的
- **插入**: O(log n) - 需要 O(log n) 時間找到位置，最多需要一次旋轉
- **刪除**: O(log n) - 需要 O(log n) 時間找到節點，最多需要一次旋轉

### 5.2 空間複雜度

- **儲存**: O(n) - 需要儲存 n 個節點
- **遞迴堆疊**: O(log n) - 遞迴深度為樹的高度

## 6. AVL 樹的優缺點

### 6.1 優點

- **保證平衡**: 始終保持 O(log n) 的搜尋時間
- **穩定效能**: 不會退化為鏈表
- **適合搜尋**: 適合需要頻繁搜尋的應用

### 6.2 缺點

- **插入/刪除複雜**: 需要維護平衡，實作較複雜
- **旋轉開銷**: 插入和刪除可能需要旋轉操作
- **記憶體開銷**: 需要額外儲存高度資訊

## 7. 練習題

### 練習題 1

請說明 AVL 樹的平衡因子定義，以及 AVL 樹對平衡因子的要求。

**參考答案：**
平衡因子 (BF) = 左子樹高度 - 右子樹高度。AVL 樹要求對於樹中的任意節點，其平衡因子的絕對值不超過 1，即 |BF| ≤ 1。

### 練習題 2

請說明四種旋轉操作的適用情況。

**參考答案：**
1. **右旋**: 左子樹比右子樹高 2 層以上，且左子樹的左子樹較高
2. **左旋**: 右子樹比左子樹高 2 層以上，且右子樹的右子樹較高
3. **左右旋**: 左子樹比右子樹高 2 層以上，且左子樹的右子樹較高
4. **右左旋**: 右子樹比左子樹高 2 層以上，且右子樹的左子樹較高

### 練習題 3

在 AVL 樹中依序插入 50, 30, 70, 20, 40, 60, 80，請展示插入過程和必要的旋轉。

**解答：**
插入 50, 30, 70: 平衡
插入 20: 需要右旋（50 的左子樹不平衡）
插入 40: 需要左右旋（30 的左右不平衡）
插入 60, 80: 平衡

## 8. 考試重點提醒

1. **平衡因子**: 理解平衡因子的計算和 AVL 樹的要求
2. **四種旋轉**: 掌握四種旋轉操作的適用情況和執行過程
3. **插入操作**: 理解插入後的平衡檢查和旋轉過程
4. **刪除操作**: 理解刪除後的平衡檢查和旋轉過程
5. **複雜度**: 記住所有操作的時間複雜度都是 O(log n)
