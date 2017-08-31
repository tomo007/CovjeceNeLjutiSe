#include "stdafx.h"
#include "Igra.h"


Igra::Igra (byte brojIgrača){
	for (int i = 0; i < brojIgrača; ++i) {
		igrači.push_back(Igrač(vratiBojuIgrača(i)));
	}
}


Igra::~Igra()
{
}
std::vector<Igrač> Igra::vratiIgrače()
{
	return igrači;
}
int Igra::bacajKocku(Igrač trenutniIgrač)
{
	if (trenutniIgrač.figureNaPolju.size() == 0)
		return 3;
	return 1;
}
Igrač Igra::promjenaIgrača(Igrač * trenutniIgrač)
{	
	Boja bojaTrenutnogIgrača = trenutniIgrač->vratiBoju();
	int brojIgrača = igrači.size();
	switch (bojaTrenutnogIgrača) 
	{
	case Boja::CRVENA:
		return igrači[1];
	case Boja::PLAVA:
		if (brojIgrača<=2)
			return igrači.front();
		else
			return igrači[2];
	case Boja::ZELENA:
		if (brojIgrača <= 3)
			return igrači.front();
		else
			return igrači[3];
	case Boja::ZUTA:
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

bool Igra::pomakniFiguru(Igrač* trenutniIgrač, Figura * figura, int brojPomaka)
{
	bool flagFiguraNaPolju = false;
	for each (Figura var in trenutniIgrač->figureNaPolju)
	{
		if (&var == figura) {
			flagFiguraNaPolju = true;
				break;
		}	
	}
	if (!flagFiguraNaPolju){
		trenutniIgrač->figureNaPolju.push_back(*figura);
		++trenutniIgrač->brojFiguraNaPolju;
	}
	if (trenutniIgrač->pomakni(figura, brojPomaka)) {
		Figura* figuraNaTomPolju = ploča.provjeraPolja(figura->trenutnoPolje.front());
		if (figuraNaTomPolju != nullptr) {
			figuraNaTomPolju = new Figura(figuraNaTomPolju->vratiBoju(), figuraNaTomPolju->vratiPočetnuTočku(), figuraNaTomPolju->vratiZavršnuTočku());
			if (figura->poljeUKući < 0)
				ploča.zauzmiPolje(figura, figura->trenutnoPolje.front());
		}
		if (trenutniIgrač->zadnjeSlobodnoMjestoUKući == 0)
			return true;
	}
	return false;
}

Igrač Igra::prviIgrač()
{
	return igrači.front();
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
