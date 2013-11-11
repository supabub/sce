#ifndef __BASIC_STREAM_H__
#define __BASIC_STREAM_H__

#include "debug.h"

namespace sce
{

	// used to read/write from files
	struct BasicStream
	{
        BasicStream()                                                   { state_ = NOT_INITIALIZED; }
        virtual ~BasicStream()                                          { }

		enum Seek
		{
			BEGIN,
			CURRENT,
			END
		};

		enum State
		{
			NOT_INITIALIZED,
			OK,
			BAD
		};

		virtual bool		read(void* buffer, const size_t size, const size_t count) = 0;
		virtual bool		readLine(char* buffer, int maxCharsPerLine) = 0;
		virtual bool		readString(char* buffer, size_t maxCharsInString) = 0;
		virtual fpos_t		size() = 0;
		virtual fpos_t		getPos() = 0;
		virtual bool		setPos(fpos_t pos) = 0;
		virtual bool		seek(fpos_t offset, Seek origin) = 0;
		virtual bool		write(const void* buffer, const size_t size, const size_t count) = 0;

		State				getState()                                      { return state_; }

	protected:
		void				setState(State state)                           { state_ = state; }
		State				state_;
	};


} // namespace sce

#endif
