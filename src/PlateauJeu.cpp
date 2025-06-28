#include "../include/PlateauJeu.h"
#include "../include/Carte.h"
#include "CarteTresor.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../include/CarteTresor.h"
#include <memory>
#include "../include/CarteVictoire.h"
#include "../include/CarteMalediction.h"
#include "../include/CarteAction.h"
#include <iomanip>
#include "../include/Joueur.h"
#include <algorithm>
#include <random>
#include <thread>
// RESET réinitialise la couleur à la valeur par défaut de la console.
#define RESET   "\033[0m"

// RED change la couleur du texte en rouge.
#define RED     "\033[91m"

// GREEN change la couleur du texte en vert.
#define GREEN   "\033[92m"

// YELLOW change la couleur du texte en jaune.
#define YELLOW  "\033[93m"

// CYAN change la couleur du texte en cyan.
#define CYAN    "\033[96m"

// PURPLE change la couleur du texte en violet.
#define PURPLE "\033[95m"

PlateauJeu::PlateauJeu(){
}
PlateauJeu::~PlateauJeu(){}

bool PlateauJeu::isFirstCall = true;
bool PlateauJeu::sauvegarde = false;

/*
 * Retourne les cartes actuellement sur le plateau de jeu.
 * @return Un vecteur de pointeurs partages vers des objets de type Carte.
 */
std::vector<std::shared_ptr<Carte>> PlateauJeu::getCartes(){
    return cartes;
}

/*
 * Retourne le nombre de joueurs sur le plateau de jeu.
 * @return Le nombre actuel de joueurs sur le plateau.
 */

int PlateauJeu::getNbjoueur(){
    return nbJoueur;
}

/*
 * Retourne le tour actuel sur le plateau de jeu.
 * @return Le numero du tour actuel.
 */
int PlateauJeu::getTour(){
    return tour;
}

/*
 * Indique si l'intelligence artificielle (IA) est activee sur le plateau de jeu.
 * @return true si l'IA est activee, false sinon.
 */
bool PlateauJeu::getIAB(){
    return IAB;
}

/*
 * Active ou desactive l'intelligence artificielle (IA) sur le plateau de jeu.
 * @param IAb true pour activer l'IA, false pour la desactiver.
 */
void PlateauJeu::setIAB(bool IAb){
    IAB=IAb;

}

/*
 * Retourne le fait de savoir s'il faut sauvegarder ou non
 * @return true s'il faut sauvegarder, false sinon.
 */
bool PlateauJeu::getSauvegarde(){
    return sauvegarde;
}

/*
 * Modifie le nombre de joueurs sur le plateau de jeu.
 * @param n Le nouveau nombre de joueurs.
 */
void PlateauJeu::setNbJoueur(int n){
    nbJoueur=n;
}

/*
 * Modifie le numero du tour actuel sur le plateau de jeu.
 * @param t Le nouveau numero de tour.
 */
void PlateauJeu::setTour(int t){
    tour=t;
}

/*
 * Verifie si une carte specifique a ete choisie sur le plateau de jeu.
 * @param carte Le nom de la carte a verifier.
 * @return true si la carte est trouvee dans la map et son booleen associe est a true, false sinon.
 */
bool PlateauJeu::estCarteChoisi( const std::string& carte) {
    // Recherche de la carte dans la map
    auto it = MapAction.find(carte);

    // Vérification si la carte est trouvée et si le booléen est à true
    return (it != MapAction.end()) && (it->second);
}

/*
 * Compte le nombre d'occurrences d'une carte specifique sur le plateau de jeu.
 * @param nomCarte Le nom de la carte a compter.
 * @return Le nombre d'occurrences de la carte specifiee sur le plateau de jeu.
 */
int PlateauJeu::CompterCartes(std::string nomCarte){
    int i=0;
    for (const auto& cartePtr : cartes) {
        if(cartePtr->getNom()==nomCarte){
            i=i+1;
        }
    }
    return i;
}

/*
 * Retire la carte voleur de la map d'actions sur le plateau de jeu.
 * La carte a retirer est determinee par la cle specifiee.
 */
void PlateauJeu::retirerCarteMap(){
    std::string keyToRemove = "Voleur";
    MapAction.erase(keyToRemove);
}

/*
 * Retourne la map d'actions actuelle sur le plateau de jeu.
 * @return Une map associant le nom des cartes a un booleen indiquant si la carte a ete choisie.
 */
std::map<std::string, bool> PlateauJeu::getMapAction(){
    return MapAction;
}

/*
 * Modifie l'etat d'une carte specifique dans la map d'actions sur le plateau de jeu.
 * Si la carte est presente dans la map et son booleen associe est a false, il le met a true.
 * @param carte Le nom de la carte a modifier.
 * @return true si la carte a ete trouvee et mise a jour, false sinon.
 */
bool PlateauJeu::setMapAction(std::string carte){
    bool b=false;
    auto it = MapAction.find(carte);
    //Verifie que la carte existe et qu'elle n'a pas encore ete ajoute au plateau
    if (it != MapAction.end()&& !(it->second)) {
        // Mise à jour du booléen à true
        it->second = true;
        std::cout << "\n La carte " << carte << " a ete ajoute au plateau." << std::endl;
        b=true;
    } else {
        std::cout << "\n La carte " << carte << " n'a pas ete trouvee" << std::endl;
    }
    return b;

}

/*
 * Retourne la deuxieme collection de cartes sur le plateau de jeu qui ne contient qu'une seule  occurence de chaque carte.
 * @return Un vecteur de pointeurs partages vers des objets de type Carte.
 */
std::vector<std::shared_ptr<Carte>> PlateauJeu::getCartes2(){
    return cartes2;
}

/*
 * Retourne la liste des joueurs actuellement sur le plateau de jeu.
 * @return Un vecteur de pointeurs partages vers des objets de type Joueur.
 */
std::vector<std::shared_ptr<Joueur>>  PlateauJeu::getJoueurs(){
    return Joueurs;
}

/*
 * Ajoute une nouvelle carteau premier vecteur de cartes sur le plateau de jeu.
 * @param nouvelleCarte Un pointeur partage vers la nouvelle carte a ajouter.
 */
void PlateauJeu::ajouterCarte(std::shared_ptr<Carte> nouvelleCarte) {
    cartes.push_back(std::move(nouvelleCarte));
}

/*
 * Ajoute une nouvelle carte au deuxieme vecteur de cartes sur le plateau de jeuqui ne contient qu'une seule  occurence de chaque carte.
 * @param nouvelleCarte Un pointeur partage vers la nouvelle carte a ajouter.
 */
void PlateauJeu::ajouterCarte2(std::shared_ptr<Carte> nouvelleCarte) {
    cartes2.push_back(std::move(nouvelleCarte));
}

/*
 * Retire une carte specifique du premier vecteur de cartes sur le plateau de jeu.
 * La carte a retirer est identifiee par son nom.
 * @param carte Un pointeur partage vers la carte a retirer.
 */
void PlateauJeu::RetirerCarte(std::shared_ptr<Carte> carte){
        // Recherche de la carte
        auto it = std::find_if(cartes.begin(), cartes.end(),
                               [&carte](const auto& elem) {
                                   return elem && carte && elem->getNom() == carte->getNom();
                               });
	// Verification si la carte est trouvee, puis suppression
        if (it != cartes.end()) {
            cartes.erase(it);
        }
    }

/*
 * Retire une carte specifique du deuxieme vecteur de cartes sur le plateau de jeu.
 * La carte a retirer est identifiee par son nom.
 * @param carte Un pointeur partage vers la carte a retirer.
 */
void PlateauJeu::RetirerCarte2(std::shared_ptr<Carte> carte) {
    auto it = std::find_if(cartes2.begin(), cartes2.end(),
	   [&carte](const auto& elem) {
	       return elem && carte && elem->getNom() == carte->getNom();
	   });
    if (it != cartes2.end()) {
        cartes2.erase(it);
    } else {
        std::cout << "\n L'element n'a pas ete trouve" << std::endl;
    }
}

/*
 * Verifie si la partie est terminee en fonction des cartes presentes sur le plateau de jeu.
 * La partie est consideree terminee si la carte "Province" est absente des cartes
 * ou si le deuxieme vecteur a moins de 15 cartes.
 * De plus, certaines cartes de la deuxieme collection sont retirees si elles ne sont pas presentes dans la premiere collection.
 * @return true si la partie est terminee, false sinon.
 */
bool PlateauJeu::FinDePartie(){
    bool b;
    for (const auto& cartePtr2 : cartes2) {
            b=false;
            // Verifie si la carte du deuxieme vecteur est presente dans le premier vecteur
            for (const auto& cartePtr : cartes) {
                if(cartePtr->getNom()==cartePtr2->getNom()){
                    b=true;
                    break;
                }
            }
            // Si la carte de la deuxieme collection n'est pas presente dans la premiere, on la retire
            if(!b){
                RetirerCarte2(cartePtr2);
                break;
            }
    }
    b=false;
    for (const auto& cartePtr2 : cartes2) {
        if(cartePtr2->getNom()=="Province"){
            b=true;
        }
    }
    // Si la carte "Province" est absente, la partie n'est pas terminee
    if(!b){
        return false;
    }
    // Si la deuxieme collection a plus de 15 cartes, la partie est terminee
    if(cartes2.size()>15){
        return true;
    }
    // Sinon, la partie n'est pas terminee
    return false;
}

/*
 * Lit les informations des cartes a partir d'un fichier CSV et ajoute ces cartes aux collections sur le plateau de jeu.
 * La fonction prend en compte les differents types de cartes (Tresor, Victoire, Malediction, Action) et initialise les collections en consequence.
 * @param filename Le nom du fichier CSV contenant les informations des cartes.
 * @param n Le nombre de joueurs dans la partie, utilise pour determiner le nombre de cartes "Province" a ajouter.
 */
