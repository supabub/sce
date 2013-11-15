#include "../headers/file_stream.h"
#include "../headers/database.h"

namespace sce
{
		
	FileStream::FileStream()
	:file_(0)
	{
	}

	FileStream::FileStream(const std::string& fileName, const std::string& modi)
	:file_(0)
	{
		open(fileName, modi);
	}

	FileStream::~FileStream()
	{
		close();
	}

	const std::string&
	FileStream::getFileName() const
	{
		return fileName_;
	}

	bool
	FileStream::open(const std::string& file, const std::string& modi)
	{
		SCE_ASSERT_2(file.find(":") == std::string::npos, "FileStream: param: file must be relative!!");

		fileName_ = file;
		std::string fileName;
		fileName = DataBase::getExecDirectory() + file;

		//fopen_s(&file_, fileName.c_str(), modi.c_str());
        file_ = fopen(fileName.c_str(), modi.c_str());
		modi_ = modi;
		if( file_ == NULL ) 
		{
			//SCE_TRACE("Can not open file: " << file << ". Check if path description uses right syntax!");
			setState(BasicStream::NOT_INITIALIZED);
			return false;
		}

		setState(BasicStream::OK);
		return true;
	}

	const std::string&
	FileStream::getModi() const
	{
		return modi_;
	}

	bool
	FileStream::close()
	{	
		if( file_ == 0 ) {
			return false;
		}
		if( !fclose(file_) ) {
			file_ = 0;
			return true;
		}
		file_ = 0;	
		return false;
	}

	bool
	FileStream::readString(char* string, size_t maxCharsInString)
	{
		char c;
		size_t counter = 0;

		do {
			if( counter >= maxCharsInString ) {
				return false;
			}
			c = fgetc(file_);
			string[counter++] = c;		
		} while( c != '\0' );

		return true;
	}

	fpos_t
	FileStream::size()
	{
		fpos_t current = getPos();

		seek(0, END);
		fpos_t position = getPos();

		setPos(current);	
		return position;
	}

	bool
	FileStream::seek(fpos_t offset, Seek origin)
	{
		switch( origin ) {
			case BEGIN:
				fseek(file_, (long)offset, SEEK_SET);
				break;
			case CURRENT:
				fseek(file_, (long)offset, SEEK_CUR);
				break;
			case END:
				fseek(file_, (long)offset, SEEK_END);
				break;
			default:
				return false;
		}

		return true;
	}

	bool
	FileStream::write(const void* buffer, const size_t size, const size_t count)
	{
		if( file_ == 0 ) {
			return false;
		}
		else {
			size_t writtenObjs = fwrite(buffer, size, count, file_);
			if( writtenObjs != count ) {
				SCE_ASSERT_2(false, "FileStream: Could not write number of requested objs!");
				return false;
			}
			else {
				return true;
			}
		}
	}

	bool
	FileStream::read(void* buffer, const size_t size, const size_t count)
	{
		size_t readObjs = fread(buffer, size, count, file_);
		if( readObjs != count ) {
			//assert(false); //, "FileStream: Could not read number of requested objs!"); does not work with eof !! eof() needs a failed read so that the eof flag is set!
			return false;
		}
		else 
			return true;
	}

	bool
	FileStream::readLine(char* buffer, int maxcharsPerLine)
	{
		if( fgets(buffer, maxcharsPerLine, file_) == NULL ) 
		{
			return false;
		}
		return true;
	}

	fpos_t
	FileStream::getPos()
	{
		fpos_t current;
		fgetpos(file_, &current); 		

		return current;
	}

	bool
	FileStream::setPos(fpos_t pos)
	{
		if( !fseek(file_, (long)pos, SEEK_SET) ) {
			return true;
		}
		return false;
	}

	bool
	FileStream::eof()
	{
		return feof(file_) ? true : false;
	}

} // namespace sce
