#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "lru.h"

/* 
    测试LRU缓存模块

*/

// 测试1：基本淘汰策略
void test_basic_evict() {
    printf("===== Test 1: Basic Evict =====\n");
    LRUCache* cache = lru_create(3);  // 容量为2

    lru_put(cache, 'A', 1);  // 缓存: [A]
    lru_put(cache, 'B', 2);  // 缓存: [B, A]
    lru_put(cache, 'C', 3);  // 缓存满，淘汰A -> [C, B]
    lru_put(cache, 'D', 4);  // 缓存满，淘汰A -> [C, B]

    // 预期：A被淘汰，B和C存在
    printf("Get A: %d (expect -1)\n", lru_get(cache, 'A')); // 应返回-1
    printf("Get B: %d (expect 2)\n", lru_get(cache, 'B'));  // 应返回2
    printf("Get C: %d (expect 3)\n", lru_get(cache, 'C'));  // 应返回3
    //printf("Get D: %d (expect 4)\n", lru_get(cache, 'D'));  // 应返回3
    lru_put(cache, 'A', 1);  // 缓存: [A]
    printf("Get A: %d (expect 1)\n", lru_get(cache, 'A')); // 应返回-1

    lru_free(cache);
}

// 测试2：访问更新顺序
void test_access_order() {
    printf("\n===== Test 2: Access Update =====\n");
    LRUCache* cache = lru_create(2);

    lru_put(cache, 'A', 1);  // [A]
    lru_put(cache, 'B', 2);  // [B, A]
    lru_get(cache, 'A');     // 访问A -> [A, B]
    lru_put(cache, 'C', 3);  // 淘汰B -> [C, A]

    printf("Get B: %d (expect -1)\n", lru_get(cache, 'B')); // 被淘汰
    printf("Get A: %d (expect 1)\n", lru_get(cache, 'A'));  // 仍存在
    printf("Get C: %d (expect 3)\n", lru_get(cache, 'C'));  // 最新

    lru_free(cache);
}

// 测试3：边界情况（容量1）
void test_capacity_one() {
    printf("\n===== Test 3: Capacity=1 =====\n");
    LRUCache* cache = lru_create(1);

    lru_put(cache, 'A', 1);  // [A]
    lru_put(cache, 'B', 2);  // 淘汰A -> [B]

    printf("Get A: %d (expect -1)\n", lru_get(cache, 'A')); // 被淘汰
    printf("Get B: %d (expect 2)\n", lru_get(cache, 'B'));  // 存在

    lru_free(cache);
}

// 测试4：多次访问更新链表
void test_multiple_access() {
    printf("\n===== Test 4: Multiple Access =====\n");
    LRUCache* cache = lru_create(3);

    lru_put(cache, 'A', 1);  // [A]
    lru_put(cache, 'B', 2);  // [B, A]
    lru_put(cache, 'C', 3);  // [C, B, A]
    lru_get(cache, 'A');     // [A, C, B]
    lru_get(cache, 'B');     // [B, A, C]
    lru_put(cache, 'D', 4);  // 淘汰C -> [D, B, A]

    printf("Get C: %d (expect -1)\n", lru_get(cache, 'C')); // 被淘汰
    printf("Get D: %d (expect 4)\n", lru_get(cache, 'D'));  // 最新

    lru_free(cache);
}

int main() {
    test_basic_evict();
    test_access_order();
    test_capacity_one();
    test_multiple_access();
    return 0;
}