#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>
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

#define NBR_LVL_F 10
#define NBR_LVL_M 10
#define L_FENETRE 700
#define H_FENETRE 450
#define NBR_PAYS 10
#define NBR_IA 3



typedef struct {
  GtkWidget *wid;
  char *nom_bonne;
  char *nom_utilisateur;
  char *nom_mauvaise;
  int nbr_matrice;

} stru;

typedef struct {
  GtkWidget *wid;
  GtkWidget *wid2;
  GtkWidget *wid3;
  GtkWidget *wid4;
  GtkWidget *wid5;
  GtkWidget *wid6;
  char *nom1;
  char *nom2;
  char *nom3;
  char *nom4;
  char *nom5;
  char *nom6;
} struc;


typedef struct {
  int nombre;
  int nombre_br;
  char *nom;
  GtkWidget *wid;
  float mat_similitude[NBR_PAYS][NBR_PAYS];
} nom_nombre;

typedef struct {
	GtkWidget *wid;
	char *nom1;
  char *nom2;
} nom_nom_nombre;

typedef struct {
  char *nom1;
} nom_struct;

enum {
  COLUMN = 0,
  NUM_COLS
};

typedef struct liste_matrice liste_matrice;
struct liste_matrice{
	int matrice[NBR_PAYS][NBR_PAYS];
	liste_matrice *suivant;
	int id ;
};

void affiche(float mat[NBR_PAYS][NBR_PAYS]){
	int i,j;
	for(i=0;i<NBR_PAYS;i++){
                        for(j=0;j<NBR_PAYS;j++){
                                printf("%.2f ",mat[i][j]);
                        }
                        printf("\n");
        }
}
void affiche_int(int mat[NBR_PAYS][NBR_PAYS]){
	int i,j;
	for(i=0;i<NBR_PAYS;i++){
                        for(j=0;j<NBR_PAYS;j++){
                                printf("%d ",mat[i][j]);
                        }
                        printf("\n");
        }
}

void affiche_ligne_int(int tab[6]){
	int i;
	for(i=0;i<6;i++)
		printf("%d ",tab[i]);
	printf("\n");
}

void copie_matrice(float ancien[NBR_PAYS][NBR_PAYS], float new[NBR_PAYS][NBR_PAYS]){
	int i,j;
	for(i=0;i<NBR_PAYS;i++){
		for(j=0;j<NBR_PAYS;j++)
			new[i][j]= ancien[i][j];
	}
}
liste_matrice* lirematrice(char* User_name){
        xmlDocPtr doc;
        xmlNodePtr cur,save;
        int cpt= 1;
        int i, j;
        //char nom[256];
        //snprintf(nom,256, "%s%s",User_name,".xml");
        doc = xmlParseFile(User_name);
        cur = xmlDocGetRootElement(doc);
        if (cur == NULL) {
                fprintf(stderr,"empty document\n");
                xmlFreeDoc(doc);
        }
        //printf("TEST 2");
        liste_matrice *liste_debut= malloc (sizeof(liste_matrice));
        liste_debut->id=0;
        liste_matrice *tmp1= liste_debut;
        cur=cur->children;
        cur=cur->next;
        //printf("Nom actuel : %s \n",cur->name);
        xmlChar *reponse;
	//printf("Test\n");
        while(cur!=NULL){
                cur= cur->children;
                cur= cur->next;
                //printf("Nom actuel : %s \n",cur->name);
                i = 0;
                j = 0;
                while(cur!=NULL){
                        cur=cur->children;
                        cur=cur->next;
                        while(cur!=NULL){
                                reponse =xmlNodeGetContent(cur);
                                //printf("%s ",reponse);
                                char*tmp_char =(char*)(reponse);
                                tmp1->matrice[i][j] = atol(tmp_char);
                                //printf("%d j = %d i = %d\n",tmp2->matrice[i][j],j,i);
                                save=cur;
                                cur=cur->next;
                                cur=cur->next;
                                j++;
                        }
                        //printf("test\n");
                        cur=save->parent;
                        save=cur;
                        cur=cur->next;
                        cur=cur->next;
                        //printf("\n");
                        i++;
                        j = 0;
                }
                printf("YE SUIS LA 2\n");
                //printf("%d \n",tmp1->id);
                cur=save->parent;
                cur=cur->next;
                cur=cur->next;
                //printf("\n");
		liste_matrice *tmp2= malloc (sizeof(liste_matrice));
		tmp2->suivant=NULL;
		(liste_debut->id)+=1;
        tmp1->id =liste_debut->id;;
		tmp1->suivant= tmp2;
		tmp1=tmp2;
        }
        cpt=liste_debut->id;
        printf("%d\n",cpt);
        return liste_debut;
}

int no_doublons(int tab[6]){
	printf("ENTREE DANS NO DOUBLONS \n");
	int i,j;
	for(i=0;i<6;i++){
		for(j=0;j<6;j++){
			if(tab[i]== tab[j] && i!=j)
				return 1;
		}
	}
	return 0;
}

void moyen(float similarite[NBR_PAYS][NBR_PAYS],int drapeau, int indice[6]){ // similarité : matrice de similarité, drapeau : numéro du drapeau, indice: tableau vide dans lequel on va strocker les indices
  int nb_dif_zero = 0 ;
  int i;
  printf("ENTREE DANS MOYEN \n");
  // On stock la bonne réponse
  indice[0]=drapeau;
  // On compte le nombre de pays qui n'ont pas de 0
  for(i=0;i<NBR_PAYS;i++){
    if(similarite[drapeau][i]>0.0 && i!=drapeau)
      nb_dif_zero++;
  }
  float tmp[nb_dif_zero];
  int tmp_indice[nb_dif_zero];
  float val = 0;
  int k=0;
  // On stock les indices des drapeaux ayant un indice différent de 0
  for(i=0;i<NBR_PAYS;i++){
    if(similarite[drapeau][i]>0.0 && i!=drapeau){
      // Cas du premier non 0 rencontré
      if(val == 0){
	tmp[0]=similarite[drapeau][i];
	val+=similarite[drapeau][i];
	tmp_indice[k]=i;
	k++;
      }
      else{
	val+=similarite[drapeau][i];
	tmp[k]=val;
	tmp_indice[k]=i;
	k++;
      }
    }
  }
  i=0;
  float alea;
  int j,t;
  int  verif=0;
  j=1;
  while(j<6 && j<nb_dif_zero){ // On choisit un nombres de drapeaux entre le minimum du nombres de drapeaux voulu et celui de drapeaux ayant une similarité différentes de 0
    // On tire un nombre aléatoire entre 0 et la somme des valeurs
    alea=(float)rand()/(((float)(RAND_MAX))/tmp[nb_dif_zero-1]);
    //printf("%.2f \n",alea);
    t=0;
    verif=1;
    // On cherche où se trouve le drapeau correspondant au numéro aléatoire tiré
    do{
      if(alea<tmp[t]){
    	  	 indice[j]=tmp_indice[t];
    	  	 j++;
    	  	 verif=0;
      }
      t++;
    }while(verif);
  }
  int last;
  // Si on a moins de drapeaux avec une similarité de 0 que de drapeaux nécessaires pour le qcm, on choisit aléatoirement parmi la liste
  while(j<6){
      last=rand()%(NBR_PAYS);
      //printf("%d \n",last);
      indice[j]=last;
      j++;
  }
  if(no_doublons(indice)){
	  for(i=0;i<6;i++)
		  indice[i]=0;
	  moyen(similarite, drapeau, indice);
  }
}

void affichage(liste_matrice *liste){
        int i,j,k;
        liste_matrice* tmp=liste;
        for(k=0;k<liste->id;k++){
                printf("identifiant :%d\n",tmp->id);
                for(i=0;i<NBR_PAYS;i++){
                        for(j=0;j<NBR_PAYS;j++){
                                printf("%d ",tmp->matrice[i][j]);
                        }
                        printf("\n");
                }
                printf("\n");
		tmp=tmp->suivant;
        }
}

void  matrice_moyenne(liste_matrice* liste, float matrice[NBR_PAYS][NBR_PAYS]){
	float coeff =1.0;
	int i,j,k,cpt;
	liste_matrice *tmp=liste;
	float nb_matrice = liste->id;
	for(i=0;i<NBR_PAYS;i++){
		for(j=0;j<NBR_PAYS;j++)
			matrice[i][j]= 0.;
	}
	printf("%f\n",nb_matrice);
	if((nb_matrice)<=10.0){
		float denom = (nb_matrice)*(nb_matrice+1)/2.0;
		for(cpt=0;cpt<nb_matrice;cpt++){
			for(i=0;i<NBR_PAYS;i++){
				for(j=0;j<NBR_PAYS;j++)
					matrice[i][j]=((tmp->matrice[i][j])*coeff/denom)+matrice[i][j];
			}
			coeff+=1.0;
			tmp=tmp->suivant;
			affiche(matrice);
			printf("\n");
		}
	}
	else{
			float denom=55;
			for(k=0;k<((liste->id)-10);k++){
				tmp=tmp->suivant;
			}
			for(cpt=0;cpt<10;cpt++){
				for(i=0;i<NBR_PAYS;i++){
					for(j=0;j<NBR_PAYS;j++)
						matrice[i][j]=((tmp->matrice[i][j])*coeff/denom)+matrice[i][j];
				}
				coeff+=1.0;
				tmp=tmp->suivant;
			}
	}
}



float norme(float tab1[]){
   float somme =0;
   int i;
   for(i=0;i<NBR_PAYS;i++){
     somme = somme + tab1[i]*tab1[i];
   }
   return (sqrt(somme));
}

float vect(float tab1[], float tab2[]){
   float somme =0;
   int i;
   for(i=0;i<NBR_PAYS;i++)
     somme= somme + tab1[i]*tab2[i];
   return somme;
}


float change(float tab1[],float tab2[]){
   float cos=0;
   float norme1 =norme(tab1);
   float norme2 =norme(tab2);
   float norme_total = norme1*norme2;
   float produit_vect = vect(tab1,tab2);
   if(norme1==0 || norme2==0)
     cos=0;
   else
     cos = produit_vect/(norme_total);
   //printf("%f\n",cos);
   return cos;
}

void similitude(float tab [NBR_PAYS][NBR_PAYS]){
   int i,j;
   float tabbis[NBR_PAYS][NBR_PAYS];
   for(i=0;i<NBR_PAYS;i++){
     for(j=0;j<NBR_PAYS;j++)
       tabbis[i][j]= change(tab[i],tab[j]);
   }
   for(i=0;i<NBR_PAYS;i++){
     for(j=0;j<NBR_PAYS;j++)
       tab[i][j]= tabbis[i][j];
   }
}

void changer_matrice(char* nom_fichier,char* adresse){
	xmlInitParser();
	LIBXML_TEST_VERSION

	xmlDoc *doc = xmlParseFile(nom_fichier);
	xmlXPathContext *xpathCtx = xmlXPathNewContext( doc );
	xmlXPathObject * xpathObj =xmlXPathEvalExpression( (xmlChar*)adresse, xpathCtx );
	int nbr_matrice= xmlXPathNodeSetGetLength(xpathObj->nodesetval);
	xmlNode *node = xpathObj->nodesetval->nodeTab[nbr_matrice-1];
	xmlNodeSetContent(node,BAD_CAST "1");
	xmlSaveFormatFileEnc( nom_fichier, doc, "utf-8", 1 );
	xmlXPathFreeObject( xpathObj );
	xmlXPathFreeContext( xpathCtx );
	xmlFreeDoc( doc );
	xmlCleanupParser();
}


