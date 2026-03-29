#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

// Struct Book
typedef struct
{
	char MaSach[21];
	char TenSach[100];
	char TacGia[50];
	int NamXB;
	int SoLuong;
}Book;

// SNode của danh sách liên kết đơn
typedef struct SNode
{
	Book Info;
	struct SNode* next;
} SNode;

// Danh sach lien ket
typedef struct
{
	SNode* Head;
	SNode* Tail;
} SList;

// Khoi tao danh sach
void initSList(SList* sl)
{
	sl->Head = NULL;
	sl->Tail = NULL;
}

// Kiem tra danh sach
int isEmpty(SList sl)
{
	return(sl.Head == NULL);
}

// Tao node
SNode* createSNode(Book x)
{
	SNode* p = (SNode*)malloc(sizeof(SNode));
	if (p == NULL)
	{
		printf("Khong du bo nho!!!\n");
		return NULL;
	}
	p->Info = x;
	p->next = NULL;
	return p;
}

// Kiem tra trung ma sach
int CheckTrungMa(SList sl, char ma[])
{
	SNode* p = sl.Head;
	while (p != NULL)
	{
		if (strcmp(p->Info.MaSach, ma) == 0)
			return 1; // Trung
		p = p->next;
	}
	return 0; // Khong trung
}

// Nhap sach
void NhapSach(SList sl, Book* a)
{
	do
	{
		printf("\nNhap ma sach: ");
		fflush(stdin);
		fgets(a->MaSach, sizeof(a->MaSach), stdin);
		a->MaSach[strcspn(a->MaSach, "\n")] = 0;

		if (CheckTrungMa(sl, a->MaSach))
			printf("Ma sach bi trung! Vui long nhap lai!\n");
	} while (CheckTrungMa(sl, a->MaSach));
	printf("\nNhap ten sach: ");
	fgets(a->TenSach, sizeof(a->TenSach), stdin);
	a->TenSach[strcspn(a->TenSach, "\n")] = 0;

	printf("\nNhap tac gia: ");
	fgets(a->TacGia, sizeof(a->TacGia), stdin);
	a->TacGia[strcspn(a->TacGia, "\n")] = 0;

	printf("\nNhap nam xuat ban sach: ");
	scanf("%d", &a->NamXB);
	getchar();

	printf("\nNhap so luong sach: ");
	scanf("%d", &a->SoLuong);
	getchar();
}

// Them dau
int insertHead(SList* sl, SNode* p)
{
	if (p == NULL)
		return 0;
	if (isEmpty(*sl))
	{
		sl->Head = p;
		sl->Tail = p;
	}
	else
	{
		p->next = sl->Head;
		sl->Head = p;
	}
	return 1;
}

// Them cuoi
int insertTail(SList* sl, SNode* p)
{
	if (p == NULL) return 0;
	if (isEmpty(*sl))
	{
		sl->Head = p;
		sl->Tail = p;
	}
	else
	{
		sl->Tail->next = p;
		sl->Tail = p;
	}
	return 1;
}

// Hien thi danh sach
void ShowSList(SList sl)
{
	if (isEmpty(sl))
	{
		printf("Danh sach rong!!!\n");
		return;
	}
	SNode* p = sl.Head;
	int i = 1;
	while (p != NULL)
	{
		printf("\nSach thu %d", i++);
		printf("\nMa sach: %s", p->Info.MaSach);
		printf("\nTen sach: %s", p->Info.TenSach);
		printf("\nTac gia: %s", p->Info.TacGia);
		printf("\nXB nam: %d", p->Info.NamXB);
		printf("\nSo luong: %d", p->Info.SoLuong);
		printf("\n=============================\n");
		p = p->next;
	}
}

// Tim sach
SNode* findSNode(SList sl, char ma[])
{
	SNode* p = sl.Head;
	while (p != NULL)
	{
		if (strcmp(p->Info.MaSach, ma) == 0)
			return p;
		p = p->next;
	}
	return NULL;
}

// Tim sach theo ten
void TimTheoTen(SList sl, char ten[])
{
	SNode* p = sl.Head;
	int found = 0;
	while (p != NULL)
	{
		if (strstr(p->Info.TenSach, ten) != NULL)
		{
			printf("\nMa sach: %s\n", p->Info.MaSach);
			printf("\nTen sach: %s\n", p->Info.TenSach);
			printf("\nTac gia: %s\n", p->Info.TacGia);
			found = 1;
		}
		p = p->next;
	}
	if (!found)
		printf("\nKhong tim thay sach\n");
}

// Sap xep danh sach theo nam ( tang dan )
void SapXepTheoNam(SList* sl)
{
	for (SNode* i = sl->Head; i != NULL; i = i->next)
		for (SNode* j = i->next; j != NULL; j = j->next)
			if (i->Info.NamXB > j->Info.NamXB)
			{
				Book temp = i->Info;
				i->Info = j->Info;
				j->Info = temp;
			}
	printf("\nDa sap xep xong!!!!\n");
}
// Xoa sach
int deleteSNode(SList* sl, char ma[])
{
	SNode* p = sl->Head;
	SNode* prev = NULL;
	while (p != NULL && strcmp(p->Info.MaSach, ma) != 0)
	{
		prev = p;
		p = p->next;
	}
	if (p == NULL) return 0;

	if (p == sl->Head)
		sl->Head = p->next;
	else
		prev->next = p->next;
	if (p == sl->Tail)
		sl->Tail = prev;
	free(p);
	return 1;
}

// MENU
void menu(SList* sl)
{
	int luachon;
	Book a;
	char ma[21];
	char ten[100];
	do
	{
		printf("\n=========MENU=============\n");
		printf("\n1. Them dau\n");
		printf("\n2. Them cuoi\n");
		printf("\n3. Hien thi danh sach\n");
		printf("\n4. Tim sach\n");
		printf("\n5. Xoa sach\n");
		printf("\n6. Tim sach theo ten\n");
		printf("\n7. Sap xep danh sach sach theo nam\n");
		printf("\n0. Thoat chuong trinh\n");
		printf("\nNhap lua chon cua ban(0-5): \n");
		scanf("%d", &luachon);
		getchar();

		switch (luachon)
		{
		case 1:
			NhapSach(*sl, &a);
			insertHead(sl, createSNode(a));
			break;
		case 2:
			NhapSach(*sl,&a);
			insertTail(sl, createSNode(a));
			break;
		case 3:
			ShowSList(*sl);
			break;
		case 4:
			printf("\nNhap ma sach can tim: ");
			getchar();
			fgets(ma, sizeof(ma), stdin);
			ma[strcspn(ma, "\n")] = 0;
			if (findSNode(*sl, ma))
				printf("Da tim thay!!!\n");
			else
				printf("Khong tim thay ma!. Vui long nhap lai ma!!!\n");
			break;
		case 5:
			printf("\nNhap ma sach can xoa: ");
			getchar();
			fgets(ma, sizeof(ma), stdin);
			ma[strcspn(ma, "\n")] = 0;
			if (deleteSNode(sl, ma))
				printf("Da xoa thanh cong!!!\n");
			else
				printf("\nKhong tim thay ma can xoa!. Vui long nhap lai ma!!!");
			break;
		case 6:
			printf("\nNhap ten sach can tim: ");
			getchar();
			fgets(ten, sizeof(ten), stdin);
			ten[strcspn(ten, "\n")] = 0;
			TimTheoTen(*sl, ten);
			break;
		case 7:
			SapXepTheoNam(sl);
			break;
		}
	} while (luachon != 0);
}

int main()
{
	SList sl;
	initSList(&sl);
	menu(&sl);
	return 0;
}






