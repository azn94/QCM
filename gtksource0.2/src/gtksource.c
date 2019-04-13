#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <unistd.h>
#include <gmodule.h>
#include <string.h>

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlreader.h>
#include <libxml/xmlmemory.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/xmlwriter.h>

#define NBR_LVL 3
#define NBR_LVL_F 3
#define NBR_LVL_M 4
#define L_FENETRE 700
#define H_FENETRE 450
#define NBR_PAYS 193


typedef struct {
  GtkWidget *wid;
  char *yes;
  char *nom_utilisateur;
  char *nom_mauvaise;
  int nbr_matrice;

} stru;
//ab
typedef struct {
  int nombre;
  char *nom;

} nom_nombre;

typedef struct {
	GtkWidget *wid;
  char *nom1;
  char *nom2;
} nom_nom_nombre;


void bonne_reponse(GtkWidget *widget, gpointer haribo) {
	GtkWidget *dialog;
	stru *london=malloc(sizeof(*london));
	london=haribo;

	g_printf("\n---------\nbonne réponse l'adresse à remplir est : %s/%s/%s\n---------\n",london->nom_utilisateur,london->yes,london->yes);
	xmlInitParser();
	LIBXML_TEST_VERSION
	char nom_fichier[500],adresse[500];
	g_snprintf(adresse,500,"/%s/matrice/%s/%s",london->nom_utilisateur,london->yes,london->yes);
	g_snprintf(nom_fichier,500,"%s.xml",london->nom_utilisateur);

	xmlDoc *doc = xmlParseFile(nom_fichier);
	xmlXPathContext *xpathCtx = xmlXPathNewContext( doc );
	xmlXPathObject * xpathObj =xmlXPathEvalExpression( (xmlChar*)adresse, xpathCtx );
	int nbr_matrice= xmlXPathNodeSetGetLength(xpathObj->nodesetval);
	xmlNode *node = xpathObj->nodesetval->nodeTab[nbr_matrice-1];
	xmlNodeSetContent(node, "1");
	xmlSaveFormatFileEnc( nom_fichier, doc, "utf-8", 1 );
	xmlXPathFreeObject( xpathObj );
	xmlXPathFreeContext( xpathCtx );
	xmlFreeDoc(doc);
	xmlCleanupParser();

   dialog = gtk_message_dialog_new(GTK_WINDOW(london->wid),GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_QUESTION,GTK_BUTTONS_OK,"Bonne réponse");
   gtk_dialog_run(GTK_DIALOG(dialog));
   gtk_widget_destroy(dialog);

   free(haribo);

}

void mauvaise_reponse(GtkWidget *widget, gpointer haribo) {
  GtkWidget *dialog;
  stru *london=malloc(sizeof(*london));
  london=haribo;

  g_printf("\n---------\nbonne réponse l'adresse à remplir est : %s/%s/%s\n---------\n",london->nom_utilisateur,london->yes,london->nom_mauvaise);
  xmlInitParser();
  LIBXML_TEST_VERSION

  char nom_fichier[500],adresse[500];
  g_snprintf(adresse,500,"/%s/matrice/%s/%s",london->nom_utilisateur,london->yes,london->nom_mauvaise);
  g_snprintf(nom_fichier,500,"%s.xml",london->nom_utilisateur);

  xmlDoc *doc = xmlParseFile(nom_fichier);
  xmlXPathContext *xpathCtx = xmlXPathNewContext( doc );
  xmlXPathObject * xpathObj =xmlXPathEvalExpression( (xmlChar*)adresse, xpathCtx );
  int nbr_matrice= xmlXPathNodeSetGetLength(xpathObj->nodesetval);
  xmlNode *node = xpathObj->nodesetval->nodeTab[nbr_matrice-1];
  xmlNodeSetContent(node, "1");
  xmlSaveFormatFileEnc( nom_fichier, doc, "utf-8", 1 );
  xmlXPathFreeObject( xpathObj );
  xmlXPathFreeContext( xpathCtx );
  xmlFreeDoc( doc );
  xmlCleanupParser();

  char Madrid[500];
  g_snprintf(Madrid,500,"mauvaise réponse, c'était : '%s'",london->yes);
  dialog = gtk_message_dialog_new(GTK_WINDOW(london->wid),GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_QUESTION,GTK_BUTTONS_OK, Madrid);
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
  free(haribo);
}
void Fin_du_jeu(GtkWidget *widget, gpointer window) {
	GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(window),GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_QUESTION,GTK_BUTTONS_OK,"\n\n\n\n\t\tFIN DU JEU\t\t\n\n\n\n");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

