#pragma once
#include "Ploča.h"
#include "Igrač.h"
#include "Figura.h"
#include <time.h> 
#include <vector>
class Igra
{
private:
	Ploča ploča;
	Boja vratiBojuIgrača(int i);
	void promjeniIndeksIgračaNaZauzetomPolju(Igrač igrač);
public:
	bool poljeJeZauzeto = false;
	int indeksZauzetogPolja;
	int indeksIgracaNaZauzetomPolju;
	Igra(byte brojIgrača);
	~Igra();
	std::vector<Igrač> igrači;
	std::vector<Igrač> vratiIgrače();
	int brojBacanjaKocke(Igrač trenutniIgrač);
	int indeksIgrača;
	bool pomakniFiguruNaPočetnoPolje(Igrač* trenutniIgrač);
	Igrač promjenaIgrača(Igrač* trenutniIgrač);
	std::vector<Figura> izaberiFiguru(Igrač* trenutniIgrač, int dobivenBrojSKocke);
	bool pomakniFiguru(Igrač* trenutniIgrač,Figura* figura, int brojPomaka);
	void oslobodiPolje(Figura* figura);
	void oslobodiPolje(int polje);
	void namjestiIndeksIgračaNaZauzetomPolju(Figura* figura);
	Igrač prviIgrač();
	void vratiPromjeneNakonZauzetoPolja();
};

