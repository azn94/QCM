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
#define NBR_LVL_F 5
#define NBR_LVL_M 4
#define L_FENETRE 700
#define H_FENETRE 450

static void update_xpath_nodes(xmlNodeSetPtr nodes, const xmlChar * value);
typedef struct {
  GtkWidget *wid;
  char *yes;
} stru;

typedef struct {
  int nombre;
  GtkWidget *nom;
} nom_nombre;

void bonne_reponse(GtkWidget *widget, gpointer window) {
  GtkWidget *dialog;
  dialog = gtk_message_dialog_new(GTK_WINDOW(window),GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_QUESTION,GTK_BUTTONS_OK,"Bonne réponse");
  //gtk_window_set_title(GTK_WINDOW(dialog), "Question");
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
}

void mauvaise_reponse(GtkWidget *widget, gpointer haribo) {
  GtkWidget *dialog;
  stru *london=malloc(sizeof(*london));
  london=haribo;
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
	static char buffer[100];
	//static char buffer2[100];
	int i=rand()%1;
	int j=0;
	while(fgets(buffer,sizeof(buffer),f)&& j<i){
		j++;
	}
	sscanf(buffer,"%s",&buffer);
	fclose(f);
	return buffer;
}

const  char* NomPaysAleatoireAfrique (){
	FILE *f=fopen("listepaysAfrique.txt","r");
	static char buffer[100];
	static char buffer2[100];
	int i=rand()%27;
	int j=0;
	while(fgets(buffer,100,f)&& j<i){
		j++;
	}
	sscanf(buffer,"%s",&buffer2);
	fclose(f);
	return buffer2;
}

