

	// ČovječeNeLjutiSeView.cpp : implementation of the CČovječeNeLjutiSeView class
	//

#include "stdafx.h"
	// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
	// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ČovječeNeLjutiSe.h"
#endif

#include "ČovječeNeLjutiSeDoc.h"
#include "ČovječeNeLjutiSeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


	// CČovječeNeLjutiSeView

	IMPLEMENT_DYNCREATE(CČovječeNeLjutiSeView, CView)

BEGIN_MESSAGE_MAP(CČovječeNeLjutiSeView, CView)
	ON_WM_TIMER()
	ON_COMMAND(ID_DVA_IGRACA, &CČovječeNeLjutiSeView::OnFileNewDvaIgrača)
	ON_COMMAND(ID_FILE_NEW, &CČovječeNeLjutiSeView::OnFileNew)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CČovječeNeLjutiSeView construction/destruction

CČovječeNeLjutiSeView::CČovječeNeLjutiSeView()
{


}



CČovječeNeLjutiSeView::~CČovječeNeLjutiSeView()
{
}


BOOL CČovječeNeLjutiSeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CČovječeNeLjutiSeView drawing
void CČovječeNeLjutiSeView::igraj()
{
	CDC* pDC =this-> GetDC();
	CBrush* oldBrush;
	oldBrush = pDC->SelectObject(vratiBrush(trenutniIgrač));
	if (trenutniIgrač.brojFiguraNaPolju == 0) {
		int i = 3;
		while (i > 0) {
		//	if (brojSKocke == 6) {
			if (trenutniIgrač.brojFiguraNaPolju == 0) {
				potresiDostupneFigure();
			}
			
			if (igra->pomakniFiguruNaPočetnoPolje(trenutniIgrač)) {
				osvjeziPolje(kučice[igra->indeksIgrača].back(), 1);
				kučice[igra->indeksIgrača].pop_back();
				RECT poljeFigure = ploča.at(trenutniIgrač.vratiPočetnoPolje());
				std::vector<RECT> vec;
				vec.push_back(poljeFigure);
				figureNaPolju.push_back(vec);
				iscrtajFiguru(pDC, poljeFigure.left, poljeFigure.top);
				osvjeziPolje(poljeFigure, 0);
		//	}
			bacajKocku = true;
			break;
			}
			++i;
			bacajKocku = true;
		}
	}
	pDC->SelectObject(oldBrush);

	

}
void CČovječeNeLjutiSeView::iscrtajPolje(CDC* pDC, double dx, double dy)
{

	CPen * oldPen;
	CPen crvenaOlovka(PS_SOLID, 7, RGB(255, 0, 0));
	CPen plavaOlovka(PS_SOLID, 7, RGB(0, 0, 255));
	CPen zelenaOlovka(PS_SOLID, 7, RGB(0, 255, 0));
	CPen zutaOlovka(PS_SOLID, 7, RGB(255, 255, 0));
	CPen crnaOlovka(PS_SOLID, 5, RGB(0, 0, 0));

	CBrush crvenaPozadina(RGB(255, 0, 0));
	CBrush plavaPozadina(RGB(0, 0, 255));
	CBrush zelenaPozadina(RGB(0, 255, 0));
	CBrush zutaPozadina(RGB(255, 255, 0));
	CBrush crnaPozadina(RGB(0, 0, 0));

	oldPen = pDC->SelectObject(&crvenaOlovka);
	iscrtajKučicu(pDC, 0, 0);
	pDC->SelectObject(oldPen);

	oldPen = pDC->SelectObject(&plavaOlovka);
	iscrtajKučicu(pDC, devetiStupac, 0);
	pDC->SelectObject(oldPen);


	oldPen = pDC->SelectObject(&zutaOlovka);
	iscrtajKučicu(pDC, 0, devetiRed);
	pDC->SelectObject(oldPen);

	oldPen = pDC->SelectObject(&zelenaOlovka);
	iscrtajKučicu(pDC, devetiStupac, devetiRed);
	pDC->SelectObject(oldPen);

	oldPen = pDC->SelectObject(&crnaOlovka);
	iscrtajCijeliRedHorizontalno(pDC, 0, cetvrtiRed);
	iscrtajCijeliRedHorizontalno(pDC, 0, sestiRed);
	iscrtajCijeliRedVertikalno(pDC, cetvrtiStupac, 0);
	iscrtajCijeliRedVertikalno(pDC, sestiStupac, 0);
	pDC->Ellipse(0, petiRed, duljinaKučice, sestiRed);
	pDC->Ellipse(petiStupac, desetiRed, sestiStupac,desetiRed+visinaKučice);
	pDC->Ellipse(desetiStupac, petiRed, desetiStupac+duljinaKučice, sestiRed);
	pDC->Ellipse(petiStupac, 0, sestiStupac, visinaKučice);
	pDC->SelectObject(oldPen);

	oldPen = pDC->SelectObject(&crvenaOlovka);
	pDC->Ellipse(0, cetvrtiRed, duljinaKučice, petiRed);
	iscrtajCiljHorizontalno(pDC, duljinaKučice, petiRed);
	pDC->SelectObject(oldPen);


	oldPen = pDC->SelectObject(&zelenaOlovka);
	pDC->Ellipse(desetiStupac, sestiRed, desetiStupac+duljinaKučice, sedmiRed);
	iscrtajCiljHorizontalno(pDC, sestiStupac, petiRed);
	pDC->SelectObject(oldPen);

	oldPen = pDC->SelectObject(&plavaOlovka);
	pDC->Ellipse(sestiStupac, 0, sedmiStupac, visinaKučice);
	iscrtajCiljVertikalno(pDC, petiStupac, visinaKučice);
	pDC->SelectObject(oldPen);

	oldPen = pDC->SelectObject(&zutaOlovka);
	pDC->Ellipse(cetvrtiStupac, desetiRed, petiStupac, desetiRed+visinaKučice);
	iscrtajCiljVertikalno(pDC, petiStupac, sestiRed);
	pDC->SelectObject(oldPen);

	oldPen = pDC->SelectObject(&crnaOlovka);
	pDC->Rectangle(petiStupac, petiRed, sestiStupac, sestiRed);
	pDC->SelectObject(oldPen);

	
	

}

