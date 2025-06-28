#ifndef PLATEAUJEU_H
#define PLATEAUJEU_H

#include <map>
#include "../include/Carte.h"
#include <vector>
#include <iostream>
#include "../include/CarteTresor.h"
#include <memory>
#include "Joueur.h"



class PlateauJeu
{
    private:
        std::vector<std::shared_ptr<Carte>> cartes; //Vecteur contenant toutes les cartes du Plateau de Jeu
        std::vector<std::shared_ptr<Carte>> cartes2; //Vecteur contenant toutes les cartes du Plateau de Jeu qui ne contient qu'une seule  occurence de chaque carte.
        std::vector<std::shared_ptr<Joueur>> Joueurs;// Vecteur contenant tous les joueurs
        int nbJoueur;// nombre de Joueur
        static bool isFirstCall;// Booleen pour savoir si c'est le premier appel de MettreDansCSV
        static bool sauvegarde;// Booleen pour savoir si le joueur veut sauvegarder
        int tour; // tour actuel
        bool IAB;// Booléen pour savoir s'il y a un IA
        //Map avec tous les noms des cartes actions et un boolééen pour savoir si elles doivent être ajoutées au Plateau de Jeu
        std::map<std::string, bool> MapAction = {
            {"Village", false},
            {"Renovation", false},
            {"Mine", false},
            {"Marche", false},
            {"Forgeron", false},
            {"Chapelle", false},
            {"Atelier", false},
            {"Bucheron", false},
            {"Sorciere", false},
            {"Cave", false},
            {"Festin", false},
            {"Festival", false},
            {"Laboratoire", false},
            {"Chancelier", false},
            {"Bibliotheque", false},
            {"ChambreDuConseil", false},
            {"Espion", false},
            {"Aventurier", false},
            {"Voleur", false},
            {"Milice", false},
            {"PreteurSurGages", false}
        };


    public:
        PlateauJeu();
        ~PlateauJeu();
        void ajouterCarte(std::shared_ptr<Carte> nouvelleCarte) ;
        void ajouterCarte2(std::shared_ptr<Carte> nouvelleCarte) ;
        void LireCartesDepuisCSV(const std::string& filename, int n);
        void AfficherCartesRestantes(const std::vector<std::shared_ptr<Carte>>& cartes) const;
        std::vector<std::shared_ptr<Carte>> getCartes();
        std::vector<std::shared_ptr<Carte>> getCartes2();
        void RetirerCarte(std::shared_ptr<Carte> carte);
        bool FinDePartie();
        void RetirerCarte2(std::shared_ptr<Carte> carte);
        void EffectuerTour(std::shared_ptr<Joueur> joueur);
        void EffectuerTourIA(std::shared_ptr<Joueur> IA, int tourIA);
        void CreationPartie(std::shared_ptr<Joueur> j);
        void ajouterJoueur(std::shared_ptr<Joueur> j);
        std::vector<std::shared_ptr<Joueur>> getJoueurs();
        int QuiGagne(std::shared_ptr<Joueur> j);
        void MettreDansCSV(std::shared_ptr<Joueur> j, const std::string& filename);
        int getNbjoueur();
        void setNbJoueur(int n);
        bool getSauvegarde();
        int getTour();
        void setTour(int t);
        void RecuperSauvegarde(const std::string& filename);
        void RecuperSauvegarde2(const std::string& filename, std::shared_ptr<Joueur> ,int i);
        std::map<std::string, bool> getMapAction();
        bool setMapAction(std::string nom);
        bool estCarteChoisi( const std::string& carte);
        int CompterCartes (std::string nomCarte);
        bool getIAB();
        void setIAB(bool IAB);
        void retirerCarteMap();
};

#endif // PLATEAUJEU_H
