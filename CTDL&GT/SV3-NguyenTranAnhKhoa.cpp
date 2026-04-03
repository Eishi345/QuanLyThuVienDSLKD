#include "Structs.h"
#include <time.h>

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

//Muon sach
NodePhieuMuon* createNodePhieuMuon(PhieuMuon pm) {
	NodePhieuMuon* newNode = new NodePhieuMuon;

	if (newNode == NULL) {
		printf("Tao phieu muon that bai.\n");
		return NULL;
	}

	newNode->data = pm;
	newNode->next = NULL;
	return newNode;
}

void taoMaPhieu(char* maPhieu) {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	sprintf(maPhieu, "PM04%d02%d02%d02%d02%d02%d",
		tm.tm_year,
		tm.tm_mon,
		tm.tm_mday,
		tm.tm_hour,
		tm.tm_min,
		tm.tm_sec
	);
}

int themPhieuMuon(BanDoc& bd, PhieuMuon pmMoi) {
}

int muonSach(QueueChoMuon& q, DanhSachBanDoc& p) {
	char MaThe[20];
	char ISBN[20];

	printf("Nhap ma the ban doc: ");
	fgets(MaThe, sizeof(MaThe), stdin);
	MaThe[strcspn(MaThe, "\n")] = 0;
	printf("Nhap ma sach muon muon: ");
	fgets(ISBN, sizeof(ISBN), stdin);
	ISBN[strcspn(ISBN, "\n")] = 0;

	NodeBanDoc* current = p.head;
	while (current != NULL) {
		if (!strcmp(current->data.MaThe, MaThe)) break;
		current = current->next;
	}

	if (!current->data.TrangThai) {
		printf("The bi khoa hoac ban doc khong con hoat dong.\n");
		return 0;
	}

	if (current->data.SoSachDangMuon >= 5) {
		printf("Ban doc da dat gioi han muon toi da la 5 cuon!\n");
		return 0;
	}
}