#include "BitField.h"

#define BITS_IN_MEM (sizeof(TELEM) * 8)

int TBitField::GetMemIndex(const int n) const
{
	return n;
};

TELEM TBitField::GetMemMask(const int n) const
{
	return (1 << (n % BITS_IN_MEM));
};

TBitField::TBitField(int len)
{
	BitLen = len;
	MemLen = (BitLen + 31) / 32;
	pMem = new TELEM[len];

	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
};

TBitField::TBitField(const TBitField& bf)
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}

};

TBitField::~TBitField()
{
	delete []pMem;

};

int TBitField::GetLength(void) const
{
	return BitLen;
}

void TBitField::SetBit(const int n)
{
	if (n >= 0 && n < BitLen)
	{
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
	}
}

void TBitField::ClrBit(const int n)
{
	if (n >= 0 && n < BitLen)
	{
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
	}

}

int TBitField::GetBit(const int n) const
{
	if (n >= 0 && n < BitLen)
	{
		return ((pMem[GetMemIndex(n)] & GetMemMask(n)) != 0);
	}
}

int TBitField::operator==(const TBitField& bf)
{
	int x = 0;

	if (BitLen == bf.BitLen)
	{
		x = 1;

		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i])
			{
				x = 0;
			}
		}
	}
	
	return x;
}


TBitField& TBitField::operator=(const TBitField& bf)
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	
	delete []pMem;

	pMem = new TELEM[MemLen];

	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}

}

TBitField TBitField::operator|(const TBitField& bf)
{
	if (BitLen >= bf.BitLen)
	{
		TBitField tmp(BitLen);
		for (int i = 0; i < MemLen; i++)
		{
			tmp.pMem[i] = pMem[i] | bf.pMem[i];
		}
		
		return tmp;
	}
	else
	{
		TBitField tmp(bf.BitLen);
		for (int i = 0; i < MemLen; i++)
		{
			tmp.pMem[i] = pMem[i] | bf.pMem[i];
		}

		return tmp;
	}

}


TBitField TBitField::operator&(const TBitField& bf)
{
	if (BitLen >= bf.BitLen)
	{
		TBitField tmp(BitLen);
		for (int i = 0; i < MemLen; i++)
		{
			tmp.pMem[i] = pMem[i] & bf.pMem[i];
		}

		return tmp;
	}
	else
	{
		TBitField tmp(bf.BitLen);
		for (int i = 0; i < MemLen; i++)
		{
			tmp.pMem[i] = pMem[i] & bf.pMem[i];
		}

		return tmp;
	}

}

TBitField TBitField::operator~(void)
{
	TBitField tmp(*this);

	for (int i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] = ~tmp.pMem[i];
	}
	return tmp;
}

istream& operator>>(istream& istr, TBitField& bf)
{
	char z;
	int x = 0;
	istr >> z;
	while (z == '1' || z == '0')
	{
		if (z == '1')
		{
			bf.SetBit(x);
		}

		if (z == '0')
		{
			bf.ClrBit(x);
		}

		x++;
		istr >> z;
	}
	return istr;

}

ostream& operator<<(ostream& ostr, const TBitField& bf)
{
	return ostr;
	cout << "[";
	for (int i = 0; i < bf.BitLen; i++)
	{
		cout << bf.GetBit(i);
	}
	cout << "]\n";
	return ostr;

}