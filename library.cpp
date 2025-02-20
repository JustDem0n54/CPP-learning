
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

struct Livre {
    std::string titre;
    std::string auteur;
    int annee;
};

// Fonction pour lire les arguments et créer un livre
Livre parseArguments(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <titre> <auteur> <annee>\n";
        exit(1);
    }
    Livre livre;
    livre.titre = argv[1];
    livre.auteur = argv[2];
    livre.annee = std::atoi(argv[3]); // Convertir l'année en entier
    return livre;
}

// Fonction pour sauvegarder un livre dans un fichier
void sauvegarderLivre(const Livre& livre, const std::string& fichier) {
    std::ofstream ofs(fichier, std::ios::app); // Ouverture en mode append
    if (!ofs) {
        std::cerr << "Erreur d'ouverture du fichier !\n";
        return;
    }
    ofs << livre.titre << ";" << livre.auteur << ";" << livre.annee << "\n";
    ofs.close();
}

void afficherLivres(const std::string& fichier) {
    std::ifstream test(fichier);
    if (!test) {
        std::cerr << "Aucun fichier trouvé, liste vide.\n";
        return;
    }

    std::string titre, auteur, annee;
    std::cout << "Liste des livres enregistrés :\n";
    while (std::getline(test, titre, ';') &&
           std::getline(test, auteur, ';') &&
           std::getline(test, annee)) {
        std::cout << "- " << titre << " de " << auteur << " (" << annee << ")\n";
    }

    test.close();
}

int main(int argc, char* argv[]) {
    const std::string fichier = "livres.txt";
    afficherLivres(fichier);
    Livre nouveauLivre = parseArguments(argc, argv);
    sauvegarderLivre(nouveauLivre, fichier);

    std::cout << "Livre ajouté : " << nouveauLivre.titre << " de " 
              << nouveauLivre.auteur << " (" << nouveauLivre.annee << ")\n";

    return 0;
}