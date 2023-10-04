#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct date{
	int jour ;
	int mois ;
	int annee ;
}date;

typedef struct dateheure{
	date DC ;
	int heure ;
	int min ;
}dateheure;

typedef struct operation{
	int N_oper ;
	int montant ;
	dateheure DH ;
	int type_oper ; // 1- virement  2- retrait
}operation;

typedef struct comptbanc{
	int NumCompt ;
	int solde ;
	int N_oper ;
	operation operations[5] ;
}comptbanc;

typedef struct client{
	char Nom[5] ;
	char CIN[5] ;
	int Nbre_Cbanc ;
	comptbanc comptbancs[5] ;
}client;

typedef struct agence {
	char RS[5] ;
	date DC ;
	char adresse[5] ;
	int NClient ;
	client clients[5] ;
}agence;

typedef struct banque {
	char RS[5] ;
	char RC[5] ;
	char patente[5] ;
	date DC ;
	int CA ;
	int N_Ag ;
	agence agences[5] ;
}banque;

typedef struct STR_GB {
	banque banques[100] ;
	int nbeffect ;
}STR_GB;

// question 3
date creedate(){
	date D ;
	printf("Saisir le jour : ");
	scanf("%d",&D.jour);
	printf("Saisir le mois : ");
	scanf("%d",&D.mois);
	printf("Saisir l annee : ");
	scanf("%d",&D.annee);
	return D ;
}
dateheure creedateheure(){
	dateheure DH ;
	printf("Saisir l heure : ");
	scanf("%d",&DH.heure);
	printf("Saisir minute : ");
	scanf("%d",&DH.min);
	DH.DC = creedate() ;
	return DH ;
}
operation creeoperation(){
	operation op ;
	printf("Saisir le numero de l operation : ");
	scanf("%d",&op.N_oper);
	printf("Saisir le montant de l operation : ");
	scanf("%d",&op.montant);
	printf("Saisir la date et heure : ");
	op.DH = creedateheure();
	printf("Saisir le type de l operation : ");
	scanf("%d",&op.type_oper);
	return op ;
}
comptbanc creecomptbanc(){
	comptbanc Cbanc ;
	int i ;
	printf("Saisir le numero de compte : ");
	scanf("%d",&Cbanc.NumCompt);
	printf("Saisir le solde du compte : ");
	scanf("%d",&Cbanc.solde);
	printf("Saisir le nombre d'operation : ");
	scanf("%d",&Cbanc.N_oper);
	for(i=0;i<Cbanc.N_oper;i++){
		Cbanc.operations[i] = creeoperation() ;
	}
	return Cbanc ;
}
client creeclient(){
	client Cl ;
	int i ;
	printf("Saisir le nom complet : ");
	scanf("%s",Cl.Nom);
	printf("Saisir le CIN : ");
	scanf("%s",Cl.CIN);
	printf("Saisir le nombre de compte bancaire : ");
	scanf("%d",&Cl.Nbre_Cbanc);
	for(i=0;i<Cl.Nbre_Cbanc;i++){
		Cl.comptbancs[i] = creecomptbanc();
	}
	return Cl ;
}
agence creeagence(){
	agence Ag ;
	int i ;
	printf("Saisir une raison sociale RS : ");
	scanf("%s",Ag.RS);
	printf("Saisir la date de creation : \n");
	Ag.DC = creedate();
	printf("Saisir l adresse : ");
	scanf("%s",Ag.adresse);
	printf("Saisir le nombre de client : ");
	scanf("%d",&Ag.NClient);
	for(i=0;i<Ag.NClient;i++){
		Ag.clients[i] = creeclient();
	}
	return Ag ;
}
banque creebanque(){
	banque b ;
	int i ;
	printf("Saisir une raison sociale RS : ");
	scanf("%s",b.RS);
	printf("Saisir un registre de commerce : ");
	scanf("%s",b.RC);
	printf("Saisir la patente : ");
	scanf("%s",b.patente);
	printf("Date de creation : \n");
	b.DC = creedate() ;
	printf("Saisir  le chiffre d affaire : ");
	scanf("%d",&b.CA);
	printf("Saisir le nombre d agence bancaire : ");
	scanf("%d",&b.N_Ag);
	for(i=0;i<b.N_Ag;i++){
		b.agences[i] = creeagence();
	}
	return b ;
}

void remplibanque(STR_GB *G , int n){
	int i ;
	for(i=0;i<n;i++){
		G->banques[i] = creebanque() ;
	}
	G->nbeffect = n ;
}

