#include<stdio.h>
#include"conio2.h"
#include <cstdlib>
#include <ctime>
#define ROZMIAR 14
//deklaracaja struktury
struct pole {
	char wartosc;
	bool mod;
};
//Funkcje (w funkcjach cz�sto u�ywane s� zmienne a i b, kt�re przenosz� warto�ci zmiennych x i y w konsoli na odpowiadaj�ce im warto�ci w planszy
void wypelnienie(pole tab[ROZMIAR][ROZMIAR])
{
	//bazowe wype�nienie planszy
	for (int i = 0; i < 14; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			if (i == 0 || j == 0 || i == 13 || j == 13)
			{
				tab[i][j].wartosc = '#';
				tab[i][j].mod = false;
			}
			else
			{
				tab[i][j].wartosc = '.';
				tab[i][j].mod = true;
			}
		}
	}
}
//reg�y
bool sprawdzenie_1_0(pole tab[ROZMIAR][ROZMIAR], int x, int y)
{
	int a = x - 36, b = y - 1;
	//sprawdzenie w poziomie
	if (tab[b][a - 1].wartosc == '0' && tab[b][a + 1].wartosc == '0') return false;
	if (tab[b][a - 1].wartosc == '0' && tab[b][a - 2].wartosc == '0') return false;
	if (tab[b][a + 1].wartosc == '0' && tab[b][a + 2].wartosc == '0') return false;
	//sprawdzenie w pionie
	if (tab[b-1][a].wartosc == '0' && tab[b+1][a].wartosc == '0') return false;
	if (tab[b-1][a].wartosc == '0' && tab[b-2][a].wartosc == '0') return false;
	if (tab[b+1][a].wartosc == '0' && tab[b+2][a].wartosc == '0') return false;

	return true;
}
bool sprawdzenie_1_1(pole tab[ROZMIAR][ROZMIAR], int x, int y)
{
	int a = x - 36, b = y - 1;
	//sprawdzenie w poziomie
	if (tab[b][a - 1].wartosc == '1' && tab[b][a + 1].wartosc == '1') return false;
	if (tab[b][a - 1].wartosc == '1' && tab[b][a - 2].wartosc == '1') return false;
	if (tab[b][a + 1].wartosc == '1' && tab[b][a + 2].wartosc == '1') return false;
	//sprawdzenie w pionie
	if (tab[b - 1][a].wartosc == '1' && tab[b + 1][a].wartosc == '1') return false;
	if (tab[b - 1][a].wartosc == '1' && tab[b - 2][a].wartosc == '1') return false;
	if (tab[b + 1][a].wartosc == '1' && tab[b + 2][a].wartosc == '1') return false;

	return true;
}

bool sprawdzenie_2_0(pole tab[ROZMIAR][ROZMIAR], int x, int y)
{
	int a = x - 36, b = y - 1, licznik_poziom = 0, licznik_pion=0;
	//zliczanie 0 w pionie i poziomie
	for (int i = 1; i <= ROZMIAR; i++)
	{
		if (tab[b][i].wartosc == '0') licznik_poziom++;
		if (tab[i][a].wartosc == '0') licznik_pion++;
	}
	if (licznik_pion == ((ROZMIAR-2)/2) || licznik_poziom == ((ROZMIAR - 2) / 2)) return false;
	else	return true;
}
bool sprawdzenie_2_1(pole tab[ROZMIAR][ROZMIAR], int x, int y)
{
	int a = x - 36, b = y - 1, licznik_poziom = 0, licznik_pion = 0;
	//zliczanie 1 w pionie i poziomie
	for (int i = 1; i <= ROZMIAR; i++)
	{
		if (tab[b][i].wartosc == '1') licznik_poziom++;
		if (tab[i][a].wartosc == '1') licznik_pion++;
	}
	if (licznik_pion ==((ROZMIAR - 2) / 2) || licznik_poziom ==((ROZMIAR - 2) / 2)) return false;
	else	return true;
}