void bonne_reponse(GtkWidget *widget, gpointer haribo) {
	GtkWidget *dialog;
	stru *london=malloc(sizeof(*london));
	london=haribo;

	printf("\n---------\nbonne réponse l'adresse à remplir est : %s/%s/%s\n---------\n",london->nom_utilisateur,london->nom_bonne,london->nom_bonne);
	char nom_fichier[5000],adresse[5000];
	sprintf(adresse,"/%s/matrice/%s/%s",london->nom_utilisateur,london->nom_bonne,london->nom_bonne);
	sprintf(nom_fichier,"%s.xml",london->nom_utilisateur);
	changer_matrice(nom_fichier,adresse);

   dialog = gtk_message_dialog_new(GTK_WINDOW(london->wid),GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_QUESTION,GTK_BUTTONS_OK,"Bonne réponse");
   GdkColor red = {0, 0xffff, 0x0000, 0x0000};
   gtk_widget_modify_bg(dialog, GTK_STATE_ACTIVE,&red);
   gtk_dialog_run(GTK_DIALOG(dialog));
   gtk_widget_destroy(dialog);

   free(haribo);
}

static void mauvaise_reponse2 (GtkButton *button99, gpointer haribo){
  GtkWidget *dialog;
  GtkWidget *content_area;
  GtkWidget *label;

  stru *london=malloc(sizeof(*london));
  london=haribo;
  GtkWindow *window = london->wid;
  char nom_fichier[500];
  char button_message[5000];
  sprintf(button_message,"mauvaise réponse,vous aviez choisi %s, c'était :",london->nom_mauvaise);
  sprintf(nom_fichier,"drapeau/%s.png",london->nom_bonne);

  printf("\n---------\nmauvaise réponse l'adresse à remplir est : %s/%s/%s\n---------\n",london->nom_utilisateur,london->nom_bonne,london->nom_mauvaise);

  GtkWidget *table = gtk_table_new (2, 1, TRUE);

  dialog = gtk_dialog_new_with_buttons (NULL,window,GTK_DIALOG_MODAL,GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);

  GtkWidget *button = gtk_label_new(button_message);
  content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
  gtk_container_set_border_width (GTK_CONTAINER (table), 50);
  label = gtk_image_new_from_file(nom_fichier);
  gtk_table_attach_defaults (GTK_TABLE (table), button, 0, 1, 0, 1);
  gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, 1, 2);
  gtk_table_set_col_spacings(GTK_TABLE(table), 20);
  gtk_table_set_row_spacings(GTK_TABLE(table), 20);
  gtk_container_add (GTK_CONTAINER (content_area), table);

  gtk_widget_show_all (dialog);

  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);

}
void mauvaise_reponse(GtkWidget *widget, gpointer haribo) {
	GtkWidget *dialog;
	stru *london=malloc(sizeof(*london));
	london=haribo;

	printf("\n---------\nmauvaise réponse l'adresse à remplir est : %s/%s/%s\n---------\n",london->nom_utilisateur,london->nom_bonne,london->nom_mauvaise);

	char nom_fichier[500],adresse[500];
	sprintf(adresse,"/%s/matrice/%s/%s",london->nom_utilisateur,london->nom_bonne,london->nom_mauvaise);
	sprintf(nom_fichier,"%s.xml",london->nom_utilisateur);
	changer_matrice(nom_fichier,adresse);

	char Madrid[500];
	sprintf(Madrid,"mauvaise réponse, c'était : %s",london->nom_bonne);
	dialog = gtk_message_dialog_new(GTK_WINDOW(london->wid),GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR,GTK_BUTTONS_OK, Madrid);
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
	int i=rand()%NBR_PAYS;
	int j=0;
	while(fscanf(f,"%s",buffer)&& j<i){
		j++;
	}
	printf("l'aleatoire donne : num %d -> %s\n",i,buffer);
	fclose(f);
	return buffer;

}

const  char* getPaysContinant(int c,int r){
	FILE *f;
	switch(c){
	case 0:
		f=fopen("listepaysAfrique.txt","r");
		break;
	case 1:
		f=fopen("listepaysAmerique.txt","r");
		break;
	case 2:
		f=fopen("listepaysAsie.txt","r");
		break;
	case 3:
		f=fopen("listepaysEurope.txt","r");
		break;
	case 4:
		f=fopen("listepaysOceanie.txt","r");
		break;
	}
	if(f==NULL){
		fprintf(stderr,"problème d'ouverture du fichier listepays \n ");
		return NULL;
	}
	static char buffer[100];
	static char buffer2[100];
	int j=0;
	while(fgets(buffer,100,f)&& j<r){
		j++;
	}
	fclose(f);
	sscanf(buffer,"%s",&buffer2);
	return buffer2		;

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
int strtoint(char* nom){
	int cpt=0;
	FILE *f=fopen("listepays.txt","r");
	if(f==NULL){
		fprintf(stderr,"problème d'ouverture du fichier listepays \n ");
		return NULL;
	}
	char buffer[100];char buffer2[100];
	while(fgets(buffer,100,f) &&sscanf(buffer,"%s",&buffer2)&& strcmp(nom,buffer2)!=0){
		cpt++;
	}
	return cpt;

}

char* liretext(int i){
	FILE *fp;
	long lSize;
	static char buffer[1000];
	char buf[1000];
	switch(i){
		case 0:
			fp=fopen("wikipedia/out.txt", "r");
			break;
		case 1:
			fp=fopen("wikipedia/out2.txt", "r");
			break;
		case 2:
			fp=fopen("wikipedia/out3.txt", "r");
			break;
		case 3:
			fp=fopen("wikipedia/out4.txt", "r");
			break;
		case 4:
			fp=fopen("wikipedia/out5.txt", "r");
			break;
		case 5:
			fp=fopen("wikipedia/out6.txt", "r");
			break;
		}

	fseek( fp , 0L , SEEK_END);
	lSize = ftell( fp );
	rewind( fp );

	fgets(buffer,1000,fp);
	fgets(buf,1000,fp);
	sprintf(buffer,"%s\n%s",buffer, buf);
	return buffer;

	free(buffer);
}
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

void DoubleClick (GtkTreeView *treeview,GtkTreePath *path,GtkTreeViewColumn  *col,gpointer userdata){
	GtkTreeIter   iter;
	GtkTreeModel *model = gtk_tree_view_get_model(treeview);
	printf("double\nle pseudo entré est: %s\n-------\n",userdata);

	if (gtk_tree_model_get_iter(model, &iter, path)){
		char *name;
		gtk_tree_model_get(model, &iter, 0, &name, -1);
		Afficher_Statistique(name,userdata);
		g_free(name);
	}
}

GtkTreeModel *create_and_fill_model(void) {
	GtkTreeIter toplevel, child;
	GtkTreeStore *treestore = gtk_tree_store_new(NUM_COLS,G_TYPE_STRING);
	int i;

	gtk_tree_store_append(treestore, &toplevel, NULL);
	gtk_tree_store_set(treestore, &toplevel, COLUMN, "Afrique", -1);
	for(i=0;i<55;i++){
		gtk_tree_store_append(treestore, &child, &toplevel);
		gtk_tree_store_set(treestore, &child, COLUMN, getPaysContinant(0,i), -1);
	}

	gtk_tree_store_append(treestore, &toplevel, NULL);
	gtk_tree_store_set(treestore, &toplevel,COLUMN, "Amerique",-1);
	for(i=0;i<33;i++){
		gtk_tree_store_append(treestore, &child, &toplevel);
		gtk_tree_store_set(treestore, &child,COLUMN, getPaysContinant(1,i),-1);
	}

	gtk_tree_store_append(treestore, &toplevel, NULL);
	gtk_tree_store_set(treestore, &toplevel,COLUMN, "Asie",-1);
	for(i=0;i<44;i++){
		gtk_tree_store_append(treestore, &child, &toplevel);
		gtk_tree_store_set(treestore, &child,COLUMN, getPaysContinant(2,i),-1);
	}

	gtk_tree_store_append(treestore, &toplevel, NULL);
	gtk_tree_store_set(treestore, &toplevel, COLUMN, "Europe",-1);
	for(i=0;i<44;i++){
		gtk_tree_store_append(treestore, &child, &toplevel);
		gtk_tree_store_set(treestore, &child,COLUMN, getPaysContinant(3,i), -1);
	}

	gtk_tree_store_append(treestore, &toplevel, NULL);
	gtk_tree_store_set(treestore, &toplevel,COLUMN, "Oceanie",-1);
	for(i=0;i<12;i++){
		gtk_tree_store_append(treestore, &child, &toplevel);
		gtk_tree_store_set(treestore, &child,COLUMN, getPaysContinant(4,i), -1);
	}
	return GTK_TREE_MODEL(treestore);
}

GtkWidget *create_view_and_model(char* user_data) {
	GtkWidget *view = gtk_tree_view_new();
	GtkTreeViewColumn *col = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(col, "Pays");
	gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);

	printf("create view\nle pseudo entré est: %s\n-------\n",user_data);

	GtkTreeViewColumn *col2 = gtk_tree_view_column_new();
	gtk_tree_view_column_set_title(col2, "taux");
	gtk_tree_view_append_column(GTK_TREE_VIEW(view), col2);


	GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
	gtk_tree_view_column_pack_start(col, renderer, TRUE);
	gtk_tree_view_column_add_attribute(col, renderer,"text", COLUMN);

	GtkTreeModel *model = create_and_fill_model();
	gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);
	g_object_unref(model);

	g_signal_connect(view, "row-activated", (GCallback) DoubleClick, user_data);
	return view;

}
void tri(float tab[NBR_PAYS], int tabindice[6]){
    int indice[NBR_PAYS];
    int i,j;
    for(i=0;i<NBR_PAYS;i++)
      indice[i]=i;
    int tmp_ind;
    float tmp;
    for(i=0;i<NBR_PAYS;i++){
      for(j=i;j<NBR_PAYS;j++){
		if(tab[j]>tab[i]){
		  tmp=tab[i];
		  tab[i]=tab[j];
		  tab[j]=tmp;
		  tmp_ind=indice[i];
		  indice[i]=indice[j];
		  indice[j]=tmp_ind;
		}
      }
    }
    for(i=0;i<6;i++)
      tabindice[i]=indice[i];
}

void difficile(float similarite[NBR_PAYS],int drapeau, int tabindice[6]){
    int indice[NBR_PAYS];
    int i,j;
    int nb_dif_zero = 0;
    tabindice[0]=drapeau;
    for(i=0;i<NBR_PAYS;i++)
      indice[i]=i;

    for(i=0;i<NBR_PAYS;i++){
        if(similarite[i]>0.0 && i!=drapeau)
          nb_dif_zero++;
     }
    float save[NBR_PAYS];
    for(i=0;i<NBR_PAYS;i++)
    	save[i]=similarite[i];
    int tmp_ind;
    float tmp;
    float echange;
    echange = save[0];
    save[0]= save[drapeau];
    save[drapeau]= echange;

    indice[0]= drapeau;
    indice[drapeau] = 0;

    for(i=1;i<NBR_PAYS;i++){
      for(j=i;j<NBR_PAYS;j++){
		if(save[j]>save[i]){
		  tmp=save[i];
		  save[i]=save[j];
		  save[j]=tmp;
		  tmp_ind=indice[i];
		  indice[i]=indice[j];
		  indice[j]=tmp_ind;
		}
      }
    }
    j = 1;
    printf("%d ",tabindice[0]);
    while(j<6 && j<nb_dif_zero+1){
    		tabindice[j]=indice[j];
    		printf("%d  ", tabindice[j]);
    		j++;
    }
    printf("\n");
    for(i=0;i<NBR_PAYS;i++)
    	printf("%.2f ",save[i]);
    printf("\n");
    int last;
    while(j<6){
         last=rand()%(NBR_PAYS);
         printf("Numero random : %d \n",last);
         tabindice[j]=last;
         j++;
     }
     if(no_doublons(tabindice)){
    	 for(i=0;i<6;i++)
    		 tabindice[i]=0;
    	 difficile(similarite, drapeau, tabindice);
     }

}

