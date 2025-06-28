#include "../include/CarteAction.h"
#define RESET   "\033[0m"
#define RED     "\033[91m"
#define GREEN   "\033[92m"
#define YELLOW  "\033[93m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[96m"
#define WHITE   "\033[37m"
#define GRAY "\033[37m"
#define PURPLE "\033[95m"

/*
 * Constructeur de la classe CarteAction.
 * @param nom Le nom de la carte.
 * @param prix Le prix de la carte.
 * @param type Le type de la carte.
 * @param nbActinos Le nombre d'actions associé à la carte Action.
 */
CarteAction::CarteAction(const std::string& nom, int prix, std::string type,int nbActions) : Carte(nom, prix,type), nbActions(nbActions) {}

/*
 * Obtient le nombre d'action de la carte action.
 * @return le nombre d'action de la carte trésor.
 */
int CarteAction::getNbActions() const{
    return nbActions;
}

/*
 * Affiche les détails de la carte d'action.
 */
void CarteAction::Afficher() const  {
    Carte::Afficher();
    std::cout << "\n";
}

/*
 * Exécute l'action de la carte Cave.
 * @param j Le joueur effectuant l'action.
 */
void CarteAction::executerActionCave(std::shared_ptr<Joueur>j) {
    int i=0;
    bool b=false;
    std::cout << "\n Effet de la carte Cave : Vous gagnez "<<RED<<"1 action "<<RESET<<"et vous pouvez defausser un certain nombre de carte et vous piocher le meme nombre de carte." << std::endl;
    j->setNmbAction(1);
    std::string CartesADefauser;
    //Verifie si le joueur n'est pas l'IA
    if(j->getNom()!="IA"){
        do{
            std::cout << "\n Quelles cartes voulez vous defausser (mettre aucune pour arreter) ? : "<<std::endl;
            std::cout << "\n";
            j->AfficherCartesRestantes2(j->getCarteMain());
            std::cout << "\n Carte que vous voulez defausser : ";
            std::cin >> CartesADefauser;
            for (const auto& cartePtr : j->getCarteMain()){
                    if(cartePtr->getNom()==CartesADefauser){
                        //La carte est trouvee et peut alors etre defaussee
                        j->ajouterCarteDefausse(cartePtr);
                        j->retirerCarteMain(cartePtr);
                        i=i+1;
                        b=true;
                        break;
                    }

            }
            if(!b && CartesADefauser!="aucune"){
                std::cout<<"\n Vous n'avez pas cette carte"<<std::endl;
            }
        b=false;
        }while(CartesADefauser!="aucune" and j->getCarteMain().size()>0);
    }
    else{
        for (const auto& cartePtr : j->getCarteMain()){
            if(cartePtr->getType()=="victoire" or cartePtr->getType()=="malediction" ){
                j->ajouterCarteDefausse(cartePtr);
                j->retirerCarteMain(cartePtr);
                i=i+1;
                break;
            }
        }
    }
        while(i>0){
            j->ajouterCarteMain();
            i=i-1;
        }

        if(j->getNom()!="IA"){
            std::cout << "\n Votre nouvelle main a la fin de cette action :" << std::endl;
            std::cout << "\n";
            j->AfficherCartesRestantes2(j->getCarteMain());

        }
}

/*
 * Exécute l'action de la carte Bucheron.
 * @param j Le joueur effectuant l'action.
 */
void CarteAction::executerActionBucheron(std::shared_ptr<Joueur>j) {
    std::cout << "\n Effet de la carte Bucheron : Vous gagnez "<<YELLOW<<"1 achat"<<RESET<<" et "<<YELLOW<<"2 pieces"<<RESET<<" de plus." << std::endl;
    j->setNmbAchat(1);
    if(j->getNom()!="IA"){
        std::cout << "\n Votre main : " << std::endl;
        std::cout << "\n";
        j->AfficherCartesRestantes2(j->getCarteMain());
    }
}

/*
 * Exécute l'action de la carte Village.
 * @param j Le joueur effectuant l'action.
 */
void CarteAction::executerActionVillage(std::shared_ptr<Joueur>j) {
    std::cout << "\n Effet de la carte Village : Piochez 1 carte et vous gagnez "<<RED<<"2 actions" <<RESET<< std::endl;
    j->setNmbAction(2);
    //Le joueur pioche une carte
    j->ajouterCarteMain();
    j->retirerCarteDeck();
    if(j->getNom()!="IA"){
        std::cout << "\n Votre nouvelle main a la fin de cette action :" << std::endl;
        std::cout << "\n";
        j->AfficherCartesRestantes2(j->getCarteMain());
    }
}

