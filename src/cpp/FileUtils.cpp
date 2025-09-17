#include "FileUtils.h"
#include <QProcess>
#include <QString>

#include <QFileInfo>



/**
 * @brief CreateCopy : Crée le path d'une copie d'un fichier
 * @param FilePath : le chemin d'accès d'un fichier
 * @return le chemin d'accès de la copie
 * @author Malek
 */
std::string FileUtils::CreateCopy(const std::string& FilePath) {
    std::string FilePathCopy = FilePath;
    size_t pos = FilePathCopy.find_last_of(".");
    if (pos == std::string::npos) {
        exit(EXIT_FAILURE);
    }
    FilePathCopy = FilePathCopy.substr(0, pos) + "Copy" + FilePathCopy.substr(pos);
    return FilePathCopy;
}

/**
 * @brief CreateZipFolder Crée le path du dossier zip du fichier copie
 * @param FilePathCopy : le chemin d'accès du fichier copie
 * @return le path du dossier zip du fichier copie
 * @author malek
 */
std::string FileUtils::CreateZipFolder(const std::string& FilePathCopy) {
    std::string FolderZipPath = FilePathCopy;
    size_t pos = FolderZipPath.find_last_of(".");
    if (pos == std::string::npos) {
        exit(EXIT_FAILURE);
    }
    FolderZipPath = FolderZipPath.substr(0, pos) + ".zip";
    return FolderZipPath;
}



/**
 * @brief ExtractXmlFolder
 * @param FilePath : le chemin d'accès d'un fichier word ou excel
 * @return le dossier contenant les fichiers xml d'un fichier dont le path est FilePath
 * @author malek
 */
std::string FileUtils::ExtractXmlFolder(const std::string& FilePath) {

    std::string FilePathCopy = FileUtils::CreateCopy(FilePath);
    QProcess process;



#if defined(_WIN32) || defined(_WIN64)
    process.start("powershell", {"-Command", "Copy-Item ", QString("\"%1\"").arg(QString::fromStdString(FilePath)), "-Destination", QString("\"%1\"").arg(QString::fromStdString(FilePathCopy))});
#elif defined(__linux__) || defined(__APPLE__)
    process.start("cp", {
                            QString::fromStdString(FilePath),
                            QString::fromStdString(FilePathCopy)
                        });

#endif

    if (!process.waitForFinished()) {

        return "";
    }


    if (!QFileInfo::exists(QString::fromStdString(FilePathCopy))) {

        return "";
    }

    std::string ZipFolder = CreateZipFolder(FilePathCopy);



#if defined(_WIN32) || defined(_WIN64)
    process.start("powershell", {"-Command", "Rename-Item ", QString("\"%1\"").arg(QString::fromStdString(FilePathCopy)), QString("\"%1\"").arg(QString::fromStdString(ZipFolder))});
#elif defined(__linux__) || defined(__APPLE__)
    process.start("mv", {QString::fromStdString(FilePathCopy),
                         QString::fromStdString(ZipFolder)});

#endif
    if (!process.waitForFinished()) {

        return "";
    }

    if (!QFileInfo::exists(QString::fromStdString(ZipFolder))) {

        return "";
    }


    size_t pos = ZipFolder.find_last_of(".");
    std::string Folder = ZipFolder.substr(0, pos) + "Folder";



#if defined(_WIN32) || defined(_WIN64)
    process.start("powershell", {"-Command", "Expand-Archive", "-Path ", QString("\"%1\"").arg(QString::fromStdString(ZipFolder)), " -Destination ", QString("\"%1\"").arg(QString::fromStdString(Folder))});
#elif  defined(__linux__) || defined(__APPLE__)
    process.start("unzip", {QString::fromStdString(ZipFolder),
                            "-d",
                            QString::fromStdString(Folder)});


#endif
    if (!process.waitForFinished()) {

        return "";
    }

    if (!QFileInfo::exists(QString::fromStdString(Folder))) {

        return "";
    }



    return Folder;
}



/**
 * @brief delete_extra : supprime les fichiers, dossiers inutiles créés
 * @param path : le chemin d'accès du dossier contenant les fichiers xml
 * @author malek
 */
void FileUtils::delete_extra(std::string& path) {
    QProcess process;



#if defined(_WIN32) || defined(_WIN64)
    process.start("powershell", {"-Command", "Remove-Item", "-Path ", QString("\"%1\"").arg(QString::fromStdString(path)), " -Recurse", "-Force"});
#elif defined(__APPLE__) || defined(__linux__)
    process.start("rm", {"-rf", QString::fromStdString(path)});
#endif
    if (!process.waitForFinished()) {

        return;
    }

    path = path.substr(0, path.length() - 6) + ".zip";



#if defined(_WIN32) || defined(_WIN64)
    process.start("powershell", {"-Command", "Remove-Item", "-Path ", QString("\"%1\"").arg(QString::fromStdString(path)), " -Force"});
#elif defined(__APPLE__) || defined(__linux__)
    process.start("rm", {"-f", QString::fromStdString(path)});
#endif
    if (!process.waitForFinished()) {

        return;
    }


}



