#include<iostream>
#include<time.h>
#include<cstdlib>
#include<windows.h>
#include<stdlib.h>
#include<stdio.h>

using namespace std;
int T[3][3];
int suma[8];
int pole1; //pierwsza wspó³rzêdna
int pole2; //druga wspó³rzêdna
int wybor; //sprawdza który tryb zosta³ wybrany
int rozpoczynajacy; // sluzy do wyboru rozpoczynajacego
char kolor_o, kolor_x, zmina_koloru; //sluza do zmiany kolorow wedlug uznania uzytkownika
int kolor1=12, kolor2=10; //sluza do zmiany kolorow wedlug uznania uzytkownika
int i;
char plansza[14][14]; //jest wyswietlana
clock_t koniec;
clock_t start;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // umozliwia wyswietlenie pojedyncych znakow w roznych kolorach

void sumowanie() //sumuje tablice sluzaca do sprawdzania czy ktos wygral
{
    suma[0]=T[0][0]+T[0][1]+T[0][2];
    suma[1]=T[1][0]+T[1][1]+T[1][2];
    suma[2]=T[2][0]+T[2][1]+T[2][2];
    suma[3]=T[0][0]+T[1][0]+T[2][0];
    suma[4]=T[0][1]+T[1][1]+T[2][1];
    suma[5]=T[0][2]+T[1][2]+T[2][2];
    suma[6]=T[0][0]+T[1][1]+T[2][2];
    suma[7]=T[2][0]+T[1][1]+T[0][2];
}

void wybor_kolorow(char zmiana_koloru) //umozliwia uzytkownikowi zmiane kolorow krzyzyka i kolka wedlug uznania
{
    cout << "Wpisz t (tak) je¿eli chcesz zmieniæ ustawienia kolorów krzy¿yka i kó³ka z domyœlnych na inne lub jakikolwiek inny znak je¿eli chcesz zachowaæ ustawienia domyœlne (zielony i czerwony)." << endl;
    cin >> zmiana_koloru;
    system ("cls");

    if (zmiana_koloru=='t')
    {
        cout << "Wpisz dan¹ literê dla koloru, który ma byæ kolorem kó³ka:" << endl;
        cout << "c-kolor czerwony" << endl;
        cout << "r-kolor ró¿owy" << endl;
        cout << "b-kolor bia³y" << endl;

        do
        {
            cout << "Podaj znak" << endl;
            cin >> kolor_o;
        }
        while (kolor_o!='c'&&kolor_o!='r'&&kolor_o!='b');
        cout << "Poda³eœ dobry znak" << endl;

        if(kolor_o=='r')
        {
            kolor1=13;
        }
        else if (kolor_o=='b')
        {
            kolor1=15;
        }
        system("cls");

        cout << "Wpisz dan¹ literê dla koloru, który ma byæ kolorem krzy¿yka:" << endl;
        cout << "z-kolor zielony" << endl;
        cout << "c-kolor ciemno niebieski" << endl;
        cout << "j-kolor jasno niebieski" << endl;

        do
        {
            cout << "Podaj znak" << endl;
            cin >> kolor_x;
        }
        while (kolor_x!='z'&&kolor_x!='c'&&kolor_x!='j');
        cout << "Poda³eœ dobry znak" << endl;

        if(kolor_x=='c')
        {
            kolor2=9;
        }
        else if (kolor_x=='j')
        {
            kolor2=11;
        }
        system("cls");
    }
}

void dobra_liczba_czlowiek()
{
	for(int x=2;x>1;x++) //sprawdza czy pole nie jest zajête. Jeœli nie jest to ³amie fora i idzie dalej a jeœli jest to trzeba wpisaæ jeszcze raz
		{
		    cout << "Podaj numer kolumny: ";
			cin>>pole1;
			cout << "Podaj numer wiersza: ";
			cin>>pole2;
			if(pole1>2||pole1<0||pole2>2||pole2<0) //sprawdza czy pole istnieje bo jak siê podaje za du¿¹ liczbê to program przestaje dzia³aæ
			{
				cout<<"Takie pole nie istnieje"<<endl;
			}
			else
			{
				if(T[pole1][pole2]==0) x=0; //oznacza ¿e nie jest zajête a ten x=0 ¿eby z³amaæ fora
				else cout<<"To pole jest zajête"<<endl;
			}
		}
}