/*
 * Exécute l'action de la carte Chapelle.
 * @param j Le joueur effectuant l'action.
 */
void CarteAction::executerActionChapelle(std::shared_ptr<Joueur>j) {
    int i=0, k=0;
    bool b=false;
    std::cout << "\n Effet de la carte Chapelle : Vous pouvez ecarter jusqu'a 4 cartes de votre main." << std::endl;
    std::string CartesAEcarter;
    if(j->getNom()!="IA"){
        do{
            std::cout << "\n Quelles cartes voulez vous ecarter (mettre aucune pour arreter) ? Vous pouvez encore en ecarter : " <<4-i<< std::endl;
            std::cout << "\n";
            j->AfficherCartesRestantes2(j->getCarteMain());
            std::cout << "\n Carte que vous voulez ecarter : ";
            std::cin >> CartesAEcarter;
            std::cout << "\n";
            for (const auto& cartePtr : j->getCarteMain()){
                    if(cartePtr->getNom()==CartesAEcarter){
                        j->retirerCarteMain(cartePtr);
                        i=i+1;
                        b=true;
                        break;
                    }
            }
            if(!b && CartesAEcarter!="aucune"){
                std::cout<<"Vous n'avez pas cette carte en main"<<std::endl;
            }
        b=false;
        }while(CartesAEcarter!="aucune" and i!=4);
        j->AfficherCartesRestantes2(j->getCarteMain());
    }
    else{
        while(i!=4 and k!=4){
            for (const auto& cartePtr : j->getCarteMain()){
                if(cartePtr->getType()=="malediction" ){
                    j->retirerCarteMain(cartePtr);
                    i=i+1;
                    break;
                }
            }
            k=k+1;
        }
    }
    if(j->getNom()!="IA"){
        std::cout << "\n Votre nouvelle main a la fin de cette action :" << std::endl;
        std::cout << "\n";
        j->AfficherCartesRestantes2(j->getCarteMain());
    }
}

/*
 * Exécute l'action de la carte Marche.
 * @param j Le joueur effectuant l'action.
 */
void CarteAction::executerActionMarche(std::shared_ptr<Joueur>j) {
    std::cout << "\n Effet de la carte Marche : Piochez 1 carte, vous gagnez "<<RED<<"1 action"<<RESET<<", vous gagnez "<<YELLOW<<"1 achat"<<RESET<<" et vous gagnez "<<YELLOW<<"1 piece"<<RESET<<" de plus." << std::endl;
    j->setNmbAction(1 );
    j->setNmbAchat(1);
    j->ajouterCarteMain();
    j->retirerCarteDeck();
    if(j->getNom()!="IA"){
        std::cout << "\n Votre nouvelle main a la fin de cette action :" << std::endl;
        std::cout << "\n";
        j->AfficherCartesRestantes2(j->getCarteMain());
    }
}

/*
 * Exécute l'action de la carte Renovation.
 * @param j Le joueur effectuant l'action.
 * @return La valeur correspondant au coût de la carte écartée.
 */
int CarteAction::executerActionRenovation(std::shared_ptr<Joueur>j) {
    bool b=false, c=false;
    int n=0;
    std::cout << "\n Effet de la carte Renovation : Ecarter 1 carte de votre main et recevez une carte coutant jusqu'a "<<YELLOW<<"2 pieces"<<RESET<<" de plus que la carte ecartee." << std::endl;
    std::string CarteAEcarter;
    if(j->getNom()!="IA"){
        do {
            std::cout << "\n Quelle carte voulez vous ecarter (mettre aucune pour arreter) ? " << std::endl;
            std::cout << "\n";
            j->AfficherCartesRestantes2(j->getCarteMain());
            std::cout << "\n";
            std::cin >> CarteAEcarter;
            std::cout << "\n";
            for (const auto& cartePtr : j->getCarteMain()){
                if(cartePtr->getNom()==CarteAEcarter){
                    //La carte est trouvee et peut etre ecartee
                    j->retirerCarteMain(cartePtr);
                    b=true;
                    n=cartePtr->getPrix();
                    break;
                }
            }
            if(!b){
                std::cout<<"Vous n'avez pas cette carte en main"<<std::endl;
            }
        }while(b==false);
    }
    else{
       for (const auto& cartePtr : j->getCarteMain()){
            if(cartePtr->getType()=="malediction" ){
                j->retirerCarteMain(cartePtr);
                n=2;
                b=true;
                break;
            }
       }
       if(!b){
           for (const auto& cartePtr : j->getCarteMain()){
                if(cartePtr->getNom()=="Domaine" ){
                    j->retirerCarteMain(cartePtr);
                    n=4;
                    c=true;
                    break;
                }
           }
       }
       if(!b and !c ){
            n=-1;
       }
    }
   if(j->getNom()!="IA"){
        std::cout << "\n Votre nouvelle main a la fin de cette action :" << std::endl;
        std::cout << "\n";
        j->AfficherCartesRestantes2(j->getCarteMain());
    }
    return n;
}

