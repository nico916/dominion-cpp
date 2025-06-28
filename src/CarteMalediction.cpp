#include "../include/CarteMalediction.h"

/*
 * Constructeur de la classe CarteMalediction.
 * @param nom Le nom de la carte.
 * @param prix Le prix de la carte.
 * @param type Le type de la carte.
 * @param penalite La p�nalit� associ�e � la carte Malediction.
 */
CarteMalediction::CarteMalediction(const std::string& nom, int prix, std::string type, int penalite): Carte(nom, prix, type), penalite(penalite) {}

/*
 * Obtient la p�nalit� associ�e � la carte Malediction.
 * @return La p�nalit� associ�e � la carte Malediction.
 */
int CarteMalediction::getPenalite() const {
    return penalite;
}

/*
 * Affiche les informations de la carte Malediction.
 */
void CarteMalediction::Afficher() const {
    Carte::Afficher();
    const std::string RESET = "\033[0m";
    const std::string PURPLE = "\033[95m";
    std::cout << PURPLE << " | P�nalit� : " << getPenalite() << RESET << std::endl;
}
