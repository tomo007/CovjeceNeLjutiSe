#include "stdafx.h"
#include "Figura.h"


Figura::Figura(Boja b, byte p, byte c)
{
	boja = b;
	poljeUKući = -1;
	početak = p;
	cilj = c;
	for (int i = početak; i != cilj;) {
		trenutnoPolje.push_back(i);
		i = (i % 40) + 1;
	}
}

Figura::Figura()
{
}


Figura::~Figura()
{
}

Boja Figura::vratiBoju()
{
	return boja;
}

byte Figura::vratiTrenutnoPolje()
{
	return trenutnoPolje.front();
}

byte Figura::vratiPočetnuTočku()
{
	return početak;
}

byte Figura::vratiZavršnuTočku()
{
	return cilj;
}