const  char* getPays (int r){
	FILE *f=fopen("listepays.txt","r");
	static char buffer[100];
	static char buffer2[100];
	int i=r;
	int j=0;
	while(fgets(buffer,100,f)&& j<i){
		j++;
	}
	sscanf(buffer,"%s",&buffer2);
	fclose(f);
	return buffer2;
}
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
update_xpath_nodes(xmlNodeSetPtr nodes, const xmlChar* value) {
    int size;
    int i;

    assert(value);
    size = (nodes) ? nodes->nodeNr : 0;

    /*
     * NOTE: the nodes are processed in reverse order, i.e. reverse document
     *       order because xmlNodeSetContent can actually free up descendant
     *       of the node and such nodes may have been selected too ! Handling
     *       in reverse order ensure that descendant are accessed first, before
     *       they get removed. Mixing XPath and modifications on a tree must be
     *       done carefully !
     */
    for(i = size - 1; i >= 0; i--) {
	assert(nodes->nodeTab[i]);

	xmlNodeSetContent(nodes->nodeTab[i], value);
	/*
	 * All the elements returned by an XPath query are pointers to
	 * elements from the tree *except* namespace nodes where the XPath
	 * semantic is different from the implementation in libxml2 tree.
	 * As a result when a returned node set is freed when
	 * xmlXPathFreeObject() is called, that routine must check the
	 * element type. But node from the returned set may have been removed
	 * by xmlNodeSetContent() resulting in access to freed data.
	 * This can be exercised by running
	 *       valgrind xpath2 test3.xml '//discarded' discarded
	 * There is 2 ways around it:
	 *   - make a copy of the pointers to the nodes from the result set
	 *     then call xmlXPathFreeObject() and then modify the nodes
	 * or
	 *   - remove the reference to the modified nodes from the node set
	 *     as they are processed, if they are not namespace nodes.
	 */
	if (nodes->nodeTab[i]->type != XML_NAMESPACE_DECL)
	    nodes->nodeTab[i] = NULL;
    }
}
void fonction_facile(GtkWidget *table99, gpointer user_data){
	GtkWidget *button,*window,*table;

	int i=rand()%3,k;
	char buffer[500]="";
	char s0[50],s1[50],s2[50];
	char *tab_button[3]={strcpy(s0,NomPaysAleatoire()),strcpy(s1,NomPaysAleatoire()),strcpy(s2,NomPaysAleatoire())};
	g_snprintf(buffer,500,"drapeau/%s.png",tab_button[0]);


	g_printf("%s \n%s \n%s\n",tab_button[0],tab_button[1],tab_button[2]);


	table = gtk_table_new (6, 3, TRUE);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "QCM drapeau-facile");
	gtk_window_set_default_size (GTK_WINDOW (window), L_FENETRE, H_FENETRE);
	gtk_container_set_border_width (GTK_CONTAINER (window), 100);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);

	gtk_table_set_col_spacings(GTK_TABLE(table), 20);

	stru *haribo=malloc(sizeof(*haribo));
	haribo->yes=malloc(sizeof(char*)*100);
	strcpy(haribo->yes,tab_button[0]);
	haribo->wid=window;

	gtk_container_add (GTK_CONTAINER (window), table);
	button = gtk_image_new_from_file(buffer);
	gtk_table_attach_defaults (GTK_TABLE (table), button, 0, 3, 0, 3);

	nom_nombre *london=malloc(sizeof(*london));
	london=user_data;

	london->nombre++;
	int aaa=london->nombre;

	xmlInitParser();
		  LIBXML_TEST_VERSION
		  char buf1[50],buf2[50];


	for(k=0;k<3;k++){
		while(tab_button[i]==0){
				i=rand()%3;
		}
		button = gtk_button_new_with_label (tab_button[i]);
		//g_snprintf(buf2,50,"/youssef/%s/%s",tab_button[0],tab_button[i]);
			gtk_table_attach_defaults (GTK_TABLE (table), button, k,k+1, 4, 5);
			if(i==0){
				g_snprintf(buf2,50,"/youssef/%s/%s",tab_button[0],tab_button[0]);
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  window);
			}else{
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse),  haribo);}
			tab_button[i]=0;
			if (aaa<4)
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( fonction_facile), london);
			else{
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( Fin_du_jeu), window);
				london->nombre=0;
			}
			g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window);
	}


	  g_snprintf(buf1,50,"%s.xml","youssef");
	  xmlDoc *doc = xmlParseFile(buf1 );
	  xmlXPathContext *xpathCtx = xmlXPathNewContext( doc );
	  xmlXPathObject * xpathObj =
	  	xmlXPathEvalExpression( (xmlChar*)buf2, xpathCtx );
	  xmlNode *node = xpathObj->nodesetval->nodeTab[0];
	  //xmlSetProp( node, (xmlChar*)"age", (xmlChar*)"3" );
	  xmlNodeSetContent(node, "1");
	  xmlSaveFormatFileEnc( "youssef.xml", doc, "utf-8", 1 );
	  xmlXPathFreeObject( xpathObj );
	  xmlXPathFreeContext( xpathCtx );
	  xmlFreeDoc( doc );
	  xmlCleanupParser();



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

void xml(char nom[]){
	gchar buff[1024];
	xmlTextReaderPtr reader;
	char buff2[4000];
	g_snprintf(buff,1024,"%s.xml",nom);

	reader = xmlReaderForFile(buff, NULL, 0);
	if(reader != NULL){
		fprintf(stderr, "le fichier existe deja ");
		return;}

    xmlDocPtr doc = NULL;       /* document pointer */
    xmlNodePtr root_node = NULL, node = NULL, node1 = NULL;/* node pointers */
    xmlNodePtr root_node2 = NULL;
    xmlDtdPtr dtd = NULL;       /* DTD pointer */
  //  char buff[256];
    int i, j;

    LIBXML_TEST_VERSION;

    doc = xmlNewDoc(BAD_CAST "1.0");
    root_node = xmlNewNode(NULL, BAD_CAST nom);
    xmlDocSetRootElement(doc, root_node);

    /*node = xmlNewNode(NULL, BAD_CAST "node4");
     node1 = xmlNewText(BAD_CAST"other way to create content (which is also a node)");
     xmlAddChild(node, node1);
     xmlAddChild(root_node, node);*/

     /*
      * A simple loop that "automates" nodes creation
      */
     for (i = 0; i < 200; i++) {
         sprintf(buff2, getPays(i), i);
         node = xmlNewChild(root_node, NULL, BAD_CAST buff2, NULL);
         for (j = 0; j < 200; j++) {
             sprintf(buff2, getPays(j), j);
             node1 = xmlNewChild(node, NULL, BAD_CAST buff2, "0");
             xmlNewProp(node1, NULL, 0);
         }
     }
    /* Dumping document to stdio or file*/
    //xmlSaveFormatFileEnc(argc > 1 ? argv[1] : "-", doc, "UTF-8", 1);
    xmlSaveFormatFileEnc( buff, doc, "utf-8", 1 );
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return;
}