void CČovječeNeLjutiSeView::iscrtajKučicu(CDC * pDC, double dx, double dy)
{
	int i = 1;
	while (i < 3) {
		pDC->Ellipse(dx, dy, dx + duljinaKučice, dy + visinaKučice);
		pDC->Ellipse(dx + duljinaKučice, dy, dx + duljinaKučice * 2, dy + visinaKučice);
		dy = dy + visinaKučice;
		++i;
	}
}

void CČovječeNeLjutiSeView::iscrtajCijeliRedHorizontalno(CDC * pDC, double dx, double dy)
{
	while (dx < duljinaKučice*brojRedova) {
		pDC->Ellipse(dx, dy, dx + duljinaKučice, dy + visinaKučice);
		dx += duljinaKučice;
	}
}

void CČovječeNeLjutiSeView::iscrtajCijeliRedVertikalno(CDC * pDC, double dx, double dy)
{
	while (dy < visinaKučice*brojRedova) {
		pDC->Ellipse(dx, dy, dx + duljinaKučice, dy + visinaKučice);
		dy += visinaKučice;
	}
}

void CČovječeNeLjutiSeView::iscrtajCiljHorizontalno(CDC * pDC, double dx, double dy)
{
	int i = 0;
	while (i<4) {
		pDC->Ellipse(dx, dy, dx + duljinaKučice, dy + visinaKučice);
		dx += duljinaKučice;
		++i;
	}

}

void CČovječeNeLjutiSeView::iscrtajCiljVertikalno(CDC * pDC, double dx, double dy)
{
	int i = 0;
	while (i<4) {
		pDC->Ellipse(dx, dy, dx + duljinaKučice, dy + visinaKučice);
		dy += visinaKučice;
		++i;
	}
}