/*
 * Exécute l'action de la carte Forgeron.
 * @param j Le joueur effectuant l'action.
 */
void CarteAction::executerActionForgeron(std::shared_ptr<Joueur>j) {
    int i=0;
    std::cout << "\n Effet de la carte Forgeron : Piochez 3 cartes." << std::endl;
    while(i!=3) {
        j->ajouterCarteMain();
        j->retirerCarteDeck();
        i=i+1;
    }
    if(j->getNom()!="IA"){
        std::cout << "\n Votre nouvelle main a la fin de cette action :" << std::endl;
        std::cout << "\n";
        j->AfficherCartesRestantes2(j->getCarteMain());
    }
}

/*
 * Exécute l'action de la carte Mine
 * @param j Le joueur effectuant l'action.
 * @return La valeur correspondant au coût de la nouvelle carte Trésor obtenue.
 */
int CarteAction::executerActionMine(std::shared_ptr<Joueur>j) {
    bool b=false;
    int n=0, n2=-1;
    std::cout << "\n Effet de la carte Mine : Vous pouvez ecarter "<<YELLOW<<"1 carte Tresor"<<RESET<<" de votre main et recevez "<<YELLOW<<"1 carte Tresor "<<RESET<<"coutant jusqu'a "<<YELLOW<<"3 pieces "<<RESET<<"de plus que la carte ecartee." << std::endl;
    std::string CarteAEcarter;
    if(j->getNom()!="IA"){
        do {
            std::cout << "\n Quelle "<<YELLOW<<"carte Tresor "<<RESET<<"voulez vous ecarter (mettre aucune pour arreter) ? " << std::endl;
            std::cout << "\n";
            j->AfficherCartesRestantesTresor(j->getCarteMain());
            std::cout << "\n";
            std::cin >> CarteAEcarter;
            std::cout << "\n";
            for (const auto& cartePtr : j->getCarteMain()){
                if(cartePtr->getNom()==CarteAEcarter && cartePtr->getType()=="tresor" ){
                    b=true;
                    j->retirerCarteMain(cartePtr);
                    n=cartePtr->getPrix();
                    break;
                }
            }
            if(!b){
                std::cout<<"\n Vous n'avez pas cette carte en main ou alors ce n'est pas une "<<YELLOW<<"carte Tresor"<<RESET<<std::endl;
            }
        }while(b==false && CarteAEcarter != "aucune");
        if(CarteAEcarter == "aucune") {
            n=-1;
        }
    }
    else{
        for (const auto& cartePtr : j->getCarteMain()){
            if(cartePtr->getType()=="tresor" and cartePtr->getPrix()>n2 and cartePtr->getNom()!="Or"){
                j->retirerCarteMain(cartePtr);
                n2=cartePtr->getPrix()+3;
            }
       }
       n=n2;
    }
    return n;
}

/*
 * Exécute l'action de piocher 2 cartes.
 * @param j Le joueur effectuant l'action.
 */
void CarteAction::executerActionSorciere(std::shared_ptr<Joueur>j){
     std::cout << "\n Effet de la carte Sorciere : Piocher 2 cartes et tous vos adversaires recoivent "<<PURPLE<<"1 carte Malediction." <<RESET<< std::endl;
     for (int i=0; i<2;i++){
        j->ajouterCarteMain();
        j->retirerCarteDeck();
     }
}

/*
 * Exécute l'action de mettre une carte malediction aux adversaires.
 * @param joueur Le joueur effectuant l'action.
 * @param pj Le plateau de jeu.
 */
void CarteAction::executerActionSorciere2(std::shared_ptr<Joueur>joueur, PlateauJeu* pj){
    for (const auto& cartePtr2 : pj->getCartes2()) {
        if(cartePtr2-> getNom()=="Malediction"){
            joueur->ajouterCarteDefausseDepuisPlateau(cartePtr2);
            pj->RetirerCarte(cartePtr2);
            pj->FinDePartie();
            break;
        }
    }
}