void xml(GtkWidget *table99, gpointer user_data){
	gchar buff[1024];
	xmlTextReaderPtr reader;
	char buff2[4000];
	gchar nom[1024];
	gchar nom2[1024];
	sprintf(nom,"%s",user_data);
	sprintf(buff,"%s.xml",nom);
	LIBXML_TEST_VERSION;
	printf("\nfonction xml \nle pseudo entré est: %s \n-------",nom);

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

		node_matrice = xmlNewChild(root_node, NULL, BAD_CAST "matrice", NULL);
		for (i = 0; i < NBR_PAYS; i++) {
			sprintf(buff2, getPays(i), i);
			node = xmlNewChild(node_matrice, NULL, BAD_CAST buff2, NULL);
			for (j = 0; j < NBR_PAYS; j++) {
				sprintf(buff2, getPays(j), j);
				node1 = xmlNewChild(node, NULL, BAD_CAST buff2,BAD_CAST "0");
		    }
		}

		xmlSaveFormatFileEnc( buff, doc, "utf-8", 1 );
		xmlFreeDoc(doc);
		//xmlCleanupParser();
	}
	else{

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
             node1 = xmlNewChild(node, NULL, BAD_CAST buff2,BAD_CAST "0");
         }
     }

    xmlSaveFormatFileEnc( buff, doc, "utf-8", 1 );
    xmlFreeDoc(doc);
    xmlCleanupParser();
	}
}
stru* copie(stru *haribo){
	stru *haribo2=malloc(sizeof(stru));
			haribo2->nom_bonne=malloc(sizeof(char)*100);
			haribo2->nom_utilisateur=malloc(sizeof(char)*100);
			haribo2->nom_mauvaise=malloc(sizeof(char*)*100);
			strcpy(haribo2->nom_bonne,haribo->nom_bonne);
			strcpy(haribo2->nom_utilisateur,haribo->nom_utilisateur);
			haribo2->wid=haribo->wid;
	return haribo2;
}

void PasDeDoublon(int nb,int *num_array){
	int visited[NBR_PAYS];
	int count = 0;
	int i,num;
	for ( i = 0; i < NBR_PAYS; i++) {
		visited[i]=0;
		}
	while (count < nb) {
		num = rand()%NBR_PAYS ;
		printf("numero tiré aléatoirement: %d\n  ",num);
		if ( visited[num] != 1 ) {
			visited[num] = 1;
			num_array[count] = num;
			count++;
			printf("ok %d/%d tiré aleatoirement correctement\n",count,nb);
		}
		else{
			printf("non ce nombre a deja été tiré\n");
		}
	}
	for ( i = 0; i < nb; i++) {
		printf("\n%d :",num_array[i]);
		printf(" %s ",getPays(num_array[i]));
	}

}
static gboolean
update_text (gpointer tokyo)
{
	struc *seoul=malloc(sizeof(*seoul));
	seoul=tokyo;
	/*printf("\npython wiki.py %s %s %s",seoul->nom1,seoul->nom2,seoul->nom3);
	char wikipython[500];
	sprintf(wikipython,"python wiki.py %s %s %s",seoul->nom1,seoul->nom2,seoul->nom3);

	 char *pythonIntrepreter="python"; // resolved using your PATH environment variable
		    char *calledPython="./wiki.py"; // explicit path necessary, not resolved using your PATH environment variable
		    char *pythonArgs[]={pythonIntrepreter,calledPython,seoul->nom1,seoul->nom2,seoul->nom3,NULL};
		    execvp(pythonIntrepreter,pythonArgs);
	//system(wikipython);
	//usleep(800000);*/
	gtk_widget_set_tooltip_markup(seoul->wid, liretext(0));
	gtk_widget_set_tooltip_markup(seoul->wid2, liretext(1));
	gtk_widget_set_tooltip_markup(seoul->wid3, liretext(2));

	return FALSE;

}
static gboolean update_text2 (gpointer tokyo){
	struc *seoul=malloc(sizeof(*seoul));
	seoul=tokyo;
	/*char wikipython[5000];
	sprintf(wikipython,"python wiki.py %s %s %s %s %s %s", seoul->nom1,seoul->nom2,seoul->nom3, seoul->nom4, seoul->nom5, seoul->nom6);
	printf("update python wiki.py %s %s %s",seoul->nom1,seoul->nom2,seoul->nom3,seoul->nom4,seoul->nom5,seoul->nom6);
	system(wikipython);
	usleep(800000);*/
	gtk_widget_set_tooltip_markup(seoul->wid, liretext(0));
	gtk_widget_set_tooltip_markup(seoul->wid2, liretext(1));
	gtk_widget_set_tooltip_markup(seoul->wid3, liretext(2));
	gtk_widget_set_tooltip_markup(seoul->wid4, liretext(3));
	gtk_widget_set_tooltip_markup(seoul->wid5, liretext(4));
	gtk_widget_set_tooltip_markup(seoul->wid6, liretext(5));

	return FALSE;
}
static gboolean
update_textsolo (gpointer tokyo)
{
	struc *seoul=malloc(sizeof(*seoul));
	seoul=tokyo;
	gtk_widget_set_tooltip_markup(seoul->wid, liretext(0));

	return FALSE;

}

void fonction_facile(GtkWidget *table99, gpointer user_data){
	int i=rand()%3,k;
	int  tab_intier[3];
	char drapeau_png[500];
	char s0[500],s1[500],s2[500];
	char niveau[50];
	GtkWidget* bouton[3];
	PasDeDoublon(3,tab_intier);
	char *tab_button[3]={strcpy(s0,getPays(tab_intier[0])),strcpy(s1,getPays(tab_intier[1])),strcpy(s2,getPays(tab_intier[2]))};
	char nom_dans_lordre[3][500];
	sprintf(drapeau_png,"drapeau/%s.png",tab_button[0]);

	printf("\nfonction facile tableau de bouton :%s-%s-%s\n",tab_button[0],tab_button[1],tab_button[2]);

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title (GTK_WINDOW (window), "QCM drapeau-facile");
		gtk_window_set_default_size (GTK_WINDOW (window), L_FENETRE, H_FENETRE);
		gtk_container_set_border_width (GTK_CONTAINER (window), 100);
		gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
		gtk_window_set_icon(GTK_WINDOW(window), gdk_pixbuf_new_from_file("battery.png",NULL));

	GtkWidget *table = gtk_table_new (6, 3, TRUE);
		gtk_table_set_col_spacings(GTK_TABLE(table), 20);
		gtk_container_add (GTK_CONTAINER (window), table);

	bouton[1]= gtk_image_new_from_file(drapeau_png);
		gtk_table_attach_defaults (GTK_TABLE (table), bouton[1], 0, 3, 0, 3);

	nom_nombre *london=malloc(sizeof(*london));
		london->nom=malloc(sizeof(char*)*100);
		london=user_data;
		london->nombre++;
	int nbr_niveau_restant=london->nombre;

	sprintf(niveau,"%d/%d",nbr_niveau_restant,NBR_LVL_F);
	GtkWidget *label1 = gtk_label_new(niveau);
		gtk_table_attach_defaults (GTK_TABLE (table), label1, 1, 2, 5, 6);


	stru *haribo=malloc(sizeof(stru));
		haribo->nom_utilisateur=malloc(sizeof(char)*100);
		haribo->nom_bonne=malloc(sizeof(char)*100);
		haribo->nom_mauvaise=malloc(sizeof(char)*100);
		strcpy(haribo->nom_bonne,tab_button[0]);
		strcpy(haribo->nom_utilisateur,london->nom);
		haribo->wid=window;

	stru *haribo2=copie(haribo);
	stru *haribo3=copie(haribo);

	struc *tokyo=malloc(sizeof(struc));

	for(k=0;k<3;k++){
		while(tab_button[i]==0){
				i=rand()%3;
			}

		bouton[k] = gtk_button_new_with_label(tab_button[i]);
		gtk_table_attach_defaults (GTK_TABLE (table), bouton[k], k,k+1, 4, 5);
		strcpy(nom_dans_lordre[k],tab_button[i]);
		if(i==0){
				g_signal_connect(G_OBJECT(bouton[k]), "clicked",G_CALLBACK(bonne_reponse),  haribo);
		}else{
			if(k==0){
				strcpy(haribo->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(bouton[k]), "clicked",G_CALLBACK(mauvaise_reponse),  haribo);
			}
			if(k==1){
				strcpy(haribo2->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(bouton[k]), "clicked",G_CALLBACK(mauvaise_reponse),  haribo2);
			}
			if(k==2){
				strcpy(haribo3->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(bouton[k]), "clicked",G_CALLBACK(mauvaise_reponse),  haribo3);
			}
		}
		tab_button[i]=0;
		if (nbr_niveau_restant<NBR_LVL_F){
			g_signal_connect(G_OBJECT(bouton[k]), "clicked",G_CALLBACK( fonction_facile), london);
		}else{
			g_signal_connect(G_OBJECT(bouton[k]), "clicked",G_CALLBACK( Fin_du_jeu), window);
			london->nombre=0;
		}
		g_signal_connect_swapped(G_OBJECT(bouton[k]), "clicked",G_CALLBACK( gtk_widget_destroy), window);

	}
	printf("fonction facile tableau de bouton dans l'ordre :%s-%s-%s\n",nom_dans_lordre[0],nom_dans_lordre[1],nom_dans_lordre[2]);
	tokyo->wid=bouton[0];tokyo->wid2=bouton[1];tokyo->wid3=bouton[2];
	char wikipython[500];
	sprintf(wikipython,"python wiki.py %s %s %s",nom_dans_lordre[0],nom_dans_lordre[1],nom_dans_lordre[2]);

	if (!system("ping -c 1 8.8.8.8 > /dev/null")){
		system(wikipython);
		g_timeout_add (10, (GSourceFunc)update_text, tokyo);
	}

	gtk_widget_show_all(GTK_WIDGET(window));
}

