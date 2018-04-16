//Michał J
//Konwersja z postaci infixowej na postfixową
#include <stdio.h>


struct elementOfList{
    char symb;
    struct elementOfList *next;
};
struct elementOfList *firstElement = NULL, *lastElement = NULL;

//deklaracje funkcji
int priorytet(char symbol);
void addElementToList(int number);
void deleteLastElementOfList(struct elementOfList **firstElement,struct elementOfList **lastElement );

int main(void)
{

    printf("Konwersja z postaci infixowej na postfixowa zakonczona. Rownanie ma postac:\n");
    //deklaracje/definicje zmiennych
    char stos[30], znakWe;
    int zapelnienieStosu = -1, priorytetZnaku, priorytetWierzcholkaStosuTablica,priorytetWierzcholkaStosuLista;
    FILE *plikWe, *plikWyTablica, *plikWyLista;
    //otwarcie plików
    plikWe = fopen("WE.txt", "r");
    if(plikWe == NULL ){
        printf("Blad otwarcia pliku WE.txt");
        return 0;
    }
    plikWyTablica = fopen("WY.txt", "w");
    plikWyLista = fopen("WY2.txt", "w");
    //algorytm !
    while((znakWe = fgetc(plikWe)) != EOF){
        //napotkanie liczby
        if(znakWe >= '0' && znakWe <='9'){
            printf("%c   ", znakWe);
            fprintf(plikWyTablica, "%c", znakWe);
            fprintf(plikWyLista, "%c", znakWe);
        }
        //napotkanie innych znaków
        if(znakWe == '('){
            zapelnienieStosu++;
            stos[zapelnienieStosu] = znakWe;
            //lista
            addElementToList(znakWe);
        }
        if(znakWe == ')'){
            //tablica
            while(stos[zapelnienieStosu] != '(') {
                //                printf("%c   ",stos[zapelnienieStosu]);
                fprintf(plikWyTablica, "%c", stos[zapelnienieStosu]);
                zapelnienieStosu--;
            }

            if(stos[zapelnienieStosu] == '(') zapelnienieStosu--;
            //lista
            while(lastElement->symb != '('){
                printf("%c   ",lastElement->symb);
                fprintf(plikWyLista, "%c", lastElement->symb);
                deleteLastElementOfList(&firstElement,&lastElement);
            }
            if(lastElement->symb == '(') deleteLastElementOfList(&firstElement,&lastElement);

        }
        while (znakWe == '+' || znakWe == '-' || znakWe == '*' || znakWe == '/' || znakWe == '^')
        {
            priorytetWierzcholkaStosuTablica = priorytet(stos[zapelnienieStosu]);
            if(lastElement == NULL) priorytetWierzcholkaStosuLista = 0;
            else priorytetWierzcholkaStosuLista = priorytet(lastElement->symb);
            priorytetZnaku = priorytet(znakWe);
            //tablica
            if (priorytetZnaku > priorytetWierzcholkaStosuTablica || zapelnienieStosu == -1)
            {
                zapelnienieStosu++;
                stos[zapelnienieStosu] = znakWe;
            }
            if (priorytetZnaku <= priorytetWierzcholkaStosuTablica)
            {
            //printf("%c   ", stos[zapelnienieStosu]);
                fprintf(plikWyTablica, "%c", stos[zapelnienieStosu]);
                zapelnienieStosu--;
            }
            //lista
            if(priorytetZnaku > priorytetWierzcholkaStosuLista || firstElement == NULL){
                addElementToList(znakWe);
                break;
            }
            if(priorytetZnaku <= priorytetWierzcholkaStosuLista){
                printf("%c   ",lastElement->symb);
                fprintf(plikWyLista, "%c", lastElement->symb);
                deleteLastElementOfList(&firstElement, &lastElement);
            }

        }
    }
    //wypisanie ze stosu tablica
    while(zapelnienieStosu != -1)
    {
        //printf("%c   ", stos[zapelnienieStosu]);
        fprintf(plikWyTablica, "%c", stos[zapelnienieStosu]);
        zapelnienieStosu--;
    }
    //wypisanie ze stosu lista
    while(firstElement != NULL){
        printf("%c   ", lastElement->symb);
        fprintf(plikWyLista, "%c", lastElement->symb);
        deleteLastElementOfList(&firstElement, &lastElement);
    }
    //zamknięcie plików
    fclose(plikWe);
    fclose(plikWyTablica);
    fclose(plikWyLista);


    return 0;
}


//definicje funkcji
int priorytet(char symbol)
{
    switch(symbol){
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

void addElementToList(int symb){
    struct elementOfList *tran = malloc(sizeof(struct elementOfList));
    tran->symb=symb;
    tran->next=NULL;
    if(firstElement != NULL)
    {
        lastElement->next=tran;
        lastElement=tran;
        lastElement->next=NULL;
    }
    else
    {
        firstElement = tran;
        lastElement = tran;
    }
}

void deleteLastElementOfList(struct elementOfList **firstElement,struct elementOfList **lastElement ){
    struct elementOfList *curr = *firstElement;
    if((*firstElement)->next == NULL){
        //usuwanie pierwszego el
        *firstElement = NULL;
    }
    else{
        //wyszukanie przedostatniego el
        while(curr->next->next != NULL){
            curr = curr->next;
        }
        free(curr->next);
        curr->next=NULL;
        *lastElement = curr;
    }
}