const  char* NomPaysAleatoire (){
	FILE *f=fopen("listepays.txt","r");
	if(f==NULL){
		fprintf(stderr,"problème d'ouverture du fichier listepays \n ");
		return NULL;
	}
	static char buffer[500];
	static char buffer2[500];
	int i=rand()%NBR_PAYS;

	int j=0;
	while(fgets(buffer,500,f)&& j<i){
		j++;
	}
	sscanf(buffer,"%s",&buffer2);
	printf("l'aleatoire donne : num %d -> %s\n",i,buffer2);
	fclose(f);
	return buffer2;
}

const  char* NomPaysAleatoire2 (){
	FILE *f=fopen("listepays.txt","r");
	if(f==NULL){
		fprintf(stderr,"problème d'ouverture du fichier listepays \n ");
		return NULL;
	}
	static char buffer[500];
	static char buffer2[500];
	int i=rand()%NBR_PAYS;
	printf("l'aleatoire2 donne :%d\n",i);
	int j=0;
	while(fgets(buffer,500,f)&& j<i){
		j++;
	}
	sscanf(buffer,"%s",&buffer2);
	fclose(f);
	return buffer2;
}
const  char* NomPaysAleatoireEurope (){
	FILE *f=fopen("listepaysEurope.txt","r");
	if(f==NULL){
		fprintf(stderr,"probleme d'ouverture\n ");
		return NULL;}
	static char buffer[100];
	//static char buffer2[100];
	int i=rand()%1;
	int j=0;
	if(fgets(buffer,100,f)==NULL)
				return NULL;
	while(fgets(buffer,sizeof(buffer),f)&& j<i){
		j++;
	}
	sscanf(buffer, "%s", &buffer);
	fclose(f);
	return buffer;
}


const  char* getPays (int r){
	FILE *f=fopen("listepays.txt","r");
	if(f==NULL){
		fprintf(stderr,"problème d'ouverture du fichier listepays \n ");
		return NULL;
	}
	static char buffer[100];
	static char buffer2[100];
	int i=r;
	int j=0;
	if(fgets(buffer,100,f)==NULL)
			return NULL;
	while(fgets(buffer,100,f)&& j<i){
		j++;
	}
	sscanf(buffer,"%s",&buffer2);
	fclose(f);
	return buffer2;
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

void fonction_facile(GtkWidget *table99, gpointer user_data){
	GtkWidget *button,*window,*table;
	GtkWidget *button2,*button3;

	int i=rand()%3,k;
	char buffer[500]="";
	char s0[500],s1[500],s2[500];
	char *tab_button[3]={strcpy(s0,NomPaysAleatoire()),strcpy(s1,NomPaysAleatoire()),strcpy(s2,NomPaysAleatoire())};
	g_snprintf(buffer,500,"drapeau/%s.png",tab_button[0]);

	g_printf("\nfonction facile tableau de bouton :%s-%s-%s\n",tab_button[0],tab_button[1],tab_button[2]);

	table = gtk_table_new (6, 3, TRUE);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "QCM drapeau-facile");
	gtk_window_set_default_size (GTK_WINDOW (window), L_FENETRE, H_FENETRE);
	gtk_container_set_border_width (GTK_CONTAINER (window), 100);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);

	gtk_table_set_col_spacings(GTK_TABLE(table), 20);
	gtk_container_add (GTK_CONTAINER (window), table);

	button = gtk_image_new_from_file(buffer);
	gtk_table_attach_defaults (GTK_TABLE (table), button, 0, 3, 0, 3);

	nom_nombre *london=malloc(sizeof(*london));
	london->nom=malloc(sizeof(char*)*100);
	london=user_data;
	london->nombre++;
	int nbr_niveau_restant=london->nombre;


	stru *haribo=malloc(sizeof(*haribo));
	haribo->yes=malloc(sizeof(char*)*100);
	haribo->nom_utilisateur=malloc(sizeof(char*)*100);
	haribo->nom_mauvaise=malloc(sizeof(char*)*100);
	strcpy(haribo->yes,tab_button[0]);
	strcpy(haribo->nom_utilisateur,london->nom);
	haribo->wid=window;

	stru *haribo2=malloc(sizeof(*haribo2));
	haribo2->yes=malloc(sizeof(char*)*100);
	haribo2->nom_utilisateur=malloc(sizeof(char*)*100);
	haribo2->nom_mauvaise=malloc(sizeof(char*)*100);
	strcpy(haribo2->yes,tab_button[0]);
	strcpy(haribo2->nom_utilisateur,london->nom);
	haribo2->wid=window;

	stru *haribo3=malloc(sizeof(*haribo3));
	haribo3->yes=malloc(sizeof(char*)*100);
	haribo3->nom_utilisateur=malloc(sizeof(char*)*100);
	haribo3->nom_mauvaise=malloc(sizeof(char*)*100);
	strcpy(haribo3->yes,tab_button[0]);
	strcpy(haribo3->nom_utilisateur,london->nom);
	haribo3->wid=window;

