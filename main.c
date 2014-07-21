/* Bibliotheque */ 
#include<stdio.h> 
#include<dos.h> 
#include<string.h> 
#include<stdlib.h> 

/** 
 * Structure récupérant la Trame RMC 
 **/ 
struct varRmc { 
	char h[3],min[3],sec[3]; 				// Variables qui stockeront l'heure, les minutes, et les secondes 
	char j[3],moi[3],an[3]; 				// Variables qui stockeront les jours, les mois et les années 
	char test;								// Variable qui stockera la valeur de la validité de la trame 
	char degLo[5],minLo[7],Lo;				// Variables qui stockerons les degrés, minutes de la longitude 
	char degLa[4],minLa[7],La;				// Variables qui stockerons les degrés, minutes de la lattitude 
}; 

/**
 * Structure récupérant la Trame GGA 
 **/ 
struct varGga { 
	char sat[3];						// Variable qui stockera le nombre de satelites, a proximite 
	char alt[6];						// Variable qui stockera l'altitude du la puce gps 
}; 

/**
 * Structure récupérant la Trame VTG 
 **/ 
struct varVtg { 
	char vit[6];						// Variable qui stockera la vitesse 
}; 

/**
 * Affichage des trames 
 **/ 
void aff(struct varRmc rmc,struct varGga gga, struct varVtg vtg) { 
	int i; 

	system("cls");						// Efface l'affichage du terminal 
	//printf("%c",201);for(i=0;i<70;i++)printf("%c",205);printf("%c\n",187); // Ouverture du joli affichage 
	printf("%c\tLe %s/%s/20%s a, ",186,rmc.j,rmc.moi,rmc.an); 
	printf("%s heure(s) %s minute(s) et %s seconde(s)\t%c\n",rmc.h,rmc.min,rmc.sec,186); 
	printf("%c\tNous obtenons les coordonnees suivantes :\t\t\t%c\n",186,186); 
	printf("%c\tLongitude %s deg %s min %c\t\t\t\t\t%c\n",186,rmc.degLo,rmc.minLo,rmc.Lo,186); 
	printf("%c\tLatitude %s deg %s min %c\t\t\t\t\t%c\n",186,rmc.degLa,rmc.minLa,rmc.La,186); 
	printf("%c\tLa vitesse : %s km/h\t\t\t\t\t\t%c\n",186,vtg.vit,186); 
	printf("%c\tIl y a %s satellite(s)\t\t\t\t\t\t%c\n",186,gga.sat,186); 
	printf("%c\tVous etes situez a %s metres\t\t\t\t\t%c\n",186,gga.alt,186); 
	//printf("%c",200);for(i=0;i<70;i++)printf("%c",205);printf("%c",188); // Fermeture du joli affichage 
	printf("\n\n\t\tAPPUYER SUR UNE TOUCHE POUR SORTIR"); 
} 

/**
 * Décodage de la trame RMC 
 **/ 
void foncRmc(char *cara, struct varRmc * rmc) { 
	int i,j=1; 
	char * var; 						// Variable qui stockera une chaine de caractère 
	 
	var = strtok(cara,","); 			// On récupère dans la variable var le contenu de la trame cara qu'il y a entre deux (virgule) 

	while(var!= NULL) {					// Tant que le contenu de la variable var n'est pas NULL 
		if(j==2){						// Enregistrement de l'HEURE dans les variables 
			for(i=0;i<2;i++) { 
				rmc->h[i]=var[i]; 
				rmc->min[i]=var[i+2]; 
				rmc->sec[i]=var[i+4]; 
			} 
			rmc->h[2]=rmc->min[2]=rmc->sec[2]='\0'; 
		} 
		if(j==3) {}					// Alerte du logiciel de navigation 
		if(j==4) {					// Récupération de la Latitude 
			int k=0; 
			rmc->degLa[0]=var[0]; 
			rmc->degLa[1]=var[1]; 
			for(i=2;i<8;i++) { 
				rmc->minLa[k]=var[i]; 
				k++; 
			} 
			rmc->degLa[2]='\0'; 
			rmc->minLa[6]='\0'; 
		} 
		if(j==5) {					// Récupération de la lettre 
			rmc->La=var[0]; 
		} 
		if(j==6) {					// Récupération de la Longitude 
		int k=0; 
			rmc->degLo[0]=var[0]; 
			rmc->degLo[1]=var[1]; 
			rmc->degLo[2]=var[2]; 
			for(i=3;i<9;i++) { 
				rmc->minLo[k]=var[i]; 
				k++; 
			} 
			rmc->degLo[3]=rmc->minLo[6]='\0'; 
		} 
		if(j==7) {					// Récupération de la lettre 
			rmc->Lo=var[0]; 
		} 
		if(j==8) {}					// Vit 
		if(j==9) {}					// CAP 
		if(j==10) {					// Récupération de la Date 
			for(i=0;i<2;i++) { 
				rmc->j[i]=var[i]; 
				rmc->moi[i]=var[i+2]; 
				rmc->an[i]=var[i+4]; 
			} 
			rmc->j[2]=rmc->moi[2]=rmc->an[2]='\0'; 
		} 
		j++;						// Incrémentation de "j" qui permet de savoir ou on est 

		var = strtok(NULL,","); 	// On récupère a nouveau dans la variable var le contenu de la trame cara qu'il y a entre deux (virgule) 
	} 
} 