void PlateauJeu::LireCartesDepuisCSV(const std::string& filename, int n) {
    std::ifstream file(filename);
    // Vérifie si le fichier CSV est ouvert avec succes
    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier CSV." << std::endl;
    }
    bool b;
    std::string line;

    // Ignore la première ligne du fichier CSV (entetes)
    std::getline(file, line);

    // Parcourt chaque ligne du fichier CSV
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int prix, valeur, points, nbActions;
        std::string nom, prix_str, valeur_str, points_str, nbActions_str;
        std::string type;

        // Extraction des informations de la ligne
        std::getline(ss, nom, ',');
        std::getline(ss, prix_str, ',');
        std::getline(ss , type, ',');
        prix = std::stoi(prix_str);
        std::getline(ss, valeur_str, ',');
        std::getline(ss, points_str, ',');
        std::getline(ss, nbActions_str, ',');

        // Traitement en fonction du type de carte
        if (type == "tresor") {
            // Création d'une carte Trésor
            valeur = std::stoi(valeur_str);
            CarteTresor nouvelleCarte(nom, prix, type, valeur);

            // Ajout de la carte à la deuxième collection et à la première collection plusieurs fois
            if (nom == "Cuivre" || nom == "Argent" || nom == "Or") {
                ajouterCarte2(std::make_unique<CarteTresor>(nouvelleCarte));
                for (int i = 0; i < (nom == "Cuivre" ? 60 : (nom == "Argent" ? 40 : 30)); i++) {
                    ajouterCarte(std::make_unique<CarteTresor>(nouvelleCarte));
                }
            }
        }
        else if (type == "victoire") {
            // Création d'une carte Victoire
            points = std::stoi(points_str);
            CarteVictoire nouvelleCarte(nom, prix, type, points);

            // Ajout de la carte à la deuxième collection et à la première collection plusieurs fois
            if (nom == "Domaine" || nom == "Duche" || nom == "Province" || nom == "Jardins") {
                ajouterCarte2(std::make_unique<CarteVictoire>(nouvelleCarte));
                int quantite = 0;
                if (nom == "Domaine") quantite = 24;
                else if (nom == "Duche") quantite = 12;
                else if (nom == "Province") quantite = (n <= 2) ? 8 : 12;
                else if (nom == "Jardins") quantite = 10;

                for (int i = 0; i < quantite; i++) {
                    ajouterCarte(std::make_unique<CarteVictoire>(nouvelleCarte));
                }
            }

        }
        else if (type== "malediction"){
            // Création d'une carte Malédiction
            points=std::stoi(points_str);
            CarteMalediction nouvelleCarte(nom, prix, type, points);
            // Ajout de la carte à la deuxième collection et à la première collection plusieurs fois
            ajouterCarte2(std::make_unique<CarteMalediction>(nouvelleCarte));
            if(nom=="Malediction"){
                for (int i=0; i<30;i++){
                    ajouterCarte(std::make_unique<CarteMalediction>(nouvelleCarte));
                }
            }
        }
        else{
            // Création d'une carte Action
            nbActions=std::stoi(nbActions_str);
            CarteAction nouvelleCarte(nom, prix, type, nbActions);
            // Vérifie si la carte a été choisie
            b= estCarteChoisi(nom);
            if(b){
                ajouterCarte2(std::make_unique<CarteAction>(nouvelleCarte));
                for (int i=0; i<10;i++){
                    ajouterCarte(std::make_unique<CarteAction>(nouvelleCarte));
                }
            }
        }
    }
    file.close();
}

/*
 * Affiche les informations des cartes restantes dans la collection specifiee sur le plateau de jeu.
 * La fonction utilise des pointeurs pour appeler la methode Afficher() sur chaque carte, independamment de son type concret.
 * @param cartes Une reference constante a un vecteur de pointeurs partages vers des objets de type Carte.
 */
void PlateauJeu::AfficherCartesRestantes(const std::vector<std::shared_ptr<Carte>>& cartes) const {
    // Utilise la dynamic_pointer_cast pour determiner le type concret de la carte
    for (const auto& cartePtr : cartes) {
        if (auto carteTresorPtr = std::dynamic_pointer_cast<CarteTresor>(cartePtr)) {
            // Si la carte est de type CarteTresor, appelle la methode Afficher() specifique a ce type
            carteTresorPtr->Afficher();
        } else if (auto carteActionPtr = std::dynamic_pointer_cast<CarteAction>(cartePtr)) {
            // Si la carte est de type CarteAction, appelle la methode Afficher() specifique a ce type
            carteActionPtr->Afficher();
        } else if (auto carteMaledictionPtr = std::dynamic_pointer_cast<CarteMalediction>(cartePtr)) {
            // Si la carte est de type CarteMalediction, appelle la methode Afficher() specifique a ce type
            carteMaledictionPtr->Afficher();
        } else if (auto carteVictoirePtr = std::dynamic_pointer_cast<CarteVictoire>(cartePtr)) {
            // Si la carte est de type CarteVictoire, appelle la methode Afficher() specifique a ce type
            carteVictoirePtr->Afficher();
        }
    }
}

/*
 * Effectue le tour d'une intelligence artificielle (IA) dans le jeu.
 * L'IA prend des decisions basees sur son etat actuel, ses ressources et la configuration du plateau de jeu.
 * @param IA Un pointeur partage vers l'objet representant l'IA.
 * @param tourIA Le numero du tour actuel de l'IA.
 */