bool sprawdzenie_3_poziom(pole tab[ROZMIAR][ROZMIAR], int y)
{
	int  b = y - 1, mod=0, licznik=0;
	//sprawdzenie czy ca�y wiersz b�dzie wype�niony w danym miejscu
	for (int k = 1; k <= ROZMIAR - 2; k++)
	{
		if (tab[b][k].wartosc == '.') mod++;
	}
	if (mod > 0) return true;

	//zliczenie powt�rze�
	for (int i = 1; i <= ROZMIAR - 2; i++)
	{
		if (i == b) continue;
		for (int j = 1; j <= ROZMIAR - 2; j++)
		{
			if (tab[i][j].wartosc == tab[b][j].wartosc) licznik++;
		}
		if (licznik == ROZMIAR - 2) return false;
	}
	return true;
}
bool sprawdzenie_3_pion(pole tab[ROZMIAR][ROZMIAR], int x)
{
	int a = x - 36, mod = 0, licznik = 0;
	//sprawdzenie czy ca�a kolumna b�dzie wype�niona w danym miejscu
	for (int k = 1; k <= ROZMIAR - 2; k++)
	{
		if (tab[k][a].wartosc == '.') mod++;
	}
	if (mod > 0) return true;

	//zliczenie powt�rze�
	for (int i = 1; i <= ROZMIAR - 2; i++)
	{
		if (i == a) continue;
		for (int j =1 ; j <= ROZMIAR - 2; j++)
		{
			if (tab[j][i].wartosc == tab[j][a].wartosc) licznik++;
		}
		if (licznik == ROZMIAR - 2) return false;
	}
	return true;
}
//sprawdzenie_3 - kt�ry wiersz/kolumna
int wiersz(pole tab[ROZMIAR][ROZMIAR], int y)
{
	//funkcja zostaje wywo�na tylko gdy wiemy o powt�rzeniu
	int b = y - 1, mod = 0, licznik = 0;
	//sprawdzenie czy ca�y wiersz b�dzie wype�niony w danym miejscu
	for (int k = 1; k <= ROZMIAR - 2; k++)
	{
		if (tab[b][k].wartosc == '.') mod++;
	}
	if (mod > 0) return true;

	//zliczenie powt�rze�
	for (int i = 1; i <= ROZMIAR - 2; i++)
	{
		if (i == b) continue;
		for (int j = 1; j <= ROZMIAR - 2; j++)
		{
			if (tab[i][j].wartosc == tab[b][j].wartosc) licznik++;
		}
		if (licznik == ROZMIAR - 2) return i;//funkcja zwraca kt�ry wiersz jest taki sam
	}
}
int kolumna(pole tab[ROZMIAR][ROZMIAR], int x)
{
	//funkcja zostaje wywo�na tylko gdy wiemy o powt�rzeniu
	int a = x - 36, mod = 0, licznik = 0;
	//sprawdzenie czy ca�a kolumna b�dzie wype�niona w danym miejscu
	for (int k = 1; k <= ROZMIAR - 2; k++)
	{
		if (tab[k][a].wartosc == '.') mod++;
	}
	if (mod > 0) return true;
	//zliczenie powt�rze�
	for (int i = 1; i <= ROZMIAR - 2; i++)
	{
		if (i == a) continue;
		for (int j = 1; j <= ROZMIAR - 2; j++)
		{
			if (tab[j][i].wartosc == tab[j][a].wartosc) licznik++;//funkcja zwraca kt�ra kolumna jest taka sama
		}
		if (licznik == ROZMIAR - 2) return i;
	}
}

