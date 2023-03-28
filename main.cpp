#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
ifstream fin("TXT.IN");
int n=0;
float x;
int m;
char med[21];
struct data{
    int zi;
    int luna;
    int an;
};
struct medicament{
    int cod;
    char nume[21];
    float pret;
    int buc;
    data data_e;
}produs[101],reteta[21];
void afisare(medicament produs[101],int n){
    cout<<" COD      DENUMIRE          PRET                    BUC                  VALOARE"<<endl;
    for(int i=1;i<=n;i++){
        cout<<produs[i].cod<<"    "<<produs[i].nume<<"           "<< produs[i].pret<<" lei                ";
        cout<< produs[i].buc<<" buc                "<<produs[i].buc*produs[i].pret<<" lei "<<endl;
    }
    return;
}
void citire(medicament produs[101], int&n){
   int i=1;
   while(fin>>produs[i].cod &&
         fin>>produs[i].nume &&
         fin>>produs[i].pret &&
         fin>>produs[i].buc &&
         fin>>produs[i].data_e.zi &&
         fin>>produs[i].data_e.luna &&
         fin>>produs[i].data_e.an){
             n++;
             fin.get();
             i++;
    }
    return;
}
void cautare_prod_nume(medicament produs[101], int n, char med[21] ){
    int k=0;
    for(int i=1;i<=n;i++)
            if(strstr(produs[i].nume,med)!=NULL){
                cout<< produs[i].cod<<' '<< produs[i].nume<<' ';
                cout<< produs[i].pret <<" lei "<< produs[i].buc <<" buc "<<endl;
                k++;
            }
    if (k==0)
        cout<<" Pe stoc nu exista acest medicament! "<<endl;
    return;
}
void afisare_prod_pret(medicament produs[101], int n, float p ){
    int k=0;
    for(int i=1;i<=n;i++)
            if(produs[i].pret==p){
                cout<< produs[i].cod<<' '<< produs[i].nume<<' ';
                cout<< produs[i].pret <<" lei "<< produs[i].buc <<" buc "<<endl;
                k++;
            }
    if(k==0)
        cout<<" Nu exista nici un medicament cu acest pret! "<<endl;
    return;
}
void prod_ieftin(medicament produs[101],int n){
    int i;
    float minim;
    minim=produs[1].pret;
    for(i=2;i<=n;i++){
        if(produs[i].pret<minim)
            minim=produs[i].pret;
    }
    afisare_prod_pret( produs,n,minim);
    return;
}
void prod_scump(medicament produs[101],int n){
    int i;
    float maxim;
    maxim=produs[1].pret;
    for(i=2;i<=n;i++){
        if(produs[i].pret>maxim)
            maxim=produs[i].pret;
    }
    afisare_prod_pret( produs,n,maxim);
    return;
}
void adauga_reteta(medicament produs[101],int n,medicament reteta[21],int j,int y){
    int i=1;
    while((produs[i].cod!=y)&&(i<=n))
        i++;
    reteta[j].cod=y;
    strcpy(reteta[j].nume,produs[i].nume);
    reteta[j].pret=produs[i].pret;
    cout<<" Numar bucati: ";
    cin>>reteta[j].buc;
    produs[i].buc=produs[i].buc-reteta[j].buc;
    reteta[j].data_e.zi=produs[i].data_e.zi;
    reteta[j].data_e.luna=produs[i].data_e.luna;
    reteta[j].data_e.an=produs[i].data_e.an;
}
void citire_reteta(medicament produs[101],int n,int &m){
    int valid,r,i=0,y=0;
    cout<<endl;
    cout<<" Validati un medicament? Da-1 si Nu-0: ";
    cin>>valid;
    if(valid)
    do{
        cout<<"Introduceti denumirea medicamentului: ";
        cin>>med;
        cautare_prod_nume(produs,n,med);
        cout<<" Se achizitioneaza? Da-1 si Nu-0: ";
        cin>>r;
        cout<<" Introduceti cod: ";
        cin>>y;
        if(r){
            i++;
            adauga_reteta(produs,n,reteta,i,y);
        }
        cout<<endl;
        cout<<" Validati medicament? Da-1, Nu-0: ";
        cin>>valid;
    }while(valid);
    m=i;
    return;
}
void afisare_reteta__pret_reteta(medicament reteta[21], int m){
    cout<<endl;
    float valoare=0,val1=0;
    for(int i=1; i<=m; i++){
        valoare+=reteta[i].pret*reteta[i].buc;
        cout<<reteta[i].cod<<"   "<<reteta[i].nume<<"   ";
        cout<< reteta[i].pret<<" lei "<< reteta[i].buc<<" buc ";
        cout<<reteta[i].pret*reteta[i].buc<<" lei "<<endl;
    }
    cout<<"Valoarea totala a retetei este:  ";
    if(valoare>=50&&valoare<=100){
        val1=valoare-(valoare/100*20);
        cout<<val1<<" lei "<<endl;
    }
    else
        if(valoare>100){
            val1=valoare-(valoare/100*30);
            cout<<val1<<" lei "<<endl;
        }
        else
            cout<<valoare<<" lei "<<endl;
    return;
}
void data_exp(medicament produs[101],int n){
    int zi,luna,an,i,ok=0;
    cout<<"Introduceti data curenta: ";
    cin>>zi>>luna>>an;
    cout<<"Medicamentul urmator este expirat: "<<endl;
    for(i=1;i<=n;i++){
        if(produs[i].data_e.an<an||
           (produs[i].data_e.an==an&&produs[i].data_e.luna<luna)||
           (produs[i].data_e.an==an&&produs[i].data_e.luna==luna&&produs[i].data_e.zi<zi)){
            produs[i].buc=0;
            ok=1;
            cout<<produs[i].cod<<' '<<produs[i].nume<<' ';
            cout<<produs[i].pret<<" lei "<<produs[i].buc<<" buc "<<endl;
        }
    }
    if(ok==0)
        cout<<"Nu exista nici un medicament expirat! "<<endl;
    return;
}
void stoc(medicament produs[101],int n){
    int i,ok=0;
    cout<<"Mai trebuie comandate: "<<endl;
    for(i=1;i<=n;i++)
        if(produs[i].buc<100){
            ok=1;
            cout<<100-produs[i].buc<<" bucati de: ";
            cout<<produs[i].cod<<' '<<produs[i].nume<<endl;
        }
    if(ok==0)
        cout<<"Nu trebuie facut stocul pentru nici un medicament! "<<endl;
    return;
}
int main(){
    citire(produs,n);
    cout<<" Cel mai ieftin produs: ";
    prod_ieftin(produs,n);
    cout<<" Cel mai scump produs: ";
    prod_scump(produs,n);
    cout<<endl;
    data_exp(produs,n);
    int m=0;
    citire_reteta(produs,n,m);
    cout<<endl;
    afisare_reteta__pret_reteta(reteta,m);
    cout<<endl;
    cout<<" Introduceti denumirea: ";
    cin>>med;
    cautare_prod_nume(produs,n,med);
    cout<<endl;
    cout<<" Introduceti pretul: ";
    cin>> x;
    afisare_prod_pret(produs, n,x);
    cout<<endl;
    cout<<endl;
    stoc(produs,n);
    cout<<endl;
    afisare(produs,n);
    fin.close();
    return 0;
}
