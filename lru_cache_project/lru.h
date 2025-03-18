#ifndef LRU_H
#define LRU_H

#define KEY_TYPE char
#define VALUE_TYPE int

// -------------------- �ṹ������ --------------------
// todo:˫��������ṹ
typedef struct Node {
	KEY_TYPE key;
	VALUE_TYPE value;
	// LRU˫������ָ��
	struct Node* prev;
	struct Node* next;
	// ��ϣ��˫������ָ��
	struct Node* hash_prev; // ָ���ϣ����ǰһ��Ԫ��
	struct Node* hash_next; // ָ���ϣ����ĺ�һ��Ԫ��
}Node;

// todo:��ϣ��ṹ
typedef struct {
	Node** buckets; // ��ϣͰ һ���ṹ��Ͱ���飨�����ڴ棩
	int capacity; // Ͱ��������
	int count; // ��Ԫ������
	float loadFactor; // ������ֵ
}HashMap;

// todo:LRU����ṹ
typedef struct LRUCache{
	int capacity; // ��������
	int count;  // ����ڵ����
	Node* dummy_head; // αͷ�ڵ�
	Node* dummy_tail; // αβ���
	HashMap* hash_map; // ��ϣ��
}LRUCache;

// -------------------- �������� --------------------
// ��ϣ�������� KEY_TYPE ת��Ϊ�޷�������
unsigned int hash_func(KEY_TYPE key, int capacity);
// ��ϣ�����
HashMap* hashmap_create(int capacity, float loadFactor); // ������ϣ��
void hash_resize(HashMap* map, int newCapacity); // ����
Node* hash_find(HashMap* map, KEY_TYPE key); // ��ϣ����
void hash_insert(HashMap* map, Node* node); // ��ϣ����
void hash_remove(HashMap* map, KEY_TYPE key); // ɾ��Ԫ��
void hashmap_free(HashMap* map); // �ͷŹ�ϣ���ڴ�


// LRU�������
LRUCache* lru_create(int capacity); // ��ʼ������ṹ
VALUE_TYPE lru_get(LRUCache* cache, KEY_TYPE key); // ��ѯ����ֵ�����·���˳��
void lru_put(LRUCache* cache, KEY_TYPE key, VALUE_TYPE value);  //  �������»����ֵ��
void lru_remove_tail(LRUCache* cache); // ���������Ƴ�β���ڵ�
void lru_free(LRUCache* cache); // �ͷŻ����ڴ�

// ˫������������
Node* create_node(KEY_TYPE key, VALUE_TYPE value);
void remove_node(LRUCache* cache, Node* node);
void move_to_head(LRUCache* cache, Node* node); // �������ƶ��ڵ㵽ͷ��
Node* pop_tail(LRUCache* cache);

#endif
