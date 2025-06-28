#include <iostream>
#include "../include/PlateauJeu.h"
#include "../include/Carte.h"
#include <algorithm>
#include <fstream>
#include <thread>
#include <iomanip>  // Pour std::setw
using namespace std;

// Codes de s�quence d'�chappement ANSI pour changer la couleur du texte
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[96m"
#define WHITE   "\033[37m"
#define GRAY "\033[37m"

int main() {
    std::cout << CYAN << "\n              Bienvenue dans notre : " << std::endl;
    std::cout << "   _ _ _                                                         " << std::endl;
    std::cout << "  /   _ \\                       _           _               " << std::endl;
    std::cout << "  |  / \\ \\   _ _ _    _     _  (_)         (_)               " << std::endl;
    std::cout << "  |  | |  | |  _ _ | | |_ _| |  _   _ __    _   _ _ _ _   _ __    " << std::endl;
    std::cout << "  |  | |  | | |   || |       | | | |  _ \\  | | |  _ _  | |  _ \\    " << std::endl;
    std::cout << "  |  \\_/  / | |_ _|| | |\\_/| | | | | | | | | | | |_ _| | | | | |  " << std::endl;
    std::cout << "  \\_ _ _ /  |_ _ __| |_|   |_| |_| |_| |_| |_| |_ _ _ _| |_| |_| " << std::endl;
    std::cout << "                                                              " << std::endl;
    PlateauJeu plateauJeu;
    int nbJoueur, a = 0, b = 0, c = 0, d = 0, tour=0, nbcartes;
    std::string s,nom, rep, s2, CarteChosi;
    int ko =0; // Compteur pour compter le nombre de tour de l'IA
    // Permet de cr�er les diff�rents Joueurs qui peuvent jouer
    std::shared_ptr<Joueur> Joueur1 = std::make_shared<Joueur>("Joueur1");
    std::shared_ptr<Joueur> Joueur2 = std::make_shared<Joueur>("Joueur2");
    std::shared_ptr<Joueur> Joueur3 = std::make_shared<Joueur>("Joueur3");
    std::shared_ptr<Joueur> Joueur4 = std::make_shared<Joueur>("Joueur4");
    std::shared_ptr<Joueur> IA = std::make_shared<Joueur>("IA");
    bool IAb =false, CarteExiste;

    std::ifstream fichier("sauvegarde.csv");
    //V�rifie si le fichier existe avant de poser la question de la reprise de sauvegarde
    if(fichier.good()){
        do{
            std::cout << "\n   Voulez-vous reprendre une sauvegarde ? (Oui ou Non): ";
            std::cin>>s;
        }while (s!="Oui" and s!="Non");
    }

    if(s=="Oui"){
    	std::cout<<RESET;
    	// R�cup�rer les donn�es du fichier tels que le nombre de joueur, le tour actuel et s'il ya un IA
        plateauJeu.RecuperSauvegarde("sauvegarde.csv");
        nbJoueur=plateauJeu.getNbjoueur();
        tour=plateauJeu.getTour();
        IAb =plateauJeu.getIAB();
        for (int i =0; i<nbJoueur; i++){
            if (i==0){
                //Recup�re les diff�rentes informations du joueur tels que son nom et ses cartes
                plateauJeu.RecuperSauvegarde2( "sauvegarde.csv",Joueur1,i);
                plateauJeu.ajouterJoueur(Joueur1);

            }

            else if(i==1){
                // Verifie qu'il ya un IA et que c'est le dernier Joueur
                if(IAb and i==nbJoueur-1){
                    //Recup�re les diff�rentes informations du joueur tels que son nom et ses cartes
                    plateauJeu.RecuperSauvegarde2( "sauvegarde.csv",IA,i);
                    plateauJeu.ajouterJoueur(IA);
                }
                else{
                    //Recup�re les diff�rentes informations du joueur tels que son nom et ses cartes
                    plateauJeu.RecuperSauvegarde2( "sauvegarde.csv",Joueur2,i);
                    plateauJeu.ajouterJoueur(Joueur2);
                }
;

            }
            else if(i==2){
                // Verifie qu'il ya un IA et que c'est le dernier Joueur
                if(IAb and i==nbJoueur-1){
                    //Recup�re les diff�rentes informations du joueur tels que son nom et ses cartes
                    plateauJeu.RecuperSauvegarde2( "sauvegarde.csv",IA,i);
                    plateauJeu.ajouterJoueur(IA);
                }
                else{
                    //Recup�re les diff�rentes informations du joueur tels que son nom et ses cartes
                    plateauJeu.RecuperSauvegarde2( "sauvegarde.csv",Joueur3,i);
                    plateauJeu.ajouterJoueur(Joueur3);
                }
            }
            else{
                // Verifie qu'il ya un IA et que c'est le dernier Joueur
                if(IAb and i==nbJoueur-1){
                    //Recup�re les diff�rentes informations du joueur tels que son nom et ses cartes
                    plateauJeu.RecuperSauvegarde2( "sauvegarde.csv",IA,i);
                    plateauJeu.ajouterJoueur(IA);
                }
                else{
                    //Recup�re les diff�rentes informations du joueur tels que son nom et ses cartes
                    plateauJeu.RecuperSauvegarde2( "sauvegarde.csv",Joueur4,i);
                    plateauJeu.ajouterJoueur(Joueur4);
                }
            }
    }

    }
    else{
        //Demande le nombre de joueurs jusqu'a que ce chiffre soit comris entre 2 et 4
        do{
            std::cout<<"\n   Combien de joueur vont jouer ? (De 2 a 4 joueurs) : " ;
            std::cin>> nbJoueur;
        }while(nbJoueur<2 or nbJoueur>4);
        // Demande si les joueurs veulent jouer avec un IA
        do{
            std::cout<<"\n   Voulez-vous jouez avec un IA qui remplacera un des "<<nbJoueur<<" joueurs (Oui/Non) : ";
            std::cin>> rep;
        }while(rep!="Oui" and rep!="Non");
        if(rep=="Oui"){
            IAb = true;
        }
        //Demander s'il le joueur veut chosir se cartes
        do{
            std::cout<<"\n   Voulez vous choisir vos cartes ou prendre les cartes de base? (Oui ou Non pour garder cartes de base) : ";
            std::cin>>s2;
            std::cout<<"\n";
        }while (s2!="Oui" and s2!="Non");
        if(s2=="Non"){
            //Permet de mettre � true dans la map l'�l�ment li�  � ce nom, lorsque cet �l�ment est � true, les cartes seront ajout�es au plateau de jeu
            //Voci les 10 cartes actions de bases
            plateauJeu.setMapAction("Cave");
            plateauJeu.setMapAction("Village");
            plateauJeu.setMapAction("Renovation");
            plateauJeu.setMapAction("Mine");
            plateauJeu.setMapAction("Marche");
            plateauJeu.setMapAction("Forgeron");
            plateauJeu.setMapAction("Chapelle");
            plateauJeu.setMapAction("Atelier");
            plateauJeu.setMapAction("Bucheron");
            plateauJeu.setMapAction("Sorciere");
        }
        if(s2=="Oui"){
            if(IAb){
                //Permet de retier la carte voleur des choix des cartes car elle ne peut pas �tre utlis� par l'IA
                plateauJeu.retirerCarteMap();
            }
        //Demander les 10 cartes actions que le joueur veut
        while(nbcartes<10){
            std::cout<<"\n   Avec quelles cartes actions voulez vous jouer parmi celles la : (vous devez encore en choisir " <<10-nbcartes<<")"<<std::endl;
            std::cout<<"\n";

            for (const auto& pair : plateauJeu.getMapAction()) {
                //Permet d'afficher seulement les cartes qui n'ont pas �t� chosi
                if(!(pair.second)){
                    //Afficher les differentes cartes que le joueur peut chosir
                    std::cout <<"    - "<<"Carte : " << pair.first<<std::endl;
                }

            }
            std::cout<<"\n Carte choisi : ";
            cin>>CarteChosi;
            //Permet de mettre � true dans la map l'�l�ment li�  � ce nom, lorsque cet �l�ment est � true, les cartes seront ajout�es au plateau de jeu
            // Verifie que la carte Existe et n'a pas encore �t� chosie
            CarteExiste=plateauJeu.setMapAction(CarteChosi);
            if(CarteExiste){
                nbcartes = nbcartes+1;
            }
        }

        }


        std::cout<<RESET<<"\n -------------------------------------------------------------------------------"<<std::endl;
        std::cout<<"\n                 Debut de la partie ! "<<std::endl;
        //Met � jour la valeur IAb du plateau de jeu
        //Sert pour une r�cuperation de sauveagarde
        plateauJeu.setIAB(IAb);
        // Ajoute les cartes dans le plateau de jeu en fonction du choix des joueurs et du nombre de joueur
        plateauJeu.LireCartesDepuisCSV("cartes.csv", nbJoueur);
        //Met � jour le nombre de joueur dans le plateau jeu
        //Sert pour une r�cuperation de sauveagarde
        plateauJeu.setNbJoueur(nbJoueur);

        for (int i =0; i<nbJoueur; i++){
            if (i==0){
                //Cr�� la partie pour le Joueur en mettant les cartes qu'il faut dans le deck et la main
                plateauJeu.CreationPartie(Joueur1);
                //Ajoute les joueurs � la liste des joueurs
                plateauJeu.ajouterJoueur(Joueur1);
                //Fais une pause pour eviter que les joueurs aient le m�me deck lors des 2 premiers tours
                std::this_thread::sleep_for(std::chrono::milliseconds(100));

            }
            else if(i==1){
                // Verifie qu'il ya un IA et que c'est le dernier Joueur
                if(IAb and i==nbJoueur-1){
                    //Cr�� la partie pour le Joueur en mettant les cartes qu'il faut dans le deck et la main
                    plateauJeu.CreationPartie(IA);
                    //Ajoute les joueurs � la liste des joueurs
                    plateauJeu.ajouterJoueur(IA);
                }
                else{
                    //Cr�� la partie pour le Joueur en mettant les cartes qu'il faut dans le deck et la main
                    plateauJeu.CreationPartie(Joueur2);
                    //Ajoute les joueurs � la liste des joueurs
                    plateauJeu.ajouterJoueur(Joueur2);
                    //Fais une pause pour eviter que les joueurs aient le m�me deck lors des 2 premiers tours
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }


            }
            else if(i==2){
                // Verifie qu'il ya un IA et que c'est le dernier Joueur
                if(IAb and i==nbJoueur-1){
                    //Cr�� la partie pour le Joueur en mettant les cartes qu'il faut dans le deck et la main
                    plateauJeu.CreationPartie(IA);
                    //Ajoute les joueurs � la liste des joueurs
                    plateauJeu.ajouterJoueur(IA);
                }
                else{
                    //Cr�� la partie pour le Joueur en mettant les cartes qu'il faut dans le deck et la main
                    plateauJeu.CreationPartie(Joueur3);
                    //Ajoute les joueurs � la liste des joueurs
                    plateauJeu.ajouterJoueur(Joueur3);
                    //Fais une pause pour eviter que les joueurs aient le m�me deck lors des 2 premiers tours
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
            }
            else{
                // Verifie qu'il ya un IA et que c'est le dernier Joueur
                if(IAb and i==nbJoueur-1){
                    //Cr�� la partie pour le Joueur en mettant les cartes qu'il faut dans le deck et la main
                    plateauJeu.CreationPartie(IA);
                    //Ajoute les joueurs � la liste des joueurs
                    plateauJeu.ajouterJoueur(IA);
                }
                else{
                    //Cr�� la partie pour le Joueur en mettant les cartes qu'il faut dans le deck et la main
                    plateauJeu.CreationPartie(Joueur4);
                    //Ajoute les joueurs � la liste des joueurs
                    plateauJeu.ajouterJoueur(Joueur4);
                }
            }
        }

    }
    //Le jeu continue tant que le joueur ne souhaite pas sauvegarder ou que la partie n'est pas termin�e.
    while(plateauJeu.FinDePartie() and plateauJeu.getSauvegarde() ==false){
        if(tour%nbJoueur==0){
            std::cout<<"\n -------------------------------------------------------------------------------"<<std::endl;
            std::cout<<"\n .C'est au tour de "<<Joueur1->getNom()<<" : "<<std::endl;
            std::cout<<"\n";
            // Effectue le tour du joueur avec ses achats et ses actions
            plateauJeu.EffectuerTour(Joueur1);
        }
        else if (tour%nbJoueur==1){
            // Verifie qu'il ya un IA et que c'est le dernier Joueur
            if(IAb and (tour%nbJoueur)-nbJoueur==-1){
                std::cout<<"\n -------------------------------------------------------------------------------"<<std::endl;
                std::cout<<"\n C'est au tour de l' "<<IA->getNom()<<std::endl;
                std::cout<<"\n";
                // Effectue le tour de l'IA avec ses achats et ses actions en fonction du tour actuel de l'IA
                plateauJeu.EffectuerTourIA(IA,ko);
                ko=ko+1;
            }
            else{
               std::cout<<"\n -------------------------------------------------------------------------------"<<std::endl;
                std::cout<<"\n .C'est au tour de "<<Joueur2->getNom()<<" : "<<std::endl;
                std::cout<<"\n";
                // Effectue le tour du joueur avec ses achats et ses actions
                plateauJeu.EffectuerTour(Joueur2);
            }

        }

        else if (tour%nbJoueur==2){
            // Verifie qu'il ya un IA et que c'est le dernier Joueur
            if(IAb and (tour%nbJoueur)-nbJoueur==-1){
                std::cout<<"\n -------------------------------------------------------------------------------"<<std::endl;
                std::cout<<"\n C'est au tour de l' "<<IA->getNom()<<std::endl;
                std::cout<<"\n";
                // Effectue le tour de l'IA avec ses achats et ses actions en fonction du tour actuel de l'IA
                plateauJeu.EffectuerTourIA(IA,ko);
                ko=ko+1;
            }
            else{
                std::cout<<"\n -------------------------------------------------------------------------------"<<std::endl;
                std::cout<<"\n .C'est au tour de "<<Joueur3->getNom()<<" : "<<std::endl;
                std::cout<<"\n";
                // Effectue le tour du joueur avec ses achats et ses actions
                plateauJeu.EffectuerTour(Joueur3);
            }

        }
        else if (tour%nbJoueur==3){
            // Verifie qu'il ya un IA et que c'est le dernier Joueur
            if(IAb and (tour%nbJoueur)-nbJoueur==-1){
                std::cout<<"\n -------------------------------------------------------------------------------"<<std::endl;
                std::cout<<"\n C'est au tour de l' "<<IA->getNom()<<std::endl;
                std::cout<<"\n";
                // Effectue le tour de l'IA avec ses achats et ses actions en fonction du tour actuel de l'IA
                plateauJeu.EffectuerTourIA(IA,ko);
                ko=ko+1;
            }
            else{
                std::cout<<"\n -------------------------------------------------------------------------------"<<std::endl;
                std::cout<<"\n .C'est au tour de "<<Joueur4->getNom()<<" : "<<std::endl;
                std::cout<<"\n";
                // Effectue le tour du joueur avec ses achats et ses actions
                plateauJeu.EffectuerTour(Joueur4);
            }

        }

        //Incr�mente le nombre de tour
        tour++;
        //Met � jour le npmbre de tour pour le plateau de jeu
        //Sert pour une r�cuperation de sauveagarde
        plateauJeu.setTour(tour);


    }
    //Se lance si le joueur a demand� une sauvegarde
    if(plateauJeu.getSauvegarde()){
        for (int i =0; i<nbJoueur; i++){
            if (i==0){
                // Mets les infos du joueur dans le fichier CSV
                plateauJeu.MettreDansCSV(Joueur1, "sauvegarde.csv");

            }
            else if(i==1){
                // Verifie qu'il ya un IA et que c'est le dernier Joueur
                if(IAb and i==nbJoueur-1){
                    // Mets les infos du joueur dans le fichier CSV
                    plateauJeu.MettreDansCSV(IA, "sauvegarde.csv");
                }
                else{
                    // Mets les infos du joueur dans le fichier CSV
                    plateauJeu.MettreDansCSV(Joueur2, "sauvegarde.csv");
                }

            }
            else if(i==2){
                // Verifie qu'il ya un IA et que c'est le dernier Joueur
                if(IAb and i==nbJoueur-1){
                    // Mets les infos du joueur dans le fichier CSV
                    plateauJeu.MettreDansCSV(IA, "sauvegarde.csv");
                }
                else{
                    // Mets les infos du joueur dans le fichier CSV
                    plateauJeu.MettreDansCSV(Joueur3, "sauvegarde.csv");
                }
            }
            else{
                // Verifie qu'il ya un IA et que c'est le dernier Joueur
                if(IAb and i==nbJoueur-1){
                    // Mets les infos du joueur dans le fichier CSV
                    plateauJeu.MettreDansCSV(IA, "sauvegarde.csv");
                }
                else{
                    // Mets les infos du joueur dans le fichier CSV
                    plateauJeu.MettreDansCSV(Joueur4, "sauvegarde.csv");
                }

            }
    }
    }
    else{
        for (int i =0; i<nbJoueur; i++){
            if (i==0){
                //Verifie le score du Joueur
                a= plateauJeu.QuiGagne(Joueur1);
            }
            else if(i==1){
                // Verifie qu'il ya un IA et que c'est le dernier Joueur
                if(IAb and i==nbJoueur-1){
                    //Verifie le score du Joueur
                    b=plateauJeu.QuiGagne(IA);
                }
                else{
                    //Verifie le score du Joueur
                    b=plateauJeu.QuiGagne(Joueur2);
                }
            }
            else if(i==2){
                // Verifie qu'il ya un IA et que c'est le dernier Joueur
                if(IAb and i==nbJoueur-1){
                    //Verifie le score du Joueur
                    c=plateauJeu.QuiGagne(IA);
                }
                else{
                    //Verifie le score du Joueur
                    c=plateauJeu.QuiGagne(Joueur3);
                }
            }
            else{
                // Verifie qu'il ya un IA et que c'est le dernier Joueur
                if(IAb and i==nbJoueur-1){
                    //Verifie le score du Joueur
                    d=plateauJeu.QuiGagne(IA);
                }
                else{
                    //Verifie le score du Joueur
                    d=plateauJeu.QuiGagne(Joueur4);
                }
            }
        }
        //Cherche le maximum parmis ses scores
        int maximum = std::max({a, b, c, d});
        //Si l'IA gagne ca sera le dernier joueur parmis les joueurs
        //Si il y a 3 joueurs l'IA sera le joueur 3
        if (maximum == a) {
            // Joueur1 a le score le plus �lev�
            std::cout << "\n Le joueur 1 a le score le plus eleve : " << a <<". Ce joueur a donc gagne !"<<std::endl;
            std::cout << "\n";
        } else if (maximum == b) {
            // Joueur2 a le score le plus �lev�

            std::cout << "\n Le joueur 2 a le score le plus eleve : " << b <<". Ce joueur a donc gagne !"<< std::endl;
            std::cout << "\n";
        } else if (maximum == c) {
            // Joueur3 a le score le plus �lev�
            std::cout << "\n Le joueur 3 a le score le plus eleve : " << c <<". Ce joueur a donc gagne !"<< std::endl;
            std::cout << "\n";
        } else {
            // Joueur4 a le score le plus �lev�
            std::cout << "\n Le joueur 4 a le score le plus eleve : " << d <<". Ce joueur a donc gagne !"<< std::endl;
            std::cout << "\n";
        }
    }
    return 0;

}
