#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX_VEHICLES = 3;
const int MAX_LOTS = 10;

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;
    double phi_do;

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);

    int lay_ma_xe() const;
    string lay_loai_xe() const;
    double lay_phi_do() const;
    double tinh_phi() const;
    void hien_thi() const;
};

phuong_tien::phuong_tien() : ma_xe(0), loai_xe(""), gio_vao(0), tg_do(0) {}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg)
    : ma_xe(ma), loai_xe(loai), gio_vao(gio), tg_do(tg) {
    tinh_phi();
	}

int phuong_tien::lay_ma_xe() const { return ma_xe; }
string phuong_tien::lay_loai_xe() const { return loai_xe; }

double phuong_tien::lay_phi_do()const {return phi_do}

double phuong_tien::tinh_phi() const {
    double gia = (loai_xe == "Car") ? 6.0 : (loai_xe == "Motorcycle") ? 4.0 : 2.0;
    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
    double tong = 0;
    for (int h = 0; h < tg_do; ++h) {
        if (h < 2) tong += gia * (cao_diem ? 1.30 : 0.95);
        else       tong += gia * 0.90;
    }
    phi_do = tong;
    return phi_do;
}

void phuong_tien::hien_thi() const {
    cout << "  ID: " << ma_xe << " | " << loai_xe
         << " | " << gio_vao << "h | " << tg_do << "h"
         << " | Phi: $" << fixed << setprecision(2) << tinh_phi() << "\n";
}

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    phuong_tien ds_xe[MAX_VEHICLES];
    int so_xe;
    int suc_chua()const ;

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    bool them(phuong_tien v);
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;
    void hien_thi() const;
    bool co_loai(string loai, int& dem, double& tong) const;
};

bai_xe::bai_xe() : ma_bai(0), kich_thuoc('S'), so_xe(0) {}

bai_xe::bai_xe(int ma, char kt) : ma_bai(ma), kich_thuoc(kt), so_xe(0) {
	if(kt == 'S' || kt == 'M' || kt == 'L'){
		kich_thuoc = kt;
	}else{
		kich_thuoc = 'S';
	}
}
int bai_xe::suc_chua()const {
	if(kich_thuoc == 'S') return 1;
	if(kich_thuoc == 'M') return 2;
	return 3;
}
int bai_xe::lay_ma() const { return ma_bai; }

bool bai_xe::them(phuong_tien v) {
    int cap = suc_chua();
    if (so_xe >= cap || so_xe >= MAX_VEHICLES) {
        return false;
    }
    ds_xe[so_xe] = v;
    so_xe++;
    return true;
}

bool bai_xe::xoa(int ma_xe) {
    for (int i = 0; i < so_xe; i++) {
        if (ds_xe[i].lay_ma_xe() == ma_xe) {
            for (int j = i; j < so_xe - 1; ++j) {
                ds_xe[j] = ds_xe[j + 1];
            }
            so_xe--;
            return true;
        }
    }
    return false;
}

bool bai_xe::chua(int ma_xe) const {
    for (int i = 0; i < so_xe; i++) {
        if (ds_xe[i].lay_ma_xe() == ma_xe) return true;
    }
    return false;
}

void bai_xe::hien_thi() const {
    int cap = suc_chua();
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
         << so_xe << "/" << cap << " xe\n";
    for (int i = 0; i < so_xe; ++i) {
        ds_xe[i].hien_thi();
    }
}

bool bai_xe::co_loai(string loai, int& dem, double& tong) const {
    dem = 0; tong = 0;
    for (int i = 0; i < so_xe; i++) {
        if (ds_xe[i].lay_loai_xe() == loai) { 
            ++dem; 
            tong += ds_xe[i].tinh_phi(); 
        }
    }
    return dem > 0;
}

class SystemInterface {
private:
    bai_xe ds_bai[MAX_LOTS];
    int so_bai;

public:
    SystemInterface();
    void runMenu();
};

SystemInterface::SystemInterface() : so_bai(0) {}