void wyswietlanie_planszy(int kolor1, int kolor2) //sluzy do wyswietlenia planszy
{
    cout << "  0    1    2" << endl;
    for (int a=0; a<14; a++)
    {
        if (a==1||a==6||a==11) //sluzy do wyswietlania bocznych wspolrzednych na planszy
        {
            cout << a/5;
        }
        else
        {
            cout << " ";
        }
        for (int b=0; b<14; b++)
        {
            if (a==4||a==9||b==4||b==9) // sprawdza czy ma wyswietlic elementy ramki
            {
                cout << plansza[b][a];
            }
            else if (T[b/5][a/5]==1) //sprawdza czy ma wyswietlac kolko
            {
                SetConsoleTextAttribute(hConsole, kolor1); //zmienia kolor dla znakow kolka
                cout << plansza[b][a];
                SetConsoleTextAttribute(hConsole, 7);
            }
            else //wyswitela krzyzyk
            {
                SetConsoleTextAttribute(hConsole, kolor2); //zmienia kolor dla znakow krzyzyka
                cout << plansza[b][a];
                SetConsoleTextAttribute(hConsole, 7);
            }
        }
        cout << endl;
    }
}

void powtarzalna_czesc_wyswietlania (int b, int c, int kolor1, int kolor2)
{
    if (c==4||c==9||b==4||b==9) // sprawdza czy ma wyswietlic elementy ramki
    {
        cout << plansza[b][c];
    }
    else if (T[b/5][c/5]==1) //sprawdza czy ma wyswietlac kolko i wyswietla go w odpowiednim kolorze
    {
        SetConsoleTextAttribute(hConsole, kolor1);
        cout << plansza[b][c];
        SetConsoleTextAttribute(hConsole, 7);
    }
    else //wyswitela dany znak krzyzyka
    {
        SetConsoleTextAttribute(hConsole, kolor2);
        cout << plansza[b][c];
        SetConsoleTextAttribute(hConsole, 7);
    }
}

