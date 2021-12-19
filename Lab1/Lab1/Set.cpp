#include "Set.h"

TSet::TSet(int mp): BitField(mp)
{
	MaxPower = mp;
};

TSet::TSet(const TSet& s): BitField (s.BitField)
{
	MaxPower = s.MaxPower;
}

TSet::TSet(const TBitField& bf): BitField (bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	TBitField tmp(this->BitField);
	return tmp;
}

int TSet::GetMaxPower(void) const
{
	return MaxPower;
}

void TSet::InsElem(const int n)
{
	BitField.SetBit(n);
}

void TSet::DelElem(const int n)
{
	BitField.ClrBit(n);
}

int TSet::IsMember(const int n) const
{
	if (BitField.GetBit(n) == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int TSet::operator==(const TSet& s)
{
	
	return (BitField == s.BitField);

}

TSet& TSet::operator=(const TSet& s)
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
}

TSet TSet::operator+(const int n)
{
	TSet tmp(*this);
	if (tmp.BitField.GetBit(n) != 1)
	{
		tmp.BitField.SetBit(n);
	}
	return tmp;
}

TSet TSet::operator-(const int n)
{
	TSet tmp(*this);
	if (tmp.BitField.GetBit(n) != 1)
	{
		tmp.DelElem(n);
	}
	return tmp;
}

TSet TSet::operator+(const TSet& s)
{
	TSet tmp(BitField | s.BitField);
	return tmp;
}

TSet TSet::operator*(const TSet& s)
{
	TSet tmp(BitField & s.BitField);
	return tmp;
}

TSet TSet::operator~(void)
{
	TSet tmp(~BitField);
	return tmp;
}

istream& operator>>(istream& istr, TSet& bf)
{
	int x;
	cin >> x;
	for (; x > -1; cin >> x)
	{
		bf.BitField.GetBit(x);
	}
	return istr;
}

ostream& operator<<(ostream& ostr, const TSet& bf)
{
	cout << "[";
	for (int i = 0; i < bf.MaxPower; i++)
	{
		cout << bf.BitField.GetBit(i);
	}
	cout << "]\n";
	return ostr;
}