//-------------------------------------------------------------------------------------------------------
	while(tab_button[i]==0){
		i=rand()%3;
	}
	button = gtk_button_new_with_label(tab_button[i]);

	gtk_table_attach_defaults (GTK_TABLE (table), button, 0,0+1, 4, 5);
	if(i==0){
		g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  haribo);
	}else{
		strcpy(haribo->nom_mauvaise,tab_button[i]);
		g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse),  haribo);
		}
	tab_button[i]=0;
	if (nbr_niveau_restant<NBR_LVL_F)
		g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( fonction_facile), london);
	else{
		g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( Fin_du_jeu), window);
		london->nombre=0;
			}
	g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window);
//-------------------------------------------------------------------------------------------------------
	while(tab_button[i]==0){
			i=rand()%3;
		}
	button = gtk_button_new_with_label(tab_button[i]);

	gtk_table_attach_defaults (GTK_TABLE (table), button, 1,1+1, 4, 5);
	if(i==0){
		g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  haribo2);
	}else{
		strcpy(haribo2->nom_mauvaise,tab_button[i]);
		g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse),  haribo2);
		}
	tab_button[i]=0;
	if (nbr_niveau_restant<NBR_LVL_F)
		g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( fonction_facile), london);
	else{
		g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( Fin_du_jeu), window);
		london->nombre=0;
		}
	g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window);
//-------------------------------------------------------------------------------------------------------
	while(tab_button[i]==0){
			i=rand()%3;
		}
	button = gtk_button_new_with_label(tab_button[i]);

		gtk_table_attach_defaults (GTK_TABLE (table), button, 2,2+1, 4, 5);
			if(i==0){
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  haribo3);
			}else{
			strcpy(haribo3->nom_mauvaise,tab_button[i]);
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse),  haribo3);
				}
		tab_button[i]=0;
		if (nbr_niveau_restant<NBR_LVL_F)
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( fonction_facile), london);
		else{
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( Fin_du_jeu), window);
			london->nombre=0;
				}
		g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window);

	gtk_widget_show_all(GTK_WIDGET(window));
	}

