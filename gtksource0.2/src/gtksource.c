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

#define NBR_LVL 3
#define NBR_LVL_F 10
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
       g_printf("bon réponse");
       	printf("bon réponse");
       //	g_printf("le nombre de maaaaaatrice est %d",compter_matrice());
       stru *london=malloc(sizeof(*london));
       london=haribo;
       //g_printf("---------\nmauvaise réponse %s \n%s \n%s\n",london->nom_utilisateur,london->yes,london->nom_mauvaise);
       xmlInitParser();
         LIBXML_TEST_VERSION


         char buf1[50],buf2[50];
         g_snprintf(buf2,50,"/%s/matrice/%s/%s",london->nom_utilisateur,london->yes,london->yes);
         g_snprintf(buf1,50,"%s.xml",london->nom_utilisateur);

         xmlDoc *doc = xmlParseFile(buf1);
         xmlXPathContext *xpathCtx = xmlXPathNewContext( doc );
         xmlXPathObject * xpathObj =xmlXPathEvalExpression( (xmlChar*)buf2, xpathCtx );
         int a= xmlXPathNodeSetGetLength(xpathObj->nodesetval);
         xmlNode *node = xpathObj->nodesetval->nodeTab[a-1];
         xmlNodeSetContent(node, "1");
         xmlSaveFormatFileEnc( buf1, doc, "utf-8", 1 );
         xmlXPathFreeObject( xpathObj );
         xmlXPathFreeContext( xpathCtx );
         xmlFreeDoc( doc );
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
  g_printf("---------\nmauvaise réponse %s \n%s \n%s\n",london->nom_utilisateur,london->yes,london->nom_mauvaise);
  xmlInitParser();
    LIBXML_TEST_VERSION


    char buf1[50],buf2[50];
    g_snprintf(buf2,50,"/%s/matrice/%s/%s",london->nom_utilisateur,london->yes,london->nom_mauvaise);
    g_snprintf(buf1,50,"%s.xml",london->nom_utilisateur);

    xmlDoc *doc = xmlParseFile(buf1);
    xmlXPathContext *xpathCtx = xmlXPathNewContext( doc );
    xmlXPathObject * xpathObj =xmlXPathEvalExpression( (xmlChar*)buf2, xpathCtx );
    int a= xmlXPathNodeSetGetLength(xpathObj->nodesetval);
    xmlNode *node = xpathObj->nodesetval->nodeTab[a];
  		  //xmlSetProp( node, (xmlChar*)"age", (xmlChar*)"3" );
    xmlNodeSetContent(node, "1");
    xmlSaveFormatFileEnc( buf1, doc, "utf-8", 1 );
    xmlXPathFreeObject( xpathObj );
    xmlXPathFreeContext( xpathCtx );
    xmlFreeDoc( doc );
    xmlCleanupParser();

  char Madrid[100];
  g_snprintf(Madrid,100,"mauvaise réponse, c'était : '%s'",london->yes);
  dialog = gtk_message_dialog_new(GTK_WINDOW(london->wid),GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_QUESTION,GTK_BUTTONS_OK,Madrid);
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
  free(haribo);
}
void Fin_du_jeu(GtkWidget *widget, gpointer window) {
	GtkWidget *dialog;
	dialog = gtk_message_dialog_new(GTK_WINDOW(window),GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_QUESTION,GTK_BUTTONS_OK,"\n\n\n\n\t\tFIN DU JEU\t\t\n\n\n\n");
	  //gtk_window_set_title(GTK_WINDOW(dialog), "Question");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}

const  char* NomPaysAleatoire (){
	FILE *f=fopen("listepays.txt","r");
	static char buffer[100];
	static char buffer2[40];
	int i=rand()%195;
	int j=0;
	while(fgets(buffer,100,f)&& j<i){
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
	sscanf(buffer,"%s",&buffer);
	fclose(f);
	return buffer;
}


const  char* getPays (int r){
	FILE *f=fopen("listepays.txt","r");
	if(f==NULL){
			fprintf(stderr,"probleme d'ouverture\n ");
			return NULL;}
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
	char s0[50],s1[50],s2[50];
	char *tab_button[3]={strcpy(s0,NomPaysAleatoire()),strcpy(s1,NomPaysAleatoire()),strcpy(s2,NomPaysAleatoire())};
	g_snprintf(buffer,500,"drapeau/%s.png",tab_button[0]);
		//g_printf("%s \n%s \n%s\n",tab_button[0],tab_button[1],tab_button[2]);

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
		//g_printf("test ici celui qui marche pas  %s \n",london->nom);

	london->nombre++;
	int aaa=london->nombre;

	char buf1[50],buf2[50];
	g_snprintf(buf2,50,"/%s/%s/%s",london->nom,tab_button[0],tab_button[0]);
	g_snprintf(buf1,50,"%s.xml",london->nom);

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
	if (aaa<NBR_LVL_F)
		g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( fonction_facile), london);
	else{
		g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( Fin_du_jeu), window);
		london->nombre=0;
			}
	g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window);

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
		if (aaa<NBR_LVL_F)
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( fonction_facile), london);
		else{
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( Fin_du_jeu), window);
			london->nombre=0;
				}
		g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window);

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
		if (aaa<NBR_LVL_F)
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( fonction_facile), london);
		else{
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( Fin_du_jeu), window);
			london->nombre=0;
				}
		g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window);


		gtk_widget_show_all(GTK_WIDGET(window));
	}

