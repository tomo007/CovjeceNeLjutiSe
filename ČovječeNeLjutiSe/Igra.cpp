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
		if (trenutniIgrač->figure.size() > 1) {
			trenutniIgrač->figure.pop_back();
		}
		else {
			trenutniIgrač->figure.clear();
		}
		++trenutniIgrač->brojFiguraNaPolju;
		--trenutniIgrač->brojFiguraUKučici;
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
	int staroPoljeUKuci = figura->poljeUKući;
	if (trenutniIgrač->pomakni(figura, brojPomaka)) {
		if (figura->vratiTrenutnoPolje() > 6) {
			oslobodiPolje((figura->vratiTrenutnoPolje() - brojPomaka));
		}
		else {
			switch (figura->vratiTrenutnoPolje()) {
			case 0:
				oslobodiPolje(40 - brojPomaka);
				break;
			case 1:
				oslobodiPolje(41 - brojPomaka);
				break;
			case 2:
				oslobodiPolje(42 - brojPomaka);
				break;
			case 3:
				oslobodiPolje(43 - brojPomaka);
				break;
			case 4:
				oslobodiPolje(44 - brojPomaka);
				break;
			case 5:
				oslobodiPolje(45 - brojPomaka);
				break;
			case 6:
				oslobodiPolje(0);
				break;
			default:
				break;
			}
		}
		if (figura->poljeUKući <= -1) {
			Figura* figuraNaTomPolju = ploča.provjeraPolja(figura->vratiTrenutnoPolje());
			if (figuraNaTomPolju != nullptr) {
				poljeJeZauzeto = true;
				oslobodiPolje(figuraNaTomPolju);
				ploča.zauzmiPolje(figura, figura->vratiTrenutnoPolje());
			}
			ploča.zauzmiPolje(figura, figura->vratiTrenutnoPolje());
			return true;
		}
	}if(staroPoljeUKuci!=figura->poljeUKući)
		return true;
	return false;
	
}

void Igra::oslobodiPolje(Figura * figura)
{
	namjestiIndeksIgračaNaZauzetomPolju(figura);
	std::vector<Figura> v = igrači[indeksIgracaNaZauzetomPolju].figureNaPolju;
	auto it = std::find(v.begin(), v.end(),*figura);
	indeksZauzetogPolja = std::distance(v.begin(), it);
	if (igrači[indeksIgracaNaZauzetomPolju].brojFiguraNaPolju > 1) {
		igrači[indeksIgracaNaZauzetomPolju].figureNaPolju.erase(v.begin() + (indeksZauzetogPolja-1));
	}
	else {
		igrači[indeksIgracaNaZauzetomPolju].figureNaPolju.clear();
	}
	--igrači[indeksIgracaNaZauzetomPolju].brojFiguraNaPolju;
	igrači[indeksIgracaNaZauzetomPolju].figure.push_back(Figura(figura->vratiBoju(),figura->vratiPočetnuTočku(),figura->vratiZavršnuTočku()));
	++igrači[indeksIgracaNaZauzetomPolju].brojFiguraUKučici;

}

void Igra::oslobodiPolje(int polje)
{
	ploča.zauzmiPolje(nullptr, polje);
}

void Igra::namjestiIndeksIgračaNaZauzetomPolju(Figura* figura)
{
	for (auto igrac : igrači)
	{
		for (auto f : igrac.figureNaPolju) {
			if (f == *figura)
				promjeniIndeksIgračaNaZauzetomPolju(igrac);
		}
	}
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