void fonction_facile2(GtkWidget *table99, gpointer user_data){
	GtkWidget *image,*button;

	int i=rand()%3,k;
	int  tab_intier[3];
	char buffer[500];
	char s0[500],s1[500],s2[500];
	PasDeDoublon(3,tab_intier);
	char *tab_button[3]={strcpy(s0,getPays(tab_intier[0])),strcpy(s1,getPays(tab_intier[1])),strcpy(s2,getPays(tab_intier[2]))};
	char wikipython[500];
	sprintf(wikipython,"python wiki.py %s",tab_button[0]);

	printf("\nfonction facile2 tableau de bouton :%s-%s-%s\n",tab_button[0],tab_button[1],tab_button[2]);

	GtkWidget *table = gtk_table_new ( 2, 2, TRUE);
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "QCM drapeau-facile mode 2");
	gtk_window_set_default_size (GTK_WINDOW (window), L_FENETRE, H_FENETRE);
	gtk_container_set_border_width (GTK_CONTAINER (window), 100);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_icon(GTK_WINDOW(window), gdk_pixbuf_new_from_file("battery.png",NULL));

	gtk_table_set_col_spacings(GTK_TABLE(table), 20);
	gtk_container_add (GTK_CONTAINER (window), table);

	GtkWidget *button0 =gtk_label_new(tab_button[0]);
	gtk_table_attach_defaults (GTK_TABLE (table), button0, 1, 2, 0, 1);

	nom_nombre *london=malloc(sizeof(*london));
	london->nom=malloc(sizeof(char*)*100);
	london=user_data;
	london->nombre++;
	int nbr_niveau_restant=london->nombre;

	stru *haribo=malloc(sizeof(*haribo));
	haribo->nom_bonne=malloc(sizeof(char*)*100);
	haribo->nom_utilisateur=malloc(sizeof(char*)*100);
	haribo->nom_mauvaise=malloc(sizeof(char*)*100);
	strcpy(haribo->nom_bonne,tab_button[0]);
	strcpy(haribo->nom_utilisateur,london->nom);
	haribo->wid=window;

	stru *haribo2=copie(haribo);
	stru *haribo3=copie(haribo);

	for(k=0;k<3;k++){
		while(tab_button[i]==0){
				i=rand()%3;
			}

		sprintf(buffer,"drapeau/%s.png",tab_button[i]);
		image = gtk_image_new_from_file (buffer);
		button = gtk_button_new ();

		gtk_button_set_image (GTK_BUTTON (button), image);
		gtk_table_attach_defaults (GTK_TABLE (table), button, k,k+1, 1, 2);
		if(i==0){
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  haribo);
		}else{
			if(k==0){
				strcpy(haribo->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse2),  haribo);
			}
			if(k==1){
				strcpy(haribo2->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse2),  haribo2);
			}
			if(k==2){
				strcpy(haribo3->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse2),  haribo3);
			}
		}
		tab_button[i]=0;
		if (nbr_niveau_restant<NBR_LVL_F)
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( fonction_facile2), london);
		else{
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( Fin_du_jeu), window);
			london->nombre=0;
			}
		g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window);
	}

	if (!system("ping -c 1 8.8.8.8 > /dev/null")){
		struc *tokyo=malloc(sizeof(struc));
		tokyo->wid=button0;
		system(wikipython);
		g_timeout_add (10, (GSourceFunc)update_textsolo, tokyo);
	}
	gtk_widget_show_all(GTK_WIDGET(window));

	}


void fonction_moyen(GtkWidget *table99,gpointer user_data){
	int i=rand()%6,k;
	int  tab_intier[6];
	PasDeDoublon(6,tab_intier);
	char buffer[500]="";
	char wikipython[50];
	char niveau[50];
	GtkWidget* bouton[6];
	char nom_dans_lordre[6][500];
	char s0[500],s1[500],s2[500],s3[500],s4[500],s5[500];
	char *tab_button[6]={strcpy(s0,getPays(tab_intier[0])),strcpy(s1,getPays(tab_intier[1])),strcpy(s2,getPays(tab_intier[2])),strcpy(s3,getPays(tab_intier[3])),strcpy(s4,getPays(tab_intier[4])),strcpy(s5,getPays(tab_intier[5]))};
	g_snprintf(buffer,500,"drapeau/%s.png",tab_button[0]);

	printf("\nfonction moyenne tableau de bouton :%s  %s  %s  %s  %s  %s\n",tab_button[0],tab_button[1],tab_button[2],tab_button[3],tab_button[4],tab_button[5]);

	GtkWidget *table = gtk_table_new (6, 3, TRUE);
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "QCM drapeau-moyen");
	gtk_window_set_default_size (GTK_WINDOW (window), L_FENETRE, H_FENETRE);
	gtk_container_set_border_width (GTK_CONTAINER (window), 100);
	gtk_window_set_icon(GTK_WINDOW(window), gdk_pixbuf_new_from_file("battery.png",NULL));
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);

	gtk_table_set_col_spacings(GTK_TABLE(table), 20);
	gtk_table_set_row_spacings(GTK_TABLE(table), 20);
	gtk_container_add (GTK_CONTAINER (window), table);


	bouton[0] = gtk_image_new_from_file(buffer);
		gtk_table_attach_defaults (GTK_TABLE (table), bouton[0] , 0, 3, 0, 3);

	nom_nombre *london=malloc(sizeof(*london));
	london->nom=malloc(sizeof(char*)*100);
	london=user_data;
	london->nombre++;
	int nbr_niveau_restant=london->nombre;

	sprintf(niveau,"%d/%d",nbr_niveau_restant,NBR_LVL_M);
	GtkWidget *label1 = gtk_label_new(niveau);
		gtk_table_attach_defaults (GTK_TABLE (table), label1, 1, 2, 6, 7);

	stru *haribo=malloc(sizeof(stru));
	haribo->nom_bonne=malloc(sizeof(char)*100);
	haribo->nom_utilisateur=malloc(sizeof(char)*100);
	haribo->nom_mauvaise=malloc(sizeof(char)*100);
	strcpy(haribo->nom_bonne,tab_button[0]);
	strcpy(haribo->nom_utilisateur,london->nom);
	haribo->wid=window;
	stru *haribo2=copie(haribo);stru *haribo3=copie(haribo);
	stru *haribo4=copie(haribo);stru *haribo5=copie(haribo);
	stru *haribo6=copie(haribo);


	for(k=0;k<3;k++){
		while(tab_button[i]==0){
			i=rand()%6;
		}
		bouton[k]  = gtk_button_new_with_label(tab_button[i]);
		gtk_table_attach_defaults (GTK_TABLE (table), bouton[k] , k,k+1, 4, 5);
		strcpy(nom_dans_lordre[k],tab_button[i]);
		if(i==0){
			if(k==0)
				g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK(bonne_reponse),  haribo);
			if(k==1)
				g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK(bonne_reponse),  haribo2);
			if(k==2)
				g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK(bonne_reponse),  haribo3);
		}else{
			if(k==0){
				strcpy(haribo->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK(mauvaise_reponse),  haribo);
			}
			if(k==1){
				strcpy(haribo2->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK(mauvaise_reponse),  haribo2);
			}
			if(k==2){
				strcpy(haribo3->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK(mauvaise_reponse),  haribo3);
			}
		}
		tab_button[i]=0;
		if (nbr_niveau_restant<NBR_LVL_M)
			g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK( fonction_moyen), london);
		else{
			g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK( Fin_du_jeu), window);
			london->nombre=0;
		}
		g_signal_connect_swapped(G_OBJECT(bouton[k]), "clicked",G_CALLBACK( gtk_widget_destroy), window);
	}

	for(k=0;k<3;k++){
		while(tab_button[i]==0){
				i=rand()%6;
			}
		bouton[k+3] = gtk_button_new_with_label(tab_button[i]);
		gtk_table_attach_defaults (GTK_TABLE (table), bouton[k+3], k,k+1, 5, 6);
		strcpy(nom_dans_lordre[k+3],tab_button[i]);
		if(i==0){
			if(k==0)
				g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK(bonne_reponse),  haribo4);
			if(k==1)
				g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK(bonne_reponse),  haribo5);
			if(k==2)
				g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK(bonne_reponse),  haribo6);
		}else{
			if(k==0){
				strcpy(haribo4->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK(mauvaise_reponse),  haribo4);
			}
			if(k==1){
				strcpy(haribo5->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK(mauvaise_reponse),  haribo5);
			}
			if(k==2){
				strcpy(haribo6->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK(mauvaise_reponse),  haribo6);
			}
		}
		tab_button[i]=0;
		if (nbr_niveau_restant<NBR_LVL_M)
			g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK( fonction_moyen), london);
		else{
			g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK( Fin_du_jeu), window);
			london->nombre=0;
		}
		g_signal_connect_swapped(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK( gtk_widget_destroy), window);
	}

	if (!system("ping -c 1 8.8.8.8 > /dev/null")){
		struc *tokyo=malloc(sizeof(struc));
		tokyo->wid=bouton[0];tokyo->wid2=bouton[1];tokyo->wid3=bouton[2];
		tokyo->wid4=bouton[3];tokyo->wid5=bouton[4];tokyo->wid6=bouton[5];
		sprintf(wikipython,"python wiki.py %s %s %s %s %s %s",nom_dans_lordre[0],nom_dans_lordre[1],nom_dans_lordre[2],nom_dans_lordre[3],nom_dans_lordre[4],nom_dans_lordre[5]);
		system(wikipython);
		g_timeout_add (10, (GSourceFunc)update_text2, tokyo);
	}

	gtk_widget_show_all(GTK_WIDGET(window));
}

void fonction_moyen2(GtkWidget *table99,gpointer user_data){
	int i=rand()%6,k;
	GtkWidget *image;
	int  tab_intier[6];
	PasDeDoublon(6,tab_intier);
	char buffer[500]="";
	char s0[500],s1[500],s2[500],s3[500],s4[500],s5[500];
	char *tab_button[6]={strcpy(s0,getPays(tab_intier[0])),strcpy(s1,getPays(tab_intier[1])),strcpy(s2,getPays(tab_intier[2])),strcpy(s3,getPays(tab_intier[3])),strcpy(s4,getPays(tab_intier[4])),strcpy(s5,getPays(tab_intier[5]))};
	g_snprintf(buffer,500,"drapeau/%s.png",tab_button[0]);
	printf("\nfonction facile tableau de bouton :%s  %s  %s  %s  %s  %s\n",tab_button[0],tab_button[1],tab_button[2],tab_button[3],tab_button[4],tab_button[5]);

	GtkWidget *table = gtk_table_new (3, 3, TRUE);
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "QCM drapeau-moyen mode 2");
	gtk_window_set_default_size (GTK_WINDOW (window), L_FENETRE, H_FENETRE);
	gtk_container_set_border_width (GTK_CONTAINER (window), 100);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_icon(GTK_WINDOW(window), gdk_pixbuf_new_from_file("battery.png",NULL));

	gtk_table_set_col_spacings(GTK_TABLE(table), 20);
	gtk_table_set_row_spacings(GTK_TABLE(table), 20);
	gtk_container_add (GTK_CONTAINER (window), table);


	GtkWidget *button = gtk_label_new(tab_button[0]);
	gtk_table_attach_defaults (GTK_TABLE (table), button, 1, 2, 0, 1);

	nom_nombre *london=malloc(sizeof(*london));
	london->nom=malloc(sizeof(char*)*100);
	london=user_data;
	london->nombre++;
	int nbr_niveau_restant=london->nombre;

	stru *haribo=malloc(sizeof(*haribo));
	haribo->nom_bonne=malloc(sizeof(char*)*100);
	haribo->nom_utilisateur=malloc(sizeof(char*)*100);
	haribo->nom_mauvaise=malloc(sizeof(char*)*100);
	strcpy(haribo->nom_bonne,tab_button[0]);
	strcpy(haribo->nom_utilisateur,london->nom);
	haribo->wid=window;

	stru *haribo2=copie(haribo);stru *haribo3=copie(haribo);
	stru *haribo4=copie(haribo);stru *haribo5=copie(haribo);
	stru *haribo6=copie(haribo);

	for(k=0;k<3;k++){
		while(tab_button[i]==0){
			i=rand()%6;
		}
		g_snprintf(buffer,500,"drapeau/%s.png",tab_button[i]);
		image = gtk_image_new_from_file (buffer);
		button = gtk_button_new ();

		gtk_button_set_image (GTK_BUTTON (button), image);

		gtk_table_attach_defaults (GTK_TABLE (table), button, k,k+1, 1, 2);
		if(i==0){
			if(k==0)
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  haribo);
			if(k==1)
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  haribo2);
			if(k==2)
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  haribo3);
		}else{
			if(k==0){
				strcpy(haribo->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse2),  haribo);
			}
			if(k==1){
				strcpy(haribo2->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse2),  haribo2);
			}
			if(k==2){
				strcpy(haribo3->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse2),  haribo3);
			}
		}
		tab_button[i]=0;
		if (nbr_niveau_restant<NBR_LVL_M)
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( fonction_moyen2), london);
		else{
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( Fin_du_jeu), window);
			london->nombre=0;
		}
		g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window);
	}

	for(k=0;k<3;k++){
		while(tab_button[i]==0){
			i=rand()%6;
		}
		g_snprintf(buffer,500,"drapeau/%s.png",tab_button[i]);
		image = gtk_image_new_from_file (buffer);
		button = gtk_button_new ();


		gtk_button_set_image (GTK_BUTTON (button), image);

		gtk_table_attach_defaults (GTK_TABLE (table), button, k,k+1, 2, 3);
		if(i==0){
			if(k==0)
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  haribo4);
			if(k==1)
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  haribo5);
			if(k==2)
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  haribo6);
		}else{
			if(k==0){
				strcpy(haribo->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse2),  haribo4);
			}
			if(k==1){
				strcpy(haribo2->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse2),  haribo5);
			}
			if(k==2){
				strcpy(haribo3->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse2),  haribo6);
			}
		}
		tab_button[i]=0;
		if (nbr_niveau_restant<NBR_LVL_M)
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( fonction_moyen2), london);
		else{
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( Fin_du_jeu), window);
			london->nombre=0;
		}
		g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window);
	}

	gtk_widget_show_all(GTK_WIDGET(window));
}

