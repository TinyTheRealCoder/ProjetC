#include <iostream>
#include "Forme.h"

using namespace std;

Forme::Forme()
{
    cout << "Forme (defaut)" << endl;
    // On alloue dynamiquement un label avec une chaine vide
    m_label = new string;
}

Forme::Forme(const std::string& label)
{
    cout << "Forme (avec un label)" << endl;
    // On alloue dynamiquement un label avec une chaine vide
    m_label = new string(label);
}

Forme::Forme(const Forme& other)
{
    cout << "Forme (avec un label)" << endl;
    // On alloue dynamiquement une copie du label de other
    m_label = new string(*(other.m_label));
}

// virtual
Forme::~Forme()
{
    cout << "~Forme" << endl;
    // Dans les dernières versions de C++, il n'est plus obligatoire de tester si le pointeur
    // vaut nullptr (équivalent à NULL depuis C++11) avant d'appeler delete. Si ce pointeur
    // est nullptr, alors il ne se passe rien. De plus, dans le code écrit ici, il n'y a
    // jamais de cas où m_label vaut nullptr (le constructeur par défaut alloue une string)
    delete m_label; 
}

Forme& Forme::operator=(const Forme& other)
{
    // La Forme ne contient qu'un attribut, le label, on peut utiliser SetLabel
    SetLabel(*(other.m_label));

    // On renvoit une référence sur l'objet courant
    return *(this);
}

// #define VERSION_ALTERNATIVE // Pour activer la version alternative du code, décommenter cette ligne

void Forme::SetLabel(const std::string& label)
{
#ifdef VERSION_ALTERNATIVE
    // Version alternative
    // On réalise une affectation des std::string (std::string.operator= de fait)
    // C'est plus simple que ce qui est demandé dans le TP et ça fonctionne car nous avons
    // *une seule* std::string. Si on gérait un tableau de strings (new std::string[XXX]),
    // çà ne fonctionnerait pas
    *m_label = label;
#else
    // Version demandée
    // On libère la précédente std::string
    delete m_label;
    // On alloue une nouvelle copie de la chaine
    m_label = new string(label);
#endif
}

std::string Forme::GetLabel() const
{
    // On renvoie une copie de la chaine
    return *(m_label);
}