void prosta_podpowiedz(pole tab[ROZMIAR][ROZMIAR], int x, int y)
{
	int ilosc = 0;//ilo�� b��d�w
	int a = x - 36, b = y - 1;
	char h = tab[b][a].wartosc, txt[32];
		if (tab[b][a].mod == false)
		{
			gotoxy(60, 7);
			cputs("Pole niemodyfikowalne");
			getch();
		}
		else
		{
			//sprawdzenie podstawowych reg�
			if (sprawdzenie_1_0(tab, x, y) == false)
			{
				ilosc++;
				gotoxy(35, 18 + ilosc);
				cputs("Blad regoly 1 dla 0;");
			}
			if (sprawdzenie_2_0(tab, x, y) == false)
			{
				ilosc++;
				gotoxy(35, 18 + ilosc);
				cputs("Blad regoly 2 dla 0;");
			}
			if (sprawdzenie_1_1(tab, x, y) == false)
			{
				ilosc++;
				gotoxy(35, 18 + ilosc);
				cputs("Blad regoly 1 dla 1;");
			}
			if (sprawdzenie_2_1(tab, x, y) == false)
			{
				ilosc++;
				gotoxy(35, 18 + ilosc);
				cputs("Blad regoly 2 dla 1;");
			}
			//sprawdzenie dost�pno�ci danych cyfr dla pola
			if (ilosc == 0)
			{
				gotoxy(60, 7);
				cputs("Na tym polu mozna umiescic 1 i 0.");
			}
			if (sprawdzenie_1_0(tab, x, y) && sprawdzenie_2_0(tab, x, y) && ilosc > 0)
			{
				gotoxy(60, 7);
				cputs("Na tym polu mozna umiescic 0.");
			}
			if (sprawdzenie_1_1(tab, x, y) && sprawdzenie_2_1(tab, x, y) && ilosc > 0)
			{
				gotoxy(60, 7);
				cputs("Na tym polu mozna umiescic 1.");
			}
			//sprawdzanie pionu i poziomu dla 1 i 0
			tab[b][a].wartosc = '1';
			if (sprawdzenie_3_pion(tab, x) == false)
			{
				int c = kolumna(tab, x);
				gotoxy(60, 7);
				sprintf_s(txt, "Przy wpisaniu 1 kolumna nr.%d bedzie taka sama.", c);
				cputs(txt);
			}
			if (sprawdzenie_3_poziom(tab, y) == false)
			{
				int c = wiersz(tab, y);
				gotoxy(60, 7);
				sprintf_s(txt, "Przy wpisaniu 1 wierz nr.%d bedzie taki sam.", c);
				cputs(txt);
			}
			tab[b][a].wartosc = '0';
			if (sprawdzenie_3_pion(tab, x) == false)
			{
				int c = kolumna(tab, x);
				gotoxy(60, 7);
				sprintf_s(txt, "Przy wpisaniu 0 kolumna nr.%d bedzie taka sama.", c); 
				cputs(txt);
			}
			if (sprawdzenie_3_poziom(tab, y) == false)
			{
				int c = wiersz(tab, y);
				gotoxy(60, 7);
				sprintf_s(txt, "Przy wpisaniu 0 wiersz nr.%d bedzie tak1 sam.", c);
				cputs(txt);
			}
			tab[b][a].wartosc = h;
			getch();//oczekiwanie
		}
}

void nowa_gra(pole tab[ROZMIAR][ROZMIAR])
{
	//reset planszy
	wypelnienie(tab);
	//ka�dy wiersz jest wierszem na polu gry
	tab[1][4].wartosc = '1'; tab[1][4].mod = false; tab[1][12].wartosc = '1'; tab[1][12].mod = false;
	tab[2][2].wartosc = '0'; tab[2][2].mod = false; tab[2][9].wartosc = '1'; tab[2][9].mod = false;
	tab[3][6].wartosc = '0'; tab[3][6].mod = false;
	tab[4][2].wartosc = '0'; tab[4][2].mod = false; tab[4][4].wartosc = '1'; tab[4][4].mod = false; tab[4][6].wartosc = '0'; tab[4][6].mod = false; tab[4][8].wartosc = '0'; tab[4][8].mod = false; tab[4][10].wartosc = '0'; tab[4][10].mod = false; tab[4][12].wartosc = '0'; tab[4][12].mod = false;
	tab[5][1].wartosc = '1'; tab[5][1].mod = false; tab[5][3].wartosc = '1'; tab[5][3].mod = false; tab[5][8].wartosc = '0'; tab[5][8].mod = false; tab[5][11].wartosc = '1'; tab[5][11].mod = false;
	tab[6][6].wartosc = '0'; tab[6][6].mod = false; tab[6][9].wartosc = '1'; tab[6][9].mod = false;
	tab[7][3].wartosc = '1'; tab[7][3].mod = false; tab[7][4].wartosc = '1'; tab[7][4].mod = false; tab[7][9].wartosc = '1'; tab[7][9].mod = false;
	tab[8][1].wartosc = '0'; tab[8][1].mod = false; tab[8][7].wartosc = '0'; tab[8][7].mod = false; tab[8][12].wartosc = '0'; tab[8][12].mod = false;
	tab[9][2].wartosc = '1'; tab[9][2].mod = false; tab[9][5].wartosc = '1'; tab[9][5].mod = false; tab[9][11].wartosc = '1'; tab[9][11].mod = false;
	tab[10][3].wartosc = '0'; tab[10][3].mod = false; tab[10][6].wartosc = '0'; tab[10][6].mod = false; tab[10][8].wartosc = '0'; tab[10][8].mod = false;
	tab[11][3].wartosc = '0'; tab[11][3].mod = false; tab[11][6].wartosc = '0'; tab[11][6].mod = false; tab[11][7].wartosc = '0'; tab[11][7].mod = false;
	tab[12][4].wartosc = '1'; tab[12][4].mod = false; tab[12][7].wartosc = '0'; tab[12][7].mod = false; tab[12][10].wartosc = '1'; tab[12][10].mod = false;
}

