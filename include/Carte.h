#ifndef CARTE_H
#define CARTE_H

#include <iostream>

class Carte
{
public:
    /*
     * Constructeur de la classe Carte.
     * @param nom Le nom de la carte.
     * @param prix Le prix de la carte.
     * @param type Le type de la carte.
     */
    Carte(const std::string& nom, int prix, std::string type);

    // Destructeur virtuel par d�faut
    virtual ~Carte() = default;


    int getPrix() const;
    std::string getNom() const;
    std::string getType() const;
    virtual void Afficher() const;

    // Op�rateur de comparaison (<) bas� sur le nom de la carte.
    bool operator<(const Carte& other) const {
        return nom < other.nom;
    }

    // Op�rateur de comparaison (==) bas� sur le nom, le prix et le type de la carte.
    bool operator==(const Carte& other) const {
        return (nom == other.nom) && (prix == other.prix) && (type == other.type);
    }

    // Constructeur de copie de la classe Carte.
    Carte(const Carte& autre);

    // Constructeur de d�placement de la classe Carte.
    Carte(Carte&& autre) noexcept;

private:
    std::string nom;
    int prix;
    std::string type;
};

#endif // CARTE_H
