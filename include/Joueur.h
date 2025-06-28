#ifndef JOUEUR_H
#define JOUEUR_H
#include <iostream>
#include <vector>
#include "Carte.h"
#include <memory>

class Joueur
{

private:

	std::vector<std::shared_ptr<Carte>>deck;//Carte du deck
	std::vector<std::shared_ptr<Carte>>main;// Carte de la main
	std::vector<std::shared_ptr<Carte>> defausse;// Carte de la defausse
    std::string nom;// Nom du Joueur
    static int nmbAchat;// Nombre d'achats du Joueur
    static int nmbActions;// Nombre d'actions du Joueur



public :

    Joueur (const std::string& nom);
    ~Joueur() {;};
    void ajouterCarteDeck(std::shared_ptr<Carte> carte);
    void ajouterCarteMain2(std::shared_ptr<Carte> carte);
    void ajouterCarteMain();
    void ajouterCarteDefausse(std::shared_ptr<Carte> carte);
    void setNmbAchat(int n);
    void setNmbAction(int n);
    void retirerCarteDeck();
    void retirerCarteMain(std::shared_ptr<Carte> carte);
    void retirerCarteDefausse();
    std::vector<std::shared_ptr<Carte>>getCarteDeck() const;
    std::vector<std::shared_ptr<Carte>>getCarteMain() const;
    std::vector<std::shared_ptr<Carte>> getCarteDefausse() const;
    void ajouterCarteDefausseDepuisPlateau(std::shared_ptr<Carte> carte);
    void MelangerCartes();
    void MelangerCartes2();
    static int getnmbAchat();
    static int getnmbAction();
    void AfficherCartesRestantes2(const std::vector<std::shared_ptr<Carte>>& cartes) const;
    void AfficherCartesRestantesTresor(const std::vector<std::shared_ptr<Carte>>& cartes) const;
    std::string getNom() const;
    void setNom(std::string n);
    int getSizeMain() const;

};

#endif // 	JOUEUR_H
