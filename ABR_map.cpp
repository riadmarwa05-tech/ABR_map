#include <iostream>
#include <chrono>
#include <map>
using namespace std;


struct Node {
    int valeur;
    Node* gauche;
    Node* droite;

    Node(int v) {
        valeur = v;
        gauche = nullptr;
        droite = nullptr;
    }
};


Node* inserer(Node* racine, int v) {
    if (racine == nullptr) {
        return new Node(v);                          // place libre
    }
    if (v < racine->valeur) {
        racine->gauche = inserer(racine->gauche, v); // à gauche
    } else {
        racine->droite = inserer(racine->droite, v); // à droite
    }
    return racine;
}

void afficher(Node* racine) {
    if (racine == nullptr) return;
    afficher(racine->gauche);
    cout << racine->valeur << " ";
    afficher(racine->droite);
}


int hauteur(Node* racine) {
    if (racine == nullptr) return 0;

    int hG = hauteur(racine->gauche);
    int hD = hauteur(racine->droite);

    if (hG > hD) return 1 + hG;
    else         return 1 + hD;
}

//   Recherche naïve 
bool rechercher(Node* racine, int v) {
    if (racine == nullptr) return false;
    if (v == racine->valeur) return true;
    if (v < racine->valeur)
        return rechercher(racine->gauche, v);
    else
        return rechercher(racine->droite, v);
}




int main() {

    //  PARTIE A : nombres de 1 à 10 
    cout << "===== PARTIE A : 1 a 10 =====" << endl;

    Node* racine = nullptr;
    for (int i = 1; i <= 10; i++) {
        racine = inserer(racine, i);
    }

    cout << "Affichage : ";
    afficher(racine);
    cout << endl;

    cout << "Hauteur : " << hauteur(racine) << endl;

    if (rechercher(racine, 7)) cout << "7 trouve" << endl;
    else cout << "7 non trouve" << endl;

    if (rechercher(racine, 50)) cout << "50 trouve" << endl;
    else cout << "50 non trouve" << endl;


    //  PARTIE B : nombres de 1 à 1000 (arbre naïf) 
    cout << endl << "===== PARTIE B : 1 a 1000 (arbre naif) =====" << endl;

    Node* racine2 = nullptr;
    for (int i = 1; i <= 1000; i++) {
        racine2 = inserer(racine2, i);
    }

    cout << "Hauteur de l'arbre : " << hauteur(racine2) << endl;

    auto debut = chrono::high_resolution_clock::now();

    bool trouve = false;
    for (int k = 0; k < 1000; k++) {      
        trouve = rechercher(racine2, 1000);
    }

    auto fin = chrono::high_resolution_clock::now();
    auto duree = chrono::duration_cast<chrono::microseconds>(fin - debut);

    cout << "Recherche de 1000 : " << (trouve ? "trouve" : "non trouve") << endl;
    cout << "Temps (arbre naif) : " << duree.count() << " microsecondes" << endl;


    //  PARTIE C : même recherche avec map 
    cout << endl << "===== PARTIE C : avec map =====" << endl;

    map<int, bool> m;
    for (int i = 1; i <= 1000; i++) {
        m[i] = true;
    }

    auto debut2 = chrono::high_resolution_clock::now();

    bool trouve2 = false;
    for (int k = 0; k < 1000; k++) {
        trouve2 = (m.find(1000) != m.end());
    }

    auto fin2 = chrono::high_resolution_clock::now();
    auto duree2 = chrono::duration_cast<chrono::microseconds>(fin2 - debut2);

    cout << "Recherche de 1000 : " << (trouve2 ? "trouve" : "non trouve") << endl;
    cout << "Temps (map) : " << duree2.count() << " microsecondes" << endl;

    return 0;
}