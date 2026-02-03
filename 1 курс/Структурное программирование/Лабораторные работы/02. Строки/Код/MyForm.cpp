#include "MyForm.h"
#include <string>
#include <stdlib.h>
#include <string.h>
#include <msclr\marshal.h>
#include <msclr\marshal_cppstd.h>
#include <msclr\marshal_windows.h>
#include <msclr\marshal_atl.h>
using namespace System;
using namespace System::Windows::Forms;
using namespace msclr::interop;

int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	lb::MyForm form;
	Application::Run(% form);
}
