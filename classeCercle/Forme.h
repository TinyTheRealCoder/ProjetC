
#ifndef __FORME_H__
#define __FORME_H__

#include <string>
#include <iostream>

class Forme
{
public:
    // Construction/Destruction
    Forme();
    Forme(const std::string& label, int IndProfond);    // Avec une string
    Forme(const Forme& other);          // Construction par recopie
    virtual ~Forme();

    // Operator d'affectation
    Forme& operator=(const Forme& other);

    // Accesseur
    void SetLabel(const std::string& s, int IndProfond);
    std::string GetLabel() const;

    // Méthodes virtuelles à déclarer dans les classes filles
    // On déclare la méthode en inline (i.e. le code est directement
    // intégré dans la déclaration de la classe).
    virtual void Display() const
    {
        std::cout << "Je suis une Forme" << std::endl;
    }

    virtual float Surface() const { return 0.0f; }
    virtual float Perimeter() const { return 0.0f; }

protected:  // ou private
    std::string * m_label;
};

#endif // __FORME_H__