void fonction_moyen2(GtkWidget *table99,gpointer user_data){
	GtkWidget *window,*table;
	GtkWidget *button,*button2,*button3,*button4,*button5,*button6;
	int i=rand()%6,k,l;
	char buffer[500]="";
	char s0[500],s1[500],s2[500],s3[500],s4[500],s5[500];
	char *tab_button[6]={strcpy(s0,NomPaysAleatoire()),strcpy(s1,NomPaysAleatoire()),strcpy(s2,NomPaysAleatoire()),strcpy(s3,NomPaysAleatoire()),strcpy(s4,NomPaysAleatoire()),strcpy(s5,NomPaysAleatoire())};
	g_snprintf(buffer,500,"drapeau/%s.png",tab_button[0]);

	g_printf("\nfonction facile tableau de bouton :%s  %s  %s  %s  %s  %s\n",tab_button[0],tab_button[1],tab_button[2],tab_button[3],tab_button[4],tab_button[5]);

	table = gtk_table_new (6, 3, TRUE);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "QCM drapeau-medium");
	gtk_window_set_default_size (GTK_WINDOW (window), L_FENETRE, H_FENETRE);
	gtk_container_set_border_width (GTK_CONTAINER (window), 100);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);

	gtk_table_set_col_spacings(GTK_TABLE(table), 20);
	gtk_table_set_row_spacings(GTK_TABLE(table), 20);
	gtk_container_add (GTK_CONTAINER (window), table);


	button = gtk_image_new_from_file(buffer);
	gtk_table_attach_defaults (GTK_TABLE (table), button, 0, 3, 0, 3);

	nom_nombre *london=malloc(sizeof(*london));
	london->nom=malloc(sizeof(char*)*100);
	london=user_data;
	london->nombre++;
	int nbr_niveau_restant=london->nombre;

	stru *haribo=malloc(sizeof(*haribo));
	haribo->yes=malloc(sizeof(char*)*100);
	haribo->nom_utilisateur=malloc(sizeof(char*)*100);
	haribo->nom_mauvaise=malloc(sizeof(char*)*100);
	strcpy(haribo->yes,tab_button[0]);
	strcpy(haribo->nom_utilisateur,london->nom);
	haribo->wid=window;

	stru *haribo2=malloc(sizeof(*haribo2));
	haribo2->yes=malloc(sizeof(char*)*100);
	haribo2->nom_utilisateur=malloc(sizeof(char*)*100);
	haribo2->nom_mauvaise=malloc(sizeof(char*)*100);
	strcpy(haribo2->yes,tab_button[0]);
	strcpy(haribo2->nom_utilisateur,london->nom);
	haribo2->wid=window;

	stru *haribo3=malloc(sizeof(*haribo3));
	haribo3->yes=malloc(sizeof(char*)*100);
	haribo3->nom_utilisateur=malloc(sizeof(char*)*100);
	haribo3->nom_mauvaise=malloc(sizeof(char*)*100);
	strcpy(haribo3->yes,tab_button[0]);
	strcpy(haribo3->nom_utilisateur,london->nom);
	haribo3->wid=window;

	stru *haribo4=malloc(sizeof(*haribo4));
	haribo4->yes=malloc(sizeof(char*)*100);
	haribo4->nom_utilisateur=malloc(sizeof(char*)*100);
	haribo4->nom_mauvaise=malloc(sizeof(char*)*100);
	strcpy(haribo4->yes,tab_button[0]);
	strcpy(haribo4->nom_utilisateur,london->nom);
	haribo4->wid=window;

	stru *haribo5=malloc(sizeof(*haribo5));
	haribo5->yes=malloc(sizeof(char*)*100);
	haribo5->nom_utilisateur=malloc(sizeof(char*)*100);
	haribo5->nom_mauvaise=malloc(sizeof(char*)*100);
	strcpy(haribo5->yes,tab_button[0]);
	strcpy(haribo5->nom_utilisateur,london->nom);
	haribo5->wid=window;

	stru *haribo6=malloc(sizeof(*haribo6));
	haribo6->yes=malloc(sizeof(char*)*100);
	haribo6->nom_utilisateur=malloc(sizeof(char*)*100);
	haribo6->nom_mauvaise=malloc(sizeof(char*)*100);
	strcpy(haribo6->yes,tab_button[0]);
	strcpy(haribo6->nom_utilisateur,london->nom);
	haribo6->wid=window;


	//-------------------------------------------------------------------------------------------------------
		while(tab_button[i]==0){
			i=rand()%6;
		}
		button = gtk_button_new_with_label(tab_button[i]);

		gtk_table_attach_defaults (GTK_TABLE (table), button, 0,0+1, 4, 5);
		if(i==0){
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  haribo);
		}else{
			strcpy(haribo->nom_mauvaise,tab_button[i]);
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse),  haribo);
			}
		tab_button[i]=0;
		if (nbr_niveau_restant<NBR_LVL_M)
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( fonction_moyen2), london);
		else{
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( Fin_du_jeu), window);
			london->nombre=0;
				}
		g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window);
	//-------------------------------------------------------------------------------------------------------
		while(tab_button[i]==0){
				i=rand()%6;
			}
		button = gtk_button_new_with_label(tab_button[i]);

		gtk_table_attach_defaults (GTK_TABLE (table), button, 1,1+1, 4, 5);
		if(i==0){
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  haribo2);
		}else{
			strcpy(haribo2->nom_mauvaise,tab_button[i]);
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse),  haribo2);
			}
		tab_button[i]=0;
		if (nbr_niveau_restant<NBR_LVL_M)
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( fonction_moyen2), london);
		else{
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( Fin_du_jeu), window);
			london->nombre=0;
			}
		g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window);
	//-------------------------------------------------------------------------------------------------------
		while(tab_button[i]==0){
				i=rand()%6;
			}
		button = gtk_button_new_with_label(tab_button[i]);

			gtk_table_attach_defaults (GTK_TABLE (table), button, 2,2+1, 4, 5);
				if(i==0){
					g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  haribo3);
				}else{
				strcpy(haribo3->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse),  haribo3);
					}
			tab_button[i]=0;
			if (nbr_niveau_restant<NBR_LVL_M)
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( fonction_moyen2), london);
			else{
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( Fin_du_jeu), window);
				london->nombre=0;
					}
			g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window);

			//-------------------------------------------------------------------------------------------------------
				while(tab_button[i]==0){
					i=rand()%6;
				}
				button = gtk_button_new_with_label(tab_button[i]);

				gtk_table_attach_defaults (GTK_TABLE (table), button, 0,0+1, 5, 6);
				if(i==0){
					g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  haribo4);
				}else{
					strcpy(haribo4->nom_mauvaise,tab_button[i]);
					g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse),  haribo4);
					}
				tab_button[i]=0;
				if (nbr_niveau_restant<NBR_LVL_M)
					g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( fonction_moyen2), london);
				else{
					g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( Fin_du_jeu), window);
					london->nombre=0;
						}
				g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window);
			//-------------------------------------------------------------------------------------------------------
				while(tab_button[i]==0){
						i=rand()%6;
					}
				button = gtk_button_new_with_label(tab_button[i]);

				gtk_table_attach_defaults (GTK_TABLE (table), button, 1,1+1, 5, 6);
				if(i==0){
					g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  haribo5);
				}else{
					strcpy(haribo5->nom_mauvaise,tab_button[i]);
					g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse),  haribo5);
					}
				tab_button[i]=0;
				if (nbr_niveau_restant<NBR_LVL_M)
					g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( fonction_moyen2), london);
				else{
					g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( Fin_du_jeu), window);
					london->nombre=0;
					}
				g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window);
			//-------------------------------------------------------------------------------------------------------
				while(tab_button[i]==0){
						i=rand()%6;
					}
				button = gtk_button_new_with_label(tab_button[i]);

					gtk_table_attach_defaults (GTK_TABLE (table), button, 2,2+1, 5, 6);
						if(i==0){
							g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  haribo6);
						}else{
						strcpy(haribo6->nom_mauvaise,tab_button[i]);
						g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse),  haribo6);
							}
					tab_button[i]=0;
					if (nbr_niveau_restant<NBR_LVL_M)
						g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( fonction_moyen2), london);
					else{
						g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( Fin_du_jeu), window);
						london->nombre=0;
							}
					g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window);










