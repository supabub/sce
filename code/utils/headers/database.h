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
	struct DataBase
	{
		~DataBase() {}

		static DataBase&	getInstance();

		void				start();

		/**
		 *	Get the working directory (all executables must be placed there).
		 *	Example:	
		 *		std::string execDir = DataBase::getInstance().getExecDirectory();
		 */
		const std::string&	getExecDirectory();

		std::string			convertBackSlashToSlash(const std::string& path);

		/**
		 *	
		 */
		void				createDirectory(const std::string& dir);			// relative to exec dir! syntax ex: "\newDir"

		/**
		 *	
		 */
		void				deleteDirectory(const std::string& dir);

		/**
		 *	
		 */
		void				deleteFile(const std::string& fileName);

		/**
		 *	
		 */
		void				renameFile(const std::string& fileName, const std::string& newFileName);

		/**
		 *	
		 */
		std::string			getRelativePath(const std::string& fullPath);		// get path relative to exec directory

		/**
		 *	
		 */
		std::string			getPathFromFile(const std::string& filePath);		// get path where file is placed

		/**
		 *	
		 */
		void				getDirectoryStructure(const std::string& filePath, std::vector<std::string>& dirs);

		/**
		 *	
		 */
		std::string			getFileFromPath(const std::string& fileAndPath);

		/**
		 *	
		 */
		bool				doesFileExist(const std::string& path);

		/**
		 *	
		 */
		bool				doesDirExist(const std::string& path);

		/**
		 *	
		 */
		void				getAllDirectories(const std::string& startDir, std::vector<std::string>& dirs);

		/**
		 *	
		 */
		bool				getAllFilesInDirectory(const std::string& startDir, 
													std::vector<std::string>& files,
													const std::string& extension = ".*",
													bool recursive = false);

		/**
		 *	
		 */
		bool				findFileInDirectory(const std::string& startDir,
												const std::string& file,
												std::string& relativePath,
												bool recursive = false);

	private:
		DataBase() {}

		std::string					execDirectory_;
		std::vector<std::string>	allDirs_;
	};

} // namespace sce

#endif