// question 4 
int rechercheRS(STR_GB G , char RS[20]){
	int i ;
	for(i=0;i<G.nbeffect;i++){
		if(strcmp(G.banques[i].RS,RS)==0)
		    return i ;
	}
	return -1 ;
}

void rempliagence(banque *b , int n){
	int i ;
	for(i=0;i<n;i++){
		b->agences[i] = creeagence();
	}
	b->N_Ag = n ;
}
void modifierag(STR_GB *G , char RS[20] , int n){
	int x ;
	x = rechercheRS(*G ,RS);
	if(x!=-1){
		rempliagence(&(G->banques[x]),n);
	}else
	    printf("La banque n existe pas \n");
}

// question 5 
void affichedate(date D){
	printf("La date est : %d/%d/%d\n",D.jour,D.mois,D.annee);
}

void affichedateheure(dateheure DH ){
	affichedate(DH.DC);
	printf("heure : %d minute : %d\n",DH.heure,DH.min);
}

void afficheoperation(operation op){
	printf("Numero d operation : %d | Montant : %d | type d operation : %d \n",op.N_oper,op.montant,op.type_oper);
	affichedateheure(op.DH);
}

void affichecomptbanc(comptbanc Cbanc){
	int i ;
	printf("Numero de compte : %d | Solde du compte : %d | Nombre d operation : %d\n",Cbanc.NumCompt,Cbanc.solde,Cbanc.N_oper);
	for(i=0;i<Cbanc.N_oper;i++){
		afficheoperation(Cbanc.operations[i]);
	}
}

void afficheclient(client Cl){
	int i ;
	printf("Nom complet : %s | CIN : %s | Nombre de compte : %d \n",Cl.Nom,Cl.CIN,Cl.Nbre_Cbanc);
	for(i=0;i<Cl.Nbre_Cbanc;i++){
		affichecomptbanc(Cl.comptbancs[i]);
	}
}

void affichehist(STR_GB G , char CIN[]){
      int i , j , k ;
	 for(i=0;i<G.nbeffect;i++){
	 	for(j=0;j<G.banques[i].N_Ag;j++){
	 		for(k=0;k<G.banques[i].agences[j].NClient;k++){
	 			if(strcmp(G.banques[i].agences[j].clients[k].CIN,CIN)==0)
	 			     afficheclient(G.banques[i].agences[j].clients[k]);
			 }
		 }
	 }	
}

// question 6
void afficheagence(agence Ag){
	int i ;
	printf("La raison sociale RS : %s | adresse : %s | Nombre de client : %d \n",Ag.RS,Ag.adresse,Ag.NClient);
	affichedate(Ag.DC);
	for(i=0;i<Ag.NClient;i++){
		afficheclient(Ag.clients[i]);
	}
}

void affichebanque(banque bq){
	int i ;
	printf("La raison sociale RS : %s | La raison commerciale RC : %s | patente : %s | Chiffre d affaire : %d | Nombre d'agence : %d \n",bq.RS,bq.RC,bq.patente,bq.CA,bq.N_Ag);
	affichedate(bq.DC);
	for(i=0;i<bq.N_Ag;i++){
		afficheagence(bq.agences[i]);
	}
}

void afficheAg(banque b ){
	int i , j , k ;
	for(i=0;i<b.N_Ag;i++){
		for(j=0;j<b.agences[i].NClient;j++){
			for(k=0;k<b.agences[i].clients[j].Nbre_Cbanc;k++){
				if(b.agences[i].clients[j].comptbancs[k].solde>20000)
				    afficheagence(b.agences[i]); 
			}
		}
	}
}

void afficheAgbq(STR_GB G ){
	int i ;
	for(i=0;i<G.nbeffect;i++){
		afficheAg(G.banques[i]);
	}
}

//question 7

void supprimer(STR_GB *G , char RS[]){
	int i , x ;
	x = rechercheRS(*G,RS);
	if(x!=-1){
		for(i=x;i<G->nbeffect-1;i++){
		     G->banques[i] = G->banques[i+1] ;	
		}
		G->nbeffect-- ;
	}else
	   printf("La banque n'existe pas \n");
}

// question 8 