/*
 * Exécute l'action de la carte Festin : Retire la carte Festin de la main du joueur.
 * @param joueur Le joueur effectuant l'action.
 */
void CarteAction::executerActionFestin(std::shared_ptr<Joueur> joueur){
    for (const auto& cartePtr : joueur->getCarteMain()){
            if(cartePtr->getNom()=="Festin"){
                joueur->retirerCarteMain(cartePtr);
                break;
            }
        }
}

/*
 * Exécute l'action de la carte Festival : augmente le nombre d'actions et d'achat du joueur.
 * @param j Le joueur effectuant l'action.
 */
void CarteAction::executerActionFestival(std::shared_ptr<Joueur> j) {
    std::cout << "\n Effet de la carte Festival : Vous gagnez "<<RED<<"2 actions"<<RESET<<", vous gagnez "<<YELLOW<<"1 achat"<<RESET<<" et vous gagnez "<<YELLOW<<"2 pieces"<<RESET<<" de plus." << std::endl;
    j->setNmbAction(2);
    j->setNmbAchat(1);
}

/*
 * Exécute l'action de la carte Laboratoire.
 * @param j Le joueur effectuant l'action.
 */
void CarteAction::executerActionLaboratoire(std::shared_ptr<Joueur> j) {
    int i=0;
    std::cout << "\n Effet de la carte Laboratoire : Vous piocher 2 cartes et vous gagnez "<<RED<<"1 action." <<RESET<< std::endl;
    j->setNmbAction(1);
    while(i!=2) {
        j->ajouterCarteMain();
        j->retirerCarteDeck();
        i=i+1;
    }
    if(j->getNom()!="IA"){
        std::cout << "\n Votre nouvelle main a la fin de cette action :" << std::endl;
        std::cout << "\n";
        j->AfficherCartesRestantes2(j->getCarteMain());
    }
}

/*
 * Exécute l'action de la carte Prêteur sur gages : Écarter 1 carte Cuivre de votre main et recevoir 3 pièces.
 * @param j Le joueur effectuant l'action.
 * @return true si le joueur a une carte cuivre, sinon false.
 */
bool CarteAction::executerActionPreteurSurGages(std::shared_ptr<Joueur> j) {
    bool b=false;
    bool n=true;
    std::cout << "\n Effet de la carte Preteur sur gages : ecarter "<<YELLOW<<"1 carte Cuivre"<<RESET<<" de votre main et recevez alors "<<YELLOW<<"3 pieces." <<RESET << std::endl;
    for (const auto& cartePtr : j->getCarteMain()){
        if(cartePtr->getNom()=="Cuivre" ){
            b=true;
            j->retirerCarteMain(cartePtr);
            break;
        }
    }
    if(!b){
        std::cout<<"\n Vous n'avez pas de carte "<<YELLOW<<"Cuivre"<<RESET<<std::endl;
        n=false;
    }
    if(j->getNom()!="IA"){
        std::cout << "\n Votre main apres l'action :" << std::endl;
        std::cout << "\n";
        j->AfficherCartesRestantes2(j->getCarteMain());
    }
    return n;
}

/*
 * Exécute l'action de la carte Chancelier.
 * @param j Le joueur effectuant l'action.
 */
void CarteAction::executerActionChancelier(std::shared_ptr<Joueur> j) {
    std::cout << "\n Effet de la carte Chancelier : Vous gagnez "<<YELLOW<<"2 pieces"<<RESET<<" et vous pouvez immediatement defausser votre deck." << std::endl;
    std::string reponse;
    if(j->getNom()!="IA"){
        do {
            std::cout << "\n Voulez vous defausser tout votre deck ? ";
            std::cin>>reponse;
            if(reponse == "Oui") {
                for (const auto& cartePtr : j->getCarteDeck()){
                        j->ajouterCarteDefausse(cartePtr);
                        j->retirerCarteDeck();
                }
                std::cout<<"\n Votre deck a bien ete defausse"<<std::endl;
                break;
            }
        }while(reponse!="Non");
    }
    else{
        for (const auto& cartePtr : j->getCarteDeck()){
            j->ajouterCarteDefausse(cartePtr);
            j->retirerCarteDeck();
        }
    }
    if(j->getNom()!="IA"){
        std::cout << "\n Votre main :" << std::endl;
        std::cout << "\n";
        j->AfficherCartesRestantes2(j->getCarteMain());
    }
}