void CČovječeNeLjutiSeView::potresiDostupneFigure()
{
	CDC* pDC = this->GetDC();
	CBrush* oldBrush = pDC->SelectObject(vratiBrush(trenutniIgrač));
	if (brojSKocke == 6) {
		for each (RECT var in kučice[igra->indeksIgrača])
		{
			int i = 0;
			while (i < 2) {
				iscrtajFiguru(pDC, var.left, var.top - visinaKučiceUKockici);
				Sleep(50);
				iscrtajFiguru(pDC, var.left, var.top);
				++i;
			}
		}
		for each (RECT var in figureNaPolju[igra->indeksIgrača])
		{
			int i = 0;
			while (i < 2) {
				iscrtajFiguru(pDC, var.left, var.top - visinaKučiceUKockici);
				Sleep(50);
				iscrtajFiguru(pDC, var.left, var.top);
				++i;
			}
		}

	}
	pDC->SelectObject(oldBrush);
	
}

void CČovječeNeLjutiSeView::iscrtajKockuSest(CDC * pDC, double dx, double dy)
{
	int i = 0;
	while (i < 3) {
		pDC->Ellipse(dx, dy, dx + duljinaKučiceUKockici, dy + visinaKučiceUKockici);
		dx = dx + duljinaKučiceUKockici + duljinaKučiceUKockici;
		pDC->Ellipse(dx, dy, dx + duljinaKučiceUKockici, dy + visinaKučiceUKockici);
		dx = dx - duljinaKučiceUKockici - duljinaKučiceUKockici;
		dy = dy + visinaKučiceUKockici + visinaKučiceUKockici - 5;
		++i;
	}

}

void CČovječeNeLjutiSeView::iscrtajKockuPet(CDC * pDC, double dx, double dy)
{
	int i = 0;
	while (i < 2) {
		pDC->Ellipse(dx, dy, dx + duljinaKučiceUKockici, dy + visinaKučiceUKockici);
		dx = dx + duljinaKučiceUKockici + duljinaKučiceUKockici;
		pDC->Ellipse(dx, dy, dx + duljinaKučiceUKockici, dy + visinaKučiceUKockici);
		dx = dx - duljinaKučiceUKockici - duljinaKučiceUKockici;
		dy = dy + visinaKučiceUKockici * 4 - 10;
		++i;
	}
	dx = dx + duljinaKučiceUKockici;
	dy = dy - visinaKučiceUKockici * 4 - 1;
	pDC->Ellipse(dx, dy, dx + duljinaKučiceUKockici, dy + visinaKučiceUKockici);
}

void CČovječeNeLjutiSeView::iscrtajKockuCetri(CDC * pDC, double dx, double dy)
{
	int i = 0;
	while (i < 2) {
		pDC->Ellipse(dx, dy, dx + duljinaKučiceUKockici, dy + visinaKučiceUKockici);
		dx = dx + duljinaKučiceUKockici + duljinaKučiceUKockici;
		pDC->Ellipse(dx, dy, dx + duljinaKučiceUKockici, dy + visinaKučiceUKockici);
		dx = dx - duljinaKučiceUKockici - duljinaKučiceUKockici;
		dy = dy + visinaKučiceUKockici + visinaKučiceUKockici - 5;
		++i;
	}
}

void CČovječeNeLjutiSeView::iscrtajKockuTri(CDC * pDC, double dx, double dy)
{
	int i = 0;
	while (i < 3) {
		pDC->Ellipse(dx, dy, dx + duljinaKučiceUKockici, dy + visinaKučiceUKockici);
		dy = dy + visinaKučiceUKockici + visinaKučiceUKockici - 5;
		++i;
	}
}

void CČovječeNeLjutiSeView::iscrtajKockuDva(CDC * pDC, double dx, double dy)
{
	int i = 0;
	while (i < 2) {
		pDC->Ellipse(dx, dy, dx + duljinaKučiceUKockici, dy + visinaKučiceUKockici);
		dx = dx + duljinaKučiceUKockici + duljinaKučiceUKockici;
		dy = dy + visinaKučiceUKockici + visinaKučiceUKockici - 5;
		++i;
	}
}