void Choix_niveaux(GtkWidget *table,gpointer user_data){
	GtkWidget *button,*window0,*table0;

	xml(gtk_entry_get_text(GTK_ENTRY(user_data)));

	g_printf("%s\n",gtk_entry_get_text(GTK_ENTRY(user_data)));

	nom_nombre *tagada=malloc(sizeof(*tagada));
	tagada->nom=GTK_ENTRY(user_data);


	 window0 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	 gtk_window_set_title (GTK_WINDOW (window0), "QCM drapeau-choix de la difficulté");
	 gtk_window_set_default_size (GTK_WINDOW (window0), L_FENETRE, H_FENETRE);
	 gtk_container_set_border_width (GTK_CONTAINER (window0), 5);
	 gtk_window_set_position(GTK_WINDOW(window0), GTK_WIN_POS_CENTER_ALWAYS);

	 table0 = gtk_table_new (7, 3, TRUE);
	 gtk_table_set_row_spacings(GTK_TABLE(table0), 50);

	button = gtk_button_new_with_label ("niveau facile");
		gtk_table_attach_defaults (GTK_TABLE (table0), button,1, 2, 1, 2);
		tagada->nombre=0;
		g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(fonction_facile), tagada);

		//g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(callback), tagada->nombre=0;);
		tagada->nombre=0;

	button = gtk_button_new_with_label ("niveau moyen");
		gtk_table_attach_defaults (GTK_TABLE (table0), button,  1, 2, 2, 3);
		g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(fonction_moyen2), NBR_LVL_M);

	button = gtk_button_new_with_label ("niveau difficile");
		gtk_table_attach_defaults (GTK_TABLE (table0), button,  1,2, 3, 4);

	gtk_container_add (GTK_CONTAINER (window0), table0);
	gtk_widget_show_all(GTK_WIDGET(window0));
}
int main (int argc,char *argv[]){
  GtkWidget *window0,*hbox,*entry,*button,*table;
  GtkWidget *label1;

  srand(time(NULL));
  gtk_init (&argc, &argv);


  window0 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window0), "QCM drapeau-choix de la difficulté");
  gtk_window_set_default_size (GTK_WINDOW (window0), L_FENETRE, H_FENETRE);
  gtk_container_set_border_width (GTK_CONTAINER (window0), 5);
  gtk_window_set_position(GTK_WINDOW(window0), GTK_WIN_POS_CENTER_ALWAYS);

  table = gtk_table_new(4, 3, FALSE);
  gtk_container_add(GTK_CONTAINER(window0), table);

  label1 = gtk_label_new("Entrez votre nom:");
  gtk_table_attach_defaults(GTK_TABLE(table), label1, 1, 2, 1, 2);

  entry=gtk_entry_new();
  gtk_table_attach_defaults(GTK_TABLE(table), entry, 0, 3,2, 3);

  button=gtk_button_new_with_label("Valider");
  gtk_table_attach_defaults (GTK_TABLE (table), button, 1, 2, 3, 4);

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
