#include <gtk/gtk.h>


typedef struct Noeud {
    int info;
    struct Noeud *pred;
    struct Noeud *suiv;
} Noeud;

Noeud* creerNoeud(int data) {
    Noeud* nvNoeud = (Noeud*)malloc(sizeof(Noeud));
    nvNoeud->info = data;
    nvNoeud->pred = NULL;
    nvNoeud->suiv = NULL;
    return nvNoeud;
}

// fonction tae trie 
Noeud* Bulle(Noeud *tete) {
    int permut, temp;
    Noeud *p1;
    Noeud *p2 = NULL;

    if (tete == NULL)
        return tete;

    do {
        permut = 0;
        p1 = tete;

        while (p1->suiv != p2) {
            if (p1->info > p1->suiv->info) {
                temp = p1->info;
                p1->info = p1->suiv->info;
                p1->suiv->info = temp;
                permut = 1;
            }
            p1 = p1->suiv;
        }
        p2 = p1;
    } while (permut);

    return tete;
}

// Fonction afficher b gtk
void afficherListe(Noeud *tete) {
    GtkWidget *fenetre, *etiquette, *vbox;

    
    gtk_init(NULL, NULL);

    
    fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(fenetre), "Liste Triée");
    gtk_window_set_default_size(GTK_WINDOW(fenetre), 300, 100);

    g_signal_connect(fenetre, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    
    vbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_add(GTK_CONTAINER(fenetre), vbox);

    
    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(cssProvider,
        "window { background-color: #000000; color: #ffffff; }", -1, NULL);
    
    GtkStyleContext *styleContext = gtk_widget_get_style_context(fenetre);
    gtk_style_context_add_provider(styleContext,
        GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    
    Noeud *courant = tete;
    while (courant->suiv != NULL) {
        etiquette = gtk_label_new(g_strdup_printf("%d <-> ", courant->info));

        gtk_box_pack_start(GTK_BOX(vbox), etiquette, FALSE, FALSE, 0);
        courant = courant->suiv;
    }
	etiquette = gtk_label_new(g_strdup_printf("%d", courant->info));

        gtk_box_pack_start(GTK_BOX(vbox), etiquette, FALSE, FALSE, 0);

    
    gtk_widget_show_all(fenetre);

    
    gtk_main();
}

int main() {
    Noeud *T = NULL;
    Noeud *Q;

    
    int num_elements;
    printf("Entrez le nombre d'elements : ");
    scanf("%d", &num_elements);

    
    for (int i = 1; i <= num_elements; ++i) {
        int value;
        printf("Entrez le %de entier : ", i);
        scanf("%d", &value);

        Noeud *nvNoeud = creerNoeud(value);
        if (T == NULL) {
            T = nvNoeud;
            T->pred = NULL;
        } else {
            // Ajouter à la fin de la liste
            Q = T;
            while (Q->suiv != NULL) {
                Q = Q->suiv;
            }
            Q->suiv = nvNoeud;
            nvNoeud->pred = Q;
            nvNoeud->suiv = NULL;
        }
    }

    
    T = Bulle(T);

    
    afficherListe(T);

    
    Noeud *courant = T;
    while (courant != NULL) {
        Noeud *suivant = courant->suiv;
        free(courant);
        courant = suivant;
    }

    return 0;
}