void fonction_moyenIA(GtkWidget *table99,gpointer user_data){
printf("ENTREE DANS MOYEN IA \n");
	int i=rand()%6,k;
	int  tab_intier[6];
	char buffer[500]="";
	char wikipython[50], niveau[10];
	GtkWidget* bouton[6];
	char nom_dans_lordre[6][500];
	char s0[500],s1[500],s2[500],s3[500],s4[500],s5[500];

	nom_nombre *london=malloc(sizeof(nom_nombre));
		london->nom=malloc(sizeof(char)*100);
		london=user_data;
		float temp[NBR_PAYS][NBR_PAYS];
		copie_matrice(london->mat_similitude,temp);
		affiche(london->mat_similitude);
		printf("\nslt\n");
		london->nombre++;
		int nbr_niveau_restant=london->nombre;

	int numero_drapeau = rand()%NBR_PAYS;
	printf("Drapeau numéro %d \n",numero_drapeau);
	moyen(temp,numero_drapeau,tab_intier);
	affiche_ligne_int(tab_intier);

	char *tab_button[6]={strcpy(s0,getPays(tab_intier[0])),strcpy(s1,getPays(tab_intier[1])),strcpy(s2,getPays(tab_intier[2])),strcpy(s3,getPays(tab_intier[3])),strcpy(s4,getPays(tab_intier[4])),strcpy(s5,getPays(tab_intier[5]))};
	g_snprintf(buffer,500,"drapeau/%s.png",tab_button[0]);

	printf("\nfonction moyenneIA tableau de bouton :%s  %s  %s  %s  %s  %s\n",tab_button[0],tab_button[1],tab_button[2],tab_button[3],tab_button[4],tab_button[5]);

	GtkWidget *table = gtk_table_new (6, 3, TRUE);
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "QCM drapeau-moyenIA");
	gtk_window_set_default_size (GTK_WINDOW (window), L_FENETRE, H_FENETRE);
	gtk_container_set_border_width (GTK_CONTAINER (window), 100);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
	gtk_window_set_icon(GTK_WINDOW(window), gdk_pixbuf_new_from_file("battery.png",NULL));

	gtk_table_set_col_spacings(GTK_TABLE(table), 20);
	gtk_table_set_row_spacings(GTK_TABLE(table), 20);
	gtk_container_add (GTK_CONTAINER (window), table);

	bouton[0] = gtk_image_new_from_file(buffer);
		gtk_table_attach_defaults (GTK_TABLE (table), bouton[0] , 0, 3, 0, 3);


	stru *haribo=malloc(sizeof(*haribo));
		haribo->nom_bonne=malloc(sizeof(char*)*100);
		haribo->nom_utilisateur=malloc(sizeof(char*)*100);
		haribo->nom_mauvaise=malloc(sizeof(char*)*100);
		strcpy(haribo->nom_bonne,tab_button[0]);
		strcpy(haribo->nom_utilisateur,london->nom);
		haribo->wid=window;

	stru *haribo2=copie(haribo);stru *haribo3=copie(haribo);
	stru *haribo4=copie(haribo);stru *haribo5=copie(haribo);
	stru *haribo6=copie(haribo);

	sprintf(niveau,"%d/%d",nbr_niveau_restant,NBR_LVL_M);
	GtkWidget *label1 = gtk_label_new(niveau);
		gtk_table_attach_defaults (GTK_TABLE (table), label1, 1, 2, 6, 7);


	for(k=0;k<3;k++){
		while(tab_button[i]==0){
			i=rand()%6;
		}
		bouton[k]  = gtk_button_new_with_label(tab_button[i]);
		gtk_table_attach_defaults (GTK_TABLE (table), bouton[k] , k,k+1, 4, 5);
		strcpy(nom_dans_lordre[k],tab_button[i]);
		if(i==0){
			if(k==0)
				g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK(bonne_reponse),  haribo);
			if(k==1)
				g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK(bonne_reponse),  haribo2);
			if(k==2)
				g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK(bonne_reponse),  haribo3);
		}else{
			if(k==0){
				strcpy(haribo->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK(mauvaise_reponse),  haribo);
			}
			if(k==1){
				strcpy(haribo2->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK(mauvaise_reponse),  haribo2);
			}
			if(k==2){
				strcpy(haribo3->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK(mauvaise_reponse),  haribo3);
			}
		}
		tab_button[i]=0;
		if (nbr_niveau_restant<NBR_LVL_M)
			g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK( fonction_moyen), london);
		else{
			g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK( Fin_du_jeu), window);
			london->nombre=0;
		}
		g_signal_connect_swapped(G_OBJECT(bouton[k]), "clicked",G_CALLBACK( gtk_widget_destroy), window);
	}

	for(k=0;k<3;k++){
		while(tab_button[i]==0){
				i=rand()%6;
			}
		bouton[k+3] = gtk_button_new_with_label(tab_button[i]);
		gtk_table_attach_defaults (GTK_TABLE (table), bouton[k+3], k,k+1, 5, 6);
		strcpy(nom_dans_lordre[k+3],tab_button[i]);
		if(i==0){
			if(k==0)
				g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK(bonne_reponse),  haribo4);
			if(k==1)
				g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK(bonne_reponse),  haribo5);
			if(k==2)
				g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK(bonne_reponse),  haribo6);
		}else{
			if(k==0){
				strcpy(haribo4->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK(mauvaise_reponse),  haribo4);
			}
			if(k==1){
				strcpy(haribo5->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK(mauvaise_reponse),  haribo5);
			}
			if(k==2){
				strcpy(haribo6->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK(mauvaise_reponse),  haribo6);
			}
		}
		tab_button[i]=0;
		if (nbr_niveau_restant<NBR_LVL_M)
			g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK( fonction_moyen), london);
		else{
			g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK( Fin_du_jeu), window);
			london->nombre=0;
		}
		g_signal_connect_swapped(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK( gtk_widget_destroy), window);
	}
	if (!system("ping -c 1 8.8.8.8 > /dev/null")){
		struc *tokyo=malloc(sizeof(*tokyo));
		tokyo->wid=bouton[0];tokyo->wid2=bouton[1];tokyo->wid3=bouton[2];
		tokyo->wid4=bouton[3];tokyo->wid5=bouton[4];tokyo->wid6=bouton[5];
		sprintf(wikipython,"python wiki.py %s %s %s %s %s %s",nom_dans_lordre[0],nom_dans_lordre[1],nom_dans_lordre[2],nom_dans_lordre[3],nom_dans_lordre[4],nom_dans_lordre[5]);
		system(wikipython);
		g_timeout_add (800, (GSourceFunc)update_text2, tokyo);
	}

	gtk_widget_show_all(GTK_WIDGET(window));
}
void fonction_moyenIA2(GtkWidget *table99,gpointer user_data){
	int i=rand()%6,k;
	GtkWidget *image;
	int  tab_intier[6];
	PasDeDoublon(6,tab_intier);
	char buffer[500]="";
	char s0[500],s1[500],s2[500],s3[500],s4[500],s5[500];
	char *tab_button[6]={strcpy(s0,getPays(tab_intier[0])),strcpy(s1,getPays(tab_intier[1])),strcpy(s2,getPays(tab_intier[2])),strcpy(s3,getPays(tab_intier[3])),strcpy(s4,getPays(tab_intier[4])),strcpy(s5,getPays(tab_intier[5]))};
	g_snprintf(buffer,500,"drapeau/%s.png",tab_button[0]);
	printf("\nfonction facile tableau de bouton :%s  %s  %s  %s  %s  %s\n",tab_button[0],tab_button[1],tab_button[2],tab_button[3],tab_button[4],tab_button[5]);

	GtkWidget *table = gtk_table_new (3, 3, TRUE);
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "QCM drapeau-medium");
	gtk_window_set_default_size (GTK_WINDOW (window), L_FENETRE, H_FENETRE);
	gtk_container_set_border_width (GTK_CONTAINER (window), 100);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);

	gtk_table_set_col_spacings(GTK_TABLE(table), 20);
	gtk_table_set_row_spacings(GTK_TABLE(table), 20);
	gtk_container_add (GTK_CONTAINER (window), table);


	GtkWidget *button = gtk_label_new(tab_button[0]);
	gtk_table_attach_defaults (GTK_TABLE (table), button, 1, 2, 0, 1);

	nom_nombre *london=malloc(sizeof(*london));
	london->nom=malloc(sizeof(char*)*100);
	london=user_data;
	london->nombre++;
	int nbr_niveau_restant=london->nombre;

	stru *haribo=malloc(sizeof(*haribo));
	haribo->nom_bonne=malloc(sizeof(char*)*100);
	haribo->nom_utilisateur=malloc(sizeof(char*)*100);
	haribo->nom_mauvaise=malloc(sizeof(char*)*100);
	strcpy(haribo->nom_bonne,tab_button[0]);
	strcpy(haribo->nom_utilisateur,london->nom);
	haribo->wid=window;

	stru *haribo2=copie(haribo);
	stru *haribo3=copie(haribo);
	stru *haribo4=copie(haribo);
	stru *haribo5=copie(haribo);
	stru *haribo6=copie(haribo);

	for(k=0;k<3;k++){
		while(tab_button[i]==0){
			i=rand()%6;
		}
		g_snprintf(buffer,500,"drapeau/%s.png",tab_button[i]);
		image = gtk_image_new_from_file (buffer);
		button = gtk_button_new ();

		gtk_button_set_image (GTK_BUTTON (button), image);

		gtk_table_attach_defaults (GTK_TABLE (table), button, k,k+1, 1, 2);
		if(i==0){
			if(k==0)
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  haribo);
			if(k==1)
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  haribo2);
			if(k==2)
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  haribo3);
		}else{
			if(k==0){
				strcpy(haribo->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse2),  haribo);
			}
			if(k==1){
				strcpy(haribo2->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse2),  haribo2);
			}
			if(k==2){
				strcpy(haribo3->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse2),  haribo3);
			}
		}
		tab_button[i]=0;
		if (nbr_niveau_restant<NBR_LVL_M)
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( fonction_moyen2), london);
		else{
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( Fin_du_jeu), window);
			london->nombre=0;
		}
		g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window);
	}

	for(k=0;k<3;k++){
		while(tab_button[i]==0){
			i=rand()%6;
		}
		g_snprintf(buffer,500,"drapeau/%s.png",tab_button[i]);
		image = gtk_image_new_from_file (buffer);
		button = gtk_button_new ();


		gtk_button_set_image (GTK_BUTTON (button), image);

		gtk_table_attach_defaults (GTK_TABLE (table), button, k,k+1, 2, 3);
		if(i==0){
			if(k==0)
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  haribo);
			if(k==1)
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  haribo2);
			if(k==2)
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(bonne_reponse),  haribo3);
		}else{
			if(k==0){
				strcpy(haribo->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse2),  haribo);
			}
			if(k==1){
				strcpy(haribo2->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse2),  haribo2);
			}
			if(k==2){
				strcpy(haribo3->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(mauvaise_reponse2),  haribo3);
			}
		}
		tab_button[i]=0;
		if (nbr_niveau_restant<NBR_LVL_M)
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( fonction_moyen2), london);
		else{
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK( Fin_du_jeu), window);
			london->nombre=0;
		}
		g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_destroy), window);
	}

	gtk_widget_show_all(GTK_WIDGET(window));
}
void fonction_difficileIA(GtkWidget *table99,gpointer user_data){
	printf("ENTREE DANS DIFFICIKE IA \n");
	int i=rand()%6,k;
	int  tab_intier[6];
	char buffer[500]="";
	char wikipython[50],niveau[10];
	GtkWidget* bouton[6];
	char nom_dans_lordre[6][500];
	char s0[500],s1[500],s2[500],s3[500],s4[500],s5[500];

	nom_nombre *london=malloc(sizeof(nom_nombre));
		london->nom=malloc(sizeof(char)*100);
		london=user_data;
		london->nombre++;
		int nbr_niveau_restant=london->nombre;

	if(nbr_niveau_restant==1){
		char nom_fichier[100];
		sprintf(nom_fichier,"%s.xml",london->nom);
		printf("nom du fichier %s \n",nom_fichier);

		liste_matrice *mat_moy=lirematrice(nom_fichier);
		float mat_similitude[NBR_PAYS][NBR_PAYS];
		matrice_moyenne(mat_moy,mat_similitude);
		similitude(mat_similitude);
		printf("\n");
		copie_matrice(mat_similitude,london->mat_similitude);
		affiche(london->mat_similitude);
		//tagada->mat_similitude=mat_similitude;
		printf("\n");
		printf("TEST ENTREE IA \n");
	}

	int numero_drapeau = rand()%NBR_PAYS;
	printf("Drapeau numéro %d \n",numero_drapeau);
	difficile(london->mat_similitude[numero_drapeau],numero_drapeau,tab_intier);
	affiche_ligne_int(tab_intier);

	char *tab_button[6]={strcpy(s0,getPays(tab_intier[0])),strcpy(s1,getPays(tab_intier[1])),strcpy(s2,getPays(tab_intier[2])),strcpy(s3,getPays(tab_intier[3])),strcpy(s4,getPays(tab_intier[4])),strcpy(s5,getPays(tab_intier[5]))};
	g_snprintf(buffer,500,"drapeau/%s.png",tab_button[0]);

	printf("\nfonction difficile tableau de bouton :%s  %s  %s  %s  %s  %s\n",tab_button[0],tab_button[1],tab_button[2],tab_button[3],tab_button[4],tab_button[5]);

	GtkWidget *table = gtk_table_new (6, 3, TRUE);
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (window), "QCM drapeau-difficileIA");
	gtk_window_set_default_size (GTK_WINDOW (window), L_FENETRE, H_FENETRE);
	gtk_container_set_border_width (GTK_CONTAINER (window), 100);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);

	gtk_table_set_col_spacings(GTK_TABLE(table), 20);
	gtk_table_set_row_spacings(GTK_TABLE(table), 20);
	gtk_container_add (GTK_CONTAINER (window), table);

	bouton[0] = gtk_image_new_from_file(buffer);
		gtk_table_attach_defaults (GTK_TABLE (table), bouton[0] , 0, 3, 0, 3);

	sprintf(niveau,"%d/%d",nbr_niveau_restant,NBR_LVL_M);
	GtkWidget *label1 = gtk_label_new(niveau);
		gtk_table_attach_defaults (GTK_TABLE (table), label1, 1, 2, 6, 7);

	stru *haribo=malloc(sizeof(stru));
	haribo->nom_bonne=malloc(sizeof(char)*100);
	haribo->nom_utilisateur=malloc(sizeof(char)*100);
	haribo->nom_mauvaise=malloc(sizeof(char)*100);
	strcpy(haribo->nom_bonne,tab_button[0]);
	strcpy(haribo->nom_utilisateur,london->nom);
	haribo->wid=window;
	stru *haribo2=copie(haribo);stru *haribo3=copie(haribo);
	stru *haribo4=copie(haribo);stru *haribo5=copie(haribo);
	stru *haribo6=copie(haribo);


	for(k=0;k<3;k++){
		while(tab_button[i]==0){
			i=rand()%6;
		}
		bouton[k]  = gtk_button_new_with_label(tab_button[i]);
		gtk_table_attach_defaults (GTK_TABLE (table), bouton[k] , k,k+1, 4, 5);
		strcpy(nom_dans_lordre[k],tab_button[i]);
		if(i==0){
			if(k==0)
				g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK(bonne_reponse),  haribo);
			if(k==1)
				g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK(bonne_reponse),  haribo2);
			if(k==2)
				g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK(bonne_reponse),  haribo3);
		}else{
			if(k==0){
				strcpy(haribo->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK(mauvaise_reponse),  haribo);
			}
			if(k==1){
				strcpy(haribo2->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK(mauvaise_reponse),  haribo2);
			}
			if(k==2){
				strcpy(haribo3->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK(mauvaise_reponse),  haribo3);
			}
		}
		tab_button[i]=0;
		if (nbr_niveau_restant<NBR_LVL_M)
			g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK( fonction_difficileIA), london);
		else{
			g_signal_connect(G_OBJECT(bouton[k] ), "clicked",G_CALLBACK( Fin_du_jeu), window);
			london->nombre=0;
		}
		g_signal_connect_swapped(G_OBJECT(bouton[k]), "clicked",G_CALLBACK( gtk_widget_destroy), window);
	}

	for(k=0;k<3;k++){
		while(tab_button[i]==0){
				i=rand()%6;
			}
		bouton[k+3] = gtk_button_new_with_label(tab_button[i]);
		gtk_table_attach_defaults (GTK_TABLE (table), bouton[k+3], k,k+1, 5, 6);
		strcpy(nom_dans_lordre[k+3],tab_button[i]);
		if(i==0){
			if(k==0)
				g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK(bonne_reponse),  haribo4);
			if(k==1)
				g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK(bonne_reponse),  haribo5);
			if(k==2)
				g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK(bonne_reponse),  haribo6);
		}else{
			if(k==0){
				strcpy(haribo4->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK(mauvaise_reponse),  haribo4);
			}
			if(k==1){
				strcpy(haribo5->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK(mauvaise_reponse),  haribo5);
			}
			if(k==2){
				strcpy(haribo6->nom_mauvaise,tab_button[i]);
				g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK(mauvaise_reponse),  haribo6);
			}
		}
		tab_button[i]=0;
		if (nbr_niveau_restant<NBR_LVL_M)
			g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK( fonction_difficileIA), london);
		else{
			g_signal_connect(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK( Fin_du_jeu), window);
			london->nombre=0;
		}
		g_signal_connect_swapped(G_OBJECT(bouton[k+3]), "clicked",G_CALLBACK( gtk_widget_destroy), window);
	}

	if (!system("ping -c 1 8.8.8.8 > /dev/null")){
		struc *tokyo=malloc(sizeof(struc));
		tokyo->wid=bouton[0];tokyo->wid2=bouton[1];tokyo->wid3=bouton[2];
		tokyo->wid4=bouton[3];tokyo->wid5=bouton[4];tokyo->wid6=bouton[5];
		sprintf(wikipython,"python wiki.py %s %s %s %s %s %s",nom_dans_lordre[0],nom_dans_lordre[1],nom_dans_lordre[2],nom_dans_lordre[3],nom_dans_lordre[4],nom_dans_lordre[5]);
		system(wikipython);
		g_timeout_add (10, (GSourceFunc)update_text2, tokyo);
	}

	gtk_widget_show_all(GTK_WIDGET(window));
}

