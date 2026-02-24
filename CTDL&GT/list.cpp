#include "list.h"

  // Tạo một node mới từ dữ liệu bạn đọc

SNode* createSNode(Reader r) 
{
    // Cấp phát bộ nhớ cho node
    SNode* p = (SNode*)malloc(sizeof(SNode));

    // Kiểm tra cấp phát thành công hay không
    if (p == NULL) 
    {
        printf("\nKhong cap phat duoc bo nho!");
        return NULL;
    }

    // Gán dữ liệu và khởi tạo con trỏ next
    p->data = r;
    p->Next = NULL;
    return p;
}

   // Khởi tạo danh sách liên kết rỗng
void initList(SNode** head) 
{
    *head = NULL;
}

   //Thêm bạn đọc vào cuối danh sách liên kết
void addReader(SNode** head, Reader r) 
{
    SNode* p = createSNode(r);

    // Nếu danh sách rỗng
    if (*head == NULL)
        *head = p;
    else 
    {
        // Duyệt đến node cuối cùng
        SNode* temp = *head;
        while (temp->Next != NULL) 
            temp = temp->Next;
        temp->Next = p;
    }
}

   //Hiển thị danh sách bạn đọc
void displayReaders(SNode* head) 
{
    SNode* temp = head;

    while (temp != NULL) 
    {
        printf("\nMa BD: %s | Ten: %s",
            temp->data.MaBanDoc,
            temp->data.HoTen);
        temp = temp->Next;
    }
}

  //Giải phóng toàn bộ bộ nhớ của danh sách liên kết
void freeList(SNode** head) 
{
    SNode* temp;
    while (*head != NULL) 
    {
        temp = *head;
        *head = (*head)->Next;
        free(temp);
    }
}