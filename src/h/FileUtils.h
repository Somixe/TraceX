#ifndef FILE_UTILS_HPP
#define FILE_UTILS_HPP

#include <string>

class FileUtils{
    public :
    static std::string CreateCopy(const std::string& FilePath);//crée le path copy d'un fichier


    static std::string CreateZipFolder(const std::string& FilePathCopy);//crée le dossier zip à partir du fichier copié


    static std::string ExtractXmlFolder(const std::string& FilePath);// décompresse le dossier zip


    static void delete_extra(std::string& path);// supprime les fichiers inutiles
};

#endif // FILE_UTILS_HPP