int compte_matrices(char*pseudo){
	int nbr_matrice=0;
	char nom_fichier[100];
	sprintf(nom_fichier,"%s.xml",pseudo);
	xmlTextReaderPtr reader = xmlReaderForFile(nom_fichier, NULL, 0);

	if(reader!=NULL){
		char adresse[100];
		sprintf(adresse,"/%s/matrice",pseudo);
		xmlDoc *doc = xmlParseFile(nom_fichier);
		xmlXPathContext *xpathCtx = xmlXPathNewContext( doc );
		xmlXPathObject * xpathObj =xmlXPathEvalExpression( (xmlChar*)adresse, xpathCtx );
		nbr_matrice= xmlXPathNodeSetGetLength(xpathObj->nodesetval);
		printf("le nombre de matrice est %d \n",nbr_matrice);
		xmlXPathFreeObject( xpathObj );
			xmlXPathFreeContext( xpathCtx );
			xmlFreeDoc( doc );
			xmlCleanupParser();
	}
	return nbr_matrice;
}

void Choix_niveaux(GtkWidget *table,gpointer user_data){
	stru *london=malloc(sizeof(*london));
	london=user_data;
	nom_nombre *tagada=malloc(sizeof(*tagada));
	tagada->nom=malloc(sizeof(char*)*100);
	strcpy(tagada->nom,london->nom_bonne);
	tagada->nombre=0;
	tagada->wid=london->wid;

	int nbr_matrice=0;
	char nom_fichier[100];
	sprintf(nom_fichier,"%s.xml",tagada->nom);
	xmlTextReaderPtr reader = xmlReaderForFile(nom_fichier, NULL, 0);

	if(reader!=NULL){
		char adresse[100];
		sprintf(adresse,"/%s/matrice",tagada->nom);
		xmlDoc *doc = xmlParseFile(nom_fichier);
		xmlXPathContext *xpathCtx = xmlXPathNewContext( doc );
		xmlXPathObject * xpathObj =xmlXPathEvalExpression( (xmlChar*)adresse, xpathCtx );
		nbr_matrice= xmlXPathNodeSetGetLength(xpathObj->nodesetval);
		printf("le nombre de matrice est %d \n",nbr_matrice);
	}
	printf("choix niveau\nle pseudo entré est: %s\n-------\n",(char*)(tagada->nom));

	GtkWidget *window0 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title (GTK_WINDOW (window0), "QCM drapeau-choix de la difficulté");
		gtk_window_set_default_size (GTK_WINDOW (window0), L_FENETRE, H_FENETRE);
		gtk_container_set_border_width (GTK_CONTAINER (window0), 5);
		gtk_window_set_position(GTK_WINDOW(window0), GTK_WIN_POS_CENTER_ALWAYS);

	GtkWidget *layout = gtk_layout_new(NULL, NULL);
		gtk_container_add(GTK_CONTAINER (window0), layout);

	GtkWidget *image = gtk_image_new_from_file("onu resize.png");
		gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);

	GtkWidget *table0 = gtk_table_new (70, 50, TRUE);
		gtk_table_set_row_spacings(GTK_TABLE(table0), 50);
		gtk_table_set_col_spacings(GTK_TABLE(table0), 20);

	GtkWidget *button = gtk_button_new_with_label ("  niveau facile ");
		gtk_table_attach_defaults (GTK_TABLE (table0), button, 2, 3, 1, 2);
		g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(xml), tagada->nom);
		g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(Choix_niveaux), london);
		g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_hide), window0);
		g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(fonction_facile), tagada);


	GtkWidget *button1;
	/*	if(nbr_matrice>=NBR_IA){
			liste_matrice *mat_moy=lirematrice(nom_fichier);
			float mat_similitude[NBR_PAYS][NBR_PAYS];
			matrice_moyenne(mat_moy,mat_similitude);
			similitude(mat_similitude);
			printf("\n");
			copie_matrice(mat_similitude,tagada->mat_similitude);
			affiche(tagada->mat_similitude);
			//tagada->mat_similitude=mat_similitude;
			printf("\n");
			printf("TEST ENTREE IA \n");
			button1 = gtk_button_new_with_label ("niv moyen IA");
			g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(xml), tagada->nom);
			g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(Choix_niveaux), london);
			g_signal_connect_swapped(G_OBJECT(button1), "clicked",G_CALLBACK( gtk_widget_hide), window0);
			g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(fonction_moyenIA), tagada);
			gtk_table_attach_defaults (GTK_TABLE (table0), button1, 2, 3, 2, 3);
		}else{*/
			button1 = gtk_button_new_with_label ("niveau moyen");
			g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(xml), tagada->nom);
			g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(Choix_niveaux), london);
			g_signal_connect_swapped(G_OBJECT(button1), "clicked",G_CALLBACK( gtk_widget_hide), window0);
			g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(fonction_moyen), tagada);
			gtk_table_attach_defaults (GTK_TABLE (table0), button1, 2, 3, 2, 3);
		//}

		if(nbr_matrice>=NBR_IA){

			GtkWidget *button2 = gtk_button_new_with_label ("niv difficile IA");
			g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(xml), tagada->nom);
			g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(Choix_niveaux), london);
			g_signal_connect_swapped(G_OBJECT(button1), "clicked",G_CALLBACK( gtk_widget_hide), window0);
			g_signal_connect(G_OBJECT(button2), "clicked",G_CALLBACK(fonction_difficileIA), tagada);
			gtk_table_attach_defaults (GTK_TABLE (table0), button2, 2, 3, 3, 4);
		}


	GtkWidget *button3=gtk_button_new_with_label ("retour");
		gtk_table_attach_defaults (GTK_TABLE (table0), button3,  1, 4, 4, 5);
		g_signal_connect_swapped(G_OBJECT(button3), "clicked",G_CALLBACK( gtk_widget_show), tagada->wid);
		g_signal_connect_swapped(G_OBJECT(button3), "clicked",G_CALLBACK( gtk_widget_destroy), window0);

	g_signal_connect(window0, "destroy",G_CALLBACK( gtk_widget_destroy), window0);

	gtk_container_add (GTK_CONTAINER (layout), table0);
	gtk_window_set_resizable (GTK_WINDOW(window0), FALSE);
	gtk_widget_set_size_request (window0, L_FENETRE, H_FENETRE);
	gtk_widget_show_all(GTK_WIDGET(window0));


}


