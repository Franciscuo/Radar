/* Fichier en-tête LCD_128x64.h (version 2) 
 
		Créé en 2006 pour le site NumEctron et mis à jour le 15 avril 2009 
		Home: http://nalhossri.free.fr 
		e-mail: nalhossri@free.fr et nabil.al-hossri@u-bordeaux1.fr 
		Copyright ©N. AL HOSSRI IUT GEII Bordeaux 
 
                All rights reserved 
                  Do not modify! 
 */ 
//===================================================================================== 
 
#ifndef LCD_128x64_H 
#define LCD_128x64_H 
 
/************************************************************************************** 
Afficheur LCD (Liquid Crystal Display) graphique (128x64 pixels) 
 
compatible KS0107B/KS0107B 
 
C'est un afficheur graphique dont la résolution d'image est de 128x64 pixels. Il ne  
possède pas de générateur interne de caractères. Pour afficher des textes, on fait donc  
appel à des tables de polices de caractères. 
 
Dans la nouvelle version (version 2) de cette bibliothèque des tables de caractères ont  
été créées : 
 
	Font 3x5       :      type Arial (3x5 points).  
	Font 5x7       :      type Arial (5x7 points) 
	Font 7x7       :      type Courier (7x7 points) 
	Font 10x14   :      type semi-graphique (10x14 points) 
 
Originalités concernant cette nouvelle version : 
 
-	Les fonctions des différents affichages ont été vectorisées : une seule fonction  
  permet d'afficher, à la position du curseur, et avec une police de caractères au choix, 
  un caractère ou un texte, directement dans la RAM du LCD. 
-	Une seule fonction capable de convertir une grandeur physique en virgule flottante et  
  d'afficher directement dans la RAM du LCD le résultat de la conversion. 
-	De même pour la conversion Hexadécimale de base 10 en base comprise entre (2 binaire)  
  et 16 (hexadécimal),  et l'affichage du résultat directement dans la RAM du LCD.   
-	Enfin, de nouvelles fonctions graphiques permettant d'afficher un point, un cadre, …   
 
Les coordonnées (1,1) représentent le point en haut à gauche de l'afficheur (connecteur  
en bas); et les ports de commandes sont positionnés à l'intérieur de la fonction  
init_lcdg d'initialisation du LCD. 
 
**************************************************************************************/ 
/* Définition des broches utilisées */ 
 
//Brochage adopté est sur deux ports (PORTA et PORTB du HC08) : 
 
/* Modifier ce qui est en rouge (qui dépend uniquement du micro utilisé, dans notre  
cas, le HC08) dans les lignes ci-dessous, en fonction de la configuration matérielle  
souhaitée. */ 
 
//bits de données (8 bits côte à côte) du LCD: 
#define PORT_DATA PTED  //PORT_DATA = PTA  
 
//bits de direction (8 bits) des broches de données: 
#define DDR_DATA PTEDD 
 
/* Port de contrôle : */ 
//bits de commande (6 bits) du LCD = utilisation des 6 broches du micro au choix: 
#define LCD_E PTDD_PTDD1 
#define LCD_RW PTDD_PTDD0 
#define LCD_RS PTBD_PTBD5 
#define LCD_CS1 PTBD_PTBD3 
#define LCD_CS2 PTBD_PTBD2 
#define LCD_RST PTBD_PTBD4 
 
//bits de direction (6 bits) des broches de commande (ou contrôle de la configuration  
//du LCD): 
#define DDR_LCD_E PTDDD_PTDDD1  
#define DDR_LCD_RW PTDDD_PTDDD0 
#define DDR_LCD_RS PTBDD_PTBDD5 
#define DDR_LCD_CS1 PTBDD_PTBDD3 
#define DDR_LCD_CS2 PTBDD_PTBDD2 
#define DDR_LCD_RST PTBDD_PTBDD4 
 
/*************************************************************************************/ 
//Définition des constantes et des types: 
 
