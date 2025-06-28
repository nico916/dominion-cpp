#ifndef CARTEMALEDICTION_H
#define CARTEMALEDICTION_H
#include <iostream>
#include "Carte.h"

/*
 * Classe repr�sentant une carte de type Malediction.
 * H�rite de la classe de base Carte.
 */
class CarteMalediction : public Carte
{
    public:
        /*
         * Constructeur de la classe CarteMalediction.
         * @param nom Le nom de la carte.
         * @param prix Le prix de la carte.
         * @param type Le type de la carte.
         * @param penalite La p�nalit� associ�e � la carte Malediction.
         */
        CarteMalediction(const std::string& nom, int prix, std::string type, int penalite);

        /*
         * Destructeur virtuel par d�faut.
         */
        virtual ~CarteMalediction() = default;

        int getPenalite() const;

        /*
         * Affiche les informations de la carte Malediction.
         * Override de la fonction Afficher de la classe de base Carte.
         */
        virtual void Afficher() const override;

    private:
        int penalite;  // La p�nalit� associ�e � la carte Malediction.
};

#endif // CARTEMALEDICTION_H