void Choix_niveaux2(GtkWidget *table,gpointer user_data){
	stru *london=malloc(sizeof(*london));
		london=user_data;
		nom_nombre *tagada=malloc(sizeof(*tagada));
		tagada->nom=malloc(sizeof(char*)*100);
		strcpy(tagada->nom,london->nom_bonne);
		tagada->nombre=0;
		tagada->wid=london->wid;

		int nbr_matrice=0;
		char nom_fichier[100];
		sprintf(nom_fichier,"%s.xml",tagada->nom);
		xmlTextReaderPtr reader = xmlReaderForFile(nom_fichier, NULL, 0);

		if(reader!=NULL){
			char adresse[100];
			sprintf(adresse,"/%s/matrice",tagada->nom);
			xmlDoc *doc = xmlParseFile(nom_fichier);
			xmlXPathContext *xpathCtx = xmlXPathNewContext( doc );
			xmlXPathObject * xpathObj =xmlXPathEvalExpression( (xmlChar*)adresse, xpathCtx );
			nbr_matrice= xmlXPathNodeSetGetLength(xpathObj->nodesetval);
			printf("le nombre de matrice est %d \n",nbr_matrice);
		}
		printf("choix niveau\nle pseudo entré est: %s\n-------\n",(char*)(tagada->nom));

		GtkWidget *window0 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
			gtk_window_set_title (GTK_WINDOW (window0), "QCM drapeau-choix de la difficulté mode 2");
			gtk_window_set_default_size (GTK_WINDOW (window0), L_FENETRE, H_FENETRE);
			gtk_container_set_border_width (GTK_CONTAINER (window0), 5);
			gtk_window_set_position(GTK_WINDOW(window0), GTK_WIN_POS_CENTER_ALWAYS);

		GtkWidget *layout = gtk_layout_new(NULL, NULL);
			gtk_container_add(GTK_CONTAINER (window0), layout);

		GtkWidget *image = gtk_image_new_from_file("onu resize.png");
			gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);

		GtkWidget *table0 = gtk_table_new (70, 50, TRUE);
			gtk_table_set_row_spacings(GTK_TABLE(table0), 50);
			gtk_table_set_col_spacings(GTK_TABLE(table0), 20);

		GtkWidget *button = gtk_button_new_with_label ("  niveau facile ");
			gtk_table_attach_defaults (GTK_TABLE (table0), button, 2, 3, 1, 2);
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(xml), tagada->nom);
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(Choix_niveaux2), london);
			g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_hide), window0);
			g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(fonction_facile2), tagada);


		GtkWidget *button1;
			if(nbr_matrice>=NBR_IA){
				liste_matrice *mat_moy=lirematrice(nom_fichier);
				float mat_similitude[NBR_PAYS][NBR_PAYS];
				matrice_moyenne(mat_moy,mat_similitude);
				similitude(mat_similitude);
				printf("\n");
				copie_matrice(mat_similitude,tagada->mat_similitude);
				affiche(tagada->mat_similitude);
				//tagada->mat_similitude=mat_similitude;
				printf("\n");
				printf("TEST ENTREE IA \n");
				button1 = gtk_button_new_with_label ("niv moyen IA");
				g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(Choix_niveaux2), london);
				g_signal_connect_swapped(G_OBJECT(button1), "clicked",G_CALLBACK( gtk_widget_hide), window0);
				g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(fonction_moyenIA2), tagada);
				g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(xml), tagada->nom);
				gtk_table_attach_defaults (GTK_TABLE (table0), button1, 2, 3, 2, 3);
			}else{
				button1 = gtk_button_new_with_label ("niveau moyen");
				g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(xml), tagada->nom);
				g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(Choix_niveaux2), london);
				g_signal_connect_swapped(G_OBJECT(button1), "clicked",G_CALLBACK( gtk_widget_hide), window0);
				g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(fonction_moyen2), tagada);
				gtk_table_attach_defaults (GTK_TABLE (table0), button1, 2, 3, 2, 3);
			}

		GtkWidget *button2;
			if(nbr_matrice>=NBR_IA){
				g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(xml), tagada->nom);
				g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(Choix_niveaux2), london);
				g_signal_connect_swapped(G_OBJECT(button1), "clicked",G_CALLBACK( gtk_widget_hide), window0);
				g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(fonction_difficileIA), tagada);
				gtk_table_attach_defaults (GTK_TABLE (table0), button2, 2, 3, 3, 4);
			}


		GtkWidget *button3=gtk_button_new_with_label ("retour");
				gtk_table_attach_defaults (GTK_TABLE (table0), button3,  1, 4, 4, 5);
				g_signal_connect_swapped(G_OBJECT(button3), "clicked",G_CALLBACK( gtk_widget_show), tagada->wid);
				g_signal_connect_swapped(G_OBJECT(button3), "clicked",G_CALLBACK( gtk_widget_destroy), window0);

		g_signal_connect(window0, "destroy",G_CALLBACK( gtk_widget_destroy), window0);

		gtk_container_add (GTK_CONTAINER (layout), table0);
		gtk_window_set_resizable (GTK_WINDOW(window0), FALSE);
		gtk_widget_set_size_request (window0, L_FENETRE, H_FENETRE);
		gtk_widget_show_all(GTK_WIDGET(window0));
}

void Afficher_Statistique(char* name,char* pseudo){
	char buffer[500];
	char buffer2[500];
	char buffer3[500];
	sprintf(buffer, "drapeau/%s.png", name);
	int indice_pays = strtoint(name);
	sprintf(buffer2, "il s'agit de %s, vous le confondez avec : ",  name);

	char nom_fichier[100];
	sprintf(nom_fichier,"%s.xml", pseudo);
	liste_matrice *mat_moy=lirematrice(nom_fichier);
	float mat_similitude[NBR_PAYS][NBR_PAYS];
	matrice_moyenne(mat_moy,mat_similitude);
	similitude(mat_similitude);
	int  tab_intier[6];float temp[NBR_PAYS][NBR_PAYS];
	difficile(temp[indice_pays],indice_pays,tab_intier);
	affiche_ligne_int(tab_intier);

	GtkWidget *table = gtk_table_new (5, 3, TRUE);
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title (GTK_WINDOW (window), "QCM afficher_statistique");
		gtk_window_set_default_size (GTK_WINDOW (window), L_FENETRE, H_FENETRE);
		gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
		gtk_container_add (GTK_CONTAINER (window), table);

	GtkWidget *button = gtk_image_new_from_file(buffer);
		gtk_table_attach_defaults (GTK_TABLE (table), button, 0, 3, 1, 2);
	GtkWidget *label1 = gtk_label_new(buffer2);
		gtk_table_attach_defaults (GTK_TABLE (table), label1, 0, 3, 2, 3);

	sprintf(buffer, "drapeau/%s.png", getPays(tab_intier[0]));
	GtkWidget *button2 = gtk_image_new_from_file(buffer);
			gtk_table_attach_defaults (GTK_TABLE (table), button2, 0, 1, 3, 4);
label1 = gtk_label_new(getPays(tab_intier[0]));
			gtk_table_attach_defaults (GTK_TABLE (table), label1, 0, 1, 4, 5);

	sprintf(buffer, "drapeau/%s.png", getPays(tab_intier[1]));
	button2 = gtk_image_new_from_file(buffer);
			gtk_table_attach_defaults (GTK_TABLE (table), button2, 1, 2, 3, 4);
			label1 = gtk_label_new(getPays(tab_intier[1]));
						gtk_table_attach_defaults (GTK_TABLE (table), label1, 1, 2, 4, 5);

	sprintf(buffer, "drapeau/%s.png", getPays(tab_intier[2]));
	button2 = gtk_image_new_from_file(buffer);
			gtk_table_attach_defaults (GTK_TABLE (table), button2, 2, 3, 3, 4);

		label1 = gtk_label_new(getPays(tab_intier[2]));
									gtk_table_attach_defaults (GTK_TABLE (table), label1, 2, 3, 4, 5);

	gtk_widget_show_all(GTK_WIDGET(window));
}

