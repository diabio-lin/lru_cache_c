#include "lru.h"
#include <stdlib.h>

// ��ϣ�����
// ��ϣ����
unsigned int hash_func(KEY_TYPE key, int capacity) {
	return (unsigned int)key % capacity;
}

// ��ϣ����
void hash_resize(HashMap* map, int newCapacity) {
	Node** newBuckets = calloc(newCapacity, sizeof(Node*));
	if (newBuckets == NULL) return;
	// ������Ͱ������ת�ؽڵ�
	for (int i = 0; i < map->capacity; i++) {
		Node* node = map->buckets[i];
		while (node != NULL) {
			Node* next = node->hash_next;
			unsigned int index = hash_func(node->key, newCapacity);
			// ��noode������Ͱ������ͷ��
			node->hash_prev = NULL;
			node->hash_next = newBuckets[index];
			if (newBuckets[index] != NULL) {
				newBuckets[index]->hash_prev = node;
			}
			newBuckets[index] = node;
			node = next;
		}
	}
	free(map->buckets);
	map->buckets = newBuckets;
	map->capacity = newCapacity;
}

// ������ϣ��
HashMap* hashmap_create(int capacity, float loadFactor) {
	HashMap *map = (HashMap*)malloc(sizeof(HashMap));
	if (map == NULL) return NULL;
	Node** buckets = calloc(capacity, sizeof(Node*));
	if (buckets == NULL) {
		free(map);
		return NULL;
	}
	map->buckets = buckets;
	map->capacity = capacity;
	map->count = 0;
	map->loadFactor = loadFactor;
	return map;
};

// ��ϣ����
Node* hash_find(HashMap* map, KEY_TYPE key){
	unsigned int index = hash_func(key, map->capacity);
	Node* node = map->buckets[index];

	// ������ϣ��
	while (node != NULL) {
		if (node->key == key) {
			return node;
		}
		node = node->hash_next;
	}
	return NULL;
}

// ��ϣ����
void hash_insert(HashMap *map, Node* node){
	if (map == NULL || node == NULL) return;


	unsigned int index = hash_func(node->key, map->capacity);

	// �����ϣͰ�����ͷ��
	node->hash_prev = NULL;
	node->hash_next = map->buckets[index];

	if (map->buckets[index]) {
		map->buckets[index]->hash_prev = node;
	}
	map->buckets[index] = node;
	map->count++;

	// ����Ƿ�Ҫ����
	if ((float)map->count / map->capacity > map->loadFactor) {
		// ������������
		hash_resize(map, map->capacity * 2);
	}
}
// ɾ��Ԫ��
void hash_remove(HashMap* map, KEY_TYPE key) {
	if (map == NULL || map->buckets == NULL) return;

	unsigned int index = hash_func(key, map->capacity);
	Node* curr = map->buckets[index];
	Node* prev = NULL;
	while (curr != NULL) {
		if (curr->key == key) {
			if(prev == NULL){
				map->buckets[index] = curr->hash_next;
			}
			else {
				prev->hash_next = curr->hash_next;
			}
			if (curr->hash_next != NULL) {
				curr->hash_next->hash_prev = prev;
			}
			//free(curr);
			map->count--;
			return;
		}
		prev = curr;
		curr = curr->hash_next;
	}
}                

// �ͷŹ�ϣ���ڴ�
void hashmap_free(HashMap* map) {
	if (map == NULL) return;
	for (int i = 0; i < map->capacity; i++) {
		Node* curr = map->buckets[i];
		while (curr != NULL) {
			Node* next = curr->hash_next;
			free(curr);
			curr = next;
		}
	}
	free(map->buckets);
	free(map);
}

  
// ˫������������
Node* create_node(KEY_TYPE key, VALUE_TYPE value) {
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL) return NULL;
	node->key = key;
	node->value = value;
	node->prev = node->next = NULL;
	return node;
}