typedef unsigned char byte; 		//facultatif. 
typedef unsigned int word; 			//facultatif. 
typedef unsigned long dword;    //facultatif. 
 
#define x_max 128			          //abscisse de la dernière colonne en pixels. 
#define y_max 64				        //ordonnée de la dernière ligne en pixels. 
#define yligne_max 8            //hauteur d'une page (8 pixels). 
#define _8pixels_max 1024			  //1024 octets représentant la totalité de l'écran. 
 
struct adresse { 				        //structure gérant la position du curseur. 
	byte x, yligne; 
} add = {1, 1};//les coordonnées du curseur (x, yligne) prennent les valeurs initiales (1,1). 
 
//************************************************************************************* 
/* Constante utile pour la conversion HEXA/ASCII. Elle contient les codes ascii des  
caractères de 0 à F. ex: h[12]=code ascii (0x43) du caractère C. */ 
const byte h[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};  
 
/*************************************************************************************/ 
/* Déclaration des fonctions élaborées */ 
 
/* Fonctions d'initialisation */ 
void ecr_ctrlg(byte ctrl); 
void ecr_datag(byte data); 
void bloc(byte select); 
void busy_lcdg(void); 
void init_lcdg(byte cl); 
void xyligne_lcdg(byte x1, byte yligne1); 
void efface_lcdg(byte cl); 
void onoff_lcdg(byte onoff); 
 
/* Fonctions d'affichage */ 
void aff_carg(byte c, byte larg, byte haut, const byte *fonte, byte cl); 
void aff_txtg(byte *chaine, byte larg,byte haut, const byte *fonte, byte cl); 
 
/* Fonctions semi-graphiques */ 
void trace_image(const byte *data, byte cl); 
void remplir_zone(byte larg, byte haut, byte data); 
void trace_logo(byte larg, byte haut, const byte *data, byte cl); 
 
/* Fonctions de conversion HEXA/ASCII, FLOAT/ASCII,... et d'affichage direct dans la  
RAM du LCD */ 
void aff_baseg(dword hexa, byte base,byte larg,byte haut, const byte *fonte, byte cl); 
void aff_floatg(float data, byte decimal,byte larg ,byte haut, const byte *fonte, byte cl); 
 
/* Fonctions graphiques */ 
byte lire_data(void); 
void trace_pointxy(byte x, byte y, byte cl); 
void trace_cadre(byte x, byte y, byte L, byte H, byte cl); 
void trace_rectangle(byte x, byte y, byte larg, byte haut,byte cl); 
 
/* Temporisation logicielle */ 
void tempo_ms(word temps); 
 
/*************************************************************************************/ 
//Inclusion des : 
 
#include "font3x5.h"			//police de caractères de type Arial 3x5 points. 
#include "font5x7.h"			//police de caractères de type Arial 5x7 points. 
#include "font7x7.h"      //police de caractères de type Courier 7x7 points. 
#include "font10x14.h"		//police semi-graphique 10x14 points. 
#include "GEII.h"         //image complète (128x64 pixels). 
#include "iut.h"          //logo (65x48 pixels). 
 
/************************************************************************************** 
void ecr_ctrlg(byte ctrl) 
 
Envoie l'octet ctrl de contrôle pour modifier la configuration du LCD. 
 
**************************************************************************************/ 
void ecr_ctrlg(byte ctrl) { 
 
	LCD_RW = 0; 
	LCD_RS = 0;             		//envoie un octet de commande. 
	PORT_DATA = ctrl; 		      //ctrl est placé sur le bus. 
	LCD_E = 1; 			            //validation par l'impulsion E. 
	LCD_E = 0; 
	busy_lcdg();          		  //test du busy. 
} 
 
/************************************************************************************** 
void ecr_datag(byte data) 
 
Envoi l'octet data de donnée vers LCD. 
 **************************************************************************************/ 