void Exporter(STR_GB G){
	int i , j , k , d , e ;
	FILE* f=NULL ;
	f = fopen("Gestionbancaire.txt","w");
	if(f!=NULL){
		for(i=0;i<G.nbeffect;i++){
			fprintf(f,"%s %s %s | %d/%d/%d | %d %d \n",G.banques[i].RS,G.banques[i].RC,G.banques[i].patente,G.banques[i].DC.jour,G.banques[i].DC.mois,G.banques[i].DC.annee,G.banques[i].CA,G.banques[i].N_Ag);
			for(j=0;j<G.banques[i].N_Ag;j++){
				fprintf(f,"%s | %d/%d/%d | %s %d \n",G.banques[i].agences[j].RS,G.banques[i].agences[j].DC.jour,G.banques[i].agences[j].DC.mois,G.banques[i].agences[j].DC.annee,G.banques[i].agences[j].adresse,G.banques[i].agences[j].NClient);
				for(k=0;k<G.banques[i].agences[j].NClient;k++){
					fprintf(f,"%s %s %d \n",G.banques[i].agences[j].clients[k].Nom,G.banques[i].agences[j].clients[k].CIN,G.banques[i].agences[j].clients[k].Nbre_Cbanc);
					for(d=0;d<G.banques[i].agences[j].clients[k].Nbre_Cbanc;d++){
						fprintf(f,"%d %d %d \n",G.banques[i].agences[j].clients[k].comptbancs[d].NumCompt,G.banques[i].agences[j].clients[k].comptbancs[d].solde,G.banques[i].agences[j].clients[k].comptbancs[d].N_oper);   
						for(e=0;e<G.banques[i].agences[j].clients[k].comptbancs[d].N_oper;e++){
							fprintf(f,"%d %d | %d/%d/%d  %d H : %d Min | %d (1.Virement / 2. Retrait)",G.banques[i].agences[j].clients[k].comptbancs[d].operations[e].N_oper,G.banques[i].agences[j].clients[k].comptbancs[d].operations[e].montant,G.banques[i].agences[j].clients[k].comptbancs[d].operations[e].DH.DC.jour,G.banques[i].agences[j].clients[k].comptbancs[d].operations[e].DH.DC.mois,G.banques[i].agences[j].clients[k].comptbancs[d].operations[e].DH.DC.annee,G.banques[i].agences[j].clients[k].comptbancs[d].operations[e].DH.heure,G.banques[i].agences[j].clients[k].comptbancs[d].operations[e].DH.min,G.banques[i].agences[j].clients[k].comptbancs[d].operations[e].type_oper); 
						}
					}
				}           
			}  
		}
		fclose(f);
	}else
         printf("Le fichier inexistant \n");
}

// question 9 : Importer








// question 10
int menu(){
	int choix ;
  do{
	printf("----------- M E N U ---------\n");
	printf("1- Ajout des banques \n");
	printf("2- modifier liste des agences d une banque \n");
	printf("3- afficher l historique d un client \n");
	printf("4- afficher les agences d une banque dont le solde > 200 000 DHS \n");
	printf("5- Supprimer une banque \n");
	printf("6- Exporter un fichier \n");
	printf("7- Importer un fichier \n");
	printf("8- Quitter le programme \n");
	printf("Saisir un choix entre [1-8] : ");
	scanf("%d",&choix);	
  }while(choix<1 || choix>8);
  
	return choix ;
}


int main(){
	
	STR_GB G ;
	G.nbeffect = 0 ;
	char RS[10] ;
	char CIN[10] ;
     int c  , Nb , NAg  ;
     printf("Hello \n");
    do{
    	
     c = menu();
     switch(c){
     	case 1 : // 1 . ajout des banques
     	        printf("Saisir le nombre de banque : ");
     	        scanf("%d",&Nb);
     	        remplibanque(&G,Nb);
     	        break ;
     	case 2 : // 2 . modifier les listes des agences 
		        printf("Saisir la raison sociale RS a rechercher : ");
		        scanf("%s",RS);
		        printf("Saisir le nombre d agences : ");
		        scanf("%d",&NAg);
		        modifierag(&G,RS,NAg);
		        break ;
		case 3 : // 3 . afficher l historique 
		        printf("Saisir le CIN a rechercher : ") ;
		        scanf("%s",CIN);
		        affichehist(G,CIN);
		        break ;
		case 4 : // 4 . afficher agences dont le solde d un client superieur a 200 000 DHS
		        printf("Les agences dont leur client possede un solde > 200 000 DHS \n")        ;
		        afficheAgbq(G);
		        break ;
		case 5 : // 5 . Supprimer 
		        printf("Saisir la raison sociale a rechercher : ") ;
		        scanf("%s",RS);
		        supprimer(&G,RS);
		        break ;
		case 6 : // 6 . Exporter
		       // Exporter(G);
			   break ;
		case 8 : // 8 . Quitter
		        printf("Fin Programme\n");
			   break ;
		default : printf("Erreur de saisie ! la saisie entre [1-8] \n");
				break ;	   	           
	}
  }while(c!=8);
 
	return 0 ;
}

















