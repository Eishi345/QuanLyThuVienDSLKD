#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Structs.h"
#include <time.h>

void inBanDocQuaHan(DanhSachBanDoc dsBD, Date ngayHienTai);
int demSoLanMuon(DanhSachBanDoc dsBD, char maSach[]);
void sortSachTheoMuon(DanhSachSach* dsSach, DanhSachBanDoc dsBD);
void top10Sach(DanhSachSach dsSach, DanhSachBanDoc dsBD);
void thongKeTheoTacGia(DanhSachSach dsSach, char tacGia[]);
void thongKeTheoNXB(DanhSachSach dsSach, char nxb[]);
void ghiLog(const char* msg);
void backupSach(DanhSachSach dsSach);
void backupBanDoc(DanhSachBanDoc dsBD);
void freePhieu(NodePhieuMuon* head);
void freeBanDoc(DanhSachBanDoc* dsBD);
void freeQueue(QueueChoMuon* q);
void freeSach(DanhSachSach* dsSach);


// ================= MENU =================
void menu() {
    printf("\n=========== MENU ===========\n");
    printf("1. In ban doc qua han\n");
    printf("2. Top 10 sach muon nhieu\n");
    printf("3. Thong ke theo tac gia\n");
    printf("4. Thong ke theo NXB\n");
    printf("5. Ghi log\n");
    printf("6. Backup du lieu\n");
    printf("0. Thoat\n");
    printf("============================\n");
}

// ================= PROCESS =================
void process(DanhSachBanDoc dsBanDoc, DanhSachSach dsSach) {
    int choice;
    char input[100];
    Date today;

    do {
        menu();
        printf("Chon: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {

        case 1:
            printf("Nhap ngay hien tai (dd mm yyyy): ");
            scanf("%d %d %d", &today.ngay, &today.thang, &today.nam);

            inBanDocQuaHan(dsBanDoc, today);
            break;

        case 2:
            top10Sach(dsSach, dsBanDoc);
            break;

        case 3:
            printf("Nhap ten tac gia: ");
            fgets(input, 100, stdin);
            input[strcspn(input, "\n")] = 0;

            thongKeTheoTacGia(dsSach, input);
            break;

        case 4:
            printf("Nhap ten NXB: ");
            fgets(input, 100, stdin);
            input[strcspn(input, "\n")] = 0;

            thongKeTheoNXB(dsSach, input);
            break;

        case 5:
            printf("Nhap noi dung log: ");
            fgets(input, 100, stdin);
            input[strcspn(input, "\n")] = 0;

            ghiLog(input);
            printf("Da ghi log!\n");
            break;

        case 6:
            backupSach(dsSach);
            backupBanDoc(dsBanDoc);
            printf("Da backup du lieu!\n");
            break;

        case 0:
            printf("Dang thoat...\n");
            freeBanDoc(&dsBanDoc);
            freeSach(&dsSach);

            printf("Da giai phong bo nho!\n");
            break;

        default:
            printf("Lua chon khong hop le!\n");
        }

    } while (choice != 0);
}

// ================= MAIN =================
int main() {
    DanhSachBanDoc dsBanDoc;
    DanhSachSach dsSach;

    // ===== KHỞI TẠO BAN ĐẦU =====
    dsBanDoc.head = dsBanDoc.tail = NULL;
    dsBanDoc.soLuong = 0;

    dsSach.arr = NULL;
    dsSach.soLuong = 0;
    dsSach.capacity = 0;

    // 👉 Bạn có thể thêm dữ liệu mẫu ở đây nếu cần

    // ===== CHẠY CHƯƠNG TRÌNH =====
    process(dsBanDoc, dsSach);

    return 0;
}

// =======================================================
//     SO SÁNH NGÀY
// =======================================================
int soSanhDate(Date a, Date b) {
    if (a.nam != b.nam) return a.nam - b.nam;
    if (a.thang != b.thang) return a.thang - b.thang;
    return a.ngay - b.ngay;
}

// =======================================================
//     IN BẠN ĐỌC QUÁ HẠN
// =======================================================
void inBanDocQuaHan(DanhSachBanDoc dsBD, Date ngayHienTai) {
    printf("\n=== BAN DOC QUA HAN ===\n");

    for (NodeBanDoc* bd = dsBD.head; bd != NULL; bd = bd->next) {
        int flag = 0;

        // duyệt danh sách phiếu mượn
        for (NodePhieuMuon* p = bd->data.dSPhieuMuon; p != NULL; p = p->next) {

            if (p->data.TrangThai == 0 &&
                soSanhDate(p->data.HanTra, ngayHienTai) < 0) {

                if (!flag) {
                    printf("\nBan doc: %s\n", bd->data.TenBanDoc);
                    flag = 1;
                }

                printf("  - Sach: %s | Han tra: %02d/%02d/%d\n",
                    p->data.MaSach,
                    p->data.HanTra.ngay,
                    p->data.HanTra.thang,
                    p->data.HanTra.nam);
            }
        }
    }
}

