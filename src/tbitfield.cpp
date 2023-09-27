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
    return n/ (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return FAKE_INT;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
}

void TBitField::ClrBit(const int n) // очистить бит
{
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  return FAKE_INT;
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
    return FAKE_BITFIELD;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    return FAKE_BITFIELD;
}

TBitField TBitField::operator~(void) // отрицание
{
    return FAKE_BITFIELD;
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
