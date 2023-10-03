// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    BitLen = len;
    if (len < 0)throw"len<0";
    if (len % (sizeof(TELEM)*8) == 0)
        MemLen = len / (sizeof(TELEM) * 8);
    else
        MemLen = (len / (sizeof(TELEM) * 8))+1;
    pMem = new TELEM[MemLen];
    for (size_t i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }

}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (size_t i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    if (pMem != nullptr) {
        delete[] pMem;
        pMem = nullptr;
        BitLen = 0;
    }
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n<0 || n>BitLen)throw "Неверный индекс";
    return n/(sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    int a = n % (sizeof(TELEM) * 8);
    TELEM M = 1;
    M = M << a;
    return M;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n > -1) && (n < BitLen))
    {
        int index = GetMemIndex(n);
        TELEM M = GetMemMask(n);
        pMem[index] |= M;
    }
    else
        throw "error setbit";
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n > -1) && (n < BitLen))
    {
        int index = GetMemIndex(n);
        TELEM M = GetMemMask(n);
        pMem[index] &= ~M;
    }
    else
        throw "error clr";
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    int res = 0;
    if ((n > -1) && (n < BitLen))
    {
        int index = GetMemIndex(n);
        TELEM M = GetMemMask(n);
        if (M == (M & pMem[index]))
            res = 1;

    }
    else
        throw "error get";
    return res;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf) {
        TBitField::~TBitField();
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (size_t i = 0; i < MemLen; i++) {
            pMem[i] = bf.pMem[i];
        }
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    int flag = 0;
    if (BitLen == bf.BitLen && MemLen == bf.MemLen)
        for (size_t i = 0; i < MemLen; i++) {
            if (pMem[i] != bf.pMem[i])flag = 1;
        }
    else flag = 1;
    if (flag == 1)
        return 0; else return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    int flag = 0;
    if (BitLen == bf.BitLen && MemLen == bf.MemLen)
        for (size_t i = 0; i < MemLen; i++) {
            if (pMem[i] != bf.pMem[i])flag = 1;
        }
    else flag = 1;
    if (flag == 1)
        return 1; else return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int maxlen = BitLen;
    if (maxlen < bf.BitLen)
        maxlen = bf.BitLen;
    TBitField res(maxlen);
    for (int i = 0; i < MemLen; i++)
        res.pMem[i] = pMem[i];
    for (int i = 0; i < bf.MemLen; i++)
        res.pMem[i] |= bf.pMem[i];
    return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int maxlen = BitLen;
    if (maxlen < bf.BitLen)
        maxlen = bf.BitLen;
    TBitField Res(maxlen);
    for (int i = 0; i < MemLen; i++)
        Res.pMem[i] = pMem[i];
    for (int i = 0; i < bf.MemLen; i++)
        Res.pMem[i] &= bf.pMem[i];
    return Res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField A(BitLen);
    for (int i = 0; i < BitLen; i++)
    {
        if (GetBit(i) == 0)
            A.SetBit(i);

    }
    return A;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    string tmp;
    istr >> tmp;
    if (tmp.size() != bf.GetLength())throw"bad length"; else {
        for (int i = 0; i < bf.GetLength(); i++) {
            if (tmp[i] == '0')bf.ClrBit(i); else if (tmp[i] == '1')bf.SetBit(i); else throw"incorect string";
        }
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.GetLength(); i++) {
        if (bf.GetBit(i) == 1) cout << 1; else cout << 0;
        }
    return ostr;
}
