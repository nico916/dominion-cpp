#include "../include/Carte.h"
#include <iostream>
#include <iomanip>

/*
 * Constructeur par défaut de la classe Carte.
 * @param nom Le nom de la carte.
 * @param prix Le prix de la carte.
 * @param type Le type de la carte.
 */
Carte::Carte(const std::string& nom, int prix, std::string type) : nom(nom), prix(prix), type(type) {}

/*
 * Constructeur de copie de la classe Carte.
 * @param autre L'objet Carte à copier.
 */
Carte::Carte(const Carte& autre) : nom(autre.nom), prix(autre.prix), type(autre.type) {}

/*
 * Constructeur de déplacement de la classe Carte.
 * @param autre L'objet Carte à déplacer.
 */
Carte::Carte(Carte&& autre) noexcept : nom(std::move(autre.nom)), prix(autre.prix), type(std::move(autre.type)) {}

/*
 * Obtient le nom de la carte.
 * @return Le nom de la carte.
 */
std::string Carte::getNom() const {
    return nom;
}

/*
 * Obtient le prix de la carte.
 * @return Le prix de la carte.
 */
int Carte::getPrix() const {
    return prix;
}

/*
 * Obtient le type de la carte.
 * @return Le type de la carte.
 */
std::string Carte::getType() const {
    return type;
}

/*
 * Affiche les informations de la carte.
 */
void Carte::Afficher() const {
    const std::string RESET = "\033[0m";
    const std::string GREEN = "\033[92m";
    const std::string YELLOW = "\033[93m";
    const std::string PURPLE = "\033[95m";
    const std::string RED = "\033[91m";
    std::string couleur;

    // Détermine la couleur du texte en fonction du type de la carte
    if (type == "victoire") {
        couleur = GREEN;
    } else if (type == "malediction") {
        couleur = PURPLE;
    } else if (type == "tresor") {
        couleur = YELLOW;
    } else if (type == "action") {
        couleur = RED;
    }

    // Affiche les informations de la carte avec la couleur appropriée
    std::cout << couleur << " - Nom : " << getNom() << " | Prix : " << getPrix() << " | Type : " << getType() << RESET;
}
