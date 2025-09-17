#ifndef FILE_H
#define FILE_H
#include <string>
#include <QString>

class File
{
private:
    std::string path;
    static QString radical;

public:
    File();
    File(std::string path);
    std::string getPath() const;
    bool existFile() const;
    QString getNom() const;
    static QString getRadical();
    static void setRadical (QString radical);
    bool isWord();
    bool isExcel();
    bool isCsv();

    virtual void debug() const {}


};


#endif // FILE_H