void losowanie(pole tab[ROZMIAR][ROZMIAR])
{
	srand(time(NULL));
	//czy�cimy plansz�
	wypelnienie(tab);
	//losujemy oko�o 1/4 p�l
	for (int i = 0; i < (((ROZMIAR - 2)*(ROZMIAR - 2)) / 4); i++)
	{
		int a = ((rand() % 12) + 1), b = ((rand() % 12) + 1);//losowanie pola
		int g = (rand() % 2);//losowanie warto�ci pola
		if (tab[a][b].mod == false)
		{
			for (int k = 0; k < ROZMIAR; k++)//ilo�� pr�b losowania w przypadku wylosownaia niemodyfikowalnego pola
			{
				a = ((rand() % 12) + 1), b = ((rand() % 12) + 1);
				if (tab[a][b].mod == false) continue;
				else break;
			}
		}
		if (tab[a][b].mod == true)
		{
			if (g == 0)
			{
				if (sprawdzenie_1_0(tab, b + 36, a + 1) == true && sprawdzenie_2_0(tab, b + 36, a + 1) == true)//sprawdzanie reg�
				{
					tab[a][b].wartosc = '0';
					tab[a][b].mod = false;
				}
				else i--;//powt�rzenie losowania
			}
			if (g == 1)
			{
				if (sprawdzenie_1_1(tab, b + 36, a + 1) == true && sprawdzenie_2_1(tab, b + 36, a + 1) == true)//sprawdzanie reg�
				{
					tab[a][b].wartosc = '1';
					tab[a][b].mod = false;
				}
				else i--;//powt�rzenie losowania
			}
			
		}
	}
}

void podpowedz_2(pole tab[ROZMIAR][ROZMIAR])
{
	int wiersz = 0, kolumna = 0, ilosc_1 = 0, ilosc_0 = 0;//zmienne zmieniaj�ce miejsce cputu i okre�laj�ce ilo�� 0 i 1 w rz�dzie b�d� kolumnie
	char txt[32];
	gotoxy(36+ROZMIAR, 1);
	//poziom
	cputs("ilosc 0|1:");
	//zliczanie powt�rze� 1 i 0
	for (int i = 1; i <= (ROZMIAR - 2); i++)
	{
		for (int j = 1; j <= (ROZMIAR - 2); j++)
		{
			if (tab[i][j].wartosc == '0') ilosc_0++;
			else if (tab[i][j].wartosc == '1') ilosc_1++;
		}
		wiersz++;
		gotoxy(36 + ROZMIAR, 1+wiersz);
		sprintf_s(txt, "%d|%d", ilosc_0, ilosc_1); //wypis ilo�ci powt�rze� 1 i 0
		cputs(txt);
		ilosc_1 = 0, ilosc_0 = 0;
	}
	//pion
	gotoxy(14 + ROZMIAR, ROZMIAR+1);
	cputs("Ilosc 0:");
	gotoxy(14 + ROZMIAR, ROZMIAR+2);
	cputs("--------");
	gotoxy(14 + ROZMIAR, ROZMIAR+3);
	cputs("Ilosc 1:");
	//zliczanie powt�rze� 1 i 0
	for (int i = 1; i <= (ROZMIAR - 2); i++)
	{
		for (int j = 1; j <= (ROZMIAR - 2); j++)
		{
			if (tab[j][i].wartosc == '0') ilosc_0++;
			else if (tab[j][i].wartosc == '1') ilosc_1++;
		}
		//wypis ilo�ci powt�rze� 1 i 0
		wiersz++;
		gotoxy(23 + ROZMIAR+kolumna, ROZMIAR+1);
		sprintf_s(txt, "%d", ilosc_0);
		cputs(txt);
		gotoxy(23 + ROZMIAR+kolumna, ROZMIAR+2);
		cputs("-");
		gotoxy(23 + ROZMIAR+kolumna, ROZMIAR+3);
		sprintf_s(txt, "%d", ilosc_1);
		cputs(txt);
		ilosc_1 = 0, ilosc_0 = 0;
		kolumna++;
	}

	getch();//oczekiwanie na klikni�cie
}

