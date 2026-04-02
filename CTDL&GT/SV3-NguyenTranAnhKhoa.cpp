#include "Structs.h"

//Tao hang cho muon sach
int initQueueDSLK(QueueChoMuon& q) {
	q.head = NULL;
	q.tail = NULL;
}

//Kiem tra hang cho trong
int isEmpty(QueueChoMuon& q) {
	return (q.head == NULL);
}

//Them vao hang cho
int enQueue(QueueChoMuon& q, NodeQueue* p) {
	if (p == NULL) return 0;

	if (isEmpty(q)) {
		q.head = p;
	}
	else {
		q.tail->next = p;
	}
	q.tail = p;
}

//Xoa khoi hang cho
int deQueue(QueueChoMuon& q, char bd[]) {
	if (isEmpty(q)) return 0;

	NodeQueue* p = q.head;
	q.head = q.head->next;
	if (q.head == NULL) {
		q.tail = NULL;
	}

	strcpy(bd, p->MaBanDoc);
	delete p;
	return 1;
}