/*
 * Exécute l'action de la carte Bibliothèque.
 * @param j Le joueur effectuant l'action.
 */
void CarteAction::executerActionBibliotheque(std::shared_ptr<Joueur> j) {
    std::cout << "\n Effet de la carte Bibliotheque : Piocher jusqu'a ce que vous ayez 7 cartes en main. Chaque carte Action piochee peut etre mise de cote. Defaussez les cartes mises de cote lorsque vous avez termine de piocher" << std::endl;
    int tailleMain = j->getSizeMain();
    std::string reponse;
    if(j->getNom()!="IA"){
        std::cout<<"\n Vous avez actuellement "<<tailleMain<<" cartes en main, vous devez en piocher "<<7-tailleMain<<std::endl;
        //Effectue l'action tant que le joueur n'a pas 7 cartes en main
        while(j->getSizeMain()!=7) {
            //On verifie si la carte piochee est une carte action ou pas
            if((j->getCarteDeck().at(j->getCarteDeck().size()-1))->getType()=="action") {
                do {
                    std::cout<<"\n Voulez vous mettre la carte action "<<(j->getCarteDeck().at(j->getCarteDeck().size()-1))->getNom()<<" de cote ? ";
                    std::cin>>reponse;
                    if(reponse == "Oui") {
                        j->ajouterCarteDefausse((j->getCarteDeck().at(j->getCarteDeck().size()-1)));
                        j->retirerCarteDeck();
                    }
                    else if(reponse == "Non"){
                        j->ajouterCarteMain();
                        j->retirerCarteDeck();
                    }
                }while(reponse !="Oui" && reponse !="Non");
            }
            else {
                j->ajouterCarteMain();
                j->retirerCarteDeck();
            }
        }
    }
    else{
        while(j->getSizeMain()!=7) {
            if((j->getCarteDeck().at(j->getCarteDeck().size()-1))->getType()=="action") {
                j->ajouterCarteDefausse((j->getCarteDeck().at(j->getCarteDeck().size()-1)));
                j->retirerCarteDeck();
            }
            else {
                j->ajouterCarteMain();
                j->retirerCarteDeck();
            }
        }
    }
     if(j->getNom()!="IA"){
        std::cout << "\n Votre main apres l'action :" << std::endl;
        std::cout << "\n";
        j->AfficherCartesRestantes2(j->getCarteMain());
    }
}

/*
 * Exécute l'action de la carte Chambre du conseil..
 * @param j Le joueur effectuant l'action.
 */
void CarteAction::executerActionChambreDuConseil (std::shared_ptr<Joueur>j) {
    int i=0;
    std::cout << "\n Effet de la carte Chambre du conseil : Vous piocher 4 cartes, vous gagnez "<<RED<<"1 achat et tous vos adversaire piochent 1 carte."<<RESET<< std::endl;
    j->setNmbAchat(1);
    while(i!=4) {
        j->ajouterCarteMain();
        j->retirerCarteDeck();
        i=i+1;
    }
}

/*
 * Exécute l'action de la carte Espion.
 * @param j Le joueur effectuant l'action.
 */
void CarteAction::executerActionEspion (std::shared_ptr<Joueur>j) {
    std::cout << "\n Effet de la carte Espion : Vous piocher 1 carte, vous gagnez "<<RED<<"1 action"<<RESET<<" et tous les joueurs (y compris vous) devoilent la premiere carte de leur deck. Vous decidez ensuite si chaque carte devoilee est defausse ou replacee sur son deck." << std::endl;
    j->setNmbAction(1);
    j->ajouterCarteMain();
    j->retirerCarteDeck();
}

/*
 * Exécute l'action de la carte Aventurier.
 * @param j Le joueur effectuant l'action.
 */