/*

	for(k=0;k<3;k++){
		while(tab_button[i]==0){
				i=rand()%6;}
			button = gtk_button_new_with_label (tab_button[i]);
				gtk_table_attach_defaults (GTK_TABLE (table), button, k,k+1, 4, 5);
				if(i==0){
					g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  window);
				}else{
					g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse),  haribo);}
				tab_button[i]=0;
				if (user_data>0)
					g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( fonction_moyen2), aaa);
				else g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( Fin_du_jeu), window);

				g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window);
		}
	for(k=0;k<3;k++){
		while(tab_button[i]==0){
				i=rand()%6;}
			button = gtk_button_new_with_label (tab_button[i]);
				gtk_table_attach_defaults (GTK_TABLE (table), button, k,k+1, 5, 6);
				if(i==0){
					g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  window);
				}else{
					g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse),  haribo);}
				tab_button[i]=0;
				if (user_data>0)
					g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( fonction_moyen2), aaa);
				else g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( Fin_du_jeu), window);

				g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window);
		}*/
	gtk_widget_show_all(GTK_WIDGET(window));
}

void xml(GtkWidget *table99,gpointer user_data){

	gchar buff[1024];
	xmlTextReaderPtr reader;
	char buff2[4000];
	gchar nom[1024];
	gchar nom2[1024];
	g_snprintf(nom,1024,"%s",user_data);
	g_snprintf(buff,1024,"%s.xml",nom);

	g_printf("\nfonction xml \nle pseudo entré est: %s \n-------",nom);

	reader = xmlReaderForFile(buff, NULL, 0);
	if(reader != NULL){
		xmlKeepBlanksDefault(0);
		fprintf(stderr, "le fichier existe deja ");
	    xmlDoc *doc = xmlParseFile(buff);
		xmlNodePtr  node_matrice = NULL, node = NULL, node1 = NULL;/* node pointers */
		xmlXPathContext *xpathCtx = xmlXPathNewContext( doc );

		g_snprintf(nom2,1024,"/%s",nom);

		xmlXPathObject * xpathObj =xmlXPathEvalExpression((xmlChar*)nom2, xpathCtx );
		xmlNode *root_node = xpathObj->nodesetval->nodeTab[0];
		int i, j;
		LIBXML_TEST_VERSION;
		   // xmlDocSetRootElement(doc, root_node);

		node_matrice = xmlNewChild(root_node, NULL, BAD_CAST "matrice", NULL);
		for (i = 0; i < NBR_PAYS; i++) {
			sprintf(buff2, getPays(i), i);
			node = xmlNewChild(node_matrice, NULL, BAD_CAST buff2, NULL);
			for (j = 0; j < NBR_PAYS; j++) {
				sprintf(buff2, getPays(j), j);
				node1 = xmlNewChild(node, NULL, BAD_CAST buff2, "0");
		    }
		}

		xmlSaveFormatFileEnc( buff, doc, "utf-8", 1 );
		xmlFreeDoc(doc);
		xmlCleanupParser();
		return;
	}

    xmlDocPtr doc = NULL;
    xmlNodePtr root_node = NULL, node_matrice = NULL, node = NULL, node1 = NULL;
    int i, j;
    LIBXML_TEST_VERSION;
    xmlKeepBlanksDefault(0);
    doc = xmlNewDoc(BAD_CAST "1.0");
    root_node = xmlNewNode(NULL, BAD_CAST nom);

    xmlDocSetRootElement(doc, root_node);
    node_matrice = xmlNewChild(root_node, NULL, BAD_CAST "matrice", NULL);
     for (i = 0; i < NBR_PAYS; i++) {
         sprintf(buff2, getPays(i), i);
         node = xmlNewChild(node_matrice, NULL, BAD_CAST buff2, NULL);
         for (j = 0; j < NBR_PAYS; j++) {
             sprintf(buff2, getPays(j), j);
             node1 = xmlNewChild(node, NULL, BAD_CAST buff2, "0");
         }
     }

    xmlSaveFormatFileEnc( buff, doc, "utf-8", 1 );
    xmlFreeDoc(doc);


    xmlCleanupParser();
    return;
}