void koniec_gry(pole tab[ROZMIAR][ROZMIAR])
{
	//sprawdzenie wszystkich p�
	for (int i = 1; i <= (ROZMIAR - 2); i++)
	{
		for (int j = 1; j <= (ROZMIAR - 2); j++)
		{
			if (tab[j][i].wartosc == '.')//sprawdzenie czy na danym polu jest warto�� czy jest puste
			{
				if (sprawdzenie_1_0(tab, i + 36, j + 1) == false || sprawdzenie_2_0(tab, i + 36, j + 1) == false)//sprawdzenie reg� dla 0
				{
					if (sprawdzenie_1_1(tab, i + 36, j + 1) == false || sprawdzenie_2_1(tab, i + 36, j + 1) == false)//sprawdzenie reg� dla 1
					{
						if (sprawdzenie_3_pion(tab, i + 36) == true || sprawdzenie_3_poziom(tab, j + 1) == true)//sprawdzenie reg�
						{
							//pod�wietlenie p�l na kt�rych nie mo�na nic wpisa�
							gotoxy(i + 36, j + 1);
							textbackground(4);
							putch(tab[j][i].wartosc);
						}
					}
				}
			}
		}
	}
	getch();
}
/* Uwaga: w docelowym programie nale�y zadeklarowa� odpowiednie
   sta�e, na przyk�ad po to, aby wyeliminowa� z programu
   warto�ci numeryczne umieszczajac w ich miejsce 
   dobrze dobrane identyfikatory */

