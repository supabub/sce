#ifndef __DATABASE_H__
#define __DATABASE_H__

#include "stringHelpers.h"

namespace sce
{

	/**
	 *	Is the entry point into the file and directory system.
	 *	The editor and the game must be placed in the ExecDirectory,
	 *	also in the ExecDirectory there has to be the data dir.
	 *	Passing a file is done by:
	 *		"/data/world/test/test.world"
	 *	Passing a directory:
	 *		"/data/entity/standards"
	 */

    namespace DataBase
    {
        
		const std::string&	getExecDirectory();

        // helper for the win32 system
		std::string			convertBackSlashToSlash(const std::string& path);

        // creation of deleting and deleting things
		bool				createDirectory(const std::string& dir);                // relative to exec dir! syntax ex: "\newDir"
		bool				deleteDirectory(const std::string& dir);                // relative to exec dir! syntax ex: "\newDir"

		bool				deleteFile(const std::string& path);
		void				renameFile(const std::string& fileName, const std::string& newFileName);

        // some simplifications handling paths and files
		std::string			getRelativePath(const std::string& absolutePath);		// get path rel. to exec directory
		std::string			getPath(const std::string& path);                       // get path out of rel./abs path
        std::string			getFile(const std::string& path);                       // get file out of rel./abs path

        // check existence
		bool				doesExist(const std::string& path);                     // check if file/dir exist

        // grab contens
		void				getAllDirectories(const std::string& startDir, std::vector<std::string>& dirs);
		bool				getAllFilesInDirectory(const std::string& startDir, 
													std::vector<std::string>& files,
													const std::string& extension = ".*",
													bool recursive = false);
		bool				findFileInDirectory(const std::string& startDir,
												const std::string& file,
												std::string& relativePath,
												bool recursive = false);
        
    }


} // namespace sce

#endif
