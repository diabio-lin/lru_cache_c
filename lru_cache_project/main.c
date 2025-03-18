#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "lru.h"

/* 
    ����LRU����ģ��

*/

// ����1��������̭����
void test_basic_evict() {
    printf("===== Test 1: Basic Evict =====\n");
    LRUCache* cache = lru_create(3);  // ����Ϊ2

    lru_put(cache, 'A', 1);  // ����: [A]
    lru_put(cache, 'B', 2);  // ����: [B, A]
    lru_put(cache, 'C', 3);  // ����������̭A -> [C, B]
    lru_put(cache, 'D', 4);  // ����������̭A -> [C, B]

    // Ԥ�ڣ�A����̭��B��C����
    printf("Get A: %d (expect -1)\n", lru_get(cache, 'A')); // Ӧ����-1
    printf("Get B: %d (expect 2)\n", lru_get(cache, 'B'));  // Ӧ����2
    printf("Get C: %d (expect 3)\n", lru_get(cache, 'C'));  // Ӧ����3
    //printf("Get D: %d (expect 4)\n", lru_get(cache, 'D'));  // Ӧ����3
    lru_put(cache, 'A', 1);  // ����: [A]
    printf("Get A: %d (expect 1)\n", lru_get(cache, 'A')); // Ӧ����-1

    lru_free(cache);
}

// ����2�����ʸ���˳��
void test_access_order() {
    printf("\n===== Test 2: Access Update =====\n");
    LRUCache* cache = lru_create(2);

    lru_put(cache, 'A', 1);  // [A]
    lru_put(cache, 'B', 2);  // [B, A]
    lru_get(cache, 'A');     // ����A -> [A, B]
    lru_put(cache, 'C', 3);  // ��̭B -> [C, A]

    printf("Get B: %d (expect -1)\n", lru_get(cache, 'B')); // ����̭
    printf("Get A: %d (expect 1)\n", lru_get(cache, 'A'));  // �Դ���
    printf("Get C: %d (expect 3)\n", lru_get(cache, 'C'));  // ����

    lru_free(cache);
}

// ����3���߽����������1��
void test_capacity_one() {
    printf("\n===== Test 3: Capacity=1 =====\n");
    LRUCache* cache = lru_create(1);

    lru_put(cache, 'A', 1);  // [A]
    lru_put(cache, 'B', 2);  // ��̭A -> [B]

    printf("Get A: %d (expect -1)\n", lru_get(cache, 'A')); // ����̭
    printf("Get B: %d (expect 2)\n", lru_get(cache, 'B'));  // ����

    lru_free(cache);
}

// ����4����η��ʸ�������
void test_multiple_access() {
    printf("\n===== Test 4: Multiple Access =====\n");
    LRUCache* cache = lru_create(3);

    lru_put(cache, 'A', 1);  // [A]
    lru_put(cache, 'B', 2);  // [B, A]
    lru_put(cache, 'C', 3);  // [C, B, A]
    lru_get(cache, 'A');     // [A, C, B]
    lru_get(cache, 'B');     // [B, A, C]
    lru_put(cache, 'D', 4);  // ��̭C -> [D, B, A]

    printf("Get C: %d (expect -1)\n", lru_get(cache, 'C')); // ����̭
    printf("Get D: %d (expect 4)\n", lru_get(cache, 'D'));  // ����

    lru_free(cache);
}

int main() {
    test_basic_evict();
    test_access_order();
    test_capacity_one();
    test_multiple_access();
    return 0;
}