void ecr_datag(byte data) { 
 
	if (add.yligne <= yligne_max) { 		  //le curseur reste à l'intérieur de l'écran. 
 
		if (add.x > x_max) { 
			add.x = 1; 
			add.yligne++; 
 
			if (add.yligne > yligne_max) 
				add.yligne = 1; 
		} 
		xyligne_lcdg(add.x, add.yligne);  	//réactualise la position du curseur. 
		LCD_RW = 0;                       	//écriture dans la RAM du LCD. 
		LCD_RS = 1; 				                //envoie un octet de donnée. 
		PORT_DATA = data;                	  //data est placé sur le bus. 
		LCD_E = 1;                        	//validation par l'impulsion E. 
		LCD_E = 0; 
		busy_lcdg();          	          	//test du busy. 
		add.x++; 				                    //incrémente l'abscisse locale. 
	} 
} 
 
/************************************************************************************** 
void bloc(byte select) 
 
Sélectionne côté gauche (64x64 pixels) ou côté droit (64x64 pixels) du LCD. 
 
select=1 : côté droit ; select=0 : côté gauche. 
 
**************************************************************************************/ 
void bloc(byte select) { 
 
	switch (select){ 
 
	case 0: 
		LCD_CS1 = 1; 
		LCD_CS2 = 0; 
		break; 
 
	case 1: 
		LCD_CS1 = 0; 
		LCD_CS2 = 1; 
		break; 
 
	default: 
		break; 
	} 
} 
/************************************************************************************** 
void busy_lcdg(void) 
 
Teste (bit Busy) si le LCD est prêt à recevoir un octet de donnée ou un octet de commande. 
 
**************************************************************************************/ 
void busy_lcdg(void){ 
 
	signed char temp; 
	do{ 
		DDR_DATA=0;      			//PORT_DATA en entrée. 
		LCD_RS=0; 
		LCD_RW=1;        			//lecture. 
		LCD_E=1;             			 
		LCD_E=1;              //retard. 
		temp=PORT_DATA;		  	//PORT_DATA dans temp. 
		LCD_E=0;              //validation par l'impulsion E. 
	}while(temp<0);      		//boucle si busy est à un. 
 
	LCD_RW=0; 
	DDR_DATA=0xFF;       		//PORT_DATA en sortie. 
} 
 
/************************************************************************************** 
void init_lcdg(byte cl) 
 
Initialise l'afficheur LCD et les PORTS utilisés. 
 
cl=0: écran à fond blanc; cl=1: écran à fond noir. 
 
**************************************************************************************/ 
void init_lcdg(byte cl){ 
 
	DDR_DATA = 0xFF; 				//PORT_DATA en sortie. 
 
	//initialise les broches de contrôle du LCD en sortie: 
	DDR_LCD_E=1;   
	DDR_LCD_RW=1;  
	DDR_LCD_RS=1;  
	DDR_LCD_CS1=1;  
	DDR_LCD_CS2=1;  
	DDR_LCD_RST=1;  
 
	busy_lcdg();   					//test du busy. 
	LCD_E = 0;	 				    //initialisation de E et RW. 
	LCD_RW = 0; 
	LCD_RST = 0; 					  //reset LCD. 
	LCD_RST = 1; 
	bloc(0); 
	ecr_ctrlg(0xC0); 				//RAM 0 sur le haut de l'afficheur côté gauche. 
	ecr_ctrlg(0x3F); 				//LCD allumé. 
	bloc(1); 
	ecr_ctrlg(0xC0); 				//RAM 0 sur le haut de l'afficheur côté droit. 
	ecr_ctrlg(0x3F); 				//LCD allumé. 
	efface_lcdg(cl);      	//efface l'écran et positionne le curseur au point (1,1). 
} 
 
