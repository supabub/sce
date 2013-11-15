
#include "../headers/database.h"
#include "../headers/debug.h"

#ifdef _WIN32
    #include <windows.h>
#endif

#include <algorithm>
#include <boost/filesystem.hpp>



namespace sce
{
    namespace DataBase
    {
        bool pathStartWithSlash(const std::string& p);
        
        bool pathStartWithSlash(const std::string& p)
        {
            if( p.empty() )
                return false;
            
            char c = p[0];
            if( c == '/' )
                return true;
            else
                return false;
        }

        const std::string&	
        DataBase::getExecDirectory()
        {
            static std::string execDir;
            if( execDir.empty() )
            {
                boost::filesystem::path full_path( boost::filesystem::current_path() );
                execDir = full_path.c_str();
                std::transform(execDir.begin(), execDir.end(), execDir.begin(), tolower);                
            }
            return execDir;
        }

        std::string	
        DataBase::convertBackSlashToSlash(const std::string& path)
        {
            std::string newPath = path;

            for( size_t i = 0 ; i < newPath.length() ; ++i )
            {
                if( newPath[i] == '\\' )
                {
                    newPath[i] = '/';
                }
            }

            return newPath;
        }

        bool
        DataBase::createDirectory(const std::string& dir)
        {
            if( !pathStartWithSlash(dir) )
                return false;
            
            std::string newDir = getExecDirectory();
            newDir += dir;
            
            boost::filesystem::path p(newDir);
            if( boost::filesystem::create_directory(p) )
                return true;
            else
                return false;
            
        }

        bool
        DataBase::deleteDirectory(const std::string& dir)
        {
            boost::filesystem::path p = getExecDirectory() + dir;
            if( boost::filesystem::remove_all(p) != 0 )
                return true;
            else
                return false;
        }

        bool
        DataBase::deleteFile(const std::string& f)
        {
            if( doesExist(f) )
            {
                boost::filesystem::path p = getExecDirectory() + f;
                boost::filesystem::remove(p);
                return true;
            }
            else
            {
                return false;
            }
        }

        void
        DataBase::renameFile(const std::string& fileName, const std::string& newFileName)
        {
//            std::string oldFN = getExecDirectory() + fileName;
//            std::string newName = getPathFromFile(oldFN);
//            newName += newFileName;
//            rename(oldFN.c_str(), newName.c_str());
        }

        std::string	
        DataBase::getRelativePath(const std::string& fullPath)
        {		
            SCE_ASSERT_2(fullPath.find(":") != std::string::npos, "");
            SCE_ASSERT_2(fullPath.length() > getExecDirectory().length(), "");

            std::string relPath = std::string(fullPath, getExecDirectory().length(), fullPath.length()-(getExecDirectory().length()));
            return relPath;
        }

//        std::string
//        DataBase::getPathFromFile(const std::string& filePath)
//        {
//            std::string path = std::string(filePath, 0, filePath.rfind("/")+1);
//            return path;
//        }
//
//        std::string			
//        DataBase::getFileFromPath(const std::string& fp)
//        {
//            std::string fileName = std::string(fp, fp.rfind("/")+1, fp.size());
//            return fileName;
//        }

        bool
        DataBase::doesExist(const std::string& path)
        {
            std::string fullpath = getExecDirectory() + path;
            boost::filesystem::path bPath = fullpath;
            
            if (boost::filesystem::exists(boost::filesystem::status(bPath))) 
                return true;
            else
                return false;
            
            
 //           allDirs_.clear();
 //           getAllDirectories("", allDirs_);		// has to be done everytime since apps can create new dirs

 //           std::string pathToLow = path;
 //           std::transform(pathToLow.begin(), pathToLow.end(), pathToLow.begin(), tolower);

 //           std::vector<std::string>::iterator it;
 //           for( it = allDirs_.begin() ; it != allDirs_.end() ; ++it ) 
            {
 //               if( (*it).find(pathToLow) != std::string::npos )
//                    return true;
            }
//            return false;
        }