void CarteAction::executerActionAventurier(std::shared_ptr<Joueur> j) {
    std::cout << "\n Effet de la carte Aventurier : Devoilez des cartes de votre deck jusqu a que "<<YELLOW<<"2 cartes Tresor "<<RESET<<"soient devoilees. Ajoutez ces "<<YELLOW<<"cartes tresor"<<RESET<< "a votre main et defaussez les autres cartes devoilees" << std::endl;
    int nombreCartesTresor = 0;
    int i=1;
    //On effetue l'action tant que l'on a pas pioche 2 cartes Tresor
    while(nombreCartesTresor!=2) {
        //On verifie si le deck est vide
        if((j->getCarteDeck()).empty()) {
            while(!j->getCarteDefausse().empty()){
                j->MelangerCartes2();
                j->ajouterCarteDeck((j->getCarteDefausse()).back());
                j->retirerCarteDefausse();
            }
            j->ajouterCarteMain();
            j->retirerCarteDeck();
        }
        //On verifie si la carte piochee est de type tresor
        if((j->getCarteDeck().at(j->getCarteDeck().size()-1))->getType()=="tresor") {
            std::cout<<"\n Carte devoilee numero "<<i<<" : "<<(j->getCarteDeck().at(j->getCarteDeck().size()-1))->getNom()<<std::endl;
            nombreCartesTresor = nombreCartesTresor + 1;
            //On verifie que le joueur n'a pas pioche 2 cartes Tresor
            if(nombreCartesTresor==2) {
                std::cout<<"\n 2eme "<<YELLOW<<"carte tresor"<<RESET<<" devoilee : fin de l'action."<<std::endl;
            }
            j->ajouterCarteMain();
            j->retirerCarteDeck();
        }
        else {
            std::cout<<"\n Carte devoilee numero "<<i<<" : "<<(j->getCarteDeck().at(j->getCarteDeck().size()-1))->getNom()<<" (va etre defaussee)"<<std::endl;
            j->ajouterCarteDefausse((j->getCarteDeck().at(j->getCarteDeck().size()-1)));
            j->retirerCarteDeck();
        }
        i=i+1;
    }
     if(j->getNom()!="IA"){
        std::cout << "\n Votre main apres l'action :" << std::endl;
        std::cout << "\n";
        j->AfficherCartesRestantes2(j->getCarteMain());
    }
}

/*
 * Exécute l'action de la carte Milice.
 * @param j Le joueur effectuant l'action.
 * @param pj Le plateau de jeu.
 */
void CarteAction::executerActionMilice(std::shared_ptr<Joueur> j,PlateauJeu* pj) {
    std::cout << "\n Effet de la carte Milice : vous gagnez "<<YELLOW<<"2 pieces"<<RESET<<" et tous vos adversaires defaussent leurs cartes de facon a n'avoir que 3 cartes en main." << std::endl;
    std::string rep;
    int i=0;
    bool b,c ;
    //On parcourt les differents joueurs
    for (auto& joueur : pj->getJoueurs()){
        //On verifie si le joueur est celui qui effectue l'action
        if(joueur->getNom() != j->getNom()){
            if(joueur->getNom()!="IA"){
                while(joueur->getCarteMain().size()>3){
                    if(i==0) {
                       std::cout<<"\n "<<joueur->getNom()<<" c'est a vous de jouer."<<std::endl;
                        i=i+1;
                    }
                    std::cout<<"\n "<<joueur->getNom()<<", votre adversaire a utilise Milice. Il faudra donc qu'il reste 3 cartes dans votre main. (il vous reste encore "<<(joueur->getCarteMain().size()-3)<<" cartes a defausser)"<<std::endl;
                    std::cout<<"\n Voici votre main "<<joueur->getNom()<<" : "<<std::endl;
                    std::cout<<"\n";
                    joueur->AfficherCartesRestantes2(joueur->getCarteMain());
                    std::cout<<"\n Quelles cartes Voulez vous defausser ? ";
                    std::cin>>rep;
                    for (const auto& cartePtr : joueur->getCarteMain()){
                        if(cartePtr->getNom()==rep ){
                            joueur->retirerCarteMain(cartePtr);
                            joueur->ajouterCarteDefausse(cartePtr);
                            i=i+1;
                            break;
                        }
                    }
                }
            }
            else{
                while(joueur->getCarteMain().size()>3){
                    for (const auto& cartePtr : joueur->getCarteMain()){
                        if(cartePtr->getNom()=="Malediction" ){
                            joueur->retirerCarteMain(cartePtr);
                            joueur->ajouterCarteDefausse(cartePtr);
                            b=true;
                            break;
                        }
                    }
                    if(!b){
                        for (const auto& cartePtr : joueur->getCarteMain()){
                            if(cartePtr->getNom()=="Domaine" ){
                                joueur->retirerCarteMain(cartePtr);
                                joueur->ajouterCarteDefausse(cartePtr);
                                c=true;
                                break;
                            }
                        }
                    }
                    if(!b and !c){
                        for (const auto& cartePtr : joueur->getCarteMain()){
                            joueur->retirerCarteMain(cartePtr);
                            joueur->ajouterCarteDefausse(cartePtr);
                            break;
                        }
                    }
                    b=false;
                    c=false;
                }

            }
        }
    }
}