/************************************************************************************** 
void xyligne_lcdg(byte x1, byte yligne1) 
 
Positionne le curseur aux coordonnées (x1, yligne1) : 1 <= x1 <= 128,   
et 1 <= yligne1 <= 8  (pages). 
 
**************************************************************************************/ 
void xyligne_lcdg(byte x1, byte yligne1) { 
 
	if (x1 <= 64){ 
		bloc(0); 				                  //côté gauche. 
		ecr_ctrlg(0x40 + x1 - 1); 		  	//colonne x1-1. 
		ecr_ctrlg(0xB8 + yligne1 - 1); 		//incrémente page. 
	} 
	else { 
		bloc(1);                        	//côté droit. 
		ecr_ctrlg(0x40 + x1 - 65); 		  	//colonne x1-1-64. 
		ecr_ctrlg(0xB8 + yligne1 - 1); 		//incrémente page. 
	} 
	add.x = x1;                       	//sauvegarde x1. 
	add.yligne = yligne1;             	//sauvegarde yligne1 
} 
 
/************************************************************************************** 
void efface_lcdg(byte cl) 
 
Efface l'écran et positionne le curseur en haut à gauche (1,1). 
 
cl=0: écran à fond blanc ; cl=1: écran à fond noir. 
 
**************************************************************************************/ 
void efface_lcdg(byte cl){ 
 
	word i = 0; 
	xyligne_lcdg(1, 1); 
 
	while (i < _8pixels_max){ 		//efface ou affiche toutes les pages du LCD. 
		if(cl) 
			ecr_datag(0xFF); 
		else 
			ecr_datag(0); 
		i++; 
	} 
	xyligne_lcdg(1, 1);       		//curseur en haut à gauche. 
} 
/************************************************************************************** 
void onoff_lcdg(byte onoff) 
 
Allume ou éteint l'affichage. La RAM n'est pas affectée.  
 
onoff = 1: allumé; onoff = 0: éteint. 
 
**************************************************************************************/ 
void onoff_lcdg(byte onoff) { 
 
	if (onoff == 1) { 
		bloc(0); 
		ecr_ctrlg(0x3F); 	//active l'affichage côté gauche. 
		bloc(1); 
		ecr_ctrlg(0x3F); 	//active l'affichage côté droit. 
	} 
	else { 
		bloc(0); 
		ecr_ctrlg(0x3E); 	//désactive l'affichage côté gauche. 
		bloc(1); 
		ecr_ctrlg(0x3E); 	//désactive l'affichage du côté gauche. 
	} 
} 
 
/************************************************************************************** 
void aff_carg(byte c, byte larg, byte haut, const byte *fonte, byte cl) 
 
Affiche sur le LCD, avec une fonte au choix et à la position du curseur, le caractère (c).  
 
Paramètres 
 
	larg     : largeur de fonte, 
	haut    : hauteur de fonte, 
	*fonte : pointe sur la table des polices de caractères désirée. 
	cl = 1 à fond blanc; cl = 0 à fond noir. 
 
**************************************************************************************/ 
void aff_carg(byte c, byte larg, byte haut, const byte *fonte,byte cl) { 
 
	byte i , j=0 , k; 
	k=(haut/yligne_max);          //passe à la ligne suivante si haut > 8 pixels. 
	if(haut%yligne_max !=0) 
		k+=1; 
 
	if (add.x > x_max-larg) { 		//curseur reste à l'intérieur de l'écran. 
		add.yligne += k; 
		add.x = 1; 
		xyligne_lcdg(add.x, add.yligne); 
	} 
 
	c-=0x20; 				              //la table ascii commence au code 0x20 
	fonte += c*larg*k;    			  //vecteur d'adresse du caractère c. 
 
	while (j < k){ 			//le caractère est à cheval entre deux pages successives. 
 
		for(i=0; i <larg; i++){ 
			if(cl == 1) 
				ecr_datag(*fonte); 
			else 
				ecr_datag(~*fonte); 
 
			fonte++; 
		} 
 
		if(cl == 1) 
			ecr_datag(0x00);	        //espace à fond blanc entre caractères. 
		else 
			ecr_datag(0xFF);	        //espace à fond noir entre caractères 
 
		j++; 
		add.yligne++; 
		add.x = add.x - larg-1 ; 
	} 
 
	xyligne_lcdg(add.x + larg+1, add.yligne - k);	//réactualise la position du curseur. 
} 
 