void PlateauJeu::EffectuerTourIA(std::shared_ptr<Joueur> IA, int tourIA){
    int argent =0, prix =0;
    bool premierachat = true;
    bool achat= true;
    bool action =true;
    std::string choixCarte;
    std::shared_ptr<Carte> C,C2;
    std::vector<std::shared_ptr<Carte>> carteChoix, carteA, CarteA4;
    AfficherCartesRestantes(IA->getCarteMain());
    while(IA->getnmbAchat()>0 or IA->getnmbAction()>0 ){
        // Selectionne les cartes d'action dans la main de l'IA
        for (const auto& cartePtr : getCartes2()) {
            for (const auto& cartePtr2 : IA->getCarteMain()) {
                if(cartePtr2->getNom()==cartePtr->getNom() and cartePtr2->getType()=="action"){

                    carteChoix.push_back(cartePtr);
                }
            }
        }
        // Si aucune carte d'action n'est disponible, l'IA utilise aucune action
        if(carteChoix.size()==0){
            IA->setNmbAction(IA->getnmbAction()*-1);
            action =false;
        }
        if (action){
            // Selectionne la carte d'action la plus chere parmi les choix disponibles
            C2 = carteChoix.front();
            for (const auto& cartePtr : carteChoix) {
                if(cartePtr->getPrix()> C2->getPrix()){
                    C2=cartePtr;
                }
            }
            IA->ajouterCarteDefausse(C2);
            IA->retirerCarteMain(C2);
            auto carteActionPtr = std::dynamic_pointer_cast<CarteAction>(C2);
            // Execute l'action specifique en fonction du type de la carte d'action
            if(C2->getNom()=="Cave"){
                carteActionPtr->executerActionCave(IA);
            }
            else if(C2->getNom()=="Bucheron"){
                carteActionPtr->executerActionBucheron(IA);
                argent = argent + 2;
            }
            else if(C2->getNom()=="Village"){
                carteActionPtr->executerActionVillage(IA);
            }
            else if(C2->getNom()=="Chapelle"){
                carteActionPtr->executerActionChapelle(IA);
            }
            else if(C2->getNom()=="Marche"){
                carteActionPtr->executerActionMarche(IA);
                argent = argent + 1;
            }
            else if(C2->getNom()=="Atelier"){
            std::cout << "\n Effet de la carte Atelier : Recevez 1 carte coutant jusqu'a "<<YELLOW<<"4 pieces" <<RESET<< std::endl;
                for (const auto& carteJusqua4 : getCartes2()) {
                    if(carteJusqua4->getPrix()==4){
                        CarteA4.push_back(carteJusqua4);
                    }
                }
                IA->ajouterCarteDefausseDepuisPlateau(CarteA4.front());
                RetirerCarte(CarteA4.front());
                CarteA4.clear();
            }
            else if(C2->getNom()=="Renovation"){
                int prix = carteActionPtr->executerActionRenovation(IA);
                if(prix!=-1){
                    for (const auto& carteJusqua4 : getCartes2()) {
                        if(carteJusqua4->getPrix()==prix){
                            CarteA4.push_back(carteJusqua4);
                        }
                    }
                    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
                    std::mt19937 gen(seed);
                    std::uniform_int_distribution<> distribution(0, CarteA4.size() - 1);
                    int randomIndex = distribution(gen);
                    //std::cout<<randomIndex<<std::endl;
                    IA->ajouterCarteDefausseDepuisPlateau(CarteA4[randomIndex]);
                    RetirerCarte(CarteA4[randomIndex]);
                    CarteA4.clear();
                }
            }
            else if(C2->getNom()=="Forgeron"){
                carteActionPtr->executerActionForgeron(IA);
            }
            else if(C2->getNom()=="Mine"){

                int prix = carteActionPtr->executerActionMine(IA);
                if(prix!=-1){
                    for (const auto& carteJusqua4 : getCartes2()) {
                        if(carteJusqua4->getPrix()==prix and carteJusqua4->getType()=="tresor"){
                            CarteA4.push_back(carteJusqua4);
                        }
                    }
                    IA->ajouterCarteMain2(CarteA4.front());
                    RetirerCarte(CarteA4.front());
                    CarteA4.clear();
                }
            }
            else if(C2->getNom()=="Sorciere"){
                carteActionPtr->executerActionSorciere(IA);
                for (auto& joueur : getJoueurs()){
                    if(joueur->getNom() != IA->getNom()){
                        carteActionPtr->executerActionSorciere2(joueur,this);
                    }
                 }
            }
            else if(C2->getNom()=="Festin"){
                IA->AfficherCartesRestantes2(IA->getCarteMain());
                carteActionPtr->executerActionFestin(IA);
                IA->AfficherCartesRestantes2(IA->getCarteMain());
                    for (const auto& carteJusqua4 : getCartes2()) {
                        if(carteJusqua4->getPrix()==5){
                            CarteA4.push_back(carteJusqua4);
                        }
                    }
                    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
                    std::mt19937 gen(seed);
                    std::uniform_int_distribution<> distribution(0, CarteA4.size() - 1);
                    int randomIndex = distribution(gen);
                    std::cout<<randomIndex<<std::endl;
                    IA->ajouterCarteDefausseDepuisPlateau(CarteA4[randomIndex]);
                    RetirerCarte(CarteA4[randomIndex]);
                    CarteA4.clear();
            }
            else if(C2->getNom()=="Festival"){
                carteActionPtr->executerActionFestival(IA);
                argent=argent+2;
            }
            else if(C2->getNom()=="Laboratoire"){
                carteActionPtr->executerActionLaboratoire(IA);
            }
            else if(C2->getNom()=="PreteurSurGages"){
                bool existe = carteActionPtr->executerActionPreteurSurGages(IA);
                if(existe == true){
                    argent = argent +3;
                }
            }
            else if(C2->getNom()=="Chancelier") {
                carteActionPtr->executerActionChancelier(IA);
                argent = argent +2;
            }
            else if(C2->getNom()=="Bibliotheque") {
                carteActionPtr->executerActionBibliotheque(IA);
            }
            else if(C2->getNom()=="ChambreDuConseil") {
                carteActionPtr->executerActionChambreDuConseil(IA);
                for(const auto& joueur : getJoueurs()) {
                    if(joueur->getNom() != IA -> getNom()) {
                        joueur->ajouterCarteMain();
                        joueur->retirerCarteDeck();
                       }
                }
            }
            else if(C2->getNom()=="Espion") {
                carteActionPtr->executerActionEspion(IA);
                for(const auto& joueur : getJoueurs()) {
                    if((joueur->getCarteDeck()).empty()) {
                        while(!joueur->getCarteDefausse().empty()){
                            joueur->MelangerCartes2();
                            joueur->ajouterCarteDeck((joueur->getCarteDefausse()).back());
                            joueur->retirerCarteDefausse();
                        }
                    }
                    std::cout<<joueur->getNom()<<std::endl;
                    std::cout<<(joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getNom()<<" | "<<(joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getType()<<" | "<<(joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getPrix()<<std::endl;
                    if((joueur->getCarteDeck().back()->getType()=="action" or joueur->getCarteDeck().back()->getType()=="tresor") and joueur->getNom()!=IA->getNom()){
                        joueur->ajouterCarteDefausse(joueur->getCarteDeck().back());
                        joueur->retirerCarteDeck();
                    }
                    else if((joueur->getCarteDeck().back()->getType()=="victoire" or joueur->getCarteDeck().back()->getType()=="malediction") and joueur->getNom()==IA->getNom()){
                        joueur->ajouterCarteDefausse(joueur->getCarteDeck().back());
                        joueur->retirerCarteDeck();
                    }

                }
            }
            else if(C2->getNom()=="Aventurier") {
                carteActionPtr->executerActionAventurier(IA);
            }
            else if(C2->getNom()=="Milice"){
                carteActionPtr->executerActionMilice(IA,this);
                argent=argent+2;
            }
            // Decremente le nombre d'actions restantes de l'IA
            IA->setNmbAction(-1);
            // Si le nombre d'actions est 0 alors l'IA ne peut plus faire d'actions
            if(IA->getnmbAction()==0){
                action=false;
            }
            C2=nullptr;
            carteChoix.clear();
        }
        // Si l'IA a des achats disponibles
        else if(achat){
            // Si c'est le premier achat, calcule la somme d'argent disponible
            if(premierachat){
                for (const auto& cartePtr : IA->getCarteMain()) {
                    if (auto carteTresorPtr = std::dynamic_pointer_cast<CarteTresor>(cartePtr)) {
                        argent = argent + carteTresorPtr->getValeur();
                    }
                }
             }
            for (const auto& cartePtr : getCartes2()) {
                if(cartePtr->getType()=="action" and cartePtr->getPrix()<=argent){
                    carteA.push_back(cartePtr);
                }
            }
            // Determine quelle carte acheter en fonction des conditions specifiees
            if(argent>=8){
                choixCarte = "Province";
            }
            else if(argent>=5 and cartes2.size()<=16) {
                choixCarte="Duche";
            }
            else if(tourIA%2==1 and carteA.size()>0){
                // Choix aleatoire parmi les cartes d'action disponibles
                for (const auto& cartePtr : carteA) {
                    if(cartePtr->getPrix()> prix){
                        prix=cartePtr->getPrix();
                    }
                }
                for (const auto& carteJusqua4 : carteA) {
                        if(carteJusqua4->getPrix()==prix){
                            CarteA4.push_back(carteJusqua4);
                        }
                    }
                    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
                    std::mt19937 gen(seed);
                    std::uniform_int_distribution<> distribution(0, CarteA4.size() - 1);
                    int randomIndex = distribution(gen);
                    C = CarteA4[randomIndex];
                    choixCarte=C->getNom();
                    CarteA4.clear();
                    prix=0;
            }
            else if(argent>=6 and argent <8 and tourIA%2 ==0){
                //std::cout<<argent<<std::endl;
                choixCarte="Or";
            }
            else if(argent>=3 and argent <5 and tourIA%2 ==0){
                choixCarte="Argent";
            }
            else if(argent==5 and tourIA%2 ==0){
                choixCarte="Duche";
            }
	    else if(argent==2 and carteA.size()>0){
                C = carteA.front();
                for (const auto& cartePtr : carteA) {
        	        if(cartePtr->getPrix()> C->getPrix()){
                            C=cartePtr;
                        }
                }
                choixCarte=C->getNom();
            }
            else if(argent<=2 ){
                choixCarte="Cuivre";
            }
	    // Effectue l'achat de la carte choisie
            for (const auto& cartePtr : cartes2){
                if(cartePtr->getNom()==choixCarte){
                    RetirerCarte(cartePtr);
                    IA->ajouterCarteDefausseDepuisPlateau(cartePtr);
                    premierachat=false;
                    argent =argent-cartePtr->getPrix();
                    std::cout<<"\n IA a achete : " << choixCarte<<std::endl;
                    break;
                }
            }
            // Decremente le nombre d'achats restants de l'IA
            IA->setNmbAchat(-1);
            if(IA->getnmbAchat()==0){
                achat=false;
            }
        }
    }
    // Fin du tour de l'IA : defausse la main, reinitialise les actions et achats disponibles, et pioche de nouvelles cartes
    std::cout<<"\n Fin de tour"<<std::endl;
    while(!IA->getCarteMain().empty()){
        IA->ajouterCarteDefausse(IA->getCarteMain().back());
        IA->retirerCarteMain(IA->getCarteMain().back());
    }
    IA->setNmbAchat(1);
    IA->setNmbAction(1);
    argent=0;
    for (int i=0; i<5; i++){
        IA->ajouterCarteMain();
        IA->retirerCarteDeck();
    }
}

/*
 * Effectue le tour d'un joueur dans le jeu.
 * Le joueur prend des decisions basees sur son etat actuel, ses ressources et la configuration du plateau de jeu.
 * @param Joueur1 Un pointeur partage vers l'objet representant le joueur.
 */
void PlateauJeu::EffectuerTour(std::shared_ptr<Joueur> Joueur1){
    std::vector<std::shared_ptr<Carte>> carteChoix;
    std::string choix, choixCarte;
    int argent =0;
    bool b= false;
    bool premierachat = true;
    // Affiche les cartes dans la main du joueur
    AfficherCartesRestantes(Joueur1->getCarteMain());
    while(Joueur1->getnmbAchat()>0 or Joueur1->getnmbAction()>0 ){
    // Affiche les actions et achats disponibles
        std::cout<<"\n Vous pouvez encore effectuer " <<RED<<Joueur1->getnmbAction()<<" action(s)"<<RESET<<" et encore "<<YELLOW<<Joueur1->getnmbAchat()<<" achat(s)"<<RESET<<std::endl;
        std::cout<<"\n Vous voulez faire une action, un achat, rien ou faire une sauvegarde ? Reponse : ";
        std::cin>> choix;
        // Verifie que l'entree utilisateur est valide
        while (choix != "action" and choix != "achat" and choix != "rien" and choix != "sauvegarde"){
            std::cout<<"\n Vous voulez faire une action, un achat, rien ou faire une sauvegarde ? Reponse : ";
            std::cin>> choix;
        }
        if(choix=="achat" and Joueur1->getnmbAchat()>0){
            if(premierachat){
            // Calcule la somme d'argent disponible si c'est le premier achat
                for (const auto& cartePtr : Joueur1->getCarteMain()) {
                    if (auto carteTresorPtr = std::dynamic_pointer_cast<CarteTresor>(cartePtr)) {
                        argent = argent + carteTresorPtr->getValeur();
                    }
                }
            }
            // Affiche les cartes disponibles a l'achat
            std::cout<<"\n Vous avez " <<YELLOW<< argent <<" pieces"<<RESET<<std::endl;
            std::cout<<"\n Vous pouvez acheter : "<<std::endl;
            std::cout<<"\n";
            for (const auto& cartePtr : getCartes2()) {
                if(cartePtr->getPrix()<=argent){
                    // Affiche les informations de la carte d'une certaine couleur en fonction de son type
                    if(cartePtr->getType()=="action") {
                        std::cout<<RED<<" - "<<cartePtr->getNom()<<" | cout : "<< cartePtr->getPrix()<<" | cartes restantes : "<<CompterCartes(cartePtr->getNom())<<RESET<<std::endl;
                        carteChoix.push_back(cartePtr);
                    }
                    else if (cartePtr->getType()=="tresor"){
                        std::shared_ptr<CarteTresor> carteTresorPtr = std::dynamic_pointer_cast<CarteTresor>(cartePtr);
                        std::cout<<YELLOW<<" - "<<cartePtr->getNom()<<" | cout : "<< cartePtr->getPrix()<<" | valeur : "<<carteTresorPtr->getValeur()<<" | cartes restantes : "<<CompterCartes(cartePtr->getNom())<<RESET<<std::endl;
                        carteChoix.push_back(cartePtr);
                    }
                    else if (cartePtr->getType()=="victoire"){
                        std::shared_ptr<CarteVictoire> carteVictoirePtr = std::dynamic_pointer_cast<CarteVictoire>(cartePtr);
                        std::cout<<GREEN<<" - "<<cartePtr->getNom()<<" | cout : "<< cartePtr->getPrix()<<" | points : "<<carteVictoirePtr->getPoints()<<" | cartes restantes : "<<CompterCartes(cartePtr->getNom())<<RESET<<std::endl;
                        carteChoix.push_back(cartePtr);
                    }
                    else if (cartePtr->getType()=="malediction"){
                        std::shared_ptr<CarteMalediction> carteMaledictionPtr = std::dynamic_pointer_cast<CarteMalediction>(cartePtr);
                        std::cout<<PURPLE<<" - "<<cartePtr->getNom()<<" | cout : "<< cartePtr->getPrix()<<" | penalite : "<<carteMaledictionPtr->getPenalite()<<" | cartes restantes : "<<CompterCartes(cartePtr->getNom())<<RESET<<std::endl;
                        carteChoix.push_back(cartePtr);
                    }
                }
            }
            do{
                std::cout<<"\n Vous voulez acheter quoi ? ";
                std::cin>>choixCarte;
                // Effectue l'achat de la carte choisie si elle existe
                for (const auto& cartePtr : carteChoix){
                    if(cartePtr->getNom()==choixCarte){
                        RetirerCarte(cartePtr);
                        b=true;
                        Joueur1->ajouterCarteDefausseDepuisPlateau(cartePtr);
                        premierachat=false;
                        argent =argent-cartePtr->getPrix();
                        break;
                    }
                }
                if(!b){
                    std::cout<<"\n Vous ne pouvez pas acheter cette carte" <<std::endl;
                }
            }while(b==false);
            // Decremente le nombre d'achats restants du joueur
            Joueur1->setNmbAchat(-1);
        }
        else if(choix=="achat" and Joueur1->getnmbAchat()<1) {
            std::cout<<"\n Vous ne pouvez plus faire d'achat"<<std::endl;
        }
        else if(choix == "sauvegarde"){
            sauvegarde = true;
            std::cout<<"\n Vous avez selectionne sauvegarde. Votre sauvegarde s effectuera a la fin de votre tour. "<<std::endl;
        }
        else if(choix=="action" and Joueur1->getnmbAction()>0){
        // Affiche les cartes d'action disponibles dans la main du joueur
            std::cout<<"\n Voici les cartes Actions que vous avez : "<<std::endl;
            std::cout<<"\n";
            for (const auto& cartePtr : getCartes2()) {
                for (const auto& cartePtr2 : Joueur1->getCarteMain()) {
                    if(cartePtr2->getNom()==cartePtr->getNom() and cartePtr2->getType()=="action"){
                        std::cout<<" - " <<cartePtr->getNom()<<std::endl;
                        carteChoix.push_back(cartePtr);
                    }
                }
            }
            if(carteChoix.size()==0){
                std::cout<<"\n Vous ne pouvez pas faire d'actions, vous n'avez pas de carte action en main"<<std::endl;
                continue;
            }
            do{
                std::cout<<"\n Vous voulez faire quelle action ? ";
                std::cin>>choixCarte;
                // Execute l'action de la carte d'action choisie
                for (const auto& cartePtr : carteChoix){
                    if(cartePtr->getNom()==choixCarte){
                        std::cout<<"\n Vous utilisez : " <<cartePtr->getNom()<<std::endl;
                        auto carteActionPtr = std::dynamic_pointer_cast<CarteAction>(cartePtr);
                        Joueur1->ajouterCarteDefausse(cartePtr);
                        Joueur1->retirerCarteMain(cartePtr);
                        if(cartePtr->getNom()=="Cave"){
                            carteActionPtr->executerActionCave(Joueur1);
                        }
                        else if(cartePtr->getNom()=="Bucheron"){
                            carteActionPtr->executerActionBucheron(Joueur1);
                            argent = argent + 2;
                        }
                        else if(cartePtr->getNom()=="Village"){
                            carteActionPtr->executerActionVillage(Joueur1);
                        }
                        else if(cartePtr->getNom()=="Chapelle"){
                            carteActionPtr->executerActionChapelle(Joueur1);
                        }
                        else if(cartePtr->getNom()=="Marche"){
                            carteActionPtr->executerActionMarche(Joueur1);
                            argent = argent + 1;
                        }
                        else if(cartePtr->getNom()=="Atelier"){
                            std::cout << "\n Effet de la carte Atelier : Recevez 1 carte coutant jusqu'a "<<YELLOW<<"4 pieces" <<RESET<< std::endl;
                            std::cout<<"\n Cartes que vous pouvez recuperez, qui coute jusqu'a "<<YELLOW<<"4 pieces"<<RESET<< std::endl;
                            std::cout<<"\n";
                            for (const auto& carteJusqua4 : getCartes2()) {
                                if(carteJusqua4->getPrix()<=4){
                                    if(carteJusqua4->getType()=="tresor") {
                                    	std::cout<<YELLOW<<" - "<<carteJusqua4->getNom()<<", cout : "<< carteJusqua4->getPrix()<<RESET<<std::endl;
                                    }
                                    else if(carteJusqua4->getType()=="victoire") {
                                    	std::cout<<GREEN<<" - "<<carteJusqua4->getNom()<<", cout : "<< carteJusqua4->getPrix()<<RESET<<std::endl;
                                    }
                                    else if(carteJusqua4->getType()=="malediction") {
                                    	std::cout<<PURPLE<<" - "<<carteJusqua4->getNom()<<", cout : "<< carteJusqua4->getPrix()<<RESET<<std::endl;
                                    }
                                    else if(carteJusqua4->getType()=="action") {
                                    	std::cout<<RED<<" - "<<carteJusqua4->getNom()<<", cout : "<< carteJusqua4->getPrix()<<RESET<<std::endl;
                                    }
                                }
                            }
                            bool existe = false;
                            do{
                                std::cout<<"\n Quelle carte voulez vous recevoir ? ";
                                std::cin>>choixCarte;
                                for (const auto& cartePtr2 : getCartes2()){
                                    if(cartePtr2->getNom()==choixCarte && cartePtr2->getPrix()<=4){
                                        RetirerCarte(cartePtr2);
                                        existe=true;
                                        Joueur1->ajouterCarteDefausseDepuisPlateau(cartePtr2);
                                        std::cout<<"\n Vous avez recu la carte : "<<cartePtr2->getNom()<<std::endl;
                                        break;
                                    }
                                }
                                if(!existe){
                                    std::cout<<"\n Vous ne pouvez pas recevoir cette carte (doit couter "<<YELLOW<<"4 pieces"<<RESET<<" ou moins) ou elle n'existe pas" <<std::endl;
                                }
                            }while(existe==false);
                            std::cout << "\n Votre main a la fin de cette action :" << std::endl;
                            std::cout << "\n";
                            Joueur1->AfficherCartesRestantes2(Joueur1->getCarteMain());
                        }
                        else if(cartePtr->getNom()=="Renovation"){
                            int prix = carteActionPtr->executerActionRenovation(Joueur1);
                            bool existe = false;
                            std::cout<<"\n Cout de la carte que vous venez d'ecarter : "<<prix<<std::endl;
                            std::cout<<"\n Ainsi vous pouvez recuperer une carte coutant jusqu'a "<<prix+2<< std::endl;
                            std::cout<<"\n";
                            for (const auto& carteJusqua : getCartes2()) {
                                if(carteJusqua->getPrix()<=prix+2){
                                    if(carteJusqua->getType()=="tresor") {
                                    	std::cout<<YELLOW<<" - "<<carteJusqua->getNom()<<", cout : "<< carteJusqua->getPrix()<<RESET<<std::endl;
                                    }
                                    else if(carteJusqua->getType()=="victoire") {
                                    	std::cout<<GREEN<<" - "<<carteJusqua->getNom()<<", cout : "<< carteJusqua->getPrix()<<RESET<<std::endl;
                                    }
                                    else if(carteJusqua->getType()=="malediction") {
                                    	std::cout<<PURPLE<<" - "<<carteJusqua->getNom()<<", cout : "<< carteJusqua->getPrix()<<RESET<<std::endl;
                                    }
                                    else if(carteJusqua->getType()=="action") {
                                    	std::cout<<RED<<" - "<<carteJusqua->getNom()<<", cout : "<< carteJusqua->getPrix()<<RESET<<std::endl;
                                    }
                                }
                            }
                            while(existe==false){
                                std::cout<<"\n Quelle carte voulez vous recevoir ? ";
                                std::cin>>choixCarte;
                                for (const auto& cartePtr2 : getCartes2()){
                                    if(cartePtr2->getNom()==choixCarte && cartePtr2->getPrix()<=prix+2){
                                        RetirerCarte(cartePtr2);
                                        existe=true;
                                        Joueur1->ajouterCarteDefausseDepuisPlateau(cartePtr2);
                                        std::cout<<"\n Vous avez recu la carte : "<<cartePtr2->getNom()<<std::endl;
                                        break;
                                    }
                                }
                            if(!existe){
                                std::cout<<"\n Vous ne pouvez pas recevoir cette carte ou elle n'existe pas" <<std::endl;
                            }
                        }
                        std::cout << "\n Votre nouvelle main a la fin de cette action :" << std::endl;
                        std::cout << "\n";
                        Joueur1->AfficherCartesRestantes2(Joueur1->getCarteMain());
                    }
                    else if(cartePtr->getNom()=="Forgeron"){
                            carteActionPtr->executerActionForgeron(Joueur1);
                        }
                    else if(cartePtr->getNom()=="Mine"){
                            int prix = carteActionPtr->executerActionMine(Joueur1);
                            bool existe = false;
                            std::cout<<"Cout de la "<<YELLOW<<"carte Tresor"<<RESET<<" que vous venez d'ecarter : "<<YELLOW<<prix<<RESET<<std::endl;
                            std::cout<<"\n Ainsi vous pouvez recuperer "<<YELLOW<<"1 carte Tresor"<<RESET<< " coutant jusqu'a "<<YELLOW<<prix+3<<RESET<< std::endl;
                            std::cout<<"\n";
                            for (const auto& carteJusqua : getCartes2()) {
                                if(carteJusqua->getPrix()<=prix+3 && carteJusqua->getType()=="tresor"){
                                    std::cout<<" - " <<YELLOW<<carteJusqua->getNom()<<RESET<<", cout : "<< carteJusqua->getPrix()<<std::endl;
                                }
                            }
                            while(existe==false){

                                std::cout<<"\n Quelle "<<YELLOW<<"carte Tresor"<<RESET<<" voulez vous recevoir ? ";
                                std::cin>>choixCarte;
                                for (const auto& cartePtr2 : getCartes2()){
                                    if(cartePtr2->getNom()==choixCarte && cartePtr2->getPrix()<=prix+3 && cartePtr2->getType()=="tresor"){
                                        RetirerCarte(cartePtr2);
                                        existe=true;
                                        Joueur1->ajouterCarteMain2(cartePtr2);
                                        std::cout<<"\n Vous avez recu la carte : "<<YELLOW<<cartePtr2->getNom()<<RESET<<std::endl;
                                        break;
                                    }
                                }
                            if(!existe){
                                std::cout<<"\n Vous ne pouvez pas recevoir cette carte ou elle n'existe pas ou encore ce n'est pas une "<<YELLOW<<"Carte Tresor"<<RESET<<std::endl;
                            }
                        }
                        std::cout << "\n Votre nouvelle main a la fin de cette action :" << std::endl;
                        std::cout << "\n";
                        Joueur1->AfficherCartesRestantes2(Joueur1->getCarteMain());
                    }
                    else if(cartePtr->getNom()=="Sorciere"){
                        carteActionPtr->executerActionSorciere(Joueur1);
                        for (auto& joueur : getJoueurs()){
                            if(joueur->getNom() != Joueur1->getNom()){
                                carteActionPtr->executerActionSorciere2(joueur,this);
                            }
                         }
                        std::cout << "\n Votre nouvelle main a la fin de cette action :" << std::endl;
                        std::cout << "\n";
                        Joueur1->AfficherCartesRestantes2(Joueur1->getCarteMain());
                    }
                    else if(cartePtr->getNom()=="Festin"){
                        carteActionPtr->executerActionFestin(Joueur1);
                        std::cout << "\n Effet de la carte Festin : Ecarter cette carte et recever une carte coutant jusqu a 5 pieces." << std::endl;
                        bool existe = false;
                        std::cout<<"\n Cartes que vous pouvez recuperez, qui coute jusqu'a "<<YELLOW<<"5 pieces :"<<RESET<< std::endl;
                        std::cout<<"\n";
                        for (const auto& carteJusqua : getCartes2()) {
                            if(carteJusqua->getPrix()<=5){
                                std::cout<<" - "<<carteJusqua->getNom()<<", cout : "<< carteJusqua->getPrix()<<std::endl;
                            }
                        }
                         while(existe==false){
                            std::cout<<"\n Quelle carte voulez vous recevoir ? ";
                            std::cin>>choixCarte;
                            for (const auto& cartePtr2 : getCartes2()){
                                if(cartePtr2->getNom()==choixCarte && cartePtr2->getPrix()<=5){
                                    RetirerCarte(cartePtr2);
                                    existe=true;
                                    Joueur1->ajouterCarteDefausseDepuisPlateau(cartePtr2);
                                    std::cout<<"\n Vous avez recu la carte : "<<cartePtr2->getNom()<<std::endl;
                                    break;
                                }
                            }
                        if(!existe){
                            std::cout<<"\n  Vous ne pouvez pas recevoir cette carte ou elle n'existe pas" <<std::endl;
                        }
                    }

                    }

                    else if(cartePtr->getNom()=="Festival"){
                        carteActionPtr->executerActionFestival(Joueur1);
                        argent=argent+2;
                        std::cout << "\n Votre nouvelle main a la fin de cette action :" << std::endl;
                        std::cout << "\n";
                        Joueur1->AfficherCartesRestantes2(Joueur1->getCarteMain());
                    }
                    else if(cartePtr->getNom()=="Laboratoire"){
                            carteActionPtr->executerActionLaboratoire(Joueur1);
                    }
                    else if(cartePtr->getNom()=="PreteurSurGages"){
                        bool existe = carteActionPtr->executerActionPreteurSurGages(Joueur1);
                        if(existe == false){
                            std::cout<<"\n Vous n'avez pas de "<<YELLOW<<"cuivre"<<RESET<<" donc vous ne pouvez donc pas recevoir de cartes"<<std::endl;
                        }
                        else{
                            argent = argent +3;
                        }
                    }
                    else if(cartePtr->getNom()=="Chancelier") {
                        carteActionPtr->executerActionChancelier(Joueur1);
                        argent = argent +2;

                    }
                    else if(cartePtr->getNom()=="Bibliotheque") {
                        carteActionPtr->executerActionBibliotheque(Joueur1);
                    }
                    else if(cartePtr->getNom()=="ChambreDuConseil") {
                        carteActionPtr->executerActionChambreDuConseil(Joueur1);
                        for(const auto& joueur : getJoueurs()) {
                            if(joueur->getNom() != Joueur1 -> getNom()) {
                                joueur->ajouterCarteMain();
                                joueur->retirerCarteDeck();
                                std::cout<<"\n Le joueur "<<joueur->getNom()<<" a pioche une carte"<<std::endl;
                               }
                        }
                        std::cout<<"\n Votre main a la fin du tour"<<std::endl;
                        std::cout<<"\n";
                        Joueur1->AfficherCartesRestantes2(Joueur1->getCarteMain());
                    }
                    else if(cartePtr->getNom()=="Espion") {
                        carteActionPtr->executerActionEspion(Joueur1);
                        std::string reponse;
                        for(const auto& joueur : getJoueurs()) {
                            std::cout<<"\n Premiere carte du deck du Joueur "<<joueur->getNom()<<" : "<<std::endl;
                            if((joueur->getCarteDeck()).empty()) {
                                while(!joueur->getCarteDefausse().empty()){
                                    joueur->MelangerCartes2();
                                    joueur->ajouterCarteDeck((joueur->getCarteDefausse()).back());
                                    joueur->retirerCarteDefausse();
                                }
                                joueur->ajouterCarteMain();
                                joueur->retirerCarteDeck();
                            }
                            std::cout<<"\n -"<<(joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getNom()<<" | "<<(joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getType()<<" | "<<(joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getPrix()<<std::endl;
                            do {
                                std::cout<<"\n Voulez vous que cette carte soit defaussee ? (si non, la carte sera remis dans le deck) ";
                                std::cin>>reponse;
                                if(reponse=="oui") {
                                    joueur->ajouterCarteDefausse(joueur->getCarteDeck().back());

                                    joueur->retirerCarteDeck();

                                    std::cout<<"\n La carte "<<(joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getNom()<<" du joueur "<<joueur->getNom()<<" a ete defaussee"<<std::endl;
                                }
                                else if (reponse=="non") {
                                    std::cout<<"\n La carte "<<(joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getNom()<<" du joueur "<<joueur->getNom()<<" a ete remise dans le deck"<<std::endl;
                                }
                            }while(reponse !="oui" && reponse !="non");
                        }
                        std::cout << "\n Votre nouvelle main a la fin de cette action :" << std::endl;
                        std::cout << "\n";
                        Joueur1->AfficherCartesRestantes2(Joueur1->getCarteMain());
                    }
                    else if(cartePtr->getNom()=="Aventurier") {
                        carteActionPtr->executerActionAventurier(Joueur1);
                    }
                    else if(cartePtr->getNom()=="Voleur") {
                        std::vector<std::shared_ptr<Carte>> cartesEcartees;
                        std::vector<std::shared_ptr<Carte>> cartesTresor;
                        std::cout << "\n Effet de la carte Voleur : Tous vos adversaires devoilent les 2 premieres cartes de leur deck. S'ils devoilent des "<<YELLOW<<"cartes Tresor"<<RESET<<", ils en ecartent 1 de votre choix. Parmis ces cartes "<<YELLOW<<"Tresor ecartees"<<RESET<<", recevez celles de votre choix. Les autres devoilees sont defaussees" << std::endl;
                        std::string reponse;
                        std::string reponse2;
                        for(const auto& joueur : getJoueurs()) {
                            if(joueur->getNom()!=Joueur1->getNom()) {
                                //Premiere carte du Deck piochée
                                std::cout<<"\n -Premiere carte du deck du Joueur "<<joueur->getNom()<<" : "<<std::endl;
                                if((joueur->getCarteDeck()).empty()) {
                                    while(!joueur->getCarteDefausse().empty()){
                                        joueur->MelangerCartes2();
                                        joueur->ajouterCarteDeck((joueur->getCarteDefausse()).back());
                                        joueur->retirerCarteDefausse();
                                    }
                                    joueur->ajouterCarteMain();
                                    joueur->retirerCarteDeck();
                                }
                                std::cout<<(joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getNom()<<" | "<<(joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getType()<<" | "<<(joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getPrix()<<std::endl;
                                if((joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getType()=="tresor") { //La premiere carte piochee est une carte tresor
                                    cartesTresor.push_back((joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1)));
                                    joueur->retirerCarteDeck();
                                    std::cout<<"\n -Deuxieme carte du deck du Joueur "<<joueur->getNom()<<" : "<<std::endl;
                                    if((joueur->getCarteDeck()).empty()) {
                                        while(!joueur->getCarteDefausse().empty()){
                                            joueur->MelangerCartes2();
                                            joueur->ajouterCarteDeck((joueur->getCarteDefausse()).back());
                                            joueur->retirerCarteDefausse();
                                        }
                                        joueur->ajouterCarteMain();
                                        joueur->retirerCarteDeck();
                                    }
                                    std::cout<<(joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getNom()<<" | "<<(joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getType()<<" | "<<(joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getPrix()<<std::endl;
                                    if((joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getType()=="tresor") { //La deuxieme carte piochee est aussi une carte tresor
                                        cartesTresor.push_back((joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1)));
                                        joueur->retirerCarteDeck();
                                        bool c=false;
                                        do {
                                            std::cout<<"\n Quelle "<<YELLOW<<"carte Tresor"<<RESET<<" voulez vous ecarter ?"<<std::endl;
                                            std::cout<<"\n";
                                            for(const auto& cartesTresorJoueur : cartesTresor) {
                                                std::cout<<cartesTresorJoueur->getNom()<<" | "<<cartesTresorJoueur->getType()<<" | "<<cartesTresorJoueur->getPrix()<<std::endl;
                                            }
                                            std::cout<<"\n";
                                            std::cin>>reponse;
                                            for (auto it = cartesTresor.begin(); it != cartesTresor.end(); ++it) {
                                                if ((*it)->getNom() == reponse) {
                                                    cartesEcartees.push_back(*it);
                                                    it = cartesTresor.erase(it); // Utilisation de l'itérateur retourné par erase
                                                    joueur->ajouterCarteDefausse(cartesTresor.at(0));
                                                    std::cout << "\n Vous avez choisi d'ecarter : " << reponse << ", ainsi l'autre "<<YELLOW<<"carte tresor"<<RESET<<" (" << cartesTresor.at(0)->getNom() << ") va etre defaussee" << std::endl;
                                                    c = true;
                                                    break;
                                                }
                                            }

                                            if (!c) {
                                                std::cout << "\n Cette carte n'a pas été tirée ou ce n'est pas une "<<YELLOW<<"carte tresor" <<RESET<< std::endl;
                                            }

                                        }while(c!=true);
                                    } else { //La premiere carte est une Tresor mais pas la deuxieme
                                        if((joueur->getCarteDeck()).empty()) {
                                        while(!joueur->getCarteDefausse().empty()){
                                            joueur->MelangerCartes2();
                                            joueur->ajouterCarteDeck((joueur->getCarteDefausse()).back());
                                            joueur->retirerCarteDefausse();
                                        }
                                        joueur->ajouterCarteMain();
                                        joueur->retirerCarteDeck();
                                    }
                                        std::cout<<"\n "<<YELLOW<<"Carte tresor directement ecartee"<<std::endl;
                                        joueur->ajouterCarteDefausse((joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1)));
                                        joueur->retirerCarteDeck();
                                        std::cout<<"\n La carte "<<(joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getNom()<<" va etre defaussee"<<std::endl;
                                        cartesEcartees.push_back(cartesTresor.at(0));
                                    }
                                } else {
                                        std::cout<<"\n La carte "<<(joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getNom()<<" va etre defaussee"<<std::endl;
                                        joueur->ajouterCarteDefausse((joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1)));
                                        joueur->retirerCarteDeck();
                                        std::cout<<"\n -Deuxieme carte du deck du Joueur "<<joueur->getNom()<<" : "<<std::endl;
                                        if((joueur->getCarteDeck()).empty()) {
                                            while(!joueur->getCarteDefausse().empty()){
                                                joueur->MelangerCartes2();
                                                joueur->ajouterCarteDeck((joueur->getCarteDefausse()).back());
                                                joueur->retirerCarteDefausse();
                                            }
                                            joueur->ajouterCarteMain();
                                            joueur->retirerCarteDeck();
                                        }
                                        std::cout<<(joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getNom()<<" | "<<(joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getType()<<" | "<<(joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getPrix()<<std::endl;
                                        if((joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getType()=="tresor") { //La premiere carte piochee n'est pas une carte Tresor mais la 2eme si
                                            std::cout<<"\n "<<YELLOW<<"Carte tresor"<<RESET<<" directement ecartee"<<std::endl;
                                            cartesTresor.push_back((joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1)));
                                            joueur->retirerCarteDeck();
                                            cartesEcartees.push_back(cartesTresor.at(0));
                                        }
                                        else { //Aucune des 2 cartes tirees n'est une carte tresor
                                            if((joueur->getCarteDeck()).empty()) {
                                                while(!joueur->getCarteDefausse().empty()){
                                                    joueur->MelangerCartes2();
                                                    joueur->ajouterCarteDeck((joueur->getCarteDefausse()).back());
                                                    joueur->retirerCarteDefausse();
                                                }
                                                joueur->ajouterCarteMain();
                                                joueur->retirerCarteDeck();
                                            }
                                            joueur->ajouterCarteDefausse((joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1)));
                                            joueur->retirerCarteDeck();
                                            std::cout<<"\n La carte "<<(joueur->getCarteDeck().at(joueur->getCarteDeck().size()-1))->getNom()<<" va etre defaussee"<<std::endl;
                                            std::cout<<"\n Ce joueur n'a pas tire de "<<YELLOW<<"carte tresor"<<RESET<<std::endl;
                                        }
                                }
                                cartesTresor.clear();
                            }

                        }
                        if (getNbjoueur()==2) {
                            if (cartesEcartees.empty()) {
                                std::cout<<"\n Votre adversaire n'a donc pas tire de "<<YELLOW<<"carte tresor"<<RESET<<", ses 2 cartes vont donc etre defaussees."<<std::endl;
                            }
                            else {
                                Joueur1->ajouterCarteDefausse(cartesEcartees.at(0));
                                std::cout<<"\n Vous avez recupere la "<<YELLOW<<"carte tresor"<<RESET<<" : "<<cartesEcartees.at(0)->getNom()<<" | "<<cartesEcartees.at(0)->getPrix()<<std::endl;
                            }
                        }
                        else {
                            if (cartesEcartees.empty()) {
                                std::cout<<"\n Aucun de vos adversaires n'a tire de "<<YELLOW<<"carte tresor"<<RESET<<", toutes les cartes devoilees vont donc etre defaussees."<<std::endl;
                            }
                            else {
                                std::cout<<"\n Voici toutes les "<<YELLOW<<"cartes tresor"<<RESET<<" que vous avez decide d'ecarter : "<<std::endl;
                                for(const auto& cartesEcarteesJoueurs : cartesEcartees) {
                                    std::cout<<cartesEcarteesJoueurs->getNom()<<" | "<<cartesEcarteesJoueurs->getType()<<" | "<<cartesEcarteesJoueurs->getPrix()<<std::endl;
                                }
                               do {
                                    std::cout << "\n Quelle "<<YELLOW<<"carte Tresor"<<RESET<<" voulez-vous recuperer ? (Mettez 'aucune' si vous n'en voulez plus)" << std::endl;
                                    for (const auto& carteEcarteeJoueur : cartesEcartees) {
                                        std::cout << carteEcarteeJoueur->getNom() << " | " << carteEcarteeJoueur->getType() << " | " << carteEcarteeJoueur->getPrix() << std::endl;
                                    }

                                    std::cin >> reponse2;
                                    bool carteTrouvee = false;

                                    if (reponse2 == "aucune") {
                                        break;
                                    }

                                    for (auto it = cartesEcartees.begin(); it != cartesEcartees.end();) {
                                        if ((*it)->getNom() == reponse2) {
                                            Joueur1->ajouterCarteDefausse(*it);
                                            std::cout << "\n Vous avez choisi d'ecarter : " << reponse2 << std::endl;
                                            it = cartesEcartees.erase(it);
                                            carteTrouvee = true;
                                            break;
                                        } else {
                                            ++it;
                                        }
                                    }

                                    if (!carteTrouvee) {
                                        std::cout << "\n Cette carte n'a pas ete tiree ou ce n'est pas une "<<YELLOW<<"carte Tresor"<<RESET<<"." << std::endl;
                                    }
                                } while (!cartesEcartees.empty());

                                for(const auto& cartesEcarteesJoueur3 : cartesEcartees) {
                                    std::cout<<"Ainsi "<<cartesEcarteesJoueur3->getNom()<<" va/vont etre etre ecartee(s)"<<std::endl;
                                }
                            }
                        }
                        cartesEcartees.clear();
                    }
                    else if(cartePtr->getNom()=="Milice"){
                            carteActionPtr->executerActionMilice(Joueur1,this);
                            argent = argent +2;
                            std::cout<<"\n C'est a nouveau au tour de "<<Joueur1->getNom()<<" de jouer "<<std::endl;
                            if(Joueur1->getNom()!="IA"){
                                std::cout << "\n Votre main :" << std::endl;
                                std::cout << "\n";
                                Joueur1->AfficherCartesRestantes2(Joueur1->getCarteMain());
                            }
                    }
                        b=true;
                        break;
                    }
                }
            }while(b==false);
            Joueur1->setNmbAction(-1);
        }
        else if (choix=="rien"){
            Joueur1->setNmbAchat(Joueur1->getnmbAchat()*-1);
            Joueur1->setNmbAction(Joueur1->getnmbAction()*-1);
        }
        carteChoix.clear();
        b=false;
    }
    std::cout<<"\n Fin de tour"<<std::endl;
    // Fin du tour, defausse toutes les cartes de la main du joueur
    while(!Joueur1->getCarteMain().empty()){
        Joueur1->ajouterCarteDefausse(Joueur1->getCarteMain().back());
        Joueur1->retirerCarteMain(Joueur1->getCarteMain().back());
    }
    // Reinitialise les compteurs d'actions et d'achats, et pioche 5 nouvelles cartes
    Joueur1->setNmbAchat(1);
    Joueur1->setNmbAction(1);
    argent=0;
    for (int i=0; i<5; i++){
        Joueur1->ajouterCarteMain();
        Joueur1->retirerCarteDeck();
    }
}

/*
 * Initialise la partie en cr�ant le deck initial et la main de d�part d'un joueur.
 * @param J Un pointeur partag� vers l'objet repr�sentant le joueur.
 */
void PlateauJeu::CreationPartie(std::shared_ptr<Joueur> J){
    int i=0, j=0; //Permet de ne pas depasser le nombre de 3 et de 7 pour le cuivre et le domaine
    // Ajoute 7 cartes "Cuivre" au deck du joueur
    // Ajoute 3 cartes "Domaine" au deck du joueur
    while(i<7 or j<3) {
        for (const auto& cartePtr : getCartes()) {
            if(cartePtr->getNom()=="Cuivre" and i<7){
                RetirerCarte(cartePtr);
                J->ajouterCarteDeck(cartePtr);
                i=i+1;
                break;
            }
            else if(cartePtr->getNom()=="Domaine" and j<3){
                RetirerCarte(cartePtr);
                J->ajouterCarteDeck(cartePtr);
                j=j+1;
                break;
            }
        }
    }
    // Melange le deck du joueur
    J->MelangerCartes();
    // Pioche 5 cartes pour la main initiale du joueur
    for (int i=0; i<5; i++){
        J->ajouterCarteMain();
        J->retirerCarteDeck();
    }
}

/*
 * Ajoute un joueur a la liste des joueurs sur le plateau de jeu.
 * @param j Un pointeur partage vers l'objet representant le joueur a ajouter.
 */
void PlateauJeu::ajouterJoueur(std::shared_ptr<Joueur> j){
    Joueurs.push_back(j);
}

/*
 * Determine le nombre de points et les points bonus pour le joueur specifie.
 * Affiche le nombre total de points et retourne cette valeur.
 * @param j Un pointeur partage vers l'objet representant le joueur.
 * @return Le nombre total de points du joueur.
 */
int PlateauJeu::QuiGagne(std::shared_ptr<Joueur> j){
    int n= 0;
    int k=0;
    // Affichage des cartes dans le deck, la main et la defausse du joueur
    std::cout<<"\n Voici toutes les cartes de "<<j->getNom()<<" : "<<std::endl;
    std::cout<<"\n";
    j->AfficherCartesRestantes2(j->getCarteDeck());
    j->AfficherCartesRestantes2(j->getCarteMain());
    j->AfficherCartesRestantes2(j->getCarteDefausse());
    // Calcul des points en fonction des cartes dans le deck, la main et la defausse
    for(const auto& cartePtr : j->getCarteDeck()){
         if (auto carteVictoirePtr = std::dynamic_pointer_cast<CarteVictoire>(cartePtr)) {
            n=n+carteVictoirePtr->getPoints();
        }
        else if (auto carteVictoirePtr = std::dynamic_pointer_cast<CarteMalediction>(cartePtr)) {
            n=n+carteVictoirePtr->getPenalite();

        }
        if(cartePtr->getNom()=="Jardins"){
            k=k+1;
        }
    }
    for(const auto& cartePtr : j->getCarteMain()){
         if (auto carteVictoirePtr = std::dynamic_pointer_cast<CarteVictoire>(cartePtr)) {
            n=n+carteVictoirePtr->getPoints();
        }
        else if (auto carteVictoirePtr = std::dynamic_pointer_cast<CarteMalediction>(cartePtr)) {
            n=n+carteVictoirePtr->getPenalite();

        }
        if(cartePtr->getNom()=="Jardins"){
            k=k+1;
        }
    }
    for(const auto& cartePtr : j->getCarteDefausse()){
         if (auto carteVictoirePtr = std::dynamic_pointer_cast<CarteVictoire>(cartePtr)) {
            n=n+carteVictoirePtr->getPoints();
        }
        else if (auto carteVictoirePtr = std::dynamic_pointer_cast<CarteMalediction>(cartePtr)) {
            n=n+carteVictoirePtr->getPenalite();
        }
        if(cartePtr->getNom()=="Jardins"){
            k=k+1;
        }
    }
    // Calcul du bonus de points en fonction du nombre de cartes Jardins
    int taille = j->getCarteDefausse().size() + j->getCarteDeck().size()+j->getCarteMain().size();
    int mod = taille/10;
    n= n+k*mod;
    std::cout<<"\n"<<j->getNom()<<" a donc "<<n<<" points."<<std::endl;
    return n;
}

/*
 * Enregistre les informations du joueur specifie dans un fichier CSV.
 * @param j Un pointeur partage vers l'objet representant le joueur.
 * @param filename Le nom du fichier CSV.
 */
void PlateauJeu::MettreDansCSV(std::shared_ptr<Joueur> j,const std::string& filename ){
    std::ofstream file;
    // Ouverture du fichier CSV en mode ajout s'il n'est pas le premier appel, sinon en mode creation
    if (!isFirstCall){
        file.open(filename, std::ios::app);
    }
    else{
        file.open(filename);
    }

    if (file.is_open()) {
        if (isFirstCall) {
            file << nbJoueur << std::endl;
            file<<tour<<std::endl;
            file<<IAB<<std::endl;
            isFirstCall = false;
            // Ecrire les informations des cartes du premier vecteur
            file<<"Carte"<<std::endl;
            for(const auto& cartePtr : cartes){
              file<<cartePtr->getNom()<<","<<cartePtr->getPrix()<<","<<cartePtr->getType()<<",";
                if (auto carteTresorPtr = std::dynamic_pointer_cast<CarteTresor>(cartePtr)) {
                    file<<carteTresorPtr->getValeur()<<","<<","<<std::endl;
                }
                else if (auto carteActionPtr = std::dynamic_pointer_cast<CarteAction>(cartePtr)) {
                    file<<","<<","<<carteActionPtr->getNbActions()<<std::endl;
                } else if (auto carteMaledictionPtr = std::dynamic_pointer_cast<CarteMalediction>(cartePtr)) {
                    file<<","<<carteMaledictionPtr->getPenalite()<<","<<std::endl;
                } else if (auto carteVictoirePtr = std::dynamic_pointer_cast<CarteVictoire>(cartePtr)) {
                    file<<","<<carteVictoirePtr->getPoints()<<","<<std::endl;

                }

            }
            // Ecrire les informations des cartes du deuxi�me vecteur
            file<<"Cartes2"<<std::endl;
            for(const auto& cartePtr : cartes2){
              file<<cartePtr->getNom()<<","<<cartePtr->getPrix()<<","<<cartePtr->getType()<<",";
                if (auto carteTresorPtr = std::dynamic_pointer_cast<CarteTresor>(cartePtr)) {
                    file<<carteTresorPtr->getValeur()<<","<<","<<std::endl;
                }
                else if (auto carteActionPtr = std::dynamic_pointer_cast<CarteAction>(cartePtr)) {
                    file<<","<<","<<carteActionPtr->getNbActions()<<std::endl;
                } else if (auto carteMaledictionPtr = std::dynamic_pointer_cast<CarteMalediction>(cartePtr)) {
                    file<<","<<carteMaledictionPtr->getPenalite()<<","<<std::endl;
                } else if (auto carteVictoirePtr = std::dynamic_pointer_cast<CarteVictoire>(cartePtr)) {
                    file<<","<<carteVictoirePtr->getPoints()<<","<<std::endl;

                }

            }
        }
        // Ecrire les informations du joueur dans le fichier
        file<<"Deck"<<std::endl;
        file<<j->getNom();
        file << "\n";
	// Ecrire les cartes du deck du joueur
        for(const auto& cartePtr : j->getCarteDeck()){
              file<<cartePtr->getNom()<<","<<cartePtr->getPrix()<<","<<cartePtr->getType()<<",";
            if (auto carteTresorPtr = std::dynamic_pointer_cast<CarteTresor>(cartePtr)) {
                file<<carteTresorPtr->getValeur()<<","<<","<<std::endl;
            }
            else if (auto carteActionPtr = std::dynamic_pointer_cast<CarteAction>(cartePtr)) {
                file<<","<<","<<carteActionPtr->getNbActions()<<std::endl;
            } else if (auto carteMaledictionPtr = std::dynamic_pointer_cast<CarteMalediction>(cartePtr)) {
                file<<","<<carteMaledictionPtr->getPenalite()<<","<<std::endl;
            } else if (auto carteVictoirePtr = std::dynamic_pointer_cast<CarteVictoire>(cartePtr)) {
                file<<","<<carteVictoirePtr->getPoints()<<","<<std::endl;

            }

        }
        file<<"Main"<<std::endl;
        // Ecrire les cartes de la main du joueur
        for(const auto& cartePtr : j->getCarteMain()){
            file<<cartePtr->getNom()<<","<<cartePtr->getPrix()<<","<<cartePtr->getType()<<",";
            if (auto carteTresorPtr = std::dynamic_pointer_cast<CarteTresor>(cartePtr)) {
                file<<carteTresorPtr->getValeur()<<","<<","<<std::endl;
            }
            else if (auto carteActionPtr = std::dynamic_pointer_cast<CarteAction>(cartePtr)) {
                file<<","<<","<<carteActionPtr->getNbActions()<<std::endl;
            } else if (auto carteMaledictionPtr = std::dynamic_pointer_cast<CarteMalediction>(cartePtr)) {
                file<<","<<carteMaledictionPtr->getPenalite()<<","<<std::endl;
            } else if (auto carteVictoirePtr = std::dynamic_pointer_cast<CarteVictoire>(cartePtr)) {
                file<<","<<carteVictoirePtr->getPoints()<<","<<std::endl;

            }

        }
        file<<"Defausse"<<std::endl;
        // Ecrire les cartes de la defausse du joueur
        for(const auto& cartePtr : j->getCarteDefausse()){
            file<<cartePtr->getNom()<<","<<cartePtr->getPrix()<<","<<cartePtr->getType()<<",";
            if (auto carteTresorPtr = std::dynamic_pointer_cast<CarteTresor>(cartePtr)) {
                file<<carteTresorPtr->getValeur()<<","<<","<<std::endl;
            }
            else if (auto carteActionPtr = std::dynamic_pointer_cast<CarteAction>(cartePtr)) {
                file<<","<<","<<carteActionPtr->getNbActions()<<std::endl;
            } else if (auto carteMaledictionPtr = std::dynamic_pointer_cast<CarteMalediction>(cartePtr)) {
                file<<","<<carteMaledictionPtr->getPenalite()<<","<<std::endl;
            } else if (auto carteVictoirePtr = std::dynamic_pointer_cast<CarteVictoire>(cartePtr)) {
                file<<","<<carteVictoirePtr->getPoints()<<","<<std::endl;

            }

        }
    }
    file.close();
}

/*
 * Recupere les informations d'une sauvegarde depuis un fichier CSV.
 * @param filename Le nom du fichier CSV.
 */
void PlateauJeu::RecuperSauvegarde(const std::string& filename){
    std::ifstream file(filename);
    int i=0;
    std::string t_str,n_str,booleanStr;
    // Verification de l'ouverture du fichier
    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier CSV." << std::endl;
        return;
    }
    std::string line;
    // Lecture du nombre de joueurs
    std::getline(file, line);
    std::stringstream ss1(line);
    std::getline(ss1, n_str);
    // Lecture du tour actuel
    std::getline(file, line);
    std::stringstream ss2(line);
    std::getline(ss2, t_str);
    setNbJoueur((std::stoi(n_str)));
    setTour((std::stoi(t_str)));
    // Lecture du booleen pour savoir s'il ya un IA
    std::getline(file, line);
    std::stringstream ss3(line);
    std::getline(ss3, booleanStr);
    if(booleanStr=="1"){
        IAB=true;
    }
    else{
        IAB=false;
    }
    // Lecture des cartes depuis le fichier
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        // Si la ligne contient "Cartes2", passer a la deuxieme pile de cartes
        if (line.find("Cartes2") != std::string::npos) {
            i = 1;
            continue;
        }
        int countVirgules = std::count(line.begin(), line.end(), ',');
        // Si la ligne contient un seul mot (une seule virgule), arrêter la boucle
        if (countVirgules <= 1) {
            break;
        }
        int prix,valeur, points,nbActions;
        std::string nom, prix_str,valeur_str, points_str,nbActions_str;
        std::string type;
        // Lecture des valeurs depuis la ligne
        std::getline(ss, nom, ',');
        std::getline(ss, prix_str, ',');
        std::getline(ss , type, ',');
        prix = std::stoi(prix_str);
        std::getline(ss, valeur_str, ',');
        std::getline(ss, points_str, ',');
        std::getline(ss, nbActions_str, ',');

        if (type=="tresor" and i==0){

            valeur=std::stoi(valeur_str);
            CarteTresor nouvelleCarte(nom, prix, type, valeur);
            ajouterCarte(std::make_unique<CarteTresor>(nouvelleCarte));
        }
        else if (type=="tresor" and i==1){

            valeur=std::stoi(valeur_str);
            CarteTresor nouvelleCarte(nom, prix, type, valeur);
            ajouterCarte2(std::make_unique<CarteTresor>(nouvelleCarte));
        }
        else if (type=="victoire" and i==0){

            points=std::stoi(points_str);
            CarteVictoire nouvelleCarte(nom, prix, type, points);
            ajouterCarte(std::make_unique<CarteVictoire>(nouvelleCarte));

        }
        else if (type=="victoire" and i==1){

            points=std::stoi(points_str);
            CarteVictoire nouvelleCarte(nom, prix, type, points);
            ajouterCarte2(std::make_unique<CarteVictoire>(nouvelleCarte));

        }
        else if (type== "malediction" and i==0){
            points=std::stoi(points_str);
            CarteMalediction nouvelleCarte(nom, prix, type, points);
            ajouterCarte(std::make_unique<CarteMalediction>(nouvelleCarte));

        }
        else if (type== "malediction" and i==1){
            points=std::stoi(points_str);
            CarteMalediction nouvelleCarte(nom, prix, type, points);
            ajouterCarte2(std::make_unique<CarteMalediction>(nouvelleCarte));

        }
        else if (type=="action" and i==0){
            nbActions=std::stoi(nbActions_str);
            CarteAction nouvelleCarte(nom, prix, type, nbActions);
            ajouterCarte(std::make_unique<CarteAction>(nouvelleCarte));

        }
        else if (type=="action" and i==1){
            nbActions=std::stoi(nbActions_str);
            CarteAction nouvelleCarte(nom, prix, type, nbActions);
            ajouterCarte2(std::make_unique<CarteAction>(nouvelleCarte));
        }
    }
}

/*
 * Recupere les informations d'une sauvegarde pour un joueur specifique depuis un fichier CSV.
 * @param filename Le nom du fichier CSV.
 * @param j Un pointeur vers le joueur concerne.
 * @param comptJ Le compteur de joueur, utilise pour identifier le joueur dans le fichier.
 */
void PlateauJeu::RecuperSauvegarde2(const std::string& filename, std::shared_ptr<Joueur> j,int comptJ){
    int k=0;
    std::ifstream file(filename);
    std::string nom;
    std::string line;
    int i=0;
    // Verification de l'ouverture du fichier
    if (!file.is_open()) {
        std::cerr << "Erreur lors de l'ouverture du fichier." << std::endl;
        return;
    }
    // Recherche du debut du bloc d'informations pour le joueur specifique
    while (std::getline(file, line)) {
        if (line.find("Deck") != std::string::npos ) {
            if(comptJ==k){
                break;
            }
            else{
                k=k+1;
            }
        }
    }
    std::getline(file, line);
    std::stringstream ss2(line);
    std::getline(ss2, nom);
    j->setNom(nom);
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            int countVirgules = std::count(line.begin(), line.end(), ',');
            // Si la ligne contient "Deck", "Main" ou "Defausse", incrementer i
            if (countVirgules <= 1 and i==3) {
                break;
            }
            else if(countVirgules <= 1){
                i=i+1;
                continue;
            }
            int prix,valeur, points,nbActions;
            std::string nom, prix_str,valeur_str, points_str,nbActions_str;
            std::string type;
            // Lecture des valeurs depuis la ligne
            std::getline(ss, nom, ',');
            std::getline(ss, prix_str, ',');
            std::getline(ss , type, ',');
            prix = std::stoi(prix_str);
            std::getline(ss, valeur_str, ',');
            std::getline(ss, points_str, ',');
            std::getline(ss, nbActions_str, ',');
            // Creation des nouvelles cartes et ajout a la pile correspondante
            if (type=="tresor" ){
                valeur=std::stoi(valeur_str);
                CarteTresor nouvelleCarte(nom, prix, type, valeur);
                if(i==0){
                    j->ajouterCarteDeck(std::make_unique<CarteTresor>(nouvelleCarte));
                }
                else if(i==1){
                    j->ajouterCarteMain2(std::make_unique<CarteTresor>(nouvelleCarte));
                }
                else if(i==2){
                    j->ajouterCarteDefausse(std::make_unique<CarteTresor>(nouvelleCarte));
                }

            }
            else if (type=="victoire"){
                points=std::stoi(points_str);
                CarteVictoire nouvelleCarte(nom, prix, type, points);
                if(i==0){
                    j->ajouterCarteDeck(std::make_unique<CarteVictoire>(nouvelleCarte));
                }
                else if(i==1){
                    j->ajouterCarteMain2(std::make_unique<CarteVictoire>(nouvelleCarte));
                }
                else if(i==2){
                    j->ajouterCarteDefausse(std::make_unique<CarteVictoire>(nouvelleCarte));
                }
            }
            else if (type=="malediction"){
                points=std::stoi(points_str);
                CarteMalediction nouvelleCarte(nom, prix, type, points);
                if(i==0){
                    j->ajouterCarteDeck(std::make_unique<CarteMalediction>(nouvelleCarte));
                }
                else if(i==1){
                    j->ajouterCarteMain2(std::make_unique<CarteMalediction>(nouvelleCarte));
                }
                else if(i==2){
                    j->ajouterCarteDefausse(std::make_unique<CarteMalediction>(nouvelleCarte));
                }

            }
            else {
                nbActions=std::stoi(nbActions_str);
                CarteAction nouvelleCarte(nom, prix, type, nbActions);
                if(i==0){
                    j->ajouterCarteDeck(std::make_unique<CarteAction>(nouvelleCarte));
                }
                else if(i==1){
                    j->ajouterCarteMain2(std::make_unique<CarteAction>(nouvelleCarte));
                }
                else if(i==2){
                    j->ajouterCarteDefausse(std::make_unique<CarteAction>(nouvelleCarte));
                }
            }

        }
}

