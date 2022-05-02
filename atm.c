// ensimmäiseksi määritelty käytetyt funktiokirjastot
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

// määritelty käytetyt funktiot
void paavalikko();
void saldonTarkistus(float saldo);
float otto(float saldo);
int lopeta();
void virhe();
void lueRoskat(void);
void takaisin();

/* main- funktio kysyy käyttäjää ensin syöttämään pankkikorttinsa, jonka jälkeen se pyytää käyttäjää
syöttämään tunnuslukunsa, Mikäli tunnusluku on väärin ohjelma pyytää käyttäjää syöttämään sen uudelleen.
Kun tunnusluku on syötetty oikein eli tässä tapauksessa "1234" ohjelma päästää käyttäjää käyttämään toimintojaan.
Tunnusluvun tarkistuksessa on käytetty while-toistorakennetta. Ohjelma ensin aukaisee päävalikon jossa käyttäjä
valitsee mitä haluaa tehdä, vaihtoehtoina on rahan nosto, tilin saldon tarkistaminen tai lopetus.
Valinta ohjelmistossa toimii switch-valintarakenteen avustuksella*/
int main (void)
{
    int valinta;
    float saldo = 1000.00;
    char tilinumero[100];
    char pin[100];
    char tarkistaPin[100];
    int tulos = 1;
    int i;
    FILE *tiedosto;
    int valinta1;
    bool uudestaan = true;
    char c[100];
/*Kotitehtävä 6. käytän do-while toistorakennetta pyytämään ensin käyttäjää syöttämään tilinumeronsa. Tilinumeron syötettyä ohjelma
aukaisee tiedoston tietokoneelta joka sisältää pin koodin. Ohjelma pyytää käyttäjää syöttämään pin koodin joka
esiintyy tiedostossa. Mikäli pin on väärin ohjelma pyytää käyttäjää syöttämään sen uudelleen. Mikäli pin on oikein
ohjelma aukaisee päävalikon. Päävalikko toimii switch-valintarakenteen avulla.*/
    do {
        printf("Syötä tilinumerosi > ");
        fgets(tilinumero, 100, stdin);

        if(tilinumero[strlen(tilinumero) -1] == '\n')
            tilinumero[strlen(tilinumero) -1] = '\0';
        else
            lueRoskat();

        strcat(tilinumero, ".acc");

        if((tiedosto = fopen(tilinumero, "r")) != NULL)
        {
            do
            {
                printf("\nNäppäile tunnusluku \nSuojaa tunnuslukusi \nLopuksi paina enter > ");
                fgets(pin, 100, stdin);

                if(pin[strlen(pin) - 1] == '\n')
                    pin[strlen(pin) - 1] = '\0';
                else
                    lueRoskat();

                fgets(tarkistaPin, 100, tiedosto);


                if(tarkistaPin[strlen(tarkistaPin) - 1] == '\n')
                    tarkistaPin[strlen(tarkistaPin) - 1] = '\0';

                if(tarkistaPin[strlen(tarkistaPin) - 1] == '\r')
                    tarkistaPin[strlen(tarkistaPin) - 1] = '\0';

                if((i = strcmp(pin, tarkistaPin)) == 0)
                {
                    tulos = 0;
                    break;

                } else
                    printf("\nVäärä pin-koodi! \nYritä uudelleen! > ");

            } while (tulos);
        } else
            printf("\nTilinumerosi on vaarin.\n");

    }while (tulos);

    while (uudestaan)
    {
        paavalikko();
        scanf("%d", &valinta);


        switch (valinta)
        {

            case 1:
                saldo = otto(saldo);
                break;

            case 2:
                saldonTarkistus(saldo);
                break;

            case 3:
                lopeta();
                return 0;

            default:
                lueRoskat();
                virhe();
                break;
        }
        printf("Palaa takaisin painamalla enter\n");
        scanf("%c", c);

    }
    return 0;
}

// paavalikko-funktiossa on pelkästään tulostettu päävalikon vaihtoehdot
void paavalikko ()
{

    printf("\nValitse \nVoit lopettaa STOP-nappaimella \n1. Otto \n2. Saldo \n3. Stop \nja paina enter > ");

}

/* saldonTarkistus-funktio näyttää tarkalleen paljonko tilillä on rahaa sillä hetkellä.
lähtökohta tässä tapauksessa on 1000 euroa, joka muuttuu mikäli tililtä nostetaan rahaa */
void saldonTarkistus (float saldo)
{
    char c[100];
    printf("\nTilin saldo: %.2f \n", saldo);
    scanf("%c", c);
}

/* otto-funktio kysyy paljonko käyttäjä haluaa nostaa rahaa tililtä. Nosto tapahtuu while-toistorakenteen avustuksella.
Jonka sisällä on käytetty if-valintarakennetta*/
float otto(float saldo)
{
    int nosto;
    bool takaisin = true;
    char c[100];
    int viiskymp;
    int kakskymp;



    while (takaisin)
    {
        printf("Valitse nostettava summa:\n");
        lueRoskat();
        scanf("%d", &nosto);

        /*olen käyttänyt if-valintarakennetta rajoittamaan käyttäjän nostot 1000 euroon sekä hylkäämällä nostot joita ei voi
        toteuttaa 20 tai 50 euron seteleillä */

        if (nosto >= 1000){
            printf("Nostorajasi on 1000 euroa\n");
            scanf("%c", c);
            return saldo;
        }
        else if (nosto == 10 || nosto == 30)
        {
            printf("Et voi nostaa kuin 20 ja 50 euron seteleitä!\n");
            scanf("%c", c);
            return saldo;
        }

        /*Tässä if-valintarakenteessa on sisälletettynä kotitehtävä5 rahojen jakamisalgoritmi*/
        if (nosto <= saldo)
        {
            takaisin = false;

            viiskymp = nosto / 50 - (nosto > 50 && nosto % 50 % 20);
            kakskymp = (nosto - viiskymp * 50) / 20;
            if(nosto != viiskymp * 50 + kakskymp * 20)
            {
                printf("Et voi nostaa kuin 20 ja 50 euron seteleitä!\n");
                scanf("%c", c);
                return saldo;
            }
            else
            {
                printf("Ota tästä %d kpl 20 euron ja %d kpl 50 euron seteleitä.\nOle hyvä!\n", kakskymp, viiskymp);
                saldo -= nosto;
            }

        }
        else
        {
            printf("Sinulla ei ole tarpeeksi rahaa:\n\n");
        }
    }
    scanf("%c", c);
    return saldo;
}

// lopeta-funktio lopettaa ohjelman toiminnan ja kiittää käyttäjää sekä toivottaa käyttäjän tervetulleeksi uudelleen
int lopeta()
{
    printf("\nKiitos kaynnista \nTervetuloa uudelleen.");
    return 0;
}

// virhe-funktio ilmoittaa mikäli käyttäjä on tehnyt jotakin väärin
void virhe()
{
    printf("Virhe, yritä uudelleen\n");
}

// lueRoskat-funktio estää ohjelman kaatumista mikäli käyttäjä syöttää muuta kuin numeroita
void lueRoskat(void){
    while( fgetc(stdin) != '\n');
}
