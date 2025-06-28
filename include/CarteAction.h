#ifndef CARTEACTION_H
#define CARTEACTION_H
#include <iostream>
#include "Carte.h"
#include "Joueur.h"
#include "PlateauJeu.h"

/*
 * Classe représentant une carte de type Action.
 * Hérite de la classe de base Carte.
 */
class CarteAction : public Carte
{
    public:

    /*
        * Constructeur de la classe CarteTresor.
        * @param nom Le nom de la carte.
        * @param prix Le prix de la carte.
        * @param type Le type de la carte.
        * @param valeur La valeur de la carte tresor.
        */
        CarteAction(const std::string& nom, int prix, std::string type , int nbActions);

        /*
         * Destructeur virtuel par défaut.
         */
        virtual ~CarteAction()=default;

        int getNbActions() const;
        virtual void Afficher() const override ;
        void executerActionCave(std::shared_ptr<Joueur> j);
        void executerActionBucheron(std::shared_ptr<Joueur> j);
        void executerActionVillage(std::shared_ptr<Joueur> j);
        void executerActionChapelle(std::shared_ptr<Joueur> j);
        void executerActionMarche(std::shared_ptr<Joueur> j);
        int executerActionRenovation(std::shared_ptr<Joueur> j);
        void executerActionForgeron(std::shared_ptr<Joueur> j);
        int executerActionMine(std::shared_ptr<Joueur> j);
        void executerActionSorciere(std::shared_ptr<Joueur> j);
        void executerActionSorciere2(std::shared_ptr<Joueur> j, PlateauJeu* pj);
        void executerActionFestin(std::shared_ptr<Joueur> j);
        void executerActionFestival(std::shared_ptr<Joueur> j);
        void executerActionLaboratoire(std::shared_ptr<Joueur> j);
        bool executerActionPreteurSurGages(std::shared_ptr<Joueur> j);
        void executerActionChancelier(std::shared_ptr<Joueur> j);
        void executerActionBibliotheque(std::shared_ptr<Joueur> j);
        void executerActionChambreDuConseil (std::shared_ptr<Joueur>j);
        void executerActionEspion (std::shared_ptr<Joueur>j);
        void executerActionAventurier(std::shared_ptr<Joueur> j);
        void executerActionMilice(std::shared_ptr<Joueur> j,PlateauJeu* pj);

    private:
        int nbActions;
};

#endif // CARTEACTION_H



