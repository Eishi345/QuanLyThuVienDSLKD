#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <string.h>

// ---------------------------------------------------------
// 1. CẤU TRÚC THỜI GIAN VÀ PHIẾU MƯỢN
// ---------------------------------------------------------
struct Date {
    int ngay;
    int thang;
    int nam;
};

struct PhieuMuon {
    char MaPhieu[20];
    char MaThe[20]; //Tức mã bạn đọc
    char MaSach[20];
    Date NgayMuon;
    Date HanTra;
    int TrangThai; // 0: Đang mượn, 1: Đã trả, 2: Quá hạn
};

// Node cho DSLK đơn quản lý Phiếu mượn của từng Bạn đọc
struct NodePhieuMuon {
    PhieuMuon data;
    NodePhieuMuon* next;
};

// ---------------------------------------------------------
// 2. CẤU TRÚC BẠN ĐỌC (Quản lý bằng DSLK đơn)
// ---------------------------------------------------------
struct BanDoc {
    char MaThe[20];
    char TenBanDoc[50];
    int TrangThai; // 1: Đang hoạt động, 0: Khóa/Đánh dấu xóa

    // Quản lý sách đang mượn (quan hệ 1-n)
    NodePhieuMuon* dSPhieuMuon;
    int SoSachDangMuon; // Validate tối đa 5 cuốn
};

struct NodeBanDoc {
    BanDoc data;
    NodeBanDoc* next;
};

struct DanhSachBanDoc {
    NodeBanDoc* head;
    NodeBanDoc* tail;
    int soLuong;
};

// ---------------------------------------------------------
// 3. CẤU TRÚC HÀNG ĐỢI (Queue chờ mượn sách)
// ---------------------------------------------------------
// Node lưu thông tin bạn đọc đang chờ mượn sách
struct NodeQueue {
    char MaBanDoc[20];
    NodeQueue* next;
};

// Hàng đợi chờ mượn (FIFO)
struct QueueChoMuon {
    NodeQueue* head;
    NodeQueue* tail;
};

// ---------------------------------------------------------
// 4. CẤU TRÚC SÁCH (Quản lý bằng DANH SÁCH ĐẶC - Mảng động)
// ---------------------------------------------------------
struct Sach {
    char ISBN[20];
    char TenSach[100];
    char TacGia[50];
    char NXB[50];
    int NamXB;
    int SoLuongIn;
    int SoLuongConLai;

    // Mỗi đầu sách có một Queue riêng để lưu danh sách chờ
    QueueChoMuon queueCho;
    int TrangThai; // 1: Đang sử dụng, 0: Đánh dấu hủy
};

// Danh sách đặc (Mảng động) quản lý các đầu sách
struct DanhSachSach {
    Sach* arr;       // Con trỏ trỏ đến mảng động chứa các sách
    int capacity;    // Sức chứa tối đa hiện tại của mảng (để cấp phát thêm khi đầy)
    int soLuong;     // Số lượng đầu sách thực tế đang có
};

#endif // STRUCTS_H