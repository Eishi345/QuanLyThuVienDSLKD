#include "menu.h"
#include <stdio.h>

/*
    Hàm menu chính
    Cho phép người dùng lựa chọn các chức năng của hệ thống
*/
void menuChinh() 
{
    int choice;

    do {
        printf("\n===== QUAN LY THU VIEN =====\n");
        printf("\n0. Thoat");
        printf("\n1. Quan ly sach");
        printf("\n2. Quan ly ban doc");
        printf("\n3. Muon / Tra sach");
        printf("\n4. Tim kiem - Sap xep");
        printf("Choice: ");
        scanf("%d", &choice);

        // Xử lý lựa chọn của người dùng
        switch (choice) 
        {
        case 1:
            printf("\n Quan ly sach\n");
            break;
        case 2:
            printf("\n Quan ly ban doc\n");
            break;
        case 3:
            printf("\n Muon / Tra sach\n");
            break;
        case 4:
            printf("\n Tim kiem - Sap xep\n");
            break;
        case 0:
            printf("\n Thoat chuong trinh.\n");
            break;
        default:
            printf("\n Lua chon khong hop le!\n");
        }
    } while (choice != 0);
}