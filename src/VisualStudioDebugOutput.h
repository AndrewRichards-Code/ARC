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
#include <fstream>

namespace arc
{
	class vsBufferedStringStreamBuf : public std::streambuf
	{
	public:
		vsBufferedStringStreamBuf(size_t bufferSize);
		virtual ~vsBufferedStringStreamBuf();

		virtual void WriteString(const std::string& string) = 0;

	private:
		int	overflow(int c) override;

		int	sync() override;
	};

	typedef void(*PFN_DebugOutputCallback)(const std::string&);

	class VisualStudioDebugOutput : public vsBufferedStringStreamBuf
	{
	public:
		VisualStudioDebugOutput(bool outputWindow = true, const char* logFilename = nullptr, size_t bufferSize = (size_t)2048, PFN_DebugOutputCallback callback = nullptr);
		virtual ~VisualStudioDebugOutput();

		void SetLogFile(const std::string& logFilename);
		void SetCallback(PFN_DebugOutputCallback callback);

		virtual void WriteString(const std::string& string) override;

	protected:
		bool m_OutputWindow;
		bool m_OutputLogFile;
		std::ofstream m_LogFile;

		std::streambuf* m_old_cout_buffer;
		std::streambuf* m_old_cerr_buffer;

		PFN_DebugOutputCallback m_PFN_DebugCallback;
	};
}
