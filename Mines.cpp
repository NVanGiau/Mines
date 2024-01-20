#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

const int KICHTHUOC_TOIDA = 10;

const char* UNREVEALED = "-";
const char* MIN = "*";
const char* RONG = " ";

struct Cell
{
    bool coMin;
    bool revealed;
    int count;
};

void BangKhoiTao(Cell bang[][KICHTHUOC_TOIDA], int kichthuoc)
{
    for (int i =0; i < kichthuoc; i++)
    {
        for(int j =0; j < kichthuoc; j++)
        {
            bang[i][j].coMin = false;
            bang[i][j].revealed = false;
            bang[i][j].count =0;
        }
    }
}

void BangHienThi(Cell bang[][KICHTHUOC_TOIDA], int kichthuoc)
{
    cout << "    ";
    for (int i =0; i < kichthuoc; i++)
    {
        cout << i << "   ";
    }
    cout << endl;

    for (int i = 0; i < kichthuoc; i++)
    {
        cout << i << " | ";
        for(int j = 0; j < kichthuoc; j++)
        {
            if (bang[i][j].revealed)
            {
                if (bang[i][j].coMin)
                {
                    cout << MIN << " | ";
                }
                else
                {
                    cout << bang[i][j].count << " | ";
                }
            }
            else
            {
                cout << UNREVEALED << " | ";
            }
        }
        cout << endl;
    }
}

void DatMin(Cell bang[][KICHTHUOC_TOIDA], int kichthuoc, int soMin)
{
    int count =0;
    while (count < soMin)
    {
        int hang = rand() % kichthuoc;
        int cot = rand () % kichthuoc;

        if (!bang[hang][cot].coMin)
        {
            bang[hang][cot].coMin = true;
            count++;
        }
    }
}

bool toaDoHopLe(int x, int y, int kichthuoc)
{
    return x >=0 && x < kichthuoc && y >= 0 && y < kichthuoc;
}

void TinhSoLuongMinLanCan(Cell bang[][KICHTHUOC_TOIDA], int kichthuoc)
{
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < kichthuoc; i++)
    {
        for (int j = 0; j < kichthuoc; j++)
        {
            if (bang[i][j].coMin)
            {
                continue;
            }

            for (int k = 0; k < 8; k++)
            {
                int nx = i + dx[k];
                int ny = j + dy[k];

                if (toaDoHopLe(nx, ny, kichthuoc) && bang[nx][ny].coMin)
                {
                    bang[i][j].count++;
                }
            }
        }
    }
}


bool kiemTraThang(Cell bang[][KICHTHUOC_TOIDA], int kichthuoc, int soMin)
{
    int count = 0;
    for (int i = 0; i < kichthuoc; i++)
    {
        for (int j = 0; j < kichthuoc; j++)
        {
            if (bang[i][j].revealed)
            {
                count++;
            }
        }
    }
    return count == kichthuoc * kichthuoc - soMin;
}

void TroChoiDoMin(Cell bang[][KICHTHUOC_TOIDA], int kichthuoc, int soMin)
{
    int hang, cot;
    int uncoveredCount = 0;

    while (true)
    {
        BangHienThi(bang, kichthuoc);

        cout << "Hay nhap hang va cot (cach nhau boi dau cach):";
        cin >> hang >> cot;

        if (!toaDoHopLe(hang, cot, kichthuoc))
        {
            cout << "Toa do khong hop le. Vui long nhap lai." << endl;
            continue;
        }

        if (bang[hang][cot].coMin)
        {
            cout << "Tro choi ket thuc ! Ban da trung mot qua min." << endl;
            bang[hang][cot].revealed = true;
            BangHienThi(bang, kichthuoc);
            break;
        }

        bang[hang][cot].revealed = true;
        uncoveredCount++;

        if (uncoveredCount == 1)
        {
            DatMin(bang, kichthuoc, soMin);
            TinhSoLuongMinLanCan(bang, kichthuoc);
        }

        if (kiemTraThang(bang, kichthuoc, soMin))
        {
            cout << "Xin chuc mung ! Ban da chien thang." << endl;
            BangHienThi(bang, kichthuoc);
            break;
        }
    }
}

int main()
{
    int kichthuoc, soMin;

    cout << "Nhap kich thuoc bang:";
    cin >> kichthuoc;

    cout << "Nhap so luong min:";
    cin >> soMin;

    if (kichthuoc > KICHTHUOC_TOIDA)
    {
        cout << "Kich thuoc khong hop le. Kich thuoc toi da la" << KICHTHUOC_TOIDA << "." << endl;
        return 1;
    }

    if (soMin >= kichthuoc * kichthuoc)
    {
        cout << "So luong min khong hop le. So luong min phai it hon" << kichthuoc * kichthuoc << "." << endl;
        return 1;
    }

    srand(time(0));
    Cell bang[KICHTHUOC_TOIDA][KICHTHUOC_TOIDA];
    BangKhoiTao(bang, kichthuoc);
    TroChoiDoMin(bang, kichthuoc, soMin);

    return 0;
}
