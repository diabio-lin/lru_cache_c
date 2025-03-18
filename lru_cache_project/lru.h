#ifndef LRU_H
#define LRU_H

#define KEY_TYPE char
#define VALUE_TYPE int

// -------------------- 结构体声明 --------------------
// todo:双向链表结点结构
typedef struct Node {
	KEY_TYPE key;
	VALUE_TYPE value;
	// LRU双向链表指针
	struct Node* prev;
	struct Node* next;
	// 哈希表双向链表指针
	struct Node* hash_prev; // 指向哈希链表前一个元素
	struct Node* hash_next; // 指向哈希链表的后一个元素
}Node;

// todo:哈希表结构
typedef struct {
	Node** buckets; // 哈希桶 一级结构：桶数组（连续内存）
	int capacity; // 桶数组容量
	int count; // 总元素数量
	float loadFactor; // 扩容阈值
}HashMap;

// todo:LRU缓存结构
typedef struct LRUCache{
	int capacity; // 缓存容量
	int count;  // 缓存节点个数
	Node* dummy_head; // 伪头节点
	Node* dummy_tail; // 伪尾结点
	HashMap* hash_map; // 哈希表
}LRUCache;

// -------------------- 函数声明 --------------------
// 哈希函数：将 KEY_TYPE 转换为无符号整数
unsigned int hash_func(KEY_TYPE key, int capacity);
// 哈希表操作
HashMap* hashmap_create(int capacity, float loadFactor); // 创建哈希表
void hash_resize(HashMap* map, int newCapacity); // 扩容
Node* hash_find(HashMap* map, KEY_TYPE key); // 哈希查找
void hash_insert(HashMap* map, Node* node); // 哈希插入
void hash_remove(HashMap* map, KEY_TYPE key); // 删除元素
void hashmap_free(HashMap* map); // 释放哈希表内存


// LRU缓存操作
LRUCache* lru_create(int capacity); // 初始化缓存结构
VALUE_TYPE lru_get(LRUCache* cache, KEY_TYPE key); // 查询缓存值并更新访问顺序
void lru_put(LRUCache* cache, KEY_TYPE key, VALUE_TYPE value);  //  插入或更新缓存键值对
void lru_remove_tail(LRUCache* cache); // 容量满了移除尾部节点
void lru_free(LRUCache* cache); // 释放缓存内存

// 双向链表辅助函数
Node* create_node(KEY_TYPE key, VALUE_TYPE value);
void remove_node(LRUCache* cache, Node* node);
void move_to_head(LRUCache* cache, Node* node); // 新增：移动节点到头部
Node* pop_tail(LRUCache* cache);

#endif
