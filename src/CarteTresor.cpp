#include "../include/CarteTresor.h"

/*
 * Constructeur de la classe CarteTresor.
 * @param nom Le nom de la carte.
 * @param prix Le prix de la carte.
 * @param type Le type de la carte.
 * @param valeur La valeur de la carte tr�sor.
 */
CarteTresor::CarteTresor(const std::string& nom, int prix, std::string type, int valeur) : Carte(nom, prix, type), valeur(valeur) {}

/*
 * Obtient la valeur de la carte tr�sor.
 * @return La valeur de la carte tr�sor.
 */
int CarteTresor::getValeur() const {
    return valeur;
}

/*
 * Affiche les informations de la carte tr�sor.
 */
void CarteTresor::Afficher() const {
    Carte::Afficher();  // Appel de la classe de base (Carte) avec la methode Afficher
    const std::string RESET = "\033[0m";
    const std::string YELLOW = "\033[93m";
    std::cout << YELLOW << " | Valeur : " << getValeur() << RESET << std::endl;
}