/************************************************************************************** 
void aff_txtg(byte *chaine, byte larg,byte haut, byte *fonte, byte cl) 
 
Affiche sur le LCD, avec une fonte au choix et à la position du curseur, la chaîne de  
caractères chaine. 
 
Paramètres 
 
o	larg     : largeur de la fonte, 
o	haut    : hauteur de la fonte, 
o	*fonte : pointe sur la table des polices de caractères désirée. 
o	cl = 1 à fond blanc; cl = 0 à fond noir. 
 
Option 
 
 \r : inséré dans la chaine, provoque le retour au début de la ligne suivante. 
  
**************************************************************************************/ 
void aff_txtg(byte *chaine, byte larg, byte haut, const byte *fonte, byte cl ) { 
 
	while (*chaine != 0){ 
 
		if (*chaine == '\r'){ 			//retour au début de la ligne suivante. 
 
			add.yligne++; 
			add.x = 1; 
			xyligne_lcdg(add.x, add.yligne); 
		} 
		else                  			//affiche le caractère suivant. 
			aff_carg(*chaine, larg, haut, fonte, cl); 
 
		chaine++; 
	} 
} 
 
/************************************************************************************** 
void aff_baseg(dword hexa, byte base, byte larg, byte haut, byte *fonte, byte cl) 
 
Convertit hexa de base 10 en base <= 16 et affiche sur le LCD, avec une police de  
caractères au choix et à la position du curseur, le résultat de la conversion. 
 
hexa est type dword (unsigned long, voir typedef plus haut) ce qui permet d'afficher  
des valeurs entières positives allant jusqu'à 4294967295 au maximum.  
 
Paramètres 
 
	base : doit satisfaire: 2 <= base <= 16, 
	larg :   largeur de la fonte,  
	haut : hauteur de la fonte, 
	*fonte : pointe sur la table des polices de caractères désirée. 
	cl = 1 à fond blanc; cl = 0 à fond noir. 
	 
**************************************************************************************/ 
void aff_baseg(dword hexa, byte base, byte larg, byte haut, const byte *fonte, byte cl){

	byte i=0;     		        //compteur.
	static byte buf[32]; 			//buffer de stockage; static car il est appel� de la fonction 
						                //aff_float  juste apr�s.
	/* remplit buf[i] par le code ascii du r�sultat de l'op�ration (hexa%base) 
               (cf constante *h d�clar�e en ent�te) */
	do{
		buf[i]=h[hexa%base];    //conversion Hexa/ASCII de la fin vers le d�but.
		hexa=hexa/base;
		i++;
	}while(hexa>0);   			

	/* affiche le contenu du buffer, de la fin vers le d�but et caract�re par caract�re, 
                directement dans la RAM du LCD. */
	do{
		i--;
		aff_carg(buf[i],larg, haut, fonte, cl);		
	} while(i > 0);
}
/************************************************************************************** 
void aff_floatg(float data, byte decimal, byte larg, byte haut, byte *fonte, byte cl) 
 
Convertit data (type float 32 bits) au format décimal, arrondit le résultat à la  
valeur supérieure, puis l'affiche sur le LCD avec au  maximum six chiffres significatifs.  
L'affichage se fait avec une police de caractères au choix et à la position du curseur. 
 
Paramètres 
 
-	decimal: nombre de chiffres décimaux souhaité après la virgule. Il doit satisfaire :  
-  0 <= decimal <= 6,  decimal=0: n'affiche que la partie entière de data.  
-	larg : largeur de la fonte,  
-	haut : hauteur de la fonte, 
-	*fonte : pointe sur la table des polices de caractères désirée. 
-	cl = 1 à fond blanc; cl = 0 à fond noir. 
	 
**************************************************************************************/ 
void aff_floatg(float data, byte decimal, byte larg, byte haut, const byte *fonte, byte cl){

	byte i;
	dword dec, dec10=10;

	if(data<0){ 			            
		aff_carg('-', larg, haut, fonte, cl); //si data est n�gatif affiche '-'.
		data*=-1;                               //data est rendu positif.
	}

	for(i=0; i< decimal; i++)   	//dec10=10^(decimal+1).
		dec10*=10;
	
	dec=dec10*(data-(dword)data); //partie d�cimale, � (decimal+1) chiffres, est rang� dans dec,
	
	if(dec%10>=5)                 //puis arrondis � la valeur sup�rieure. 
		dec+=10;  

	if(dec>(dec10-1)){            //si Overflow,
		data +=1;                   //ajoute 1 � la partie enti�re, 
		dec=0;                      //et la partie d�cimale est mise � 0.
	}  

	
	aff_baseg(data, 10, larg, haut, fonte, cl);//tronque data et affiche la partie enti�re.

	if(decimal !=0){
		aff_carg('.', larg, haut, fonte, cl);
		dec10/=100;                                 //dec10=10^(decimal-1).
    dec=dec/10;
		while(dec/dec10==0 && decimal>1){           //met les z�ros � gauche de la partie d�cimale.
			aff_carg('0', larg, haut, fonte, cl);
			dec10/=10;
			decimal--;
		}
		aff_baseg(dec, 10, larg, haut, fonte, cl);//affiche le reste de la partie d�cimale.
	}
}
 