void Choix_niveaux(GtkWidget *table,gpointer user_data){
	GtkWidget *window0, *table0, *layout, *image;
	GtkWidget *button, *button1, *button2;

	g_printf("choix niveau\nle pseudo entré est: %s\n-------\n",gtk_entry_get_text(GTK_ENTRY(user_data)));

	nom_nombre *tagada=malloc(sizeof(*tagada));
	tagada->nom=malloc(sizeof(char*)*100);
	strcpy(tagada->nom,gtk_entry_get_text(user_data));
	tagada->nombre=0;

	window0 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window0), "QCM drapeau-choix de la difficulté");
	gtk_window_set_default_size (GTK_WINDOW (window0), L_FENETRE, H_FENETRE);
	gtk_container_set_border_width (GTK_CONTAINER (window0), 5);
	gtk_window_set_position(GTK_WINDOW(window0), GTK_WIN_POS_CENTER_ALWAYS);

	layout = gtk_layout_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER (window0), layout);

	image = gtk_image_new_from_file("onu resize.png");
	gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);

	table0 = gtk_table_new (7, 5, TRUE);
	gtk_table_set_row_spacings(GTK_TABLE(table0), 50);
	gtk_table_set_col_spacings(GTK_TABLE(table0), 20);

	button = gtk_button_new_with_label ("niveau facile");
		gtk_table_attach_defaults (GTK_TABLE (table0), button,2, 3, 1, 2);

		g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(fonction_facile), tagada);
		g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(xml), tagada->nom);

	button1 = gtk_button_new_with_label ("niveau moyen");
		gtk_table_attach_defaults (GTK_TABLE (table0), button1,  2, 3, 2, 3);
		g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(fonction_moyen2), tagada);
		g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(xml), tagada->nom);

	button2 = gtk_button_new_with_label ("niveau difficile");
		gtk_table_attach_defaults (GTK_TABLE (table0), button2,  2, 3, 3, 4);
		g_signal_connect(G_OBJECT(button2), "clicked",G_CALLBACK(xml), tagada->nom);

	gtk_container_add (GTK_CONTAINER (layout), table0);
	gtk_window_set_resizable (window0, FALSE);
	gtk_widget_set_size_request (window0, L_FENETRE, H_FENETRE);
	gtk_widget_show_all(GTK_WIDGET(window0));
}



