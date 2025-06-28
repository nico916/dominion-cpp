#include "../include/Joueur.h"
#include <iostream>
#include <vector>
#include "../include/Carte.h"
#include <memory>
#include "../include/PlateauJeu.h"
#include <algorithm>
#include <random>
#include <chrono>
#include "../include/CarteTresor.h"
#include "../include/CarteVictoire.h"
#include "../include/CarteMalediction.h"
#include "../include/CarteAction.h"



int Joueur::nmbAchat  = 1 ;
int Joueur::nmbActions = 1;


/*
 * Constructeur de la classe Joueur.
 * @param nom Le nom du joueur.
 */
Joueur::Joueur(const std::string& nom): nom(nom){}

/*
 * Obtient le nom du joueur.
 * @return Le nom du joueur.
 */
std::string Joueur::getNom() const {
    return nom;
}

/*
 * Obtient le deck du joueur.
 * @return Le deck du joueur.
 */
std::vector<std::shared_ptr<Carte>> Joueur::getCarteDeck() const {
    return deck;
}

/*
 * Obtient la main du joueur.
 * @return La main du joueur.
 */
std::vector<std::shared_ptr<Carte>> Joueur::getCarteMain() const {
    return main;
}

/*
 * Obtient la defausse du joueur.
 * @return La defausse du joueur.
 */
std::vector<std::shared_ptr<Carte>> Joueur::getCarteDefausse() const {
    return defausse;
}

/*
 * Ajoute une carte au deck.
 * @param carte La carte à ajouter.
 */
void Joueur::ajouterCarteDeck(std::shared_ptr<Carte> carte) {
    deck.push_back(carte);

}

/*
 * Modifie le nom du joueur.
 * @param n Le nouveau nom du joueur.
 */
void Joueur::setNom(std::string n){
    nom=n;
}

/*
 * Ajoute une carte à la defausse.
 * @param carte La carte à ajouter.
 */
void Joueur::ajouterCarteDefausse(std::shared_ptr<Carte> carte) {
        defausse.push_back(carte);
}

/*
 * Mélange les cartes du deck.
 */
void Joueur::MelangerCartes(){
        // Obtient un nombre aléatoire basé sur l'horloge système
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        // Crée une une séquence de nombres qui est déterminée par une valeur initiale
        std::mt19937 g(seed);
        // Mélange les cartes dans la pile de cartes du joueur en utilisant le générateur
        std::shuffle(deck.begin(), deck.end(), g);
}

/*
 * Mélange les cartes de la defausse.
 */
void Joueur::MelangerCartes2() {
     // Obtient un nombre aléatoire basé sur l'horloge système
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    // Créeune une séquence de nombres qui est déterminée par une valeur initiale
    std::mt19937 g(seed);
    // Mélange les cartes dans la pile de cartes défaussées du joueur en utilisant le générateur
    std::shuffle(defausse.begin(), defausse.end(), g);
}

/*
 * Ajoute la dernière carte du deck à la main du joueur, si le deck n'est pas vide.
 */
void Joueur::ajouterCarteMain() {

    if (!deck.empty()) {
        std::shared_ptr<Carte> derniereCarte = deck.back();
        main.push_back(derniereCarte);
    }
}

/*
 * Ajoute une carte à la main du joueur.
 * @param carte La carte à ajouter à la main.
 */
void Joueur::ajouterCarteMain2(std::shared_ptr<Carte> carte) {
        main.push_back(carte);
}

/*
 * Retire la dernière carte du deck du joueur, si le deck n'est pas vide.
 * Si le deck est vide, mélange les cartes de la défausse, puis vider la defausse dans le deck
 */
void Joueur::retirerCarteDeck() {
    if (!deck.empty()) {
        // Retire la dernière carte du deck
        auto it = deck.end() - 1;
        deck.erase(it);
    } else {
        // Mélange les cartes de la défausse dans le deck
        while (!defausse.empty()) {
            MelangerCartes2();
            ajouterCarteDeck(defausse.back());
            retirerCarteDefausse();
        }
        // Ajoute la carte du deck qui n'avait pas pu être ajouté du fait que le deck était vide
        ajouterCarteMain();
        // Retire une carte du deck
        retirerCarteDeck();
    }
}

/*
 * Modifie le nombre d'achats du joueur en ajoutant la valeur spécifiée.
 * @param n La valeur à ajouter au nombre d'achats.
 */
void Joueur::setNmbAchat(int n) {
    Joueur::nmbAchat += n;
}

/*
 * Modifie le nombre d'actions du joueur en ajoutant la valeur spécifiée.
 * @param n La valeur à ajouter au nombre d'actions.
 */
void Joueur::setNmbAction(int n) {
    Joueur::nmbActions += n;
}

/*
 * Renvoie le nombre d'achats actuel du joueur.
 * @return Le nombre d'achats du joueur.
 */
int Joueur::getnmbAchat() {
    return Joueur::nmbAchat;
}

/*
 * Renvoie le nombre d'actions actuel du joueur.
 * @return Le nombre d'actions du joueur.
 */
int Joueur::getnmbAction() {
    return Joueur::nmbActions;
}

/*
 * Retire la carte spécifiée de la main du joueur.
 * @param carte La carte à retirer de la main.
 */
void Joueur::retirerCarteMain(std::shared_ptr<Carte> carte)  {
    auto it = std::find_if(main.begin(), main.end(),
                            [&carte](const auto& elem) {
                                    return elem && carte && elem->getNom() == carte->getNom();
                               });
    main.erase(it);
}
/*
 * Retire la dernière carte de la défausse du joueur.
 */
void Joueur::retirerCarteDefausse()  {
    auto it = defausse.end() - 1;
    defausse.erase(it);
}

/*
 * Ajoute la carte spécifiée à la défausse du joueur depuis le plateau de jeu.
 * @param carte La carte à ajouter à la défausse.
 */
void Joueur::ajouterCarteDefausseDepuisPlateau(std::shared_ptr<Carte> carte) {
    defausse.push_back(carte);

}

/*
 * Affiche les informations des cartes restantes dans la collection spécifiée, y compris les trésors, actions,maledictions et cartes victoires.
 * @param cartes La collection de cartes à afficher.
 */
void Joueur::AfficherCartesRestantes2(const std::vector<std::shared_ptr<Carte>>& cartes) const {

    for (const auto& cartePtr : cartes) {
        if (auto carteTresorPtr = std::dynamic_pointer_cast<CarteTresor>(cartePtr)) {
            carteTresorPtr->Afficher();

        } else if (auto carteActionPtr = std::dynamic_pointer_cast<CarteAction>(cartePtr)) {
            carteActionPtr->Afficher();
        } else if (auto carteMaledictionPtr = std::dynamic_pointer_cast<CarteMalediction>(cartePtr)) {
            carteMaledictionPtr->Afficher();
        } else if (auto carteVictoirePtr = std::dynamic_pointer_cast<CarteVictoire>(cartePtr)) {
            carteVictoirePtr->Afficher();

        }
    }

}

/*
 * Affiche les informations des cartes trésors restantes dans la collection spécifiée.
 * @param cartes La collection de cartes trésors à afficher.
 */
void Joueur::AfficherCartesRestantesTresor(const std::vector<std::shared_ptr<Carte>>& cartes) const {
    for (const auto& cartePtr : cartes) {
        if (auto carteTresorPtr = std::dynamic_pointer_cast<CarteTresor>(cartePtr)) {
            carteTresorPtr->Afficher();
        }
    }
}

/*
 * Retourne la taille de la main du joueur.
 * @return La taille de la main du joueur.
 */
int Joueur::getSizeMain() const {
    return main.size();
}
