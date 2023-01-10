#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct knjiga
{
    int sifra;
    char autor[30];
    char naziv[30];
    int kolicina;
    char zanr[30];
    struct knjiga* sledeci;
    
}knjiga;

void stampaj_knjigu(knjiga* k){
    printf(" %3d  %18s   %25s  %2d  %s \n", k->sifra, k->autor, k->naziv, k->kolicina, k->zanr);
}

void ubaci_element(knjiga **koren, knjiga *novi){
    if(*koren == NULL || (*koren)->sifra >= novi->sifra){
        novi->sledeci = *koren;
        *koren = novi;
        
    }else{
          knjiga* temp = *koren;
        while ( temp->sledeci != NULL && temp->sledeci->sifra < novi->sifra  )
        {
        //    printf("$$$$ sadasni je:  ");
        //    stampaj_knjigu(temp);
           //printf("sledeca sifra je: %d , dok je nasa sifra %d \n",temp->sledeci->sifra, novi->sifra );
            temp = temp->sledeci;
            
        }

        novi->sledeci = temp->sledeci;
        temp->sledeci = novi;

     
    }  
}

knjiga* ucitaj(char ime_fajla[30]){

    FILE* f = fopen(ime_fajla, "r");

    knjiga* koren = NULL;

    int n;
    fscanf(f, "%d", &n);
    //printf("n je: %d\n",n);

    for (int i = 0; i < n; i++)
    {
        // printf("A i:%d \n",i);
        knjiga* temp = (knjiga*) malloc(sizeof(knjiga));

        fscanf(f, "%d\n", &temp->sifra);
        // printf("i:%d  sifra je: %d   \n", i, temp->sifra);
        fgets(temp->autor,30,f);
        // printf("i:%d  autor je: %s   \n", i, temp->autor);
        fgets(temp->naziv,30,f);
        // printf("i:%d  naziv je: %s   \n", i, temp->naziv);
        fscanf(f, "%d\n", &temp->kolicina);
        // printf("i:%d  kolicina je: %d   \n", i, temp->kolicina);
        fgets(temp->zanr,30,f);
        // printf("i:%d  zanr je: %s   \n", i, temp->zanr);


        int len = strlen( temp->autor );
        if (len > 0 && temp->autor[len-1] == '\n') {
            temp->autor[len-1] = '\0';
        }

        len = strlen(temp->naziv);
        if (len > 0 && temp->naziv[len-1] == '\n') {
            temp->naziv[len-1] = '\0';
        }


        len = strlen(temp->zanr);
        if (len > 0 && temp->zanr[len-1] == '\n') {
            temp->zanr[len-1] = '\0';
        }
        


        ubaci_element(&koren, temp);
        

    } 
    return koren;
}



void stampaj(knjiga* koren) {
    while( koren != NULL ){
        stampaj_knjigu(koren);
        koren = koren->sledeci;
    }
}




int prodaj(int index, knjiga* koren){

    knjiga* temp = koren;


    while(temp->sledeci != NULL && temp->sledeci->sifra != index){
        temp = temp->sledeci;
    }

    if(temp == NULL) {
        printf("DOSLO JE DO GRESKE, NISMO NASLI KNJIGU SA INDEKSOM %d \n\n" , index);
        return 0; 
    }

    // sada temp->sifra == index
    if(temp->sledeci->kolicina > 1){
        temp->sledeci->kolicina = temp->sledeci->kolicina -1;
        return temp->sledeci->kolicina; // Kao povratynu vrednost vracamo broj knjiga koje su preostale

    }else if(temp->kolicina < 1 ){
         printf("DOSLO JE DO GRESKE, NEMAMO NI 1 KNJIGU SA INDEKSOM %d \n\n" , index);
         return 0;

    }else{ // temp.sledeci.kolicina == 1
        temp->sledeci = temp->sledeci->sledeci;
        return -1; // Vracamo -1 ako nemamo vise primeraka te knjige

    }

}



int main(int argc, char const *argv[])
{
    printf(" ##### POCETAK PROGRAMA ##### \n\n");


    knjiga* koren = ucitaj("knjizara.txt");


    //



    stampaj(koren);

    printf(" \n\n $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  \n\n");
    

    int ostalo_jos = -5;

    ostalo_jos = prodaj(157, koren);
    ostalo_jos = prodaj(157, koren);
    ostalo_jos = prodaj(157, koren);
    ostalo_jos = prodaj(157, koren);
    ostalo_jos = prodaj(157, koren);
    ostalo_jos = prodaj(157, koren);

    printf("Ostalo je jos %d knjiga sa ondexom 157 \n", ostalo_jos);

    printf(" \n\n $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$  \n\n");

    stampaj(koren);





    
    printf("\n\n ##### KRAJ PROGRAMA #####");
    return 0;
}