/**
 * Décodage de la Tram GGA 
 **/ 
void foncGga(char *cara, struct varGga * gga) { 
	int i,j=1; 
	char * var; 

	var = strtok(cara,",");			// On récupère dans la variable var le contenu de la trame cara qu'il y a entre deux virgules 

	while(var!= NULL) { 
		if(j==8) {					// Récupération du nombre de satellite 
			gga->sat[0]=var[0]; 
			gga->sat[1]=var[1]; 
			gga->sat[2]='\0'; 
		} 
		if(j==10) {					// Récupération de l'altitude 
			for(i=0;i<5;i++) 
				gga->alt[i]=var[i]; 
			gga->alt[5]='\0'; 
		} 
		j++;						// Incrémentation de "j" qui permet de savoir ou on est 
		var = strtok(NULL,",");		// On récupère a nouveau dans la variable var le contenu de la trame cara qu'il y a entre deux (virgule) 
	} 
} 

/**
 * Décodage de la Tram VTG 
 **/ 
void foncVtg(char *cara, struct varVtg * vtg) {
	int i,j=1,temp; 
	char * var; 
	 
	var = strtok(cara,",");				// On récupère dans la variable var le contenu de la trame cara qu'il y a entre deux (virgule) 

	while(var!= NULL) { 
		if(j==7) {						// Récupération de la vitesse en Km/h 
			temp=sizeof(var);			// Récupère la taille du tableau var 
			for(i=0;i<temp+1;i++) 
				vtg->vit[i]=var[i]; 
			vtg->vit[temp+2]='\0'; 
		} 
		j++;							// Incrémentation de "j" qui permet de savoir ou on est 
		var = strtok(NULL,",");			// On récupère à nouveau dans la variable var le contenu de la trame cara qu'il y a entre deux (virgule) 
	}
} 

/**
 * Choix de la Trame a décoder 
 **/ 
void decodage(char *cara, struct varRmc * rmc, struct varGga * gga, struct varVtg * vtg) {
	if(cara[1]=='R')					// Si c'est une trame RMC alors on lance la fonction : foncRmc 
		if(cara[2]=='M') 
			if(cara[3]=='C') 
				foncRmc(cara,rmc); 

	if(cara[1]=='G')					// Si c'est une trame GGA alors on lance la fonction : foncGga 
		if(cara[2]=='G') 
			if(cara[3]=='A') 
				foncGga(cara,gga); 

	if(cara[1]=='V')					// Si c'est une trame VTG alors on lance la fonction : foncVtg 
		if(cara[2]=='T') 
			if(cara[3]=='G') 
				foncVtg(cara,vtg); 
} 

/**
 * Lecture de chaque bit 
 **/ 
char lireBit(int adr,int numBit) { 
	return ((inportb(adr) >> numBit) & 0x01); 
} 

/**
 * Initialisation du port série 
 **/ 
void init() { 
	outportb(0x3FB,0x80);				// Passage du DLAB a 0 
	outportb(0x3F8,0x18);				// Initialisation du registre DLL 
	outportb(0x3F9,0x0);				// Initialisation du registre DLM 
	outportb(0x3fB,0x3);				// Passage du DLAB a 1 et initialisation du reste 
} 

/**
 * Fonction principal 
 **/ 
int main (void) { 
	int i=0,deb=0,fin=0,var; 
	char ent; 
	char cara[100];						// Déclaration de la chaine de caractère cara a 100 caractere 
	struct varRmc rmc;					// Déclaration de la structure RMC 
	struct varGga gga;					// Déclaration de la structure GGA 
	struct varVtg vtg;					// Déclaration de la structure VTG 
	init();								// Appel de la fonction init 

	do { 
		if(lireBit(0x3FD,0)==1)	{		// Appel de la fonction lireBit si elle retourne "1" cela signifie qu'un caractère est en attente de lecture 
			var=inportb(0x3F8);			// On récupère le caractère envoyé par le GPS 

			if(var=='$' && deb==0)		// Si on trouve le caractère $ on passe la variable deb a 1 
				deb=1;					// Si le caractère précèdent est $ (soit) deb egale a 1 et si le caractère récupère est G alors on passe la variable deb a 2 
			if(var=='G' && deb==1) 
				deb=2; 
			if(var=='P' && deb==2)		// Si le caractère précèdent est G (soit) deb égale a 2 et si le caractère récupère est G alors on passe la variable deb a 3 
				deb=3; 
			if(deb==3) {				// Si le caractère précèdent est P (soit) deb égale a 3 on fait :
				cara[i]=var;			// On stock le caractère récupère dans le tableau cara 
				i++;					// On incrémente i 
			} 
			if(var==0xd && fin==0) 
				fin=1; 
			if(var==0xd && fin==1) 
				fin=2; 
			if(var==0xa && fin==2) 
				fin=3;
			if(fin==3) {
				cara[i+1]='\0';					// On marque la fin de chaine avec \0
				decodage(cara,&rmc,&gga,&vtg);	// Appel de la fonction décodage
				aff(rmc,gga,vtg);				// Appel de la fonction affichage
				deb=0 ;							// Initialisation de la variable deb a 0
				fin=0;							// Initialisation de la variable fin a 0
                i=0;							// Initialisation de la variable i a 0
			}
		}
	} while(!kbhit());							// Tant qu'aucune touche n'a été appuyée on retourne dans la boucle
	return 0;
}