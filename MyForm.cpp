#include "MyForm.h"
#include <Windows.h>
#include "ClassField.h"

using namespace kursgraf1; // Название проекта
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

[STAThreadAttribute]
void main(array <String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	kursgraf1::MyForm form; //which form starts first
	Application::Run(% form);
	
}

System::Void kursgraf1::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	Application::Exit();
}

System::Void kursgraf1::MyForm::radioButtonServer_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	opponent_is_server = true;
}

System::Void kursgraf1::MyForm::radioButtonPeople_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
{
	opponent_is_server = false;
}

System::Void kursgraf1::MyForm::buttonSave_Click(System::Object^ sender, System::EventArgs^ e)
{
	int N;
	try {
		N = System::Convert::ToInt32(textBoxSize->Text);
		size_of_field = N;
		MyForm::radioButtonPeople->Enabled = false;
		MyForm::radioButtonServer->Enabled = false;
		MyForm::buttonSave->Enabled = false;
		MyForm::textBoxSize->Enabled = false;
		//game_field->game_process(N);
		MyForm::pictureBox1->Enabled = true;
	}
	catch (...) {
		MessageBox::Show("Can't get size", "Error", MessageBoxButtons::OK);
	}
}

System::Void kursgraf1::MyForm::pictureBox1_Click(System::Object^ sender, System::EventArgs^ e)
{
	int Pict_X = MyForm::pictureBox1->Location.X;
	int Pict_Y = MyForm::pictureBox1->Location.Y;
	int cell_x = (int)MyForm::pictureBox1->Width;
	int cell_y = (int)MyForm::pictureBox1->Height;

	//Graphics^ g = Graphics::FromHwnd(this->Handle);
	//g->FillRectangle(Brushes::Black, Pict_X-1, Pict_Y-1, 602, 402);
	//g->FillRectangle(Brushes::White, Pict_X, Pict_Y, 600, 400);
	
	int Curs_X = Cursor->Position.X;
	int Curs_Y = Cursor->Position.Y;
	int Imag_position_X = MyForm::pictureBox1->Location.X + MyForm::Location.X;
	int Imag_position_Y = MyForm::pictureBox1->Location.Y + MyForm::Location.Y;
	
	MyForm::labelCursCoordX->Text = Curs_X.ToString();
	MyForm::labelCursCoordY->Text = Imag_position_Y.ToString();
	MyForm::pictureBox1->Refresh();
	
	//g->FillRectangle(Brushes::Black, 100, 100, 200, 133);
	//g->FillRectangle(Brushes::Black, 100, 100, 200, 133);

	Graphics^ ris = MyForm::pictureBox1->CreateGraphics();
	ris->FillRectangle(Brushes::Black, 0, 0, 200, 133);
}