/************************************************************************************** 
void aff_image(byte *data, byte cl) 
 
Affiche (data) une image complète (128x64 pixels) ; cl = 1 à fond blanc; cl = 0 à fond  
noir. 
 
**************************************************************************************/ 
void trace_image(const byte *data, byte cl) { 
 
	word i = 0; 
	xyligne_lcdg(1, 1); 
 
	while (i < _8pixels_max){ 		      //écriture de 1024 octets constituant l'image. 
 
		if (cl) 
			ecr_datag(*data); 
		else 
			ecr_datag(~*data); 
		data++; 
		i++; 
	} 
} 
 
/************************************************************************************** 
void remplir_zone(byte larg, byte haut, byte data) 
 
 Remplit une zone, à partir de la position du curseur, par l'octet data. Hauteur (haut)  
 doit être multiple de 8. 
 
Paramètres 
 
-	larg : largeur, 
-	haut : hauteur, 
 
**************************************************************************************/ 
 
void remplir_zone(byte larg, byte haut, byte data) { 
 
	byte i = 0, j = 0; 
 
	while (j < haut / 8){             				//remplit la zone page par page.  
 
		for (i = 0; i < larg; i++) 
			ecr_datag(data); 
 
		j++; 
		add.yligne++; 
		add.x = add.x - larg; 
		xyligne_lcdg(add.x, add.yligne); 
	}; 
} 
 
/************************************************************************************** 
void trace_logo(byte larg, byte haut, const byte *data, byte cl) 
 
Trace, à partir de la position du curseur, un logo data qui doit avoir pour hauteur un  
multiple de 8  pixels. 
 
Paramètres 
 
-	larg : largeur, 
-	haut : hauteur, 
-	*data : logo, 
-	cl = 1 à fond blanc; cl = 0 à fond noir. 
 
**************************************************************************************/ 
void trace_logo(byte larg, byte haut, const byte *data, byte cl) { 
 
	byte i = 0, j = 0; 
 
	while (j < (haut/8)){ 
 
		for (i = 0; i < larg; i++) { 
 
			if (cl == 1) 
				ecr_datag(*data);   		  //inscrit data. 
			else 
				ecr_datag(~*data); 	     	//inscrit le complément de data. 
 
			data++ ; 
		}; 
 
		j++; 
		add.yligne++; 
		add.x = add.x - larg; 
	}; 
} 
 
