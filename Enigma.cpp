#include<stdio.h>
#include<cstdlib>

void zwolnijPamiec(int**, int**, int**, int*, int**, int*);
int wyznaczLiczbe();
void daneORotorachINotchach(int**, int**, int*, int**, int, int);
void daneOReflektorach(int, int**, int);
void wyznaczWyjscie(int*, int, int*, int**, int*, int**, int, int, int);
void bezDoubleStepa(int**, int*, int*, int, int);
void wykonajDoubleStep(int*, int);
bool czyDoubleStep(int*, bool, int*, int, int**, int*, int);

int main() {
    
    int alfabet = wyznaczLiczbe();
    int ile_rotorow = wyznaczLiczbe();

    int** tablica_wszystkich_rotorow = (int**)malloc(sizeof(int) * ile_rotorow);
    int** tablica_notchy = (int**)malloc(sizeof(int) * ile_rotorow);
    int* liczba_notchy = (int*)malloc(sizeof(int) * ile_rotorow);
    int** czy_notch = (int**)malloc(sizeof(int) * ile_rotorow);

    daneORotorachINotchach(tablica_wszystkich_rotorow, tablica_notchy, liczba_notchy, czy_notch, alfabet, ile_rotorow);

    int ile_reflektorow = wyznaczLiczbe();
    int** tablica_wszystkich_reflektorow = (int**)malloc(sizeof(int) * ile_reflektorow);

    daneOReflektorach(ile_reflektorow, tablica_wszystkich_reflektorow, alfabet);

    int ile_wiadomosci= wyznaczLiczbe();
    int* ile_rotorow_bedzie_w_wiadomosci = (int*)malloc(sizeof(int) * ile_wiadomosci);


    int i = 0;
    while (i < ile_wiadomosci) {
        scanf_s("%d", &ile_rotorow_bedzie_w_wiadomosci[i]);
        int* ktory_rotor_uzyto = (int*)malloc(sizeof(int) * ile_rotorow_bedzie_w_wiadomosci[i]);
        int* na_jakiej_pozycji_stoi_rotor = (int*)malloc(sizeof(int) * ile_rotorow_bedzie_w_wiadomosci[i]);

        for (int j = 0; j < ile_rotorow_bedzie_w_wiadomosci[i]; j++) {
            scanf_s("%d", &ktory_rotor_uzyto[j]);
            scanf_s("%d", &na_jakiej_pozycji_stoi_rotor[j]);
        }

        int ktory_reflektor_w_tej_wiadomosci = wyznaczLiczbe();

        ++na_jakiej_pozycji_stoi_rotor[0];
        if (na_jakiej_pozycji_stoi_rotor[0] > alfabet)
            na_jakiej_pozycji_stoi_rotor[0] -= alfabet;


        bool aktywny = false;
        int liczba;
        bool doublestep = false;

        while (scanf_s("%d", &liczba)) {
            if (liczba == NULL)
                break;

            wyznaczWyjscie(ile_rotorow_bedzie_w_wiadomosci, alfabet, na_jakiej_pozycji_stoi_rotor, tablica_wszystkich_rotorow,
                ktory_rotor_uzyto, tablica_wszystkich_reflektorow, ktory_reflektor_w_tej_wiadomosci, i, liczba);

           
            ++na_jakiej_pozycji_stoi_rotor[0];
            if (na_jakiej_pozycji_stoi_rotor[0] > alfabet)
                na_jakiej_pozycji_stoi_rotor[0] -= alfabet;

            if (ile_rotorow_bedzie_w_wiadomosci[i] > 1 && liczba_notchy[ktory_rotor_uzyto[0]] > NULL && doublestep == false)
                bezDoubleStepa(czy_notch, ktory_rotor_uzyto, na_jakiej_pozycji_stoi_rotor, aktywny, alfabet);

            if(doublestep == true)
                wykonajDoubleStep(na_jakiej_pozycji_stoi_rotor, alfabet);
         
            doublestep = czyDoubleStep(ile_rotorow_bedzie_w_wiadomosci, aktywny, na_jakiej_pozycji_stoi_rotor, alfabet,
                czy_notch, ktory_rotor_uzyto, i);
           
        }
        ++i;
        free(ktory_rotor_uzyto);
        free(na_jakiej_pozycji_stoi_rotor);
    }
    
    zwolnijPamiec(tablica_notchy, tablica_wszystkich_reflektorow, tablica_wszystkich_rotorow, liczba_notchy,
        czy_notch, ile_rotorow_bedzie_w_wiadomosci);
   
}

int wyznaczLiczbe() {
    int liczba;
    scanf_s("%d", &liczba);
    return liczba;
}

void daneORotorachINotchach(int** tablica_wszystkich_rotorow, int** tablica_notchy,
                            int* liczba_notchy, int** czy_notch, int alfabet, int ile_rotorow ) {
    
    int j = 0;
    int iterator1;
    while (j < ile_rotorow) {
        tablica_wszystkich_rotorow[j] = (int*)malloc(sizeof(int) * alfabet);
        czy_notch[j] = (int*)malloc(sizeof(int) * alfabet);
        iterator1 = 0;
        while (iterator1 < alfabet) {
            scanf_s("%d", &tablica_wszystkich_rotorow[j][iterator1]);
            ++iterator1;
        }
        scanf_s("%d", &liczba_notchy[j]);
        tablica_notchy[j] = (int*)malloc(sizeof(int) * liczba_notchy[j]);
        if (liczba_notchy[j] != NULL) {
            iterator1 = 0;
            while (iterator1 < liczba_notchy[j]) {
                scanf_s("%d", &tablica_notchy[j][iterator1]);
                czy_notch[j][tablica_notchy[j][iterator1]] = 1;
                ++iterator1;
            }
        }
        ++j;
    }
}