void wyswietlanie_po_wygranej(int a)
{
    cout << "  0    1    2" << endl;
    for (int c=0; c<14; c++)
    {
        if (c==1||c==6||c==11) //sprawdza czy ma wyswietlic boczne wspolrzedne na planszy
        {
            cout << c/5;
        }
        else
        {
            cout << " ";
        }
        for (int b=0; b<14; b++)
        {
            if (a==0||a==1||a==2) //sprawdza czy ma wyswietlac przekreslenie w pionie
            {
                if (b==a*5+1||b==a*5+2) //sprawdza czy ma wyswietlac element przekreslenia
                {
                    SetConsoleTextAttribute(hConsole, 14);
                    cout << plansza[b][c];
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else
                {
                    powtarzalna_czesc_wyswietlania(b, c, kolor1, kolor2);
                }
            }
            else if (a==3||a==4||a==5) //sprawdza czy ma wyswietlac przekreslenie w poziomie
            {
                int d=a-3;
                if (c==d*5+1) //sprawdza czy ma wyswietlac element przekreslenia
                {
                    SetConsoleTextAttribute(hConsole, 14);
                    cout << plansza[b][c];
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else
                {
                    powtarzalna_czesc_wyswietlania(b, c, kolor1, kolor2);
                }
            }
            else if (a==6) //sprawdza czy ma wyswietlac przekreslenie w skosie od lewgo gornego rogu
            {
                if (b==c) //sprawdza czy ma wyswietlac element przekreslenia
                {
                    SetConsoleTextAttribute(hConsole, 14);
                    cout << plansza[b][c];
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else
                {
                    powtarzalna_czesc_wyswietlania(b, c, kolor1, kolor2);
                }
            }
            else //sprawdza czy ma wyswietlac przekreslenie w skosie od prawego gornego rogu
            {
                if (b==13-c) //sprawdza czy ma wyswietlac element przekreslenia
                {
                    SetConsoleTextAttribute(hConsole, 14);
                    cout << plansza[b][c];
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else
                {
                    powtarzalna_czesc_wyswietlania(b, c, kolor1, kolor2);
                }
            }
        }
    cout << endl;
    }
}

void wynik(int i)
{
    for (int a=0; a<8; a++)
    {
        if(suma[a]==3) //sprawdza czy wygralo kolko
        {
            koniec=clock();
            system("cls");
            double czas = double(koniec - start)/CLOCKS_PER_SEC;
            cout<<endl<<"Wygrywa kó³ko w czasie "<<czas<<"s!";
            exit(0);
        }
        else if(suma[a]==27) //sprawdza czy wygral krzyzyk
        {
            koniec=clock();
            system("cls");
            double czas = double(koniec - start)/CLOCKS_PER_SEC;
            cout<<endl<<"Wygrywa krzy¿yk w czasie "<<czas<<"s!";
            exit(0);
        }
        else if(i==8)
        {
            koniec=clock();
            double czas = double(koniec - start)/CLOCKS_PER_SEC;
            cout<<endl<<"Po "<<czas<<"s nastêpuje remis!";
            exit(0);
        }
    }
}

void wynik_z_wyswietlaniem(int i, int kolor1, int kolor2)
{
    for (int a=0; a<8; a++)
    {
        if(suma[a]==3) //sprawdza czy wygralo kolko
        {
            koniec=clock();
            if (a>=0&&a<=2) //przekresla trzy kolka w linii w pionie
            {
                for (int x=0; x<14; x++)
                {
                    plansza[a*5+1][x]='|';
                    plansza[a*5+2][x]='|';
                }
                system("cls");
                wyswietlanie_po_wygranej(a);
            }
            else if (a>=3&&a<=5) //przekresla trzy kolka w linii w poziomie
            {
                for (int x=0; x<14; x++)
                {
                    int y=a-3;
                    plansza[x][y*5+1]='_';
                }
                system("cls");
                wyswietlanie_po_wygranej(a);
            }
            else if (a==6) //przekresla trzy kolka w linii w skosie od lewego gornego rogu
            {
                for (int x=0; x<14; x++)
                {
                    plansza[x][x]='\\';
                }
                system("cls");
                wyswietlanie_po_wygranej(a);
            }
            else //przekresla trzy kolka w skosie od prawego gornego rogu
            {
                for (int x=0; x<14; x++)
                {
                    plansza[13-x][x]='/';
                }
                system("cls");
                wyswietlanie_po_wygranej(a);
            }
            double czas = double(koniec - start)/CLOCKS_PER_SEC;
            cout<<endl<<"Wygrywa kó³ko w czasie "<<czas<<"s!";
            exit(0);
        }
        else if(suma[a]==27) //sprawdza czy wygral krzyzyk
        {
            koniec=clock();
            if (a>=0&&a<=2) //przekreœla trzy krzyzyki w linii w pionie
            {
                for (int x=0; x<14; x++)
                {
                    plansza[a*5+1][x]='|';
                    plansza[a*5+2][x]='|';
                }
                system("cls");
                wyswietlanie_po_wygranej(a);
            }
            else if (a>=3&&a<=5) //przekreœlla trzy krzyzyki w linii w poziomie
            {
                for (int x=0; x<14; x++)
                {
                    plansza[x][(a-3)*5+1]='_';
                }
                system("cls");
                wyswietlanie_po_wygranej(a);
            }
            else if (a==6) //przekreœla trzy krzyzyki w linii w skosie od lewego gornego rogu
            {
                for (int x=0; x<14; x++)
                {
                    plansza[x][x]='\\';
                }
                system("cls");
                wyswietlanie_po_wygranej(a);
            }
            else //przekreœla trzy krzyzyki w linii w skosie od prawego gornego rogu
            {
                for (int x=0; x<14; x++)
                {
                    plansza[13-x][x]='/';
                }
                system("cls");
                wyswietlanie_po_wygranej(a);
            }
            double czas = double(koniec - start)/CLOCKS_PER_SEC;
            cout<<endl<<"Wygrywa krzy¿yk w czasie "<<czas<<"s!";
            exit(0);
        }
        else if(i==8)
        {
            koniec=clock();
            double czas = double(koniec - start)/CLOCKS_PER_SEC;
            cout<<endl<<"Po "<<czas<<"s nastêpuje remis!";
            exit(0);
        }
    }
}

void zmiana_na_kolko() // zmienia dane miejsce w planszy na kolko
{
    plansza[pole1*5+1][pole2*5]='_';
    plansza[pole1*5+2][pole2*5]='_';
    plansza[pole1*5+1][pole2*5+2]='_';
    plansza[pole1*5+2][pole2*5+2]='_';
    plansza[pole1*5][pole2*5+1]='/';
    plansza[pole1*5+3][pole2*5+1]='\\';
    plansza[pole1*5][pole2*5+2]='\\';
    plansza[pole1*5+3][pole2*5+2]='/';
}

void zmiana_na_krzyzyk() // zmienia dane miejsce w planszy na krzyzyk
{
    for (int a=0; a<4; a++)
    {
        plansza[pole1*5+a][pole2*5+a]='\\';
        plansza[pole1*5+a][pole2*5+3-a]='/';
    }
}

void pseldo_inteligencja(int i, int rozpoczynajacy)
{
    sumowanie();
    if(rozpoczynajacy==i%2) //sprawdza czy ruch robi komputer
    {
        cout<<"Teraz ruch robi krzy¿yk (komputer)"<<endl<<"Komputer myœli..."<<endl;
        bool wychodzenie1=true, wychodzenie2=true; //umozliwiaja wyjscie z pozniejszych petli jezeli zostanie wykonany ruch
        for (int a=0; a<8; a++)
        {
            if (suma[a]==18) //sprawdza czy komputer ma mozliwosc wygrania w pojedynczym ruchu
            {
                if (a==0||a==1||a==2) //sprawdza czy w pionie
                {
                    for (int k=0; k<3; k++)
                    {
                        if (T[a][k]==0)
                        {
                            T[a][k]=9;
                            wychodzenie1=false;
                            wychodzenie2=false;
                            pole1=a;
                            pole2=k;
                            k=3;
                            a=8;
                        }
                    }
                }
                else if (a==3||a==4||a==5) // sprawdza czy w poziomie
                {
                    int n=a-3;
                    for (int k=0; k<3; k++)
                    {
                        if (T[k][n]==0)
                        {
                            T[k][n]=9;
                            wychodzenie1=false;
                            wychodzenie2=false;
                            pole1=k;
                            pole2=n;
                            k=3;
                            a=8;
                        }
                    }
                }
                else if (a==6) //sprawdza czy w skosie
                {
                    for (int k=0; k<3; k++)
                    {
                        if (T[k][k]==0)
                        {
                            T[k][k]=9;
                            wychodzenie1=false;
                            wychodzenie2=false;
                            pole1=k;
                            pole2=k;
                            k=3;
                            a=8;
                        }
                    }
                }
                else //robi w dugim skosie
                {
                    for (int k=0; k<3; k++)
                    {
                        if (T[2-k][k]==0)
                        {
                            T[2-k][k]=9;
                            wychodzenie1=false;
                            wychodzenie2=false;
                            pole1=2-k;
                            pole2=k;
                            k=3;
                            a=8;
                        }
                    }
                }
            }
        }
        for (int a=0; a<8; a++)
        {
            if (suma[a]==2&&wychodzenie1) //sprawdza czy gracz ma szanse wygrac w pojedynczym ruchu
            {
                if (a==0||a==1||a==2) //sprawdza czy w pionie
                {
                    for (int k=0; k<3; k++)
                    {
                        if (T[a][k]==0)
                        {
                            T[a][k]=9;
                            wychodzenie2=false;
                            pole1=a;
                            pole2=k;
                            k=3;
                            a=8;
                        }
                    }
                }
                else if (a==3||a==4||a==5) //sprawdza czy w poziomie
                {
                    int n=a-3;
                    for (int k=0; k<3; k++)
                    {
                        if (T[k][n]==0)
                        {
                            T[k][n]=9;
                            wychodzenie2=false;
                            pole1=k;
                            pole2=n;
                            k=3;
                            a=8;
                        }
                    }
                }
                else if (a==6) //sprawdza czy w skosie
                {
                    for (int k=0; k<3; k++)
                    {
                        if (T[k][k]==0)
                        {
                            T[k][k]=9;
                            wychodzenie2=false;
                            pole1=k;
                            pole2=k;
                            k=3;
                            a=8;
                        }
                    }
                }
                else //robi w drugim skosie
                {
                    for (int k=0; k<3; k++)
                    {
                        if (T[2-k][k]==0)
                        {
                            T[2-k][k]=9;
                            wychodzenie2=false;
                            pole1=2-k;
                            pole2=k;
                            k=3;
                            a=8;
                        }
                    }
                }
            }
        }
        if (wychodzenie2) //jezeli ani komputer ani gracz nie maja szansy wygrania to komputer losuje miejsce polozenia krzyzyka
        {
            do
            {
                pole1=rand()%3;
                pole2=rand()%3;
            }
            while (T[pole1][pole2]!=0);
        }
        Sleep(1000);
        cout<<"Komputer wybra³ pole "<<pole1<<"x"<<pole2<<endl;
        T[pole1][pole2]=9;
        zmiana_na_krzyzyk();
    }
    else
    {
        cout<<"Teraz ruch robi kó³ko (gracz)"<<endl;
        dobra_liczba_czlowiek();
        T[pole1][pole2]=1;
        zmiana_na_kolko();
    }
}
int main()
{
    system("chcp 1250");
    system("cls");

	for(int z=0;z<3;z++) // nadaje kazdemu indeksowi 0 ¿eby nie przypisa³o mu siê 3 albo 27 bo wtedy poka¿e ¿e kó³ko albo krzy¿yk wygra³o
	{
		for(int a=0;a<3;a++)
			{
				T[z][a]=0;
			}
	}

	for (int a=0; a<14; a++) // przypisanie pustych pol na wyœwietlanej planszy
    {
        for (int b=0; b<14; b++)
        {
            plansza[a][b]=' ';
        }
    }

    for (int a=4; a<14; a=a+5) // tworzenie ramki na wyswietlanej planszy
    {
        for (int b=0; b<14; b++)
        {
            plansza[a][b]='|';
            plansza[b][a]='-';
        }
    }
    plansza[4][4]='+';
    plansza[4][9]='+';
    plansza[9][4]='+';
    plansza[9][9]='+';

	for(int e=3;e>2;e++)//¿eby wykonywa³o siê dopóki ktoœ nie wprowadzi dobrej liczby
	{
        cout<<"Wpisz 1, ¿eby zagraæ z drug¹ osob¹ na zapamiêtywanie"<<endl<<"Wpisz 2, ¿eby zagraæ z drug¹ osob¹ w normalny tryb"<<endl<<"Wpisz 3, ¿eby zagraæ z komputerem na zapamiêtywanie (zaczyna gracz)"<<endl;
        cout<<"Wpisz 4, ¿eby zagraæ z komputerem w normalny tryb (zaczyna gracz)"<<endl<<"Wpisz 5, ¿eby zagraæ z komputerem na zapamiêtywanie (zaczyna komputer)"<<endl<<"Wpisz 6, ¿eby zagraæ z komputerem w normalny tryb (zaczyna komputer)"<<endl;
        cout << "Wpisz 7, ¿eby zagraæ z komputerem (trudniejszy poziom) na zapamiêtywanie (rozpoczynaj¹cy jest losowany)" << endl;
        cout << "Wpisz 8, ¿eby zagraæ z komputerem (trudniejszy poziom) w normalny tryb (rozpoczynaj¹cy jest losowany)" << endl;
        cin>>wybor;
        system("cls");
        start=clock();
        switch(wybor)
        {
                case 1:
                    cout<<"Wybrany tryb: "<<endl<<"Gra z drug¹ osob¹ na zapamiêtywanie"<<endl<<endl<<"Jest to normalny tic-tac-toe, ale trzeba zapamiêtywac ruchy, bo plansza siê nie wyœwietla"<<endl<<"Nale¿y wpisaæ pierwsz¹ wspó³rzêdn¹ (numer kolumny), nacisn¹æ klawisz enter, wpisaæ drug¹ wspó³rzêdn¹ (numer wiersza) i znowu klikn¹æ enter"<<endl<<"Pamietaj ¿e pierwszy indeks to 0!"<<endl<<endl;
                    cout << "Naciœnij klawisz enter aby zacz¹æ grê." << endl;
                    cin.ignore();
                    getchar();
                    system("cls");
                    for(int i=0;i<9;i++)
                    {
                        if(i%2==0) cout<<"Teraz ruch robi kó³ko"<<endl;
                        else cout<<"Teraz ruch robi krzy¿yk"<<endl;
                        dobra_liczba_czlowiek();
                        if(i%2==0)
                        {
                            T[pole1][pole2]=1;
                        }
                        else
                        {
                            T[pole1][pole2]=9;
                        }
                        system("cls");
                        sumowanie();
                        wynik(i);
                    }
                    e=0;
                case 2:
                    wybor_kolorow(zmina_koloru);
                    cout<<"Wybrany tryb: "<<endl<<"Gra z drug¹ osob¹"<<endl<<endl<<"Jest to normalny tic-tac-toe"<<endl<<"Nale¿y wpisaæ pierwsz¹ wspó³rzêdn¹ (numer kolumny), nacisn¹æ klawisz enter, wpisaæ drug¹ wspó³rzêdn¹ (numer wiersza) i znowu klikn¹æ enter"<<endl<<"Pamietaj ¿e pierwszy indeks to 0!"<<endl<<endl;
                    cout << "Naciœnij enter aby rozpocz¹æ" << endl;
                    cin.ignore();
                    getchar();
                    system("cls");
                    wyswietlanie_planszy(kolor1, kolor2);

                    for(int i=0;i<9;i++)
                    {
                        if(i%2==0) cout<<"Teraz ruch robi kó³ko"<<endl;
                        else cout<<"Teraz ruch robi krzy¿yk"<<endl;
                        dobra_liczba_czlowiek();
                        if(i%2==0)
                        {
                            T[pole1][pole2]=1;
                            zmiana_na_kolko();
                        }
                        else
                        {
                            T[pole1][pole2]=9;
                            zmiana_na_krzyzyk();
                        }
                        system("cls");
                        wyswietlanie_planszy(kolor1, kolor2);
                        sumowanie();
                        wynik_z_wyswietlaniem(i, kolor1, kolor2);
                    }
                    e=0;
                case 3:
                    cout<<"Wybrany tryb: "<<endl<<"Gra z komputerem na zapamiêtywanie"<<endl<<endl<<"Jest to normalny tic-tac-toe z komputerem, ale trzeba zapamiêtywac ruchy, bo plansza siê nie wyœwietla"<<endl<<"Nale¿y wpisaæ pierwsz¹ wspó³rzêdn¹ (numer kolumny), nacisn¹æ klawisz enter, wpisaæ drug¹ wspó³rzêdn¹ (numer wiersza) i znowu klikn¹æ enter"<<endl<<"Pamiêtaj ¿e pierwszy indeks to 0!"<<endl<<endl;
                    cout << "Naciœnij enter by rozpocz¹æ" << endl;
                    cin.ignore();
                    getchar();
                    system("cls");

                    for(int i=0;i<9;i++)
                    {
                        if(i%2==0)
                        {
                            cout<<"Teraz ruch robi kó³ko (gracz)"<<endl;
                            dobra_liczba_czlowiek();
                            T[pole1][pole2]=1;
                        }
                        else
                        {
                            cout<<"Teraz ruch robi krzy¿yk (komputer)"<<endl<<"Komputer mysli..."<<endl;
                            for(int x=2;x>1;x++) //sprawdza czy pole istnieje i czy nie jest zajête. Jeœli istnieje i nie jest zajête to ³amie fora i idzie dalej a jeœli jest to trzeba wpisaæ jeszcze raz
                            {
                                pole1=rand()%3;
                                pole2=rand()%3;
                                if(T[pole1][pole2]==0)
                                {
                                    x=0;
                                }
                            }
                            Sleep(1000);
                            cout<<"Komputer wybra³ pole "<<pole1<<"x"<<pole2<<endl;
                            cout << "Naciœnij klawisz enter by kontynuowaæ grê." << endl;
                            cin.ignore();
                            getchar();
                            T[pole1][pole2]=9;
                        }
                        system("cls");
                        sumowanie();
                        wynik(i);
                    }
                    e=0;
                case 4:
                    wybor_kolorow(zmina_koloru);
                    cout<<"Wybrany tryb: "<<endl<<"Gra z komputerem"<<endl<<endl<<"Jest to normalny tic-tac-toe z komputerem"<<endl<<"Nale¿y wpisaæ pierwsz¹ wspó³rzêdn¹ (numer kolumny), nacisn¹æ klawisz enter, wpisaæ drug¹ wspó³rzêdn¹ (numer wiersza) i znowu klikn¹æ enter"<<endl<<"Pamiêtaj ¿e pierwszy indeks to 0!"<<endl<<endl;
                    cout << "Naciœnij enter" << endl;
                    cin.ignore();
                    getchar();
                    system("cls");
                    wyswietlanie_planszy(kolor1, kolor2);

                    for(int i=0;i<9;i++)
                    {
                        if(i%2==0)
                        {
                            cout<<"Teraz ruch robi kó³ko (gracz)"<<endl;
                            dobra_liczba_czlowiek();
                            T[pole1][pole2]=1;
                            zmiana_na_kolko();
                        }
                        else
                        {
                            cout<<"Teraz ruch robi krzy¿yk (komputer)"<<endl<<"Komputer mysli..."<<endl;
                            for(int x=2;x>1;x++) //sprawdza czy pole istnieje i czy nie jest zajête. Jeœli istnieje i nie jest zajête to ³amie fora i idzie dalej a jeœli jest to trzeba wpisaæ jeszcze raz
                            {
                                pole1=rand()%3;
                                pole2=rand()%3;
                                if(T[pole1][pole2]==0)
                                {
                                    x=0;
                                }
                            }
                            Sleep(1000);
                            cout<<"Komputer wybra³ pole "<<pole1<<"x"<<pole2<<endl;
                            T[pole1][pole2]=9;
                            zmiana_na_krzyzyk();
                        }
                        system("cls");
                        wyswietlanie_planszy(kolor1, kolor2);
                        sumowanie();
                        wynik_z_wyswietlaniem(i, kolor1, kolor2);
                    }
                    e=0;
                case 5:
                    cout<<"Wybrany tryb: "<<endl<<"Gra z komputerem na zapamiêtywanie"<<endl<<endl<<"Jest to normalny tic-tac-toe z komputerem, ale trzeba zapamiêtywaæ ruchy, bo plansza siê nie wyœwietla"<<endl<<"Nale¿y wpisaæ pierwsz¹ wspó³rzêdn¹ (numer kolumny), nacisn¹æ klawisz enter, wpisaæ drug¹ wspó³rzêdn¹ (numer wiersza) i znowu klikn¹æ enter"<<endl<<"Pamietaj ze pierwszy indeks to 0!"<<endl<<endl;
                    cout << "Naciœnij enter aby rozpocz¹æ" << endl;
                    cin.ignore();
                    getchar();
                    system("cls");

                    for(int i=0;i<9;i++)
                    {
                        if(i%2==0)
                        {
                            cout<<"Teraz ruch robi krzy¿yk (komputer)"<<endl<<"Komputer mysli..."<<endl;
                            for(int x=2;x>1;x++) //sprawdza czy pole istnieje i czy nie jest zajête. Jeœli istnieje i nie jest zajête to ³amie fora i idzie dalej a jeœli jest to trzeba wpisaæ jeszcze raz
                            {
                                pole1=rand()%3;
                                pole2=rand()%3;
                                if(T[pole1][pole2]==0)
                                {
                                    x=0;
                                }
                            }
                            Sleep(1000);
                            cout<<"Komputer wybra³ pole "<<pole1<<"x"<<pole2<<endl;
                            cout << "Naciœnij klawisz enter by kontynuowaæ grê." << endl;
                            cin.ignore();
                            getchar();
                            T[pole1][pole2]=9;
                        }
                        else
                        {
                            cout<<"Teraz ruch robi kó³ko (gracz)"<<endl;
                            dobra_liczba_czlowiek();
                            T[pole1][pole2]=1;
                        }
                        system("cls");
                        sumowanie();
                        wynik(i);
                    }
                    e=0;
                case 6:
                    wybor_kolorow(zmina_koloru);
                    cout<<"Wybrany tryb: "<<endl<<"Gra z komputerem"<<endl<<endl<<"Jest to normalny tic-tac-toe z komputerem"<<endl<<"Nale¿y wpisaæ pierwsz¹ wspó³rzêdn¹ (numer kolumny), nacisn¹æ klawisz enter, wpisaæ drug¹ wspó³rzêdn¹ (numer wiersza) i znowu klikn¹æ enter"<<endl<<"Pamiêtaj ¿e pierwszy indeks to 0!"<<endl<<endl;
                    cout << "Naciœnij dowolny klawisz aby zacz¹æ grê." << endl;
                    cin.ignore();
                    getchar();
                    system("cls");
                    wyswietlanie_planszy(kolor1, kolor2);

                    for(int i=0;i<9;i++)
                    {
                        if(i%2==0)
                        {
                            cout<<"Teraz ruch robi krzy¿yk (komputer)"<<endl<<"Komputer mysli..."<<endl;
                            for(int x=2;x>1;x++) //sprawdza czy pole istnieje i czy nie jest zajête. Jeœli istnieje i nie jest zajête to ³amie fora i idzie dalej a jeœli jest to trzeba wpisaæ jeszcze raz
                            {
                                pole1=rand()%3;
                                pole2=rand()%3;
                                if(T[pole1][pole2]==0)
                                {
                                    x=0;
                                }
                            }
                            Sleep(1000);
                            cout<<"Komputer wybra³ pole "<<pole1<<"x"<<pole2<<endl;
                            T[pole1][pole2]=9;
                            zmiana_na_krzyzyk();
                        }
                        else
                        {
                            cout<<"Teraz ruch robi kó³ko (gracz)"<<endl;
                            dobra_liczba_czlowiek();
                            T[pole1][pole2]=1;
                            zmiana_na_kolko();
                        }
                        system("cls");
                        wyswietlanie_planszy(kolor1, kolor2);
                        sumowanie();
                        wynik_z_wyswietlaniem(i, kolor1, kolor2);
                    }
                    e=0;
                case 7:
                    cout << "Wybrany tryb: " << endl << "Gra z komputerem (trudniejszy poziom) na zapamiêtywanie" << endl << endl;
                    cout << "Jest to normalny tic-tac-toe z komputerem, ale trzeba zapamiêtywaæ ruchy bo plansza siê nie wyœwietla." << endl;
                    cout << "Nale¿y wpisaæ pierwsz¹ wspó³rzêdn¹ (numer kolumny), nacisn¹æ klawisz enter, wpisaæ drug¹ wspó³rzêdn¹ (numer wiersza) i znowu klikn¹æ enter." << endl;
                    cout << "Pamiêtaj ¿e pierwszy indeks to 0!" << endl << endl;
                    cout << "Naciœnij enter." << endl;
                    cin.ignore();
                    getchar();
                    system("cls");

                    srand(time(NULL));
                    rozpoczynajacy=rand()%2;

                    for (int i=0; i<9; i++)
                    {
                        pseldo_inteligencja(i, rozpoczynajacy);
                        system("cls");
                        sumowanie();
                        wynik(i);
                    }
                    e=0;
                case 8:
                    wybor_kolorow(zmina_koloru);
                    cout << "Wybrany tryb: " << endl << "Gra z komputerem (trudniejszy poziom)" << endl << endl;
                    cout << "Jest to normalny tic-tac-toe z komputerem" << endl;
                    cout << "Nale¿y wpisaæ pierwsz¹ wspó³rzêdn¹ (numer kolumny), nacisn¹æ klawisz enter, wpisaæ drug¹ wspó³rzêdn¹ (numer wiersza) i znowu klikn¹æ enter" << endl;
                    cout << "Pamiêtaj ¿e pierwszy indeks to 0!" << endl << endl;
                    cout << "Naciœnij enter aby rozpocz¹æ." << endl;
                    cin.ignore();
                    getchar();
                    system("cls");
                    wyswietlanie_planszy(kolor1, kolor2);

                    srand(time(NULL));
                    rozpoczynajacy=rand()%2;

                    for (int i=0; i<9; i++)
                    {
                        pseldo_inteligencja(i, rozpoczynajacy);
                        system("cls");
                        wyswietlanie_planszy(kolor1, kolor2);
                        sumowanie();
                        wynik_z_wyswietlaniem(i, kolor1, kolor2);
                    }
                    e=0;
            }
        }
	return 0;
}
