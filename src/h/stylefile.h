#ifndef STYLEFILE_H
#define STYLEFILE_H
#include <string>
#include <QString>

class StyleFile
{
private:
    std::string id;
    std::string name;
    std::string police;
    int policeSize;
    std::string color;
    bool gras;
    bool italique;
    bool souligne;
    bool shadow;
public:

    StyleFile(const std::string& id,const std::string& name,const std::string& police,const int& policeSize,const std::string& color,const bool& gras,const bool& italique,const bool& souligne,const bool& shadow);
    StyleFile();

    std::string getId() const;

    std::string getPolice()const ;


    int getPoliceSize()const;

    std::string getColor()const ;

    std::string getName()const ;

    bool isGras() const ;

    bool isItalique() const;


    bool isSouligne() const;

    bool isShadow() const ;

    QString toQString()const ;
};

#endif // STYLEFILE_H