void CČovječeNeLjutiSeView::iscrtajKockuJedan(CDC * pDC, double dx, double dy)
{
	pDC->Ellipse(dx, dy, dx + duljinaKučiceUKockici, dy + visinaKučiceUKockici);
}

void CČovječeNeLjutiSeView::iscrtajFiguru(CDC * pDC, double dx, double dy)
{
	double početakTijelaDx = dx + duljinaKučiceUKockici;
	double početakTijelaDy = dy + visinaKučiceUKockici;
	double krajTijelaDx = (dx + duljinaKučice) - duljinaKučiceUKockici;
	double krajTijelaDy = (dy + visinaKučice) - visinaKučiceUKockici;

	double početakGlaveDx = početakTijelaDx + duljinaKučiceUKockici;
	double početakGlaveDy = početakTijelaDy + visinaKučiceUKockici;
	double krajGlaveDx = početakGlaveDx + duljinaKučiceUKockici;
	double krajGlaveDy = početakGlaveDy + visinaKučiceUKockici;
	CBrush* oldPen;
	pDC->Ellipse(početakTijelaDx, početakTijelaDy, krajTijelaDx, krajTijelaDy);
	CBrush brush1;
	brush1.CreateSolidBrush(RGB(204, 0, 204));
	oldPen=pDC->SelectObject(&brush1);
	pDC->Ellipse(početakGlaveDx, početakGlaveDy, krajGlaveDx, krajGlaveDy);
	pDC->SelectObject(oldPen);
}

CBrush*  CČovječeNeLjutiSeView::vratiBrush(Igrač trenutniIgrač)
{
	switch (trenutniIgrač.vratiBoju()) {
	case Boja::CRVENA:
		return new CBrush(RGB(255, 0, 0));
	case Boja::PLAVA:
		return new CBrush(RGB(0, 0, 255));
	case Boja::ZELENA:
		return new CBrush(RGB(0, 255, 0));
	case Boja::ZUTA:
		return new CBrush(RGB(255, 255, 0));
	default:
		return nullptr;
	}
}

void CČovječeNeLjutiSeView::prodiPoljaHorizontalno(double dx, double dy, int brojPoljaZaPoci)
{
	RECT p;
	for (int i = 0; i < brojPoljaZaPoci; ++i) {
		p.left = dx;
		p.right = dx + duljinaKučice;
		p.top = dy;
		p.bottom = dy + visinaKučice;
		ploča.push_back(p);
		dx = dx + duljinaKučice;
	}
}

void CČovječeNeLjutiSeView::prodiPoljaVertikalno(double dx, double dy, int brojPoljaZaPoci)
{
	RECT p;
	for (int i = 0; i < brojPoljaZaPoci; ++i) {
		p.left = dx;
		p.right = dx + duljinaKučice;
		p.top = dy;
		p.bottom = dy + visinaKučice;
		ploča.push_back(p);
		dy = dy + visinaKučice;
	}
}

void CČovječeNeLjutiSeView::prodiKucicu(double dx, double dy)
{
	RECT r;
	int i = 0;
	std::vector<RECT> vec;
	while (i < 2) {
		r.left = dx;
		r.right = dy+duljinaKučice;
		r.top = dy;
		r.bottom = dy + visinaKučice;
		vec.push_back(r);
		r.left = dx + duljinaKučice;
		r.right = dx + duljinaKučice * 2;
		vec.push_back(r);
		dy = dy + visinaKučice;
		++i;
	}
	kučice.push_back(vec);
}

void CČovječeNeLjutiSeView::prodiPoljaVertikalnoPremaGore(double dx, double dy, int brojPoljaZaPoci)
{
	RECT p;
	for (int i = 0; i < brojPoljaZaPoci; ++i) {
		p.left = dx;
		p.right = dx + duljinaKučice;
		p.top = dy;
		p.bottom = dy + visinaKučice;
		ploča.push_back(p);
		dy = dy - visinaKučice;
	}
}

