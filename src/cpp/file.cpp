#include "file.h"
#include <QString>
#include <QFileInfo>
#include <QProcess>

//initialisation de l'attribut statique (obligatoire)
QString File::radical = QString();
/**
 * @brief File::File Constructeur qui construit un objet File sans path
 * @author malek
 */
File::File(){
    this->path="";
}
/**
 * @brief File::File Constructeur qui construit un objet de type File à partir de son chemin d'accès
 * @param path : chemin d'accès du fichier
 * @author malek
 */
File::File(std::string path) :
        path(path){}
/**
 * @brief File::getPath
 * @return la valeur de l'attribut path (le chemin d'accès du fichier)
 * @author malek
 */
std::string File::getPath() const{
    return path;
}

/**
 * @brief File::existFile vérifie si un fichier existe dans le pc de l'utilisateur
 * @return vrai si un fichier existe dans le pc de l'utilisateur, faux sinon
 * @author malek
 */
bool File::existFile() const{
    QString filePath = QString::fromStdString(this->path); // Remplace par ton chemin
    QFile file(filePath);
    return file.exists();
}


/**
 * @brief File::getNom
 * @return le nom du fichier
 * @author malek
 */
QString File::getNom() const{
    QString filePath = QString::fromStdString(this->path);
    QFileInfo file(filePath);
    return file.fileName();
}

QString File::getRadical()
{
    return radical;
}


/**
 * @brief File::isWord vérifie si un fichier est un fichier word à partir de son extension
 * @return vrai si le fichier est un fichier word, faux sinon
 * @author malek
 */
bool File::isWord()
{
    bool isword = false;
    QString filePath = QString::fromStdString(this->path);
    QFileInfo file(filePath);
    QString extension = file.suffix();
    if(extension == "docx" || extension == "doc"){
        isword=true;
    }
    return isword;
}

/**
 * @brief File::isExcel vérifie si un fichier est un fichier excel à partir de son extension
 * @return vrai si le fichier est un fichier excel, faux sinon
 * @author malek
 */
bool File::isExcel()
{
    bool isexcel = false;
    QString filePath = QString::fromStdString(this->path);
    QFileInfo file(filePath);
    QString extension = file.suffix();
    if(extension == "xlsx" || extension == "xls"){
        isexcel=true;
    }
    return isexcel;
}

/**
 * @brief File::isCsv vérifie si un fichier est un fichier csv à partir de son extension
 * @return vrai si le fichier est un fichier csv, faux sinon
 * @author malek
 */
bool File::isCsv()
{
    bool iscsv = false;
    QString filePath = QString::fromStdString(this->path);
    QFileInfo file(filePath);
    QString extension = file.suffix();
    if(extension == "csv" || extension == "csv"){
        iscsv=true;
    }
    return iscsv;
}

/**
 * @brief Définit le radical associé au fichier.
 *
 * Cette méthode permet d'assigner un radical (identifiant de base) à un fichier. Le radical est stocké
 * dans l'attribut "radical" de la classe "File".
 *
 * @param radical Le radical à associer au fichier.
 * @return void
 * @author Malek
 */
void File::setRadical(QString radical)
{
    File::radical=radical;
}







