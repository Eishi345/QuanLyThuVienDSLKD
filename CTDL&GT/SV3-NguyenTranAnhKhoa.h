#ifndef	QUEUE_MUON_TRA_H
#define QUEUE_MUON_TRA_H

#include "Structs.h"

void menuConMuonTra(DanhSachSach& dsSach, DanhSachBanDoc& p, char MaThe[], char ISBN[]);

int muonSach(DanhSachSach& dsSach, DanhSachBanDoc& p, char MaThe[], char ISBN[]);

int traSach(DanhSachSach& dsSach, DanhSachBanDoc& p, char MaThe[], char ISBN[]);

#endif