int main() {
	int zn = 0, x = 40, y = 12, attr = 7, back = 0, zero = 0;
	char txt[32];
	pole tab[ROZMIAR][ROZMIAR];
	wypelnienie(tab);
	// je�eli program jest kompilowany w czystym j�zyku C
	// nale�y wywo�a� poni�sz� lini�
#ifndef __cplusplus
	Conio2_Init();
#endif
	// settitle ustawia tytu� okienka
	settitle("Damian Marek s171952");
	do {	
		int linia = 0;
		// ustawiamy czarny kolor t�a, z kt�rego b�dziemy
		// korzystali rysuj�c po ekranie
		// prosz� zerkn�� do conio2.h na list� dost�pnych kolor�w
		textbackground(BLACK);
		// czy�cimy ekran: wype�niamy spacjami z ustawionym kolrem t�a
		clrscr();
		// ustawiamy kolor tekstu na jasnoszary (7 == LIGHTGRAY)
		textcolor(7);
		//wypis pola
		gotoxy(36, 1);
		for (int i = 0; i < (ROZMIAR); i++)
		{
			for (int j = 0; j < (ROZMIAR); j++)
			{
				if (tab[i][j].mod == true)
				{
					textcolor(9);
					putch(tab[i][j].wartosc);
					textcolor(7);				
				}
				else putch(tab[i][j].wartosc);
			}
			gotoxy(36, 2 + i);
		}
		//wypis menu
		linia++;//wiersz legedny
		int a = 1;//kolumna legendy
		gotoxy(1, linia);
		// wy�wietlamy na ekranie, w miejscu kursora napis
		// kursor przesuwa si� w prawo o d�ugo�� napisu
		cputs("Damian Marek s171952"); linia += 2;
		gotoxy(a, linia);
		cputs("Lista implementacji:"); linia++;
		gotoxy(a, linia);
		cputs("a,b,c,d,e,f,g,h,k,j"); linia += 2;
		gotoxy(a, linia);
		cputs("Niebieskie pola - modyfikowalne"); linia ++;
		gotoxy(a, linia);
		cputs("Skroty klawiszowe:"); linia++;
		gotoxy(a, linia);
		cputs("esc = wyjscie"); linia++;
		gotoxy(a, linia);
		cputs("strzalki = poruszanie"); linia++;
		gotoxy(a, linia);
		cputs("1/0 = wpisanie cyfry"); linia++;
		gotoxy(a, linia);
		cputs("backspace = usuniecie wpisania"); linia++;
		gotoxy(a, linia);
		cputs("n = nowa gra"); linia++;
		gotoxy(a, linia);
		cputs("o = losowe uzupelnienie planszy"); linia++;
		gotoxy(a, linia);
		cputs("p = prosta podpowiedz"); linia++;
		gotoxy(a, linia);
		cputs("d = podpowiedz dot.reg.2"); linia++;
		gotoxy(a, linia);
		cputs("k = Czy gre mozna skonczyc?"); linia++;
		gotoxy(a, linia);
		cputs("spacja = zmiana koloru"); linia++;
		gotoxy(a, linia);
		cputs("enter = zmiana koloru tla"); linia++;
		gotoxy(a, linia);
		sprintf_s(txt, "pozcja na planszy x,y:%d,%d", x-36,y-1); linia++;
		cputs(txt);
		// wypisujemy na ekranie kod ostatnio naci�ni�tego klawisza
		if(zero) sprintf_s(txt, "kod klawisza: 0x00 0x%02x", zn);
		else sprintf_s(txt, "kod klawisza: 0x%02x", zn);  linia++;
		gotoxy(a, linia);
		cputs(txt);

		// rysujemy na ekranie kolorow� gwiazdk�
		gotoxy(x, y);
		textcolor(attr);
		textbackground(back);
		// putch rysuje jeden znak i przesuwa kursor w prawo
		putch('*');

		// czekamy na naci�ni�cie klawisza i odczytujemy jego kod,
		// wi�kszo�� kod�w klawiszy odpowiada ich znakom, np.
		// a to 'a', 2 to '2', + to '+', ale niekt�re klawisze
		// specjalne, np. strza�ki s� zg�aszane jako dwa kolejne znaki,
		// z kt�rych pierwszy jest zerem, np. strza�ka w g�r�
		// to zero i 'H'
		zero = 0;
		zn = getch();
		//opcje w menu
		//wpisanie 0
		if (zn == 0x30)
		{
			if (tab[y - 1][x - 36].mod == true)
			{
				if (sprawdzenie_1_0(tab, x, y) == true && sprawdzenie_2_0(tab, x, y) == true)
				{
					tab[y - 1][x - 36].wartosc = '0';
					if (sprawdzenie_3_pion(tab, x) == false || sprawdzenie_3_poziom(tab, y) == false)
					{
						tab[y - 1][x - 36].wartosc = '.';
					}
				}
			}
		}
		//wpisanie 1
		if (zn == 0x31)
		{
			if (tab[y - 1][x - 36].mod == true)
			{
				if (sprawdzenie_1_1(tab, x, y) == true && sprawdzenie_2_1(tab, x, y) == true)
				{
					tab[y - 1][x - 36].wartosc = '1';
					if (sprawdzenie_3_pion(tab, x) == false || sprawdzenie_3_poziom(tab, y) == false)
					{
						tab[y - 1][x - 36].wartosc = '.';
					}
				}
			}
		}
		//usuni�cie wpisania backspace
		if (zn == 0x08)
		{
			if (tab[y - 1][x - 36].mod == true)
			{
					tab[y - 1][x - 36].wartosc = '.';
			}
		}
		//n- nowa gra
		if (zn == 0x6e || zn ==0x4e)
		{ 
			nowa_gra(tab);
		}
		//0-losowe wypelnienie
		if (zn == 0x6f || zn == 0x4f)
		{
			losowanie(tab);
		}
		//p- prosta podpowied�
		if (zn == 0x70 || zn == 0x50)
		{
			prosta_podpowiedz(tab, x, y);
		}
		//d-podpowied� dot. reg2
		if (zn == 0x64 || zn == 0x44)
		{
			podpowedz_2(tab);
		}
		//K-sprawdzenie mo�liwo�ci uko�czenia gry
		if (zn == 0x6b || zn == 0x4b)
		{
			koniec_gry(tab);
		}
		// nie chcemy, aby klawisz 'H' dzia�a� jako strza�ka w g�r�
		// wi�c sprawdzamy, czy pierwszym znakiem by�o zero
		if(zn == 0) {
			zero = 1;		// je�eli tak, to czytamy
			zn = getch();		// kolejny znak wiedz�c ju�,
			if(zn == 0x48) y--;		// �e b�dzie to znak specjalny
			if (y<2 || y>(ROZMIAR - 1)) y++;//ograniczenie ruchu gracza
			else if(zn == 0x50) y++;
			if (y<2 || y>(ROZMIAR - 1)) y--;//ograniczenie ruchu gracza
			else if(zn == 0x4b) x--;
			if (x<37 || x>37+(ROZMIAR-3)) x++;//ograniczenie ruchu gracza
			else if(zn == 0x4d) x++;
			if (x<37 || x>37 + (ROZMIAR-3)) x--;//ograniczenie ruchu gracza
		} else if(zn == ' ') attr = (attr + 1) % 16;
		else if(zn == 0x0d) back = (back + 1) % 16;
	} while (zn != 0x1b);

	return 0;
	}