        void				
        DataBase::getAllDirectories(const std::string& startDir, std::vector<std::string>& dirs)
        {
            std::string fullPath;
            if( startDir == "" )
                fullPath = getExecDirectory();
            else
                fullPath = getExecDirectory() + startDir;
    /*
            WIN32_FIND_DATA dirDat;

            std::string ss = fullPath + "/*";	// prepare for passing the right syntax
            HANDLE found = FindFirstFile( ss.c_str(), &dirDat );
            // make the string lower case!!
            std::string s(dirDat.cFileName);
            std::transform(s.begin(), s.end(), s.begin(), tolower);

            if( s != "." && s != ".." ) {
                if( (dirDat.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0 ) {
                    dirs.push_back(startDir+"/"+s);
                    getAllDirectories(startDir+"/"+s, dirs);
                }
            }

            while( FindNextFile( found, &dirDat ) ) {
                // make the string lower case!!
                s.assign(dirDat.cFileName);
                std::transform(s.begin(), s.end(), s.begin(), tolower);

                if( s != "." && s != ".." ) {
                    if( (dirDat.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0) {
                        dirs.push_back(startDir+"/"+s);
                        getAllDirectories(startDir+"/"+s, dirs);	
                    }
                }
            }

            FindClose(found);*/
        }

        bool 
        getAllFiles(const std::string& baseDir, 
                    std::vector<std::string>& files,
                    const std::string& extension,
                    bool recursive)
        {
    /*		WIN32_FIND_DATA dirDat;

            std::string baseD;
            if( baseDir.size() != 0 && baseDir[baseDir.size()-1] != '/' )
            {
                baseD = baseDir + "/";
            }
            else
            {
                baseD = baseDir;
            }

            std::string ss = baseD + "*";			// prepare for passing the right syntax
            HANDLE found = FindFirstFile( ss.c_str(), &dirDat );

            // make the string lower case!!
            std::string s(dirDat.cFileName);
            std::transform(s.begin(), s.end(), s.begin(), tolower);

            if( s != "." && s != ".." ) {
                if( s.find(extension) != std::string::npos || extension == ".*" ) {
                    files.push_back(baseD + s);
                }
                if( (dirDat.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0 && recursive) {
                    getAllFiles(baseD +s, files, extension, recursive);
                }
            }

            while( FindNextFile( found, &dirDat ) ) {
                // make the string lower case!!
                s.assign(dirDat.cFileName);
                std::transform(s.begin(), s.end(), s.begin(), tolower);

                if( s != "." && s != ".." ) {
                    if( (dirDat.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0 && recursive) {
                        getAllFiles(baseD + s, files, extension, recursive);	
                    }
                    else if( s.find(extension) != std::string::npos || extension == ".*"  ) {
                        files.push_back(baseD + s);
                    }
                }
            }

            FindClose(found);*/

            return true;
        }

        bool
        DataBase::getAllFilesInDirectory(const std::string& startDir, 
                                        std::vector<std::string>& files,
                                        const std::string& extension,
                                        bool recursive)
        {
            if( startDir.find(":") != std::string::npos ) 
            {
                SCE_ASSERT_2(false, "getAllFilesInDirectory() baseDir param must be relative,				\
                                   if you want to search the whole data dir use an empty string");
                return false;
            }

            if( !doesExist(startDir) )
            {
                return false;
            }

            std::string fullPath;
            if( startDir == "" )
                fullPath = getExecDirectory() + "/";
            else
                fullPath = getExecDirectory() + startDir;

            std::string lowerCaseExtName = extension;
            std::transform(lowerCaseExtName.begin(), lowerCaseExtName.end(), lowerCaseExtName.begin(), tolower);
            getAllFiles(fullPath, files, lowerCaseExtName, recursive);

            // make all paths relative to data dir
            std::vector<std::string>::iterator it = files.begin();
            for( it ; it != files.end() ; ++it ) 
            {
                SCE_ASSERT_2(fullPath.size() < (*it).size(), "This should never happen!");
                std::string sss= *it;
                *it = std::string(*it, getExecDirectory().length(), (*it).length() - getExecDirectory().length());
                std::string sssss = *it;
            }

            return true;
        }

        bool
        DataBase::findFileInDirectory(const std::string& startDir,
                            const std::string& file,
                            std::string& relativePath,
                            bool recursive)
        {
            if( file == "" )
            {
                relativePath = "";
                return false;
            }

            // fixing stl
            if( startDir.find(":") != std::string::npos ) 
            {
                SCE_ASSERT_2(false, "findFileInDirectory() directory param must be relative");
                return false;
            }

            // everything is handled with lowercase strings
            std::string fileToSearchFor = file;
            std::transform(fileToSearchFor.begin(), fileToSearchFor.end(), fileToSearchFor.begin(), tolower);

            std::vector<std::string> files;
            getAllFilesInDirectory(startDir, files, ".*", recursive);

            std::vector<std::string>::iterator it(files.begin());
            for( it ; it != files.end() ; ++it ) 
            {
                std::string fileI = (*it);
                if( (*it).find(fileToSearchFor) != std::string::npos ) 
                {
                    relativePath = *it;
                    return true;
                }
            }
            return false;
        }
                             

                             
    }   // namespace DataBase

} // namespace sce