void daneOReflektorach(int ile_reflektorow, int**tablica_wszystkich_reflektorow, int alfabet) {
    for (int i = 0; i < ile_reflektorow;i++) {
        tablica_wszystkich_reflektorow[i] = (int*)malloc(sizeof(int) * alfabet);
        for(int j=0;j<alfabet;j++ ) {
            scanf_s("%d", &tablica_wszystkich_reflektorow[i][j]);
            tablica_wszystkich_reflektorow[i][j] -= (j + 1);
        }
    }

}

void zwolnijPamiec(int**tablica_notchy,int**tablica_wszystkich_reflektorow,int**tablica_wszystkich_rotorow,
                   int*liczba_notchy,int**czy_notch,int* ile_rotorow_bedzie_w_wiadomosci) {

    free(tablica_wszystkich_reflektorow);
    free(tablica_wszystkich_rotorow);
    free(tablica_notchy);
    free(liczba_notchy);
    free(czy_notch);
    free(ile_rotorow_bedzie_w_wiadomosci);
}

void wyznaczWyjscie(int* ile_rotorow_bedzie_w_wiadomosci, int alfabet, int* na_jakiej_pozycji_stoi_rotor,
                    int** tablica_wszystkich_rotorow, int* ktory_rotor_uzyto, int** tablica_wszystkich_reflektorow,
                    int ktory_reflektor_w_tej_wiadomosci, int i, int liczba) {

        int iterator1 = 0;
        while (iterator1 < ile_rotorow_bedzie_w_wiadomosci[i]) {
            liczba = liczba + na_jakiej_pozycji_stoi_rotor[iterator1] - 1;
            if (liczba > alfabet)
                liczba -= alfabet;
            liczba = tablica_wszystkich_rotorow[ktory_rotor_uzyto[iterator1]][liczba - 1];


            liczba = liczba - na_jakiej_pozycji_stoi_rotor[iterator1] + 1;
            if (liczba <= NULL)
                liczba += alfabet;
            ++iterator1;
        }

        liczba += tablica_wszystkich_reflektorow[ktory_reflektor_w_tej_wiadomosci][liczba - 1];

        iterator1 = ile_rotorow_bedzie_w_wiadomosci[i];
        while (iterator1 > NULL) {
            liczba = liczba + na_jakiej_pozycji_stoi_rotor[iterator1 - 1] - 1;
            if (liczba > alfabet)
                liczba -= alfabet;

            int iterator2 = alfabet - 1;
            while (iterator2 >= NULL) {
                if (tablica_wszystkich_rotorow[ktory_rotor_uzyto[iterator1 - 1]][iterator2] == liczba) {
                    liczba = iterator2 - na_jakiej_pozycji_stoi_rotor[iterator1 - 1] + 2;
                    break;
                }
                --iterator2;
            }
            if (liczba <= NULL)
                liczba += alfabet;
            --iterator1;
        }
        printf("%d ", liczba);
}

void bezDoubleStepa(int** czy_notch, int* ktory_rotor_uzyto, int* na_jakiej_pozycji_stoi_rotor, int aktywny, int alfabet) {
    if (czy_notch[ktory_rotor_uzyto[0]][na_jakiej_pozycji_stoi_rotor[0]] == 1) {
        aktywny = true;
        ++na_jakiej_pozycji_stoi_rotor[1];
        if (na_jakiej_pozycji_stoi_rotor[1] > alfabet)
            na_jakiej_pozycji_stoi_rotor[1] -= alfabet;
    }
}

void wykonajDoubleStep(int* na_jakiej_pozycji_stoi_rotor, int alfabet) {
    ++na_jakiej_pozycji_stoi_rotor[1];
    if (na_jakiej_pozycji_stoi_rotor[1] > alfabet)
        na_jakiej_pozycji_stoi_rotor[1] -= alfabet;

    ++na_jakiej_pozycji_stoi_rotor[2];
    if (na_jakiej_pozycji_stoi_rotor[2] > alfabet)
        na_jakiej_pozycji_stoi_rotor[2] -= alfabet;
}

bool czyDoubleStep(int* ile_rotorow_bedzie_w_wiadomosci, bool aktywny, int* na_jakiej_pozycji_stoi_rotor,
                   int alfabet, int** czy_notch, int* ktory_rotor_uzyto, int i) {
    if (ile_rotorow_bedzie_w_wiadomosci[i] > 2 && aktywny == true &&
        na_jakiej_pozycji_stoi_rotor[1] != alfabet &&
        czy_notch[ktory_rotor_uzyto[1]][na_jakiej_pozycji_stoi_rotor[1] + 1] == 1) {
        return true;

    }
    else if (ile_rotorow_bedzie_w_wiadomosci[i] > 2 && aktywny == true && na_jakiej_pozycji_stoi_rotor[1] == alfabet && czy_notch[ktory_rotor_uzyto[1]][1] == 1) {
        return true;
    }
    return false;
}