void CČovječeNeLjutiSeView::prodiPoljaHorizontalnoSDesnaNaLijevo(double dx, double dy, int brojPoljaZaPoci)
{
	RECT p;
	for (int i = 0; i < brojPoljaZaPoci; ++i) {
		p.left = dx;
		p.right = dx + duljinaKučice;
		p.top = dy;
		p.bottom = dy + visinaKučice;
		ploča.push_back(p);
		dx = dx - duljinaKučice;
	}
}

void CČovječeNeLjutiSeView::inicijalizirajVarijableCrtanja()
{
	CRect r;
	GetClientRect(&r);
	duljinaKučice =r.right / brojRedova;
	visinaKučice = r.bottom / brojRedova;
	//stupci
	cetvrtiStupac = duljinaKučice * 4;
	petiStupac = duljinaKučice * 5;
	sestiStupac = duljinaKučice * 6;
	sedmiStupac = duljinaKučice * 7;
	devetiStupac = duljinaKučice * 9;
	desetiStupac = duljinaKučice * 10;
	//redci
	cetvrtiRed = visinaKučice * 4;
	petiRed = visinaKučice * 5;
	sestiRed = visinaKučice * 6;
	sedmiRed = visinaKučice * 7;
	devetiRed = visinaKučice * 9;
	desetiRed = visinaKučice * 10;
	duljinaKučiceUKockici = duljinaKučice / 5;
	visinaKučiceUKockici = visinaKučice / 5;
}

void CČovječeNeLjutiSeView::inicijalizirajVektorPolja()
{
	prodiPoljaHorizontalno(0, petiRed, 5);
	prodiPoljaVertikalnoPremaGore(petiStupac, cetvrtiRed, 4);
	ploča.push_back(CRect(petiStupac, 0, sestiStupac, visinaKučice));
	prodiPoljaVertikalno(sestiStupac, 0, 4);
	prodiPoljaHorizontalno(sestiRed, petiRed, 5);
	ploča.push_back(CRect(desetiStupac, sestiRed, duljinaKučice * 11, sedmiRed));
	prodiPoljaHorizontalnoSDesnaNaLijevo(desetiStupac, sedmiRed, 5);
	prodiPoljaVertikalnoPremaGore(sestiStupac, sedmiRed + visinaKučice, 4);
	ploča.push_back(CRect(petiStupac, desetiRed, sestiStupac, visinaKučice * 11));
	prodiPoljaVertikalno(petiStupac, desetiRed, 4);
	prodiPoljaHorizontalnoSDesnaNaLijevo(cetvrtiRed, sedmiRed, 4);
	ploča.push_back(CRect(0, sestiRed, duljinaKučice, sedmiRed));
}

void CČovječeNeLjutiSeView::inicijalizirajKučicu(Boja b)
{
	double dx, dy;
	switch (b) {
	case Boja::CRVENA:
		dx = 0;
		dy = 0;
		break;
	case Boja::PLAVA:
		dx = devetiStupac;
		dy = 0;
		break;
	case Boja::ZELENA:
		dx = 0;
		dy = devetiRed;
		break;
	case Boja::ZUTA:
		dx = devetiStupac;
		dy = devetiRed;
		break;
	}
	prodiKucicu(dx, dy);
}

void CČovječeNeLjutiSeView::osvjeziPolje(RECT r,int izbrisi)
{
	r.left += duljinaKučiceUKockici;
	r.top += visinaKučiceUKockici;
	r.right -= duljinaKučiceUKockici;
	r.bottom -= visinaKučiceUKockici;
	InvalidateRect(&r, izbrisi);
}

