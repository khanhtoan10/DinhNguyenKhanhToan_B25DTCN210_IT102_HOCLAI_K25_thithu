#include <stdio.h>
#include <string.h>

#define MAX_SP 100
#define MAX_HD_LINES 20

typedef struct {
    char ma[11];
    char ten[41];
    char dvt[11];
    float gia;
    int sl;
} SanPham;

typedef struct {
    char ma[11];
    char ten[41];
    char dvt[11];
    int slMua;
    float donGia;
    float thanhTien;
} DongHoaDon;

void xoaXuongDong(char str[]) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void themSanPham(SanPham ds[], int *n) {
    if (*n >= MAX_SP) {
        printf("Danh sach da day, khong the them!\n");
        return;
    }

    SanPham sp;
    while (1) {
        printf("Nhap ma san pham (<= 10 ky tu): ");
        fgets(sp.ma, sizeof(sp.ma), stdin);
        xoaXuongDong(sp.ma);

        if (strlen(sp.ma) == 0) {
            printf("Ma san pham khong duoc de trong. Vui long nhap lai!\n");
            continue;
        }

        int trung = 0;
        for (int i = 0; i < *n; i++) {
            if (strcmp(ds[i].ma, sp.ma) == 0) {
                trung = 1;
                break;
            }
        }
        if (trung) {
            printf("Ma san pham da ton tai. Vui long nhap ma khac!\n");
        } else {
            break;
        }
    }

    printf("Nhap ten san pham (<= 40 ky tu): ");
    fgets(sp.ten, sizeof(sp.ten), stdin);
    xoaXuongDong(sp.ten);

    printf("Nhap don vi tinh (<= 10 ky tu): ");
    fgets(sp.dvt, sizeof(sp.dvt), stdin);
    xoaXuongDong(sp.dvt);

    do {
        printf("Nhap don gia (VND, > 0): ");
        if (scanf("%f", &sp.gia) != 1 || sp.gia <= 0) {
            printf("Don gia phai la so thuc lon hon 0. Nhap lai!\n");
            while(getchar() != '\n');
        } else {
            while(getchar() != '\n');
            break;
        }
    } while (1);

    do {
        printf("Nhap so luong ton (>= 0): ");
        if (scanf("%d", &sp.sl) != 1 || sp.sl < 0) {
            printf("So luong phai la so nguyen >= 0. Nhap lai!\n");
            while(getchar() != '\n');
        } else {
            while(getchar() != '\n');
            break;
        }
    } while (1);

    ds[*n] = sp;
    (*n)++;
    printf("Them san pham thanh cong!\n");
}

void hienThiDanhSach(SanPham ds[], int n) {
    if (n == 0) {
        printf("Chua co san pham nao, hay chon 1 truoc.\n");
        return;
    }

    printf("\n========================================================================================\n");
    printf("%-4s | %-10s | %-25s | %-10s | %-12s | %-6s | %-15s\n", 
           "STT", "Ma SP", "Ten San Pham", "DVT", "Don Gia", "SL", "Gia Tri Ton");
    printf("----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        float giaTriTon = ds[i].gia * ds[i].sl;
        printf("%-4d | %-10s | %-25s | %-10s | %-12.0f | %-6d | %-15.0f\n",
               i + 1, ds[i].ma, ds[i].ten, ds[i].dvt, ds[i].gia, ds[i].sl, giaTriTon);
    }
    printf("========================================================================================\n");
}

int timTheoMa(SanPham ds[], int n, char ma[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(ds[i].ma, ma) == 0) {
            return i;
        }
    }
    return -1;
}

void chucNangTimKiem(SanPham ds[], int n) {
    if (n == 0) {
        printf("Chua co san pham nao, hay chon 1 truoc.\n");
        return;
    }
    char ma[11];
    printf("Nhap ma san pham can tim: ");
    fgets(ma, sizeof(ma), stdin);
    xoaXuongDong(ma);

    int idx = timTheoMa(ds, n, ma);
    if (idx != -1) {
        printf("\nTim thay san pham:\n");
        printf("Ma: %s | Ten: %s | DVT: %s | Don gia: %.0f | SL: %d\n",
               ds[idx].ma, ds[idx].ten, ds[idx].dvt, ds[idx].gia, ds[idx].sl);
    } else {
        printf("Khong tim thay\n");
    }
}