// �Ƴ��ڵ㺯��������ȫ��飩
void remove_node(LRUCache* cache, Node* node) {
	if (node == NULL || cache == NULL) return;

	// ȷ�� node ����αͷβ�ڵ�
	if (node == cache->dummy_head || node == cache->dummy_tail) {
		return;
	}

	Node* prev_node = node->prev;
	Node* next_node = node->next;

	// ȷ������������
	if (prev_node != NULL) {
		prev_node->next = next_node;
	}
	if (next_node != NULL) {
		next_node->prev = prev_node;
	}

	// ��ѡ���� node ��ָ���ÿգ�������������
	node->prev = NULL;
	node->next = NULL;
}


// ������ƶ���ͷ������ʾ���ʹ�ã�
void move_to_head(LRUCache* cache, Node* node) {
	if (node == cache->dummy_head->next) return; // ����Ѿ���ͷ��ֱ���˳�
	// �Ͽ�ԭ������
	// ��������½ڵ㣬��Ҫ�ȶϿ�ԭ������
	if (node->next != NULL) {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
	// ����αͷ�ڵ��
	node->next = cache->dummy_head->next;
	node->prev = cache->dummy_head;
	if(cache->dummy_head->next != NULL)
		cache->dummy_head->next->prev = node;
	cache->dummy_head->next = node;
}

// ����β��㣨��̭���δʹ�ã�
Node* pop_tail(LRUCache* cache) {
	Node* tail = cache->dummy_tail->prev;
	remove_node(cache, tail);
	return tail;
}


// LRU�������
// ��ʼ������ṹ
LRUCache* lru_create(int capacity) {
	LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
	if (cache == NULL) return NULL;
	cache->capacity = capacity;
	cache->count = 0;

	// ��ʼ��αͷβ�ڵ�
	cache->dummy_head = create_node(0, 0);
	cache->dummy_tail = create_node(0, 0);

	if (cache->dummy_head == NULL || cache->dummy_tail == NULL) {
		free(cache);
		return NULL;
	}

	// αͷβ����ָ��
	cache->dummy_head->next = cache->dummy_tail;
	cache->dummy_tail->prev = cache->dummy_head;

	// ��ʼ����ϣ��
	cache->hash_map = hashmap_create(16, 0.75);
	if (cache->hash_map == NULL) {
		free(cache->dummy_head);
		free(cache->dummy_tail);
		free(cache);
		return NULL;
	}
	return cache;
}


// ��ѯ����ֵ�����·���˳��
VALUE_TYPE lru_get(LRUCache* cache, KEY_TYPE key) {
	Node* node = hash_find(cache->hash_map, key);
	if (node == NULL) return -1;
	move_to_head(cache, node);
	return node->value;
}

//  �������»����ֵ��
void lru_put(LRUCache* cache, KEY_TYPE key, VALUE_TYPE value) {
	Node* node = hash_find(cache->hash_map, key);
	if (node != NULL) {
		node->value = value;
		move_to_head(cache, node);
	}
	else {
		if (cache->capacity == cache->count) {
			Node* temp = pop_tail(cache);
			hash_remove(cache->hash_map, temp->key);
			cache->count--;
		}
		node = create_node(key, value);
		hash_insert(cache->hash_map, node);
		if (node == NULL) return;
		move_to_head(cache, node);
		cache->count++;
	}
}

// ���������Ƴ�β���ڵ�
void lru_remove_tail(LRUCache* cache) {
    if (cache == NULL || cache->dummy_tail == NULL) return;
    Node* node = cache->dummy_tail->prev;
    if (node != NULL && node != cache->dummy_head) {
        remove_node(cache, node);
        hash_remove(cache->hash_map, node->key);
        free(node);
        cache->count--;
    }
}


// �ͷŻ����ڴ�
void lru_free(LRUCache* cache) {
	if (cache == NULL) return;
	hashmap_free(cache->hash_map);
	free(cache->dummy_head);
	free(cache->dummy_tail);
	free(cache);
}


