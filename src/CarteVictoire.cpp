#include "../include/CarteVictoire.h"

/*
 * Constructeur de la classe CarteVictoire.
 * @param nom Le nom de la carte.
 * @param prix Le prix de la carte.
 * @param type Le type de la carte.
 * @param points Les points de victoire associés à la carte.
 */
CarteVictoire::CarteVictoire(const std::string& nom, int prix, std::string type, int points): Carte(nom, prix, type), points(points) {}

/*
 * Obtient les points de victoire de la carte.
 * @return Les points de victoire de la carte.
 */
int CarteVictoire::getPoints() const {
    return points;
}

/*
 * Affiche les informations de la carte victoire.
 */
void CarteVictoire::Afficher() const {
    Carte::Afficher();
    const std::string RESET = "\033[0m";
    const std::string GREEN = "\033[92m";
    std::cout << GREEN << " | Points : " << getPoints() << RESET << std::endl;
}
