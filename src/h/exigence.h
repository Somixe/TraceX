#ifndef EXIGENCE_H
#define EXIGENCE_H

#include <string>

class Exigence
{
private:
    std::string id;
public:

    Exigence(const std::string& id);

    std::string getId() const;

    std::string toString() const;

};

#endif // EXIGENCE_H
