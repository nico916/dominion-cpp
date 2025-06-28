#ifndef CARTETRESOR_H
#define CARTETRESOR_H

#include <iostream>
#include "Carte.h"

/*
 * Classe représentant une carte trésor qui hérite de la classe Carte.
 */
class CarteTresor : public Carte {
public:

    /*
     * Constructeur de la classe CarteTresor.
     * @param nom Le nom de la carte.
     * @param prix Le prix de la carte.
     * @param type Le type de la carte.
     * @param valeur La valeur de la carte tresor.
     */
    CarteTresor(const std::string& nom, int prix, std::string type, int valeur);

    /*
     * Destructeur virtuel par défaut.
     */
    virtual ~CarteTresor() = default;
    int getValeur() const;

    /*
     * Affiche les informations de la carte Tresor.
     * Override de la fonction Afficher de la classe de base Carte.
     */
    virtual void Afficher() const override;

private:
    int valeur;  // La valeur specifique à la carte tresor.
};

#endif // CARTETRESOR_H