// =======================================================
//     ĐẾM SỐ LẦN MƯỢN SÁCH
// =======================================================
int demSoLanMuon(DanhSachBanDoc dsBD, char maSach[]) {
    int count = 0;

    for (NodeBanDoc* bd = dsBD.head; bd != NULL; bd = bd->next) {
        for (NodePhieuMuon* p = bd->data.dSPhieuMuon; p != NULL; p = p->next) {
            if (strcmp(p->data.MaSach, maSach) == 0)
                count++;
        }
    }
    return count;
}

// =======================================================
//      SẮP XẾP SÁCH THEO LƯỢT MƯỢN
// =======================================================
void sortSachTheoMuon(DanhSachSach* dsSach, DanhSachBanDoc dsBD) {
    for (int i = 0; i < dsSach->soLuong - 1; i++) {
        for (int j = i + 1; j < dsSach->soLuong; j++) {

            int a = demSoLanMuon(dsBD, dsSach->arr[i].ISBN);
            int b = demSoLanMuon(dsBD, dsSach->arr[j].ISBN);

            if (a < b) {
                Sach temp = dsSach->arr[i];
                dsSach->arr[i] = dsSach->arr[j];
                dsSach->arr[j] = temp;
            }
        }
    }
}

// =======================================================
//     TOP 10 SÁCH
// =======================================================
void top10Sach(DanhSachSach dsSach, DanhSachBanDoc dsBD) {
    sortSachTheoMuon(&dsSach, dsBD);

    printf("\n=== TOP 10 SACH ===\n");

    int n = dsSach.soLuong < 10 ? dsSach.soLuong : 10;

    for (int i = 0; i < n; i++) {
        int sl = demSoLanMuon(dsBD, dsSach.arr[i].ISBN);

        printf("%d. %s (%d luot)\n",
            i + 1,
            dsSach.arr[i].TenSach,
            sl);
    }
}

// =======================================================
//     THỐNG KÊ THEO TÁC GIẢ / NXB
// =======================================================
void thongKeTheoTacGia(DanhSachSach dsSach, char tacGia[]) {
    printf("\nTac gia: %s\n", tacGia);

    for (int i = 0; i < dsSach.soLuong; i++) {
        if (strcmp(dsSach.arr[i].TacGia, tacGia) == 0)
            printf("- %s\n", dsSach.arr[i].TenSach);
    }
}

void thongKeTheoNXB(DanhSachSach dsSach, char nxb[]) {
    printf("\nNXB: %s\n", nxb);

    for (int i = 0; i < dsSach.soLuong; i++) {
        if (strcmp(dsSach.arr[i].NXB, nxb) == 0)
            printf("- %s\n", dsSach.arr[i].TenSach);
    }
}

// =======================================================
//       GHI LOG
// =======================================================
void ghiLog(const char* msg) {
    FILE* f = fopen("log.txt", "a");

    if (f == NULL) {
        printf("Loi mo file log!\n");
        return;
    }

    fprintf(f, "%s\n", msg);
    fclose(f);
}

// =======================================================
//      BACKUP
// =======================================================
void backupSach(DanhSachSach dsSach) {
    FILE* f = fopen("backup_sach.txt", "w");

    for (int i = 0; i < dsSach.soLuong; i++) {
        fprintf(f, "%s|%s|%s|%s|%d\n",
            dsSach.arr[i].ISBN,
            dsSach.arr[i].TenSach,
            dsSach.arr[i].TacGia,
            dsSach.arr[i].NXB,
            dsSach.arr[i].NamXB);
    }

    fclose(f);
}

void backupBanDoc(DanhSachBanDoc dsBD) {
    FILE* f = fopen("backup_bandoc.txt", "w");

    for (NodeBanDoc* bd = dsBD.head; bd != NULL; bd = bd->next) {

        fprintf(f, "BanDoc:%s|%s\n",
            bd->data.MaThe,
            bd->data.TenBanDoc);

        for (NodePhieuMuon* p = bd->data.dSPhieuMuon; p != NULL; p = p->next) {

            fprintf(f, "  %s|%02d/%02d/%d\n",
                p->data.MaSach,
                p->data.HanTra.ngay,
                p->data.HanTra.thang,
                p->data.HanTra.nam);
        }
    }

    fclose(f);
}

// =======================================================
//       FREE MEMORY (QA)
// =======================================================
void freePhieu(NodePhieuMuon* head) {
    while (head != NULL) {
        NodePhieuMuon* temp = head;
        head = head->next;
        free(temp);
    }
}

void freeBanDoc(DanhSachBanDoc* dsBD) {
    NodeBanDoc* p = dsBD->head;

    while (p != NULL) {
        freePhieu(p->data.dSPhieuMuon);

        NodeBanDoc* temp = p;
        p = p->next;
        free(temp);
    }

    dsBD->head = dsBD->tail = NULL;
}

void freeQueue(QueueChoMuon* q) {
    while (q->head != NULL) {
        NodeQueue* temp = q->head;
        q->head = q->head->next;
        free(temp);
    }
    q->tail = NULL;
}

void freeSach(DanhSachSach* dsSach) {
    for (int i = 0; i < dsSach->soLuong; i++) {
        freeQueue(&dsSach->arr[i].queueCho);
    }

    free(dsSach->arr);
    dsSach->arr = NULL;
}