void capNhatSanPham(SanPham ds[], int n) {
    if (n == 0) {
        printf("Chua co san pham nao, hay chon 1 truoc.\n");
        return;
    }
    char ma[11];
    printf("Nhap ma san pham can cap nhat: ");
    fgets(ma, sizeof(ma), stdin);
    xoaXuongDong(ma);

    int idx = timTheoMa(ds, n, ma);
    if (idx == -1) {
        printf("Khong tim thay san pham co ma nay!\n");
        return;
    }

    printf("Thong tin hien tai: %s - %s (Gia: %.0f, SL: %d)\n", ds[idx].ma, ds[idx].ten, ds[idx].gia, ds[idx].sl);

    do {
        printf("Nhap don gia moi (> 0): ");
        if (scanf("%f", &ds[idx].gia) != 1 || ds[idx].gia <= 0) {
            printf("Don gia khong hop le. Nhap lai!\n");
            while(getchar() != '\n');
        } else {
            while(getchar() != '\n');
            break;
        }
    } while (1);

    int slThem;
    do {
        printf("Nhap so luong nhap them (>= 0): ");
        if (scanf("%d", &slThem) != 1 || slThem < 0) {
            printf("So luong khong hop le. Nhap lai!\n");
            while(getchar() != '\n');
        } else {
            while(getchar() != '\n');
            break;
        }
    } while (1);

    ds[idx].sl += slThem;
    printf("Cap nhat thanh cong!\n");
}

void xoaSanPham(SanPham ds[], int *n) {
    if (*n == 0) {
        printf("Chua co san pham nao, hay chon 1 truoc.\n");
        return;
    }
    char ma[11];
    printf("Nhap ma san pham can xoa: ");
    fgets(ma, sizeof(ma), stdin);
    xoaXuongDong(ma);

    int idx = timTheoMa(ds, *n, ma);
    if (idx == -1) {
        printf("Khong tim thay san pham co ma nay!\n");
        return;
    }

    for (int i = idx; i < *n - 1; i++) {
        ds[i] = ds[i + 1];
    }
    (*n)--;
    printf("Xoa san pham thanh cong!\n");
}

void banHang(SanPham ds[], int n, int *soHoaDonBan, float *tongDoanhThu) {
    if (n == 0) {
        printf("Chua co san pham nao, hay chon 1 truoc.\n");
        return;
    }

    DongHoaDon hd[MAX_HD_LINES];
    int soDong = 0;
    char ma[11];
    int slMua;

    printf("\n--- BAN HANG (Nhap ma '0' hoac de trong de ket thuc) ---\n");
    while (soDong < MAX_HD_LINES) {
        printf("Nhap ma san pham (hoac 0 de dung): ");
        fgets(ma, sizeof(ma), stdin);
        xoaXuongDong(ma);

        if (strcmp(ma, "0") == 0 || strlen(ma) == 0) {
            break;
        }

        int idx = timTheoMa(ds, n, ma);
        if (idx == -1) {
            printf("Loi: Khong co ma san pham nay!\n");
            continue;
        }

        if (ds[idx].sl == 0) {
            printf("Loi: San pham da het hang!\n");
            continue;
        }

        printf("San pham: %s (Ton kho: %d)\n", ds[idx].ten, ds[idx].sl);
        printf("Nhap so luong mua: ");
        if (scanf("%d", &slMua) != 1 || slMua <= 0) {
            printf("So luong mua khong hop le!\n");
            while(getchar() != '\n');
            continue;
        }
        while(getchar() != '\n');

        if (slMua > ds[idx].sl) {
            printf("Loi: Khong du hang (Chi con lai %d)!\n", ds[idx].sl);
            continue;
        }

        ds[idx].sl -= slMua;

        int daCo = -1;
        for (int i = 0; i < soDong; i++) {
            if (strcmp(hd[i].ma, ds[idx].ma) == 0) {
                daCo = i;
                break;
            }
        }

        if (daCo != -1) {
            hd[daCo].slMua += slMua;
            hd[daCo].thanhTien = hd[daCo].slMua * hd[daCo].donGia;
        } else {
            strcpy(hd[soDong].ma, ds[idx].ma);
            strcpy(hd[soDong].ten, ds[idx].ten);
            strcpy(hd[soDong].dvt, ds[idx].dvt);
            hd[soDong].slMua = slMua;
            hd[soDong].donGia = ds[idx].gia;
            hd[soDong].thanhTien = slMua * ds[idx].gia;
            soDong++;
        }
        printf("Da them vao hoa don.\n");
    }

    if (soDong == 0) {
        printf("Chua co hang nao duoc mua.\n");
        return;
    }

    float tongTien = 0;
    for (int i = 0; i < soDong; i++) {
        tongTien += hd[i].thanhTien;
    }

    float giamGia = 0;
    if (tongTien >= 500000) {
        giamGia = tongTien * 0.10;
    }
    float thanhToan = tongTien - giamGia;

    printf("\n======================= HOA DON BAN HANG =======================\n");
    printf("%-4s | %-10s | %-20s | %-5s | %-8s | %-10s | %-12s\n", 
           "STT", "Ma SP", "Ten SP", "DVT", "SL", "Don Gia", "Thanh Tien");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < soDong; i++) {
        printf("%-4d | %-10s | %-20s | %-5s | %-8d | %-10.0f | %-12.0f\n",
               i + 1, hd[i].ma, hd[i].ten, hd[i].dvt, hd[i].slMua, hd[i].donGia, hd[i].thanhTien);
    }
    printf("----------------------------------------------------------------\n");
    printf("Tong tien hang:     %.0f VND\n", tongTien);
    printf("Giam gia (10%%):     %.0f VND\n", giamGia);
    printf("Tong thanh toan:    %.0f VND\n", thanhToan);
    printf("================================================================\n");

    (*soHoaDonBan)++;
    (*tongDoanhThu) += thanhToan;
}