void SystemInterface::runMenu() {
    int chon;
    while (true) {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        cout << "Chon: ";
        cin >> chon;
//các e chuy?n sang l?nh switch cho th?y
       switch(chon){
       	case 1: {
                int ma; char kt;
                cout << "Ma bai: "; cin >> ma;
                cout << "Kich thuoc (S/M/L): "; cin >> kt;
                if(kt != 'S' && kt != 'M' && kt != 'L'){
                	cout << "Loi ky tu";
                	break;
				}
                ds_bai[so_bai] = bai_xe(ma, kt);
                so_bai++;
                cout << "Da tao bai " << ma << "\n";
                break;
            }
		case 2: {
                int ma, gio, tg; string loai;
                cout << "Ma xe: "; cin >> ma;
                cout << "Loai (Car/Motorcycle/Bicycle): "; cin >> loai;
                cout << "Gio vao (0-23): "; cin >> gio;
                if(gio < 0 || gio > 23){
				cout << "Loi sai thoi gian khi xe di vao";
				break;
				}
                cout << "Thoi luong (1-23): "; cin >> tg;
                if(tg < 1 || tg > 23){
				cout << "Loi sai thoi gian do xe";
				break;
				}
                phuong_tien v(ma, loai, gio, tg);
                bool ok = false;
                for (int i = 0; i < so_bai; i++) {
                    if (ds_bai[i].them(v)) {
                        ok = true;
                        break;
                    }
                }
                if (ok) cout << "Da them xe " << ma << " | Phi: $" << fixed << setprecision(2) << v.tinh_phi() << "\n";
                else    cout << "Tat ca bai da day!\n";
                break;
            }
            case 3: {
                int ma;
                cout << "Ma bai can xoa: "; cin >> ma;
                int so_bai_cu = so_bai;
                for (int i = 0; i < so_bai; i++) {
                    if (ds_bai[i].lay_ma() == ma) {
                        for (int j = i; j < so_bai - 1; j++) {
                            ds_bai[j] = ds_bai[j + 1];
                        }
                        so_bai--;
                        cout << "Da xoa bai " << ma << "\n";
                        break;
                    }
                }
                break;
            }
            case 4: {
                int ma;
                cout << "Ma xe can lay ra: "; cin >> ma;
                bool ok = false;
                for (int i = 0; i < so_bai; i++) {
                    if (ds_bai[i].xoa(ma)) {
                        ok = true;
                        break;
                    }
                }
                cout << (ok ? "Da lay xe ra\n" : "Khong tim thay xe\n");
                break;
            }
            case 5: {
                for (int i = 0; i < so_bai; i++) {
                    ds_bai[i].hien_thi();
                }
                break;
            }
            case 6: {
                int ma;
                cout << "Ma bai: "; cin >> ma;
                bool tim_thay = false;
                for (int i = 0; i < so_bai; i++) {
                    if (ds_bai[i].lay_ma() == ma) {
                        ds_bai[i].hien_thi();
                        tim_thay = true;
                        break;
                    }
                }
                break;
            }
            case 7: {
                string loai;
                cout << "Loai xe: "; cin >> loai;
                int dem, tong_xe = 0; double tong;
                for (int i = 0; i < so_bai; i++) {
                    if (ds_bai[i].co_loai(loai, dem, tong)) {
                        ds_bai[i].hien_thi();
                        tong_xe += dem;
                    }
                }
                break;
            }
            case 8: {
                string loai_arr[3] = {"Car", "Motorcycle", "Bicycle"};
                for (int t = 0; t < 3; ++t) {
                    int dem = 0; double tong = 0;
                    int d; double s;
                    for (int i = 0; i < so_bai; i++) {
                        ds_bai[i].co_loai(loai_arr[t], d, s);
                        dem += d; 
                        tong += s;
                    }
                    cout << loai_arr[t] << ": ";
                    if (dem == 0) cout << "khong co xe\n";
                    else cout << dem << " xe | TB: $" << fixed << setprecision(2) << tong / dem << "\n";
                }
                break;
            }
            case 9:
                cout << "Thoat chuong trinh.\n";
                return;
            default:
                cout << "Lua chon khong hop le! Vui long chon tu 1 den 9.\n";
	   }
    }
}

int main() {
    SystemInterface sys;
    sys.runMenu();
    return 0;
}	
