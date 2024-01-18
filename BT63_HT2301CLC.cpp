#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int kichthuoc = 5; //kích thước của bảng trò chơi
const int luongmin = 5; // lượng mìn trong bảng
char bang[kichthuoc][kichthuoc]; //lưu thông tin bảng chơi
char hienthibang[kichthuoc][kichthuoc]; // bảng hiển thị
void khoitaoBang()
{
    for (int i = 0; i < kichthuoc; ++i)
    {
        for (int j = 0; j < kichthuoc; ++j)
        {
            bang[i][j] = '-';
            hienthibang[i][j] = '-';
        }
    }
}
void hienthiBang(bool hienMin = false)
{
    cout << "  ";
    for (int i = 0; i < kichthuoc; ++i)
    {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < kichthuoc; ++i)
    {
        cout << i << " ";
        for (int j = 0; j < kichthuoc; ++j)
        {
            if (hienMin && bang[i][j] == '*')
            {
                cout << "* ";
            } else
            {
                cout << hienthibang[i][j] << " ";
            }
        }
        cout << endl;
    }
}

void datMin()
{
    srand(time(nullptr));
    for (int i = 0; i < luongmin; ++i)
    {
        int hangmoi = rand() % kichthuoc;
        int cotmoi = rand() % kichthuoc;
        while (bang[hangmoi][cotmoi] == '*')
        {
            hangmoi = rand() % kichthuoc;
            cotmoi = rand() % kichthuoc;
        }
        bang[hangmoi][cotmoi] = '*';
    }
}

bool hopLe(int hang, int cot)
{
    return (hang >= 0 && hang < kichthuoc && cot >= 0 && cot < kichthuoc);
}

int demMinLienKe(int hang, int cot)
{
    int dem = 0;
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            if (hopLe(hang + i, cot + j) && bang[hang + i][cot + j] == '*')
            {
                dem++;
            }
        }
    }

    return dem;
}

void kichhoat(int hang, int cot)
{
    if (hopLe(hang, cot) && hienthibang[hang][cot] == '-')
    {
        hienthibang[hang][cot] = '0' + demMinLienKe(hang, cot);
        if (hienthibang[hang][cot] == '0')
        {
            for (int i = -1; i <= 1; ++i)
            {
                for (int j = -1; j <= 1; ++j)
                {
                    kichhoat(hang + i, cot + j);
                }
            }
        }
    }
}

bool kiemtrathang()
{
    for (int i = 0; i < kichthuoc; ++i)
    {
        for (int j = 0; j < kichthuoc; ++j)
        {
            if (bang[i][j] != '*' && hienthibang[i][j] == '-')
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    khoitaoBang();
    datMin();

    int hang, cot;

    do
    {
        hienthiBang();
        cout << "Nhap toa do hang va cot ma ban muon di chuyen (cach nhau boi khoang trang): ";
        cin >> hang >> cot;
        if (bang[hang][cot] == '*')
        {
            cout << "That bai, ban da dam min." << endl;
            hienthiBang(true);
            break;
        } else
        {
            kichhoat(hang, cot);
        }
        if (kiemtrathang())
        {
            cout << "Ban da chien thang, chuc mung" << endl;
            hienthiBang(true);
            break;
        }

    } while (true);

    return 0;
}