void sapHetHang(SanPham ds[], int n) {
    if (n == 0) {
        printf("Chua co san pham nao, hay chon 1 truoc.\n");
        return;
    }

    int dem = 0;
    printf("\n--- DANH SACH SAN PHAM SAP HET HANG (SL < 5) ---\n");
    printf("%-4s | %-10s | %-25s | %-10s | %-6s\n", "STT", "Ma SP", "Ten San Pham", "DVT", "SL Ton");
    printf("-------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        if (ds[i].sl < 5) {
            dem++;
            printf("%-4d | %-10s | %-25s | %-10s | %-6d\n",
                   dem, ds[i].ma, ds[i].ten, ds[i].dvt, ds[i].sl);
        }
    }
    if (dem == 0) {
        printf("Khong co san pham nao sap het hang.\n");
    } else {
        printf("-------------------------------------------------------------------\n");
        printf("Tong so mat hang sap het: %d\n", dem);
    }
}

void sapXepDonGia(SanPham ds[], int n) {
    if (n == 0) {
        printf("Chua co san pham nao, hay chon 1 truoc.\n");
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (ds[i].gia > ds[j].gia) {
                SanPham temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            }
        }
    }
    printf("Da sap xep danh sach theo don gia tang dan thanh cong!\n");
    hienThiDanhSach(ds, n);
}

void thongKe(SanPham ds[], int n, int soHoaDonBan, float tongDoanhThu) {
    if (n == 0) {
        printf("Chua co san pham nao, hay chon 1 truoc.\n");
        return;
    }

    float tongGiaTriTon = 0;
    float maxGia = ds[0].gia;
    int idxMaxGia = 0;

    for (int i = 0; i < n; i++) {
        tongGiaTriTon += ds[i].gia * ds[i].sl;
        if (ds[i].gia > maxGia) {
            maxGia = ds[i].gia;
            idxMaxGia = i;
        }
    }

    printf("\n======================= THONG KE CUA HANG =======================\n");
    printf("1. Tong so mat hang trong kho: %d\n", n);
    printf("2. Tong gia tri ton kho:        %.0f VND\n", tongGiaTriTon);
    printf("3. San pham co don gia cao nhat: %s - %s (%.0f VND)\n", 
           ds[idxMaxGia].ma, ds[idxMaxGia].ten, ds[idxMaxGia].gia);
    printf("4. So hoa don da ban:          %d\n", soHoaDonBan);
    printf("5. Tong doanh thu:             %.0f VND\n", tongDoanhThu);
    printf("=================================================================\n");
}

int main() {
    SanPham ds[MAX_SP];
    int n = 0;
    int chon;
    int soHoaDonBan = 0;
    float tongDoanhThu = 0;

    do {
        printf("\n====== QUAN LY CUA HANG ======\n");
        printf("1. Them san pham\n");
        printf("2. Hien thi danh sach san pham\n");
        printf("3. Tim san pham theo ma\n");
        printf("4. Cap nhat gia / nhap them hang\n");
        printf("5. Xoa san pham\n");
        printf("6. Ban hang va in hoa don\n");
        printf("7. Danh sach san pham sap het hang\n");
        printf("8. Sap xep theo don gia tang dan\n");
        printf("9. Thong ke\n");
        printf("0. Thoat\n");
        printf("==============================\n");
        printf("Chon: ");

        if (scanf("%d", &chon) != 1) {
            printf("Lua chon khong hop le. Vui long nhap so!\n");
            while(getchar() != '\n');
            continue;
        }
        while(getchar() != '\n');

        if (chon >= 2 && chon <= 9 && n == 0) {
            printf("Chua co san pham nao, hay chon 1 truoc.\n");
            continue;
        }

        switch (chon) {
            case 1:
                themSanPham(ds, &n);
                break;
            case 2:
                hienThiDanhSach(ds, n);
                break;
            case 3:
                chucNangTimKiem(ds, n);
                break;
            case 4:
                capNhatSanPham(ds, n);
                break;
            case 5:
                xoaSanPham(ds, &n);
                break;
            case 6:
                banHang(ds, n, &soHoaDonBan, &tongDoanhThu);
                break;
            case 7:
                sapHetHang(ds, n);
                break;
            case 8:
                sapXepDonGia(ds, n);
                break;
            case 9:
                thongKe(ds, n, soHoaDonBan, tongDoanhThu);
                break;
            case 0:
                printf("Cam on ban da su dung chuong trinh!\n");
                break;
            default:
                printf("Lua chon khong hop le! Vui long chon tu 0 den 9.\n");
        }
    } while (chon != 0);

    return 0;
}