int main (int argc,char *argv[]){
  GtkWidget *window0,*entry,*button,*table;
  GtkWidget *label1,*label0,*label00;
  GtkWidget *image,*layout;
  GtkWidget *myGrid;

  srand(time(NULL));
  gtk_init (&argc, &argv);

  window0 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window0), "QCM entrez votre nom");
  gtk_window_set_default_size (GTK_WINDOW (window0), L_FENETRE, H_FENETRE);
  gtk_container_set_border_width (GTK_CONTAINER (window0), 5);
  gtk_window_set_position(GTK_WINDOW(window0), GTK_WIN_POS_CENTER_ALWAYS);

  layout = gtk_layout_new(NULL, NULL);
  gtk_container_add(GTK_CONTAINER (window0), layout);

  image = gtk_image_new_from_file("onu resize.png");
  gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);
//

  myGrid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER (layout), myGrid);
  gtk_grid_set_row_spacing (myGrid, 20);

  label0 = gtk_label_new("                                                                  ");
  gtk_grid_attach(myGrid, label0, 0, 0, 1, 1);
  label00 = gtk_label_new("\n\n\ ");
  gtk_grid_attach(myGrid, label00, 1, 0, 1, 1);


  label1 = gtk_label_new("Entrez votre nom svp :");
  gtk_grid_attach(myGrid, label1, 1, 1, 1, 1);

  entry=gtk_entry_new();
  gtk_grid_attach(myGrid, entry, 1, 2, 1, 1);

  button=gtk_button_new_with_label("Valider");
  gtk_grid_attach(myGrid, button, 1, 5, 1, 1);

  g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(Choix_niveaux),entry);
  g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window0);


  gtk_widget_show_all (window0);
  gtk_window_set_resizable (window0, FALSE);
  gtk_widget_set_size_request (window0, L_FENETRE, H_FENETRE);
  gtk_main ();

  return 0;
}
/*
int main (int argc,char *argv[]){
  GtkWidget *window0,*hbox,*entry,*button,*table;

  srand(time(NULL));
  gtk_init (&argc, &argv);

  window0 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window0), "QCM drapeau-choix de la difficulté");
  gtk_window_set_default_size (GTK_WINDOW (window0), L_FENETRE, H_FENETRE);
  gtk_container_set_border_width (GTK_CONTAINER (window0), 5);
  gtk_window_set_position(GTK_WINDOW(window0), GTK_WIN_POS_CENTER_ALWAYS);

 hbox=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,5);
  gtk_container_add(GTK_CONTAINER(window0),hbox);

  entry=gtk_entry_new();
  gtk_box_pack_start(GTK_BOX(hbox),entry,TRUE,TRUE,5);
  button=gtk_button_new_with_label("Valider");

  gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,0);

  g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(Choix_niveaux),entry);
  g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window0);

  gtk_widget_show_all (window0);
  gtk_main ();

  return 0;
}*/

// const gchar* cur_value =gtk_entry_get_text (GTK_ENTRY (entry));
// g_snprintf(nom_dutilisatuer,50,"%s", gtk_entry_get_text(GTK_ENTRY(entry)));


/*xmlInitParser();
	LIBXML_TEST_VERSION*/

/*
	  xmlDoc *doc = xmlParseFile(buf1);

	  xmlXPathContext *xpathCtx = xmlXPathNewContext( doc );
	  xmlXPathObject * xpathObj =xmlXPathEvalExpression( (xmlChar*)buf2, xpathCtx );
	  xmlNode *node = xpathObj->nodesetval->nodeTab[0];
	  //xmlSetProp( node, (xmlChar*)"age", (xmlChar*)"3" );
	  xmlNodeSetContent(node, "1");
	  xmlSaveFormatFileEnc( buf1, doc, "utf-8", 1 );
	  xmlXPathFreeObject( xpathObj );
	  xmlXPathFreeContext( xpathCtx );
	  xmlFreeDoc( doc );
	  xmlCleanupParser();*/
