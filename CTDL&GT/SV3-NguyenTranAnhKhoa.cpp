#include "Structs.h"
#include <time.h>

//Lay thoi gian hien tai
Date layNgayHienTai() {
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	Date d;
	d.ngay = tm.tm_mday;
	d.thang = tm.tm_mon + 1;
	d.nam = tm.tm_year + 1900;
	return d;
}

//Tinh han tra sach
Date tinhHanTra(int soNgayMuon = 14) {
	time_t t = time(NULL) + (soNgayMuon * 24 * 60 * 60);
	struct tm tm = *localtime(&t);

	Date d;
	d.ngay = tm.tm_mday;
	d.thang = tm.tm_mon + 1;
	d.nam = tm.tm_year + 1900;
	return d;
}

//Tao hang cho muon sach
void initQueueDSLK(QueueChoMuon& q) {
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
	return 1;
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
	NodePhieuMuon* newNode = createNodePhieuMuon(pmMoi);

	if (newNode == NULL) {
		printf("Loi tao phieu muon.\n");
		return 0;
	}

	newNode->next = bd.dSPhieuMuon;
	bd.dSPhieuMuon->next = newNode;
	bd.SoSachDangMuon++;
	return 1;
}

int muonSach(DanhSachSach& dsSach, DanhSachBanDoc& p) {
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

	if (current == NULL) {
		printf("Khong tim thay ban doc!\n");
		return 0;
	}

	if (!current->data.TrangThai) {
		printf("The bi khoa hoac ban doc khong con hoat dong.\n");
		return 0;
	}

	if (current->data.SoSachDangMuon >= 5) {
		printf("Ban doc da dat gioi han muon toi da la 5 cuon!\n");
		return 0;
	}

	int indexSach = -1;
	for (int i = 0; i < dsSach.capacity; i++) {
		if (!strcmp(ISBN, dsSach.arr[i].ISBN) && dsSach.arr[i].TrangThai == 1) {
			indexSach = i;
			break;
		}
	}

	if (indexSach == -1) {
		printf("Khong tim thay sach trong kho hoac sach da bi xoa!\n");
	}

	Sach& SachMuon = dsSach.arr[indexSach];
	if (SachMuon.SoLuongConLai > 0) {
		PhieuMuon pmMoi;
		taoMaPhieu(pmMoi.MaPhieu);
		strcpy(pmMoi.MaThe, MaThe);
		strcpy(pmMoi.MaSach, SachMuon.ISBN);
		pmMoi.NgayMuon = layNgayHienTai();
		pmMoi.HanTra = tinhHanTra();
		pmMoi.TrangThai = 0;

		if (themPhieuMuon(current->data, pmMoi)) {
			SachMuon.SoLuongConLai--;
			printf("Muon sach thanh cong! Ma phieu muon cua ban la: %s", pmMoi.MaPhieu);
			return 1;
		}
		else return 0;
	}
	else {
		NodeQueue* nodeCho = new NodeQueue;
		strcpy(nodeCho->MaBanDoc, MaThe);
		nodeCho->next = NULL;

		if (enQueue(SachMuon.queueCho, nodeCho)) {
			printf("Sach hien tai da het, ban doc %s da duoc them vao hang cho.\n", current->data.TenBanDoc);
			return 1;
		}
		else {
			printf("Loi! Khong the them vao hang cho.\n");
			return 0;
		}
	}
}