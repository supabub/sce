#ifndef __FILE_STREAM_H__
#define __FILE_STREAM_H__

#include "basic_stream.h"

namespace sce
{

	// used to read/write from files
	struct FileStream:public BasicStream
	{
			FileStream();
			FileStream(const std::string& fileName, const std::string& modi = "rb");
			virtual ~FileStream();

		const std::string&	getFileName() const;
		bool				open(const std::string& fileName, const std::string& modi = "rb");
		const std::string&	getModi() const;
		bool				close();

		virtual bool		read(void* buffer, const size_t size, const size_t count);
		virtual bool		readLine(char* buffer, int maxCharsPerLine);
		virtual bool		readString(char* buffer, size_t maxCharsInString);
		virtual bool		eof();
		virtual fpos_t		size();
		virtual fpos_t		getPos();
		virtual bool		setPos(fpos_t pos);
		virtual bool		seek(fpos_t offset, Seek origin);
		virtual bool		write(const void* buffer, const size_t size, const size_t count);

	private:
		FileStream(const FileStream&);
		FileStream& operator=(const FileStream&);

		std::string		fileName_;
		std::string		modi_;

		FILE* file_;
	};

} // namespace sce

#endif
