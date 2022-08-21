// Copyright 2007 - 2022 Simul Software Ltd https://github.com/simul/Platform/
//
// Permission is hereby  granted, free of charge, to any  person obtaining a copy
// of this software and associated  documentation files (the "Software"), to deal
// in the Software  without restriction, including without  limitation the rights
// to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
// copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
// IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
// FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
// AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
// LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// This file has been modified on 2022-08-19 from the original was provided by:
// Simul Software Ltd https://github.com/simul/Platform/

#pragma once
#include "Log.h"
#include <fstream>

namespace arc
{
	class vsBufferedStringStreamBuf : public std::streambuf
	{
	public:
		vsBufferedStringStreamBuf(size_t bufferSize)
		{
			if (bufferSize)
			{
				char* ptr = new char[bufferSize];
				setp(ptr, ptr + bufferSize);
			}
			else
			{
				setp(0, 0);
			}
		}
		virtual ~vsBufferedStringStreamBuf()
		{
			delete[] pbase();
		}

		virtual void WriteString(const std::string& string) = 0;

	private:
		int	overflow(int c) override
		{
			sync();

			if (c != std::char_traits<char>::eof())
			{
				if (pbase() == epptr())
				{
					std::string temp;
					temp += static_cast<char>(c);
					WriteString(temp);
				}
				else
				{
					sputc(static_cast<char>(c));
				}
			}

			return 0;
		}

		int	sync() override
		{
			if (pbase() != pptr())
			{
				std::string temp(pbase(), pptr());
				WriteString(temp);
				setp(pbase(), epptr());
			}

			return 0;
		}
	};

	typedef void(*PFN_DebugOutputCallback)(const std::string&);

	class VisualStudioDebugOutput : public vsBufferedStringStreamBuf
	{
	public:
		VisualStudioDebugOutput(bool outputWindow = true, const char* logFilename = nullptr, size_t bufferSize = (size_t)2048 , PFN_DebugOutputCallback callback = nullptr)
			:vsBufferedStringStreamBuf(bufferSize), m_OutputLogFile(false), m_old_cout_buffer(nullptr), m_old_cerr_buffer(nullptr), m_PFN_DebugCallback(callback)
		{
			m_OutputWindow = outputWindow;

			if (logFilename)
			{
				SetLogFile(logFilename);
			}

			m_old_cout_buffer = std::cout.rdbuf(this);
			m_old_cerr_buffer = std::cerr.rdbuf(this);
		}

		virtual ~VisualStudioDebugOutput()
		{
			if (m_OutputLogFile)
			{
				m_LogFile << std::endl;
				m_LogFile.close();
			}
			std::cout.rdbuf(m_old_cout_buffer);
			std::cerr.rdbuf(m_old_cerr_buffer);
		}

		void SetLogFile(const std::string& logFilename)
		{
			m_LogFile.open(logFilename);
			if (m_LogFile.is_open())
			{
				m_OutputLogFile = true;
			}
			else
			{
				ARC_ERROR(false, "Failed to create LogFile at location: %s", logFilename);
			}
		}

		void SetCallback(PFN_DebugOutputCallback callback)
		{
			m_PFN_DebugCallback = callback;
		}

		virtual void WriteString(const std::string& string) override
		{
			if (m_OutputWindow)
			{
				OutputDebugStringA(string.c_str());
			}
			if (m_OutputLogFile)
			{
				m_LogFile << string;
				m_LogFile.flush();
			}
			if (m_PFN_DebugCallback)
			{
				m_PFN_DebugCallback(string);
			}
		}

	protected:
		bool m_OutputWindow;
		bool m_OutputLogFile;
		std::ofstream m_LogFile;

		std::streambuf* m_old_cout_buffer;
		std::streambuf* m_old_cerr_buffer;

		PFN_DebugOutputCallback m_PFN_DebugCallback;
	};
}