void fonction_moyen2(GtkWidget *table99,gpointer user_data){
	GtkWidget *button,*button2,*window,*table;
	int i=rand()%6,j=rand()%18,k,l;
	char buffer[500]="";
	char s1[50],s2[50],s3[50],s4[50],s5[50];
	char *tab_button[6]={NomPaysAleatoire(),strcpy(s1,NomPaysAleatoire()),strcpy(s2,NomPaysAleatoire()),strcpy(s3,NomPaysAleatoire()),strcpy(s4,NomPaysAleatoire()),strcpy(s5,NomPaysAleatoire())};
	g_snprintf(buffer,500,"drapeau/%s.png",tab_button[0]);

	table = gtk_table_new (6, 3, TRUE);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "QCM drapeau-medium");
	gtk_window_set_default_size (GTK_WINDOW (window), L_FENETRE, H_FENETRE);
	gtk_container_set_border_width (GTK_CONTAINER (window), 100);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);

	gtk_table_set_col_spacings(GTK_TABLE(table), 20);
	gtk_table_set_row_spacings(GTK_TABLE(table), 20);
	stru *haribo=malloc(sizeof(*haribo));
	haribo->yes=malloc(sizeof(char*));
	strcpy(haribo->yes,tab_button[0]);
	haribo->wid=window;

	gtk_container_add (GTK_CONTAINER (window), table);

	button = gtk_image_new_from_file(buffer);
	gtk_table_attach_defaults (GTK_TABLE (table), button, 0, 3, 0, 3);

	int aaa=user_data;
	aaa--;

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
		}
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

	g_printf("testxml voir le nom  %s \n",nom);


	reader = xmlReaderForFile(buff, NULL, 0);
	if(reader != NULL){
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
		             //xmlNewProp(node1, NULL, 0);
		         }
		     }
		    xmlSaveFormatFileEnc( buff, doc, "utf-8", 1 );
		    xmlFreeDoc(doc);
		    xmlCleanupParser();
		    return;

	}

    xmlDocPtr doc = NULL;
    xmlNodePtr root_node = NULL, node_matrice = NULL, node = NULL, node1 = NULL;/* node pointers */
    int i, j;
    LIBXML_TEST_VERSION;
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
             //xmlNewProp(node1, NULL, 0);
         }

     }
    xmlSaveFormatFileEnc( buff, doc, "utf-8", 1 );
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return;
}
void Choix_niveaux(GtkWidget *table,gpointer user_data){
	GtkWidget *button,*window0,*table0,*layout,*image;
	GtkWidget *button1,*button2;


	g_printf("%s\n",gtk_entry_get_text(GTK_ENTRY(user_data)));

	nom_nombre *tagada=malloc(sizeof(*tagada));
	tagada->nom=malloc(sizeof(char*)*100);

	strcpy(tagada->nom,gtk_entry_get_text(user_data));
	//tagada->nom=gtk_entry_get_text(user_data);

	//g_printf("l'autre test %s\n",tagada->nom);

	 window0 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	 gtk_window_set_title (GTK_WINDOW (window0), "QCM drapeau-choix de la difficulté");
	 gtk_window_set_default_size (GTK_WINDOW (window0), L_FENETRE, H_FENETRE);
	 gtk_container_set_border_width (GTK_CONTAINER (window0), 5);
	 gtk_window_set_position(GTK_WINDOW(window0), GTK_WIN_POS_CENTER_ALWAYS);


	 layout = gtk_layout_new(NULL, NULL);
	  gtk_container_add(GTK_CONTAINER (window0), layout);
	    // gtk_widget_show(layout);

	  image = gtk_image_new_from_file("onu resize.png");
	  gtk_layout_put(layout, image, 0, 0);


	 table0 = gtk_table_new (7, 5, TRUE);
	 gtk_table_set_row_spacings(GTK_TABLE(table0), 50);
	 gtk_table_set_col_spacings(GTK_TABLE(table0), 20);

	button = gtk_button_new_with_label ("niveau facile");
		gtk_table_attach_defaults (GTK_TABLE (table0), button,2, 3, 1, 2);
		tagada->nombre=0;

		g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(fonction_facile), tagada);
		g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(xml), tagada->nom);

	button1 = gtk_button_new_with_label ("niveau moyen");
		gtk_table_attach_defaults (GTK_TABLE (table0), button1,  2, 3, 2, 3);
		g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(fonction_moyen2), NBR_LVL_M);

	button2 = gtk_button_new_with_label ("niveau difficile");
		gtk_table_attach_defaults (GTK_TABLE (table0), button2,  2, 3, 3, 4);

	gtk_container_add (GTK_CONTAINER (layout), table0);
	gtk_widget_show_all(GTK_WIDGET(window0));
}
int main (int argc,char *argv[]){
  GtkWidget *window0,*entry,*button,*table;
  GtkWidget *label1;
  GtkWidget *image,*layout;

  srand(time(NULL));
  gtk_init (&argc, &argv);


  window0 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window0), "QCM drapeau-choix de la difficulté");
  gtk_window_set_default_size (GTK_WINDOW (window0), L_FENETRE, H_FENETRE);
  gtk_container_set_border_width (GTK_CONTAINER (window0), 5);
  gtk_window_set_position(GTK_WINDOW(window0), GTK_WIN_POS_CENTER_ALWAYS);



  layout = gtk_layout_new(NULL, NULL);
  gtk_container_add(GTK_CONTAINER (window0), layout);
    // gtk_widget_show(layout);

  image = gtk_image_new_from_file("onu resize.png");
  gtk_layout_put(layout, image, 0, 0);


  table = gtk_table_new(8, 8, FALSE);
  gtk_container_add(GTK_CONTAINER(layout), table);
  gtk_table_set_row_spacings(GTK_TABLE(table), 5);
  gtk_table_set_col_spacings(GTK_TABLE(table), 20);


  label1 = gtk_label_new("Entrez votre nom:");
  gtk_table_attach_defaults(GTK_TABLE(table), label1, 6, 7, 2, 3);

  entry=gtk_entry_new();
  gtk_table_attach_defaults(GTK_TABLE(table), entry, 6, 7, 6, 7);

  button=gtk_button_new_with_label("Valider");
  gtk_table_attach_defaults (GTK_TABLE (table), button, 6, 7, 7, 8);

  g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(Choix_niveaux),entry);
  g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window0);


  gtk_widget_show_all (window0);
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
