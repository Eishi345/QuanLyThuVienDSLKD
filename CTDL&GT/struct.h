/*
Họ và tên   :  Dương Thị Anh Thơ
MSSV        :  2045250186   
Lớp         :  16DHKHDL04
*/
//================================================================
#ifndef STRUCT_H
#define STRUCT_H
//================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
//================================================================
/*
    Cấu trúc Book:
    Lưu trữ thông tin của một đầu sách trong thư viện
*/
 typedef struct  
{
    char MaSach[20];        // Mã sách (ISBN)
    char TenSach[100];    // Tên sách
    char TacGia[50];      // Tên tác giả
    int NamXuatBan;       // Năm xuất bản
    int SoLuongTong;          // Tổng số bản in
    int ConLai;           // Số lượng còn lại trong thư viện
    int DaXoa;            // Đánh dấu xóa (0: còn sử dụng, 1: đã xóa)
}Book;
 //================================================================
/*
    Cấu trúc Reader:
    Lưu trữ thông tin của một bạn đọc
*/
typedef struct 
{
    char MaBanDoc[20];    // Mã bạn đọc
    char HoTen[50];       // Họ tên bạn đọc
    int KhoaThe;          // Trạng thái thẻ (0: hoạt động, 1: bị khóa)
}Reader;
//================================================================
/*
    Node của Danh sách liên kết đơn
    Mỗi node chứa thông tin 1 bạn đọc
*/
typedef struct SNode
{
    Reader data;
    struct SNode* Next;
} SNode;

#endif


//====================================================================


