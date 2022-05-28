#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int NoSali = -1;

typedef struct list
{
    struct node *head;
} list;

typedef struct node
{
    int numar;
    int locuri;
    int status;
    struct node *next;
} node;

struct list lista_sali;

void Append(list *l,int loc,int nr,int stat){

    node* NOU = (node*)malloc(sizeof(node*));
    NOU -> next = NULL;
    NOU -> numar = nr;
    NOU -> status = stat;
    NOU -> locuri = loc;

    if(l -> head == NULL){
        l->head = NOU;

    }
    else{

        node* aux = l->head;
        while(aux->next!= NULL)aux = aux->next;
            aux->next = NOU;



    }

}


void citire_CSV(){

FILE* c=fopen("Sali_FIle.csv","r");

if(!c)printf("Eroare");
else{
    char buffer[1024];
    int row=0;
    int col=0;

    while(fgets(buffer,1024,c)){
    int locuri=0,status=0,nr;
    NoSali++;
        col = 0;
        row++;
        if(row==1)continue;
        char* val=strtok(buffer,",");
        while(val){
        if(col == 0)nr = NoSali;
        if(col == 1)locuri = atoi(val);
        if(col == 2)status = atoi(val);

        val = strtok(NULL,",");
        col++;
        }

    Append(&lista_sali,locuri,nr,status);


    }

   fclose(c);
}


return;


}

void Stergere(list* l,int k){

node* current =l->head;
node* prev = NULL;

while(current!=NULL){


    if(current->numar==k){

        if(prev!=NULL){
            prev->next=current->next;
            free(current);
            return;
        }
        l->head=current->next;
        free(current);

    }
    prev=current;
    current=current->next;


}



}

node* Find_Node(list l,int k){

    node* start=l.head;

while(start!=NULL){

    if(start->numar==k)return start;

    start=start->next;
}
return NULL;

}

void An_Rez(int k){

    node* aux= Find_Node(lista_sali,k);

    aux->status=1;

    return;
}



void Rezerv(int k){

    node* aux= Find_Node(lista_sali,k);
    aux->status=0;

    return;


}


void print_list_numar(list l,int k){

    node* first=l.head;

    while(first!=NULL){

        if(first->locuri==k) {
            if (first->status != 0)printf("%d, %d, Nezervat\n", first->numar, first->locuri);
            else if (first->status == 0)printf("%d, %d, Rezervat\n", first->numar, first->locuri);

        }
        first=first->next;

    }
    return;

}

void print_list_nerez(list l){

    node* first=l.head;

    while(first!=NULL){

        if(first->status!=0)printf("%d, %d, Nezervat\n",first->numar,first->locuri);

        first=first->next;

    }

}

void print_list_rez(list l){

    node* first=l.head;

    while(first!=NULL){

        if(first->status==0)printf("%d, %d, Rezervat\n",first->numar,first->locuri);

        first=first->next;

    }


}

void Save(){
FILE* s=fopen("Sali_FIle.csv","w+");

node* aux = lista_sali.head;


fprintf(s,"Nume,Locuri,Status\n");

while(aux!=NULL){

    fprintf(s,"%d,%d,%d\n",aux->numar,aux->locuri,aux->status);
    aux=aux->next;


}



fclose(s);

}




void SaliDisponibile(){
    puts("\n\n\n");
        int sub_alegere1 = 1;
        while(sub_alegere1 != 0){

            puts("|============================|");
            puts("       Vizualizare sali");
            puts("|============================|");


            puts("1.Sali disponibile");
            puts("2.Sali rezervate");
            puts("3.Dupa un numar de locuri");
            puts("0.Inapoi la meniul principal");

            puts(">>>  ");
            scanf("%d",&sub_alegere1);

            if(sub_alegere1==1){print_list_nerez(lista_sali); puts("1.Intoarcere la meniul vizualizare sali?");
                puts(">>> ");scanf("%d",&sub_alegere1); }
                else if(sub_alegere1==2){print_list_rez(lista_sali); puts("1.Intoarcere la meniul vizualizare sali?");
                puts(">>> ");scanf("%d",&sub_alegere1); }
                        else if(sub_alegere1==3){
                            int nrloc=0; puts("Numarul de locuri cautat:");
                            scanf("%d",&nrloc);
                            print_list_numar(lista_sali,nrloc);
                puts("1.Intoarcere la meniul vizualizare sali?");
                puts(">>> ");
                scanf("%d",&sub_alegere1);

                        }







        }


    return;


}

