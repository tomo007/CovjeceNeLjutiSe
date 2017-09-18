#include "stdafx.h"
#include "Igra.h"


Igra::Igra (byte brojIgrača){
	for (int i = 0; i < brojIgrača; ++i) {
		igrači.push_back(Igrač(vratiBojuIgrača(i)));
	}
	indeksIgrača = 0;
	indeksZauzetogPolja = -1;
	indeksIgracaNaZauzetomPolju = -1;
}


Igra::~Igra()
{
}
std::vector<Igrač> Igra::vratiIgrače()
{
	return igrači;
}
int Igra::brojBacanjaKocke(Igrač trenutniIgrač)
{
	if (trenutniIgrač.figureNaPolju.size() == 0)
		return 3;
	return 1;
}
bool Igra::pomakniFiguruNaPočetnoPolje(Igrač* trenutniIgrač)
{
	if (trenutniIgrač->figure.size() > 0) {
		Figura f = trenutniIgrač->figure.back();
		trenutniIgrač->figureNaPolju.push_back(f);
		trenutniIgrač->figure.pop_back();
		++trenutniIgrač->brojFiguraNaPolju;
		return true;
	}
	else
		return false;
}
Igrač Igra::promjenaIgrača(Igrač * trenutniIgrač)
{	
	Boja bojaTrenutnogIgrača = trenutniIgrač->vratiBoju();
	int brojIgrača = igrači.size();
	switch (bojaTrenutnogIgrača) 
	{
	case Boja::CRVENA:
		indeksIgrača = 1;
		return igrači[1];
	case Boja::PLAVA:
		if (brojIgrača <= 2) {
			indeksIgrača = 0;
			return igrači.front();
		}else {
			indeksIgrača = 2;
			return igrači[2];
		}
	case Boja::ZELENA:
		if (brojIgrača <= 3) {
			indeksIgrača = 0;
			return igrači.front();
		}else
			indeksIgrača = 3;
			return igrači[3];
	case Boja::ZUTA:
		indeksIgrača = 0;
		return igrači.front();
	}
	
}

std::vector<Figura> Igra::izaberiFiguru(Igrač * trenutniIgrač, int dobivenBrojSKocke)
{
	if (dobivenBrojSKocke == 6)
		return trenutniIgrač->figure;
	else
		return trenutniIgrač->figureNaPolju;
}

bool Igra::pomakniFiguru(Igrač* trenutniIgrač, Figura* figura, int brojPomaka)
{

	if (trenutniIgrač->pomakni(figura, brojPomaka)) {
		oslobodiPolje((figura->vratiTrenutnoPolje()-brojPomaka)%40);
		Figura* figuraNaTomPolju = ploča.provjeraPolja(figura->vratiTrenutnoPolje());
		if (figuraNaTomPolju != nullptr) {
			poljeJeZauzeto = true;
			oslobodiPolje(figuraNaTomPolju);
			ploča.zauzmiPolje(figura, figura->vratiTrenutnoPolje());
		}
		ploča.zauzmiPolje(figura, figura->vratiTrenutnoPolje());
		return true;
	}
	return false;
	
}

void Igra::oslobodiPolje(Figura * figura)
{
	Igrač* igrač = dajIgračaSTomFigurom(figura);
	std::vector<Figura> v = igrač->figureNaPolju;
	auto it = std::find(v.begin(), v.end(),*figura);
	promjeniIndeksIgračaNaZauzetomPolju(*igrač);
	indeksZauzetogPolja = std::distance(v.begin(), it);
	igrač->figureNaPolju.erase(std::find(v.begin(), v.end(),*figura));
	--igrač->brojFiguraNaPolju;
	igrač->figure.push_back(*figura);

}

void Igra::oslobodiPolje(int polje)
{
	ploča.zauzmiPolje(nullptr, polje);
}

Igrač* Igra::dajIgračaSTomFigurom(Figura* figura)
{
	for each (Igrač var in igrači)
	{
		if (figura->vratiBoju() == var.vratiBoju())
			return &var;
	}
	return nullptr;
}

Igrač Igra::prviIgrač()
{
	return igrači.front();
}

void Igra::vratiPromjeneNakonZauzetoPolja()
{
	poljeJeZauzeto = false;
	indeksZauzetogPolja = -1;
	indeksIgracaNaZauzetomPolju = -1;
}

Boja Igra::vratiBojuIgrača(int i)
{
	switch (i) {
	case 0:
		return Boja::CRVENA;
	case 1:
		return Boja::PLAVA;
	case 2:
		return Boja::ZELENA;
	case 3:
		return Boja::ZUTA;
	default:
		break;
	}
}

void Igra::promjeniIndeksIgračaNaZauzetomPolju(Igrač igrač)
{
	switch (igrač.vratiBoju()) {
	case Boja::CRVENA:
		indeksIgracaNaZauzetomPolju =0;
		break;
	case Boja::PLAVA:
		indeksIgracaNaZauzetomPolju = 1;
		break;
	case Boja::ZELENA:
		indeksIgracaNaZauzetomPolju = 2;
		break;
	case Boja::ZUTA:
		indeksIgracaNaZauzetomPolju = 3;
		break;
	default:
		break;
	}
}
