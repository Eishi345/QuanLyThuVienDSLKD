NodeBanDoc* createNodeBanDoc(BanDoc x)
{
    NodeBanDoc* p = new NodeBanDoc;

    if (p == NULL)
    {
        printf("Khong du bo nho\n");
        return NULL;
    }

    p->info = x;
    p->next = NULL;

    return p;
}

// ============================================================
// ============================================================
int insertTail(DanhSachBanDoc &ds, NodeBanDoc* p)
{
    if (p == NULL)
        return 0;

    if (ds.head == NULL)
    {
        ds.head = ds.tail = p;
    }
    else
    {
        ds.tail->next = p;
        ds.tail = p;
    }

    return 1;
}
// ============================================================
// ============================================================
void showBanDoc(BanDoc x)
{
    printf("%-15s %-30s %-10d ",
           x.mathe,
           x.hoTen,
           x.namSinh);

    if (x.TrangThai == 1)
        printf("Hoat dong\n");
    else
        printf("Bi khoa\n");
}
// ============================================================
// ============================================================
void showListBanDoc(DanhSachBanDoc ds)
{
    if (ds.head == NULL)
    {
        printf("\nDanh sach rong\n");
        return;
    }

    printf("\n%-5s %-15s %-30s %-10s %-10s\n",
           "STT","MaThe","HoTen","NamSinh","TrangThai");

    int stt = 1;
    NodeBanDoc* p = ds.head;

    while (p != NULL)
    {
        printf("%-5d", stt++);
        showBanDoc(p->info);
        p = p->next;
    }
}
// ============================================================
// ============================================================
NodeBanDoc* findBanDoc_ByMaThe(DanhSachBanDoc ds, char mathe[])
{
    NodeBanDoc* p = ds.head;

    while (p != NULL)
    {
        if (strcmp(p->info.mathe, mathe) == 0)
            return p;

        p = p->next;
    }

    return NULL;
}
// ============================================================
// ============================================================
int khoaThe(DanhSachBanDoc &ds, char mathe[])
{
    NodeBanDoc* p = findBanDoc_ByMaThe(ds, mathe);

    if (p == NULL)
    {
        printf("Khong tim thay ban doc\n");
        return 0;
    }

    if (p->info.TrangThai == 0)
    {
        printf("The da bi khoa truoc do\n");
        return 0;
    }

    p->info.TrangThai = 0;

    printf("Da khoa the thanh cong\n");
    printf("Ma the: %s\n", p->info.mathe);
    printf("Ho ten: %s\n", p->info.hoTen);

    return 1;
}
// ============================================================
// ============================================================
char myToLower(char c)
{
    if (c >= 'A' && c <= 'Z')
        return c + 32;
    return c;
}
// ============================================================
// ============================================================

int myStrcmpi(const char* a, const char* b)
{
    while (*a != '\0' && *b != '\0')
    {
        if (myToLower(*a) != myToLower(*b))
            return myToLower(*a) - myToLower(*b);

        a++;
        b++;
    }

    return myToLower(*a) - myToLower(*b);
}
// ============================================================
// ============================================================

int myStrstr(const char* text, const char* pattern)
{
    if (*pattern == '\0')
        return 1;

    for (int i = 0; text[i] != '\0'; i++)
    {
        int match = 1;

        for (int j = 0; pattern[j] != '\0'; j++)
        {
            if (text[i + j] == '\0')
            {
                match = 0;
                break;
            }

            if (myToLower(text[i+j]) != myToLower(pattern[j]))
            {
                match = 0;
                break;
            }
        }

        if (match)
            return 1;
    }

    return 0;
}
// ============================================================
// ============================================================

void findSach_ByTen(SList sl, char ten[])
{
    SNode* p = sl.Head;
    int found = 0;

    while (p != NULL)
    {
        if (myStrstr(p->Info.TenSach, ten))
        {
            printf("\nMa sach: %s", p->Info.MaSach);
            printf("\nTen sach: %s", p->Info.TenSach);
            printf("\nTac gia: %s\n", p->Info.TacGia);

            found = 1;
        }

        p = p->next;
    }

    if (!found)
        printf("\nKhong tim thay sach\n");
}
// ============================================================
// ============================================================

void findSach_ByTacGia(SList sl, char tacgia[])
{
    SNode* p = sl.Head;
    int found = 0;

    while (p != NULL)
    {
        if (myStrstr(p->Info.TacGia, tacgia))
        {
            printf("\nMa sach: %s", p->Info.MaSach);
            printf("\nTen sach: %s", p->Info.TenSach);
            printf("\nTac gia: %s\n", p->Info.TacGia);

            found = 1;
        }

        p = p->next;
    }

    if (!found)
        printf("\nKhong tim thay sach\n");
}
// ============================================================
// ============================================================

NodeBanDoc* findBanDoc_ByMaThe(DanhSachBanDoc ds, char mathe[])
{
    NodeBanDoc* p = ds.head;

    while (p != NULL)
    {
        if (myStrcmpi(p->info.mathe, mathe) == 0)
            return p;

        p = p->next;
    }

    return NULL;
}
// ============================================================
// ============================================================

void sortBanDoc_ByTen(DanhSachBanDoc &ds)
{
    if (ds.head == NULL)
        return;

    int swapped;

    do
    {
        swapped = 0;

        NodeBanDoc* p = ds.head;

        while (p->next != NULL)
        {
            NodeBanDoc* q = p->next;

            if (myStrcmpi(p->info.hoTen, q->info.hoTen) > 0)
            {
                BanDoc temp = p->info;
                p->info = q->info;
                q->info = temp;

                swapped = 1;
            }

            p = p->next;
        }

    } while (swapped);
}
// ============================================================
// ============================================================
void sortSach_ByNamXB(SList* sl)
{
    int swapped;

    do
    {
        swapped = 0;

        SNode* p = sl->Head;

        while (p->next != NULL)
        {
            SNode* q = p->next;

            int canSwap = 0;

            if (p->Info.NamXB > q->Info.NamXB)
                canSwap = 1;

            else if (p->Info.NamXB == q->Info.NamXB &&
                     myStrcmpi(p->Info.TenSach, q->Info.TenSach) > 0)
                canSwap = 1;

            if (canSwap)
            {
                Book temp = p->Info;
                p->Info = q->Info;
                q->Info = temp;

                swapped = 1;
            }

            p = p->next;
        }

    } while (swapped);

    printf("\nDa sap xep sach theo nam XB.\n");
}