void Statistique(GtkWidget *table,gpointer user_data){
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
		gtk_window_set_title(GTK_WINDOW(window), "Statistique ");
		gtk_window_set_default_size (GTK_WINDOW (window), L_FENETRE, H_FENETRE);
		gtk_window_set_icon(GTK_WINDOW(window), gdk_pixbuf_new_from_file("battery.png",NULL));
		printf("statistique\nle pseudo entré est: %s\n-------\n",user_data);

	GtkWidget *view = create_view_and_model(user_data);
	GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL, NULL);
		gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_ALWAYS, GTK_POLICY_NEVER);
		gtk_container_add (GTK_CONTAINER(scrolled_window), view);

	GtkWidget *hbox = gtk_hbox_new(FALSE, 0);
		gtk_container_add (GTK_CONTAINER (hbox), scrolled_window);
		gtk_container_add (GTK_CONTAINER (window), hbox);

	gtk_widget_set_size_request (window, L_FENETRE, H_FENETRE);
	gtk_widget_show_all(window);
}

void Apropos(GtkWidget *widget, gpointer data) {
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("battery.png", NULL);
	GtkWidget *dialog = gtk_about_dialog_new();
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "4.0");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),"Youssef KADHI");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog),"apprendre les drapeaux du monde ");
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog),"https://github.com/Yurof/QCM");
	gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), pixbuf);
	g_object_unref(pixbuf), pixbuf = NULL;
	gtk_dialog_run(GTK_DIALOG (dialog));
	gtk_widget_destroy(dialog);


}
void Menu_principal2(GtkWidget *table,gpointer user_data){
		Menu_principal(table,user_data);
}

void Choix_orientation(GtkWidget *table,gpointer user_data){

	stru *london=malloc(sizeof(*london));
	london=user_data;
	nom_nombre *tagada=malloc(sizeof(*tagada));
		tagada->nom=malloc(sizeof(char*)*100);
		strcpy(tagada->nom,london->nom_bonne);
		tagada->nombre=0;
		tagada->wid=london->wid;

	gint x, y;
	gtk_window_get_position(GTK_WINDOW(tagada->wid), &x, &y);

	printf("choix orientation\nle pseudo entré est: %s\n-------\n",(char*)(london->nom_bonne));

	GtkWidget *window0 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title (GTK_WINDOW (window0), "QCM Choix du mode de jeu");
		gtk_window_set_default_size (GTK_WINDOW (window0), L_FENETRE, H_FENETRE);
		gtk_container_set_border_width (GTK_CONTAINER (window0), 5);
		 gtk_window_move(GTK_WINDOW(window0), x, y);
		//gtk_window_set_position(GTK_WINDOW(window0), GTK_WIN_POS_CENTER_ALWAYS);
		gtk_window_set_icon(GTK_WINDOW(window0), gdk_pixbuf_new_from_file("battery.png",NULL));
		london->wid=window0;

	GtkWidget *layout = gtk_layout_new(NULL, NULL);
		gtk_container_add(GTK_CONTAINER (window0), layout);

	GtkWidget *image = gtk_image_new_from_file("onu resize.png");
		gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);

	GtkWidget *table0 = gtk_table_new (7, 5, TRUE);
		gtk_table_set_row_spacings(GTK_TABLE(table0), 50);
		gtk_table_set_col_spacings(GTK_TABLE(table0), 20);

	GtkWidget *button2=gtk_button_new_with_label ("retour");
		gtk_table_attach_defaults (GTK_TABLE (table0), button2,  1, 4, 4, 5);
		g_signal_connect(G_OBJECT(button2), "clicked",G_CALLBACK(Menu_principal2), london->nom_bonne);
		g_signal_connect_swapped(G_OBJECT(button2), "clicked",G_CALLBACK( gtk_widget_destroy), window0);

	GtkWidget *button = gtk_button_new_with_label ("pays");
		gtk_table_attach_defaults (GTK_TABLE (table0), button, 2, 3, 1, 2);
		g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(Choix_niveaux), london);
		g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_hide), window0);

	GtkWidget *button1 = gtk_button_new_with_label ("    drapeaux    ");
		gtk_table_attach_defaults (GTK_TABLE (table0), button1,  2, 3, 2, 3);
		g_signal_connect(G_OBJECT(button1), "clicked",G_CALLBACK(Choix_niveaux2), london);
		g_signal_connect_swapped(G_OBJECT(button1), "clicked",G_CALLBACK( gtk_widget_hide), window0);

	//g_signal_connect(window0, "destroy",G_CALLBACK( gtk_widget_destroy), window0);
	g_signal_connect(tagada->wid, "destroy",G_CALLBACK(gtk_main_quit), NULL);
	//g_signal_connect(window, "destroy",G_CALLBACK(gtk_main_quit), NULL);
	gtk_container_add (GTK_CONTAINER (layout), table0);
	gtk_window_set_resizable (GTK_WINDOW(window0), FALSE);
	gtk_widget_set_size_request (window0, L_FENETRE, H_FENETRE);
	gtk_widget_show_all(GTK_WIDGET(window0));

}

void Menu_principal(GtkWidget *table,gpointer user_data){

	gint width  = gdk_screen_width();
		   gint height = gdk_screen_height();
		   printf("%d %d",width,height);

	printf("Menu_principal\nle pseudo entré est: %s\n-------\n",user_data);

	stru *haribo=malloc(sizeof(*haribo));
		haribo->nom_bonne=malloc(sizeof(char*)*100);
		strcpy(haribo->nom_bonne,user_data);


	GtkWidget *window0 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title (GTK_WINDOW (window0), "QCM Menu principal");

		gtk_window_set_default_size (GTK_WINDOW (window0), width*0.36, height*0.41);
		gtk_container_set_border_width (GTK_CONTAINER (window0), 5);
		gtk_window_set_position(GTK_WINDOW(window0), GTK_WIN_POS_CENTER);
		gtk_window_set_icon(GTK_WINDOW(window0), gdk_pixbuf_new_from_file("battery.png",NULL));

	GtkWidget *layout = gtk_layout_new(NULL, NULL);
		gtk_container_add(GTK_CONTAINER (window0), layout);

		GtkWidget *image = gtk_image_new_from_file("ONU.svg");
		GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file ("ONU.svg", NULL);
			   if (pixbuf == NULL) {
			      g_printerr("Failed to resize image\n");
			      return;
			   }
			   GdkPixbuf *pxbscaled = gdk_pixbuf_scale_simple(pixbuf, width*0.36, height*0.41, GDK_INTERP_BILINEAR);
			   gtk_image_set_from_pixbuf(GTK_IMAGE(image), pxbscaled);
				gtk_layout_put(GTK_LAYOUT(layout), image , 0, 0);

	GtkWidget *table0 = gtk_table_new (7, 5, TRUE);
		gtk_table_set_row_spacings(GTK_TABLE(table0), 50);
		gtk_table_set_col_spacings(GTK_TABLE(table0), 20);

	GtkWidget *button = gtk_button_new_with_label ("  Jouer  ");
		gtk_table_attach_defaults (GTK_TABLE (table0), button,2, 3, 1, 2);
		haribo->wid=window0;
		g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(Choix_orientation),haribo);
		g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_hide), window0);

	GtkWidget *button1 = gtk_button_new_with_label ("statistique");
		gtk_table_attach_defaults (GTK_TABLE (table0), button1,  2, 3, 2, 3);
		g_signal_connect(G_OBJECT(button1),"clicked",G_CALLBACK(Statistique),haribo->nom_bonne);

	GtkWidget *button2 = gtk_button_new_with_label ("    A propos    ");
		gtk_table_attach_defaults (GTK_TABLE (table0), button2,  2, 3, 3, 4);
		g_signal_connect(G_OBJECT(button2),"clicked",G_CALLBACK(Apropos),NULL);

	//g_signal_connect(window0, "destroy",G_CALLBACK( gtk_widget_destroy), window0);

	g_signal_connect(window0, "destroy",G_CALLBACK(gtk_main_quit), NULL);
	gtk_container_add (GTK_CONTAINER (layout), table0);
	gtk_window_set_resizable (GTK_WINDOW(window0), FALSE);
	//gtk_widget_set_size_request (window0, L_FENETRE, H_FENETRE);
	gtk_widget_show_all(window0);

}


int main (int argc,char *argv[]){
	srand(time(NULL));
	gtk_init (&argc, &argv);
	GtkWidget *window = NULL;
	   GtkWidget *container = NULL;
	   GdkPixbuf *pixbuf = NULL;
	   gint width  = gdk_screen_width();
	   gint height = gdk_screen_height();
	   printf("%d %d",width,height);

	GtkWidget *window0 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		gtk_window_set_title (GTK_WINDOW (window0), "QCM entrez votre nom");
		gtk_window_set_default_size (GTK_WINDOW (window0), width*0.36, height*0.41);
		gtk_container_set_border_width (GTK_CONTAINER (window0), 5);
		gtk_window_set_position(GTK_WINDOW(window0), GTK_WIN_POS_CENTER_ALWAYS);

	GtkWidget *layout = gtk_layout_new(NULL, NULL);
		gtk_container_add(GTK_CONTAINER (window0), layout);
		gtk_widget_show(layout);

	GtkWidget *image = gtk_image_new_from_file("ONU.svg");
	 pixbuf = gdk_pixbuf_new_from_file ("ONU.svg", NULL);
	   if (pixbuf == NULL) {
	      g_printerr("Failed to resize image\n");
	      return 1;
	   }
	   GdkPixbuf *pxbscaled = gdk_pixbuf_scale_simple(pixbuf, width*0.36, height*0.41, GDK_INTERP_BILINEAR);
	   gtk_image_set_from_pixbuf(GTK_IMAGE(image), pxbscaled);
		gtk_layout_put(GTK_LAYOUT(layout), image , 0, 0);

	GtkWidget *label1 = gtk_label_new(" Entrez votre nom svp :");
		gtk_layout_put(GTK_LAYOUT(layout), label1, 270, 50);
		gtk_widget_set_size_request(label1, 80, 35);

	GtkWidget *entry=gtk_entry_new_with_buffer (gtk_entry_buffer_new("pseudo", -1));;
		gtk_layout_put(GTK_LAYOUT(layout), entry, 265, 150);
		gtk_widget_set_size_request(entry, 80, 35);
		gtk_window_set_icon(GTK_WINDOW(window0), gdk_pixbuf_new_from_file("battery.png",NULL));

	GtkWidget *button=gtk_toggle_button_new_with_label("Valider");
		gtk_layout_put(GTK_LAYOUT(layout), button, 270, 250);
		gtk_widget_set_size_request(button, 160, 35);
		g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(Menu_principal),gtk_entry_get_text(GTK_ENTRY(entry)));
		g_signal_connect_swapped(G_OBJECT(button), "clicked",G_CALLBACK( gtk_widget_hide), window0);

	g_signal_connect(window0, "destroy",G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all (window0);
	//gtk_window_set_resizable (GTK_WINDOW(window0), FALSE);
	//gtk_widget_set_size_request (window0, L_FENETRE, H_FENETRE);
	gtk_main ();

	return 0;

}