/************************************************************************************** 
byte lire_data(void) 
 
Retourne la valeur de l'octet affiché à la position du curseur. 
 
**************************************************************************************/ 
byte lire_data(void){ 
 
	char temp; 
	DDR_DATA=0x00;                            	//PORT_DATA en entrée. 
	LCD_RS = 1;                               	//envoie un octet de donnée. 
	LCD_RW = 1;                               	//lecture de la RAM du LCD. 
	LCD_E = 1;    
	temp = PORT_DATA;                         	//l'octet lu est mis dans temp. 
	LCD_E = 0;                                	//validation par l'impulsion E; 
	LCD_RW = 0;                               	//écriture dans la RAM du LCD. 
	DDR_DATA = 0xFF;                          	//PORT_DATA en sortie. 
	return temp;                              	//retourne la valeur de l'octet lu. 
} 
 
/************************************************************************************** 
void trace_pointxy(byte x, byte y, byte cl) 
 
Trace un point de coordonnées (x,y) tel que 1 <= x <= 128 et 1 <= y <= 64. 
 
cl=1: point noir; cl=0: point blanc. 
 
**************************************************************************************/ 
void trace_pointxy(byte x, byte y, byte cl){ 
 
	byte pointxy; 
	xyligne_lcdg(x,((y-1)/8)+1);
	
	
	pointxy = lire_data(); 			//transfert de l'octet lu vers pointxy. 
	pointxy = lire_data(); 			//validation au deuxième transfert. 
 
	if(cl==1) 
		pointxy = 1<<(y-1)%8; 
	else 
		pointxy = ~(1<<(y-1)%8); 
 
	ecr_datag(pointxy); 
 
} 
 
/************************************************************************************** 
void trace_cadre(byte x, byte y, byte L, byte H, byte cl) 
 
Trace ou efface un cadre. 
 
Paramètres 
 
-  (x, y) : coordonnées du point haut gauche du cadre, 
-  larg : largeur, 
-  haut : hauteur, 
-  cl=1 : cadre noir; cl=0 : cadre blanc. 
 
**************************************************************************************/ 
void trace_cadre(byte x, byte y, byte larg, byte haut, byte cl){ 
 
	byte j; 
 
	for (j = 0; j < haut; j++){ 
		trace_pointxy(x, y + j, cl); 			      //trace le côté vertical gauche. 
		trace_pointxy(x + larg - 1, y + j, cl); //trace le côté vertical droit. 
	} 
 
	for (j = 0; j < larg; j++){ 
		trace_pointxy(x + j, y, cl); 			      //trace le côté horizontal haut. 
		trace_pointxy(x + j, y + haut - 1, cl);	//trace côte horizontal bas. 
	} 
} 
 
/************************************************************************************** 
void trace_rectangle(byte x, byte y, byte larg, byte haut,byte cl) 
 
Trace ou efface un rectangle plein. 
 
Paramètres 
 
-  (x, y) : coordonnées du point haut gauche du rectangle, 
-  larg : largeur, 
-  haut : hauteur, 
-  cl=1 : affiche; cl=0 : efface. 
  
**************************************************************************************/ 
void trace_rectangle(byte x, byte y, byte larg, byte haut,byte cl){ 
 
	byte i, j; 
	for (i=0;i< haut;i++){ 
		for (j = 0; j < larg; j++) 
			trace_pointxy(x+i, y+j,cl); 
	} 
} 
 
/************************************************************************************** 
void tempo_ms(word temps) 
 
Temporisation logicielle approximative avec un pas de #1ms. 
  
**************************************************************************************/ 
void tempo_ms(word temps) { 
 
	word j = 0, i = 0; 
 
	for (j = 0; j < temps; j++)			//répète temps x 1ms. 
		for (i = 0; i < 90; i++); 		//un pas de #1ms pour un quartz de #10MHz. 
} 
 
/*************************************************************************************/ 
 
#endif 
 
/**************************************  FIN  *****************************************/