void RezervareSali(){

puts("\n\n\n");
        int sub_alegere2 = 1;
        while(sub_alegere2 != 0){

            puts("|============================|");
            puts("        Rezervare sala        ");
            puts("|============================|");

            print_list_nerez(lista_sali);
            puts("1.Rezervare");
            puts("0.Inapoi la meniul principal");
            puts("Precizati numarul salii pe care doriti sa o rezervati:");

            puts(">>>  ");
            scanf("%d",&sub_alegere2);

           if(sub_alegere2==1){int nrsala;
               char ora[1024];
               puts("Precizati numarul salii pe care doriti sa o rezervati:");
               puts(">>> ");
               scanf("%d",&nrsala);
               Rezerv(nrsala);

            puts("Rezervare efectuata cu succes!");
            puts("Intoarcere la meniul de rezervari!");}
            else if(sub_alegere2==0){

               puts("Intoarcere la meniul principal");
            }
            else printf("INVALID!");


        }
        Save();
return;

}

void AnulareRezervare(){
puts("\n\n\n");
       int sub_alegere3 = 1;
       while(sub_alegere3!=0){

            puts("|============================|");
            puts("        Anulare rezervare        ");
            puts("|============================|");
           print_list_rez(lista_sali);
            puts("1.Anulare");
            puts("0.Inapoi la meniul principal");
            puts(">>> ");

            scanf("%d", &sub_alegere3);
            if(sub_alegere3==1){int nrsala;
            puts("Introduceti numarul salii rezervate");
            puts(">>> ");
            scanf("%d",&nrsala);
                An_Rez(nrsala);
            puts("Anulare efectuata cu succes!");

            }
            else if(sub_alegere3 == 0){


            puts("\n");
            puts("Intoarecere la meniul principal");}
                else puts("INVALID");

       }

Save();
return;


}

void CautaSala(){
puts("\n\n\n");
        int sub_alegere4 = 1;

        while(sub_alegere4 != 0){
            puts("|============================|");
            puts("        Cauta o sala       ");
            puts("|============================|");
            puts("1.Cauta sala");
            puts("0.Inapoi la meniul princial");
            puts(">>> ");

            scanf("%d",&sub_alegere4);

            if(sub_alegere4 == 1){int nrsala;

                puts("|============================|");
                puts("Introduceti numarul salii");
                puts(">>> ");
                scanf("%d",&nrsala);

                node*aux= Find_Node(lista_sali,nrsala);
                if(aux->status==0)printf("Date despre sala: No:%d\n Locuri: %d\n  Status:Rezervat\n",aux->numar,aux->locuri,aux->status);
                else printf("Date despre sala: No:%d\n Locuri: %d\n  Status:Nezervat\n",aux->numar,aux->locuri,aux->status);

                puts("1.Intoarcere la meniul de cautare ?");
                puts(">>> ");
                scanf("%d",&nrsala);
            }
            else if(sub_alegere4 == 0){

                 puts("\n");
            puts("Intoarecere la meniul principal");
            }
                else puts("INVALID");


        }
return;
}

void AdaugaStergeSala(){
puts("\n\n\n");
        int sub_alegere5 = 1;

        while(sub_alegere5!=0){
            puts("|============================|");
            puts("      Adauga|sterge o sala     ");
            puts("|============================|");

            puts("1.Adauga o sala");
            puts("2.Sterge o sala");
            puts("0.Inapoi la meniul principal");

            puts(">>> ");

            scanf("%d",&sub_alegere5);

            if(sub_alegere5 == 1){int locuri;
                    puts("|============================|");
                    puts("Introduceti numarul de locuri : ");
                    scanf("%d",&locuri);
                NoSali++;

                Append(&lista_sali,locuri,NoSali,1);
                    puts("Sala adaugata cu succes!");


            }
            if(sub_alegere5 == 2){int nrsala;
                puts("|============================|");

                print_list_nerez(lista_sali);
                puts("Stergerea se poate realiza doar pe sali nerezervate !");
                puts("Introduceti numarul salii:");
                scanf("%d",&nrsala);

                Stergere(&lista_sali,nrsala);
                puts("Sala inlaturata cu succes!");


            }
            if(sub_alegere5 == 0){

                puts("Intoarecere la meniul principal");

            }


        }

Save();
return;


}





int main()
{ int alegere = 0;


citire_CSV();




while(alegere != 6){

        puts("\n\n\n");

     puts("|============================|");

    puts("            Meniu           ");

     puts("|============================|");


    puts("1.Vizualizare sali");
    puts("2.Rezervare sala");
    puts("3.Anulare rezervare");
    puts("4.Cauta o sala");
    puts("5.Adauga|sterge o sala");
    puts("6.Inchide aplicatie");//daca nu se alege una din variantele de mai sus print INVALID


    printf(">> ");
    scanf("%d",&alegere);


    switch(alegere){
    case 1:
        SaliDisponibile();
        break;
    case 2:
       RezervareSali();
        break;
    case 3:
       AnulareRezervare();
        break;
    case 4:
       CautaSala();
        break;
    case 5:
      AdaugaStergeSala();

        break;
    case 6:
        puts("Exit");
        break;
    default:
        puts("INVALID");




    }

}


Save();
return 0;
}
