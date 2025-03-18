# LRU Cache Project

## 项目简介
这是一个用C++实现的LRU（Least Recently Used）缓存项目。LRU缓存是一种缓存淘汰策略，当缓存已满时，会移除最久未使用的缓存项。
(个人学完c语言练手项目，仅作学习使用，功能简陋)

## 文件结构
- `lru.h`：包含LRU缓存的结构体和函数声明。
- `lru.c`：包含LRU缓存的主要实现函数。
- `main.c`: 一些测试用例

## 主要功能
- **哈希表操作**
  - `hashmap_create`：创建哈希表
  - `hash_resize`：扩容哈希表
  - `hash_find`：查找哈希表中的元素
  - `hash_insert`：向哈希表中插入元素
  - `hash_remove`：从哈希表中删除元素
  - `hashmap_free`：释放哈希表内存

- **LRU缓存操作**
  - `lru_create`：初始化LRU缓存
  - `lru_get`：查询缓存值并更新访问顺序
  - `lru_put`：插入或更新缓存键值对
  - `lru_remove_tail`：移除缓存尾部节点
  - `lru_free`：释放缓存内存

- **双向链表辅助函数**
  - `create_node`：创建新节点
  - `remove_node`：移除节点
  - `move_to_head`：将节点移动到头部
  - `pop_tail`：弹出尾部节点

## 依赖
- C

## 编译
使用Visual Studio 2022打开项目文件 `lru_cache_project.vcxproj`，然后编译运行。

## 贡献
欢迎提交问题和贡献代码。

## 许可证
此项目遵循MIT许可证。

   