void CČovječeNeLjutiSeView::OnDraw(CDC* pDC)
{
	CČovječeNeLjutiSeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CBrush* oldBrush;
	CBrush crnaPozadina(RGB(0, 0, 0));
	oldBrush=pDC->SelectObject(&crnaPozadina);
	if (kockaSeOkreće) {
		switch (brojSKocke)
		{
		case 1:
			iscrtajKockuJedan(pDC, petiStupac + duljinaKučiceUKockici * 2, petiRed + visinaKučiceUKockici * 2);
			break;
		case 2:
			iscrtajKockuDva(pDC, petiStupac + duljinaKučiceUKockici, petiRed + visinaKučiceUKockici);
			break;
		case 3:
			iscrtajKockuTri(pDC, petiStupac + duljinaKučiceUKockici * 2, petiRed + 5);
			break;
		case 4:
			iscrtajKockuCetri(pDC, petiStupac + duljinaKučiceUKockici, petiRed + visinaKučiceUKockici);
			break;
		case 5:
			iscrtajKockuPet(pDC, petiStupac + duljinaKučiceUKockici, petiRed + 5);
			break;
		case 6:
			iscrtajKockuSest(pDC, petiStupac + duljinaKučiceUKockici, petiRed + 5);
			break;
		default:
			break;
		}
		pDC->SelectObject(oldBrush);
	}
	

	// TODO: add draw code for native data here
}


// CČovječeNeLjutiSeView diagnostics

#ifdef _DEBUG
void CČovječeNeLjutiSeView::AssertValid() const
{
	CView::AssertValid();
}

void CČovječeNeLjutiSeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}


void CČovječeNeLjutiSeView::OnTimer(UINT_PTR nIDEvent)
{
	static int brojOkretajaKocke = 0;
	if (brojOkretajaKocke < 5) {
		if (!kockaSeOkreće)
			kockaSeOkreće = true;
		srand(time(NULL));
		brojSKocke = rand() % 6 + 1;
		++brojOkretajaKocke;
		InvalidateRect(CRect(duljinaKučice * 5, visinaKučice * 5, duljinaKučice * 6, visinaKučice * 6));
	}
	else {
		KillTimer(timer);
		igraj();
		kockaSeOkreće = false;
		brojOkretajaKocke = 0;
		
	}


}

void CČovječeNeLjutiSeView::OnFileNew()
{
	
}
void CČovječeNeLjutiSeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	POINT p;
	GetCursorPos(&p);
	if (bacajKocku) {
		if (point.x > duljinaKučice * 5 && point.x < duljinaKučice * 6) {
			if (point.y > visinaKučice * 5 && point.y < visinaKučice * 6)
				timer = SetTimer(1, 1000, 0);
			bacajKocku = false;
		}
	}
	


}

void CČovječeNeLjutiSeView::OnFileNewDvaIgrača()
{
	
	CBrush* oldBrush;
	CBrush plavaPozadina(RGB(51, 51, 255));
	CBrush crvenaPozadina(RGB(255, 0, 0));
	CDC* pDC = this->GetDC();
	igra = new Igra(2);
	trenutniIgrač = igra->prviIgrač();
	int indeks = 0;
	bacajKocku = true;
	inicijalizirajVarijableCrtanja();
	inicijalizirajVektorPolja();
	iscrtajPolje(pDC, 0, 0);

	for each (Igrač igrac in igra->vratiIgrače())
	{
		inicijalizirajKučicu(igrac.vratiBoju());
			switch (igrac.vratiBoju()) {
				case Boja::CRVENA: 					
					oldBrush=pDC->SelectObject(&crvenaPozadina);
					indeks = 0;
					break; 
				case Boja::PLAVA:					
					oldBrush = pDC->SelectObject(&plavaPozadina);
					indeks = 1;
					break;
				default:
					oldBrush = new CBrush();
					break;
			}
			for each(RECT r in kučice[indeks]) {
				iscrtajFiguru(pDC, r.left, r.top);
			}
			pDC->SelectObject(oldBrush);
		}
		
	}



CČovječeNeLjutiSeDoc* CČovječeNeLjutiSeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CČovječeNeLjutiSeDoc)));
	return (CČovječeNeLjutiSeDoc*)m_pDocument;
}
#endif //_DEBUG
