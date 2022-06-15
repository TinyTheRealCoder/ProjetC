#include <iostream>
#include "Forme.h"

using namespace std;

Forme::Forme()
{
    cout << "Forme (defaut)" << endl;
    // On alloue dynamiquement un label avec une chaine vide et une profondeur avec une chaine vide
    m_label = new string;
    m_IndProfond = new int;
}

Forme::Forme(const std::string& label, int& IndProfond)
{
    cout << "Forme (avec un label et une profondeur)" << endl;
    // On alloue dynamiquement un label et une profondeur avec une chaine vide
    m_label = new string(label);
    m_IndProfondeur = new int(IndProfond);
}

Forme::Forme(const Forme& other)
{
    cout << "Forme (avec un label et une profondeur)" << endl;
    // On alloue dynamiquement une copie de la profondeur et du label de other
    m_label = new string(*(other.m_label));
    m_IndProfond = new int(*(other.m_IndProfond));
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
    delete m_IndProfond;
}

Forme& Forme::operator=(const Forme& other)
{
    // La Forme contient deux attribut, le label et IndProfond, on peut utiliser SetLabel
    SetLabel(*(other.m_label));
    SetIndProfond(*(other.m_IndProfond));

    // On renvoit une référence sur l'objet courant
    return *(this);
}
/*
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
*/
