#ifndef LIST_H
#define LIST_H

#include "struct.h"

SNode* createSNode(Reader r);	//Hàm tạo node mới cho danh sách liên kết
void initList(SNode** head);	//Khởi tạo danh sách liên kết rỗng
void addReader(SNode** head, Reader r);	//Thêm một bạn đọc vào cuối danh sách
void displayReaders(SNode* head);	//Hiển thị danh sách bạn đọc
void freeList(SNode** head);	//Giải phóng toàn bộ bộ nhớ của danh sách liên kết

#endif
