#pragma once
#include "Plo�a.h"
#include "Igra�.h"
#include "Figura.h"
#include <time.h> 
#include <vector>
class Igra
{
private:
	Plo�a plo�a;
	std::vector<Igra�> igra�i;
	Boja vratiBojuIgra�a(int i);
public:
	Igra(byte brojIgra�a);
	~Igra();
	std::vector<Igra�> vratiIgra�e();
	int bacajKocku(Igra� trenutniIgra�);
	Igra� promjenaIgra�a(Igra�* trenutniIgra�);
	std::vector<Figura> izaberiFiguru(Igra�* trenutniIgra�, int dobivenBrojSKocke);
	bool pomakniFiguru(Igra�* trenutniIgra�,Figura* figura, int brojPomaka);
	Igra� prviIgra�();
};

