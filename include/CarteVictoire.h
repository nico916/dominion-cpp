#ifndef CARTEVICTOIRE_H
#define CARTEVICTOIRE_H

#include <iostream>
#include "Carte.h"

/*
 * Classe d�finissant une carte de type "Victoire" h�ritant de la classe Carte.
 */
class CarteVictoire : public Carte
{
    public:
        /*
         * Constructeur de la classe CarteVictoire.
         * @param nom Le nom de la carte.
         * @param prix Le prix de la carte.
         * @param type Le type de la carte.
         * @param points Les points de victoire associ�s � la carte.
         */
        CarteVictoire(const std::string& nom, int prix, std::string type, int points);

        /*
         * Destructeur virtuel par d�faut.
         */
        virtual ~CarteVictoire() = default;


        int getPoints() const;

        /*
         * Affiche les informations de la carte Victoire.
         * Override de la fonction Afficher de la classe de base Carte.
         */
        virtual void Afficher() const override;

    private:
        int points;  // Points de victoire associ�s � la carte.
};

#endif // CARTEVICTOIRE_H
