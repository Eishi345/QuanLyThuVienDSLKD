#define _CRT_SECURE_NO_WARNINGS
#include "Structs.h"
#include <time.h>
#define SNM 14

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
Date tinhHanTra(int soNgayMuon = SNM) {
	time_t t = time(NULL) + (soNgayMuon * 24 * 60 * 60);
	struct tm tm = *localtime(&t);

	Date d;
	d.ngay = tm.tm_mday;
	d.thang = tm.tm_mon + 1;
	d.nam = tm.tm_year + 1900;
	return d;
}

int ktraQuaHanTraSach(Date hanTra, Date ngayTra) {
	struct tm nHT = { 0 };
	struct tm nT = { 0 };

	nHT.tm_mday = hanTra.ngay;
	nHT.tm_mon = hanTra.thang - 1;
	nHT.tm_year = hanTra.nam - 1900;

	nT.tm_mday = ngayTra.ngay;
	nT.tm_mon = ngayTra.thang - 1;
	nT.tm_year = ngayTra.nam - 1900;

	time_t hanTra_Sec = mktime(&nHT);
	time_t ngayTra_Sec = mktime(&nT);

	if (difftime(ngayTra_Sec, hanTra_Sec) > 0) {
		return 1;
	}
	return 0;
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

	sprintf(maPhieu, "PM%04d%02d%02d%02d%02d%02d",
		tm.tm_year + 1900,
		tm.tm_mon + 1,
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
	bd.dSPhieuMuon = newNode;
	bd.SoSachDangMuon++;
	return 1;
}

int muonSach(DanhSachSach& dsSach, DanhSachBanDoc& p, char MaThe[], char ISBN[]) {
	//char MaThe[20];
	//char ISBN[20];

	//printf("Nhap ma the ban doc: ");
	//fgets(MaThe, sizeof(MaThe), stdin);
	//MaThe[strcspn(MaThe, "\n")] = 0;
	//printf("Nhap ma sach muon muon: ");
	//fgets(ISBN, sizeof(ISBN), stdin);
	//ISBN[strcspn(ISBN, "\n")] = 0;

	NodeBanDoc* bd = p.head;
	while (bd != NULL) {
		if (!strcmp(bd->data.MaThe, MaThe)) break;
		bd = bd->next;
	}

	if (bd == NULL) {
		printf("Khong tim thay ban doc!\n");
		return 0;
	}

	if (!bd->data.TrangThai) {
		printf("The bi khoa hoac ban doc khong con hoat dong.\n");
		return 0;
	}

	if (bd->data.SoSachDangMuon >= 5) {
		printf("Ban doc da dat gioi han muon toi da la 5 cuon!\n");
		return 0;
	}

	int indexSach = -1;
	for (int i = 0; i < dsSach.soLuong; i++) {
		if (!strcmp(ISBN, dsSach.arr[i].ISBN) && dsSach.arr[i].TrangThai == 1) {
			indexSach = i;
			break;
		}
	}

	if (indexSach == -1) {
		printf("Khong tim thay sach trong kho hoac sach da bi xoa!\n");
		return 0;
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

		if (themPhieuMuon(bd->data, pmMoi)) {
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
			printf("Sach hien tai da het, ban doc %s da duoc them vao hang cho.\n", bd->data.TenBanDoc);
			return 1;
		}
		else {
			printf("Loi! Khong the them vao hang cho.\n");
			return 0;
		}
	}
}

int traSach(DanhSachSach& dsSach, DanhSachBanDoc& p, char MaThe[], char ISBN[]) {
	//char MaThe[20];
	//char ISBN[20];

	//printf("Nhap ma the ban doc: ");
	//fgets(MaThe, sizeof(MaThe), stdin);
	//MaThe[strcspn(MaThe, "\n")] = 0;
	//printf("Nhap ma sach muon tra: ");
	//fgets(ISBN, sizeof(ISBN), stdin);
	//ISBN[strcspn(ISBN, "\n")] = 0;

	NodeBanDoc* bd = p.head;
	while (bd != NULL) {
		if (!strcmp(bd->data.MaThe, MaThe)) break;
		bd = bd->next;
	}

	if (bd == NULL) {
		printf("Khong tim thay ban doc!\n");
		return 0;
	}

	NodePhieuMuon* pm = bd->data.dSPhieuMuon;
	while (pm != NULL) {
		if (!strcmp(pm->data.MaSach, ISBN) && pm->data.TrangThai != 1) {
			break;
		}
		pm = pm->next;
	}

	if (pm == NULL) {
		printf("Khong tim thay phieu muon!\n");
		return 0;
	}

	int indexSach = -1;
	for (int i = 0; i < dsSach.soLuong; i++) {
		if (!strcmp(dsSach.arr[i].ISBN, ISBN)) {
			indexSach = i;;
			break;
		}
	}

	if (indexSach == -1) {
		printf("Ma sach sai hoac sach khong ton tai!\n");
		return 0;
	}

	Sach& sachHienTai = dsSach.arr[indexSach];
	pm->data.TrangThai = 1;
	bd->data.SoSachDangMuon--;
	sachHienTai.SoLuongConLai++;

	if (ktraQuaHanTraSach(pm->data.HanTra, layNgayHienTai())) {
		printf("CANH BAO: Ban doc tra sach qua han.\n");
	}
	else printf("Ban doc tra sach thanh cong (dung han).\n");

	if (!isEmpty(sachHienTai.queueCho)) {
		char nguoiMuonMoi[20];

		deQueue(sachHienTai.queueCho, nguoiMuonMoi);
		muonSach(dsSach, p, nguoiMuonMoi, ISBN);
		printf("Da cho ban doc co ma %s muon sach.\n", nguoiMuonMoi);
	}
	return 1;
}