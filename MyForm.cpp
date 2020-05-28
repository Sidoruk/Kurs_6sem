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
		if (N <= 0)
			throw 1;
		else {
			size_of_field = N;
			MyForm::radioButtonPeople->Enabled = false;
			MyForm::radioButtonServer->Enabled = false;
			MyForm::buttonSave->Enabled = false;
			MyForm::textBoxSize->Enabled = false;
			MyForm::pictureBox1->Enabled = true;
			cell_height = int(MyForm::pictureBox1->Height / N);
			cell_width = int(MyForm::pictureBox1->Width / N);
		}
		
		
	}
	catch (...) {
		MessageBox::Show("Can't get size", "Error", MessageBoxButtons::OK);
	}
}

System::Void kursgraf1::MyForm::pictureBox1_Click(System::Object^ sender, System::EventArgs^ e)
{
	int Curs_X = Cursor->Position.X - MyForm::pictureBox1->Location.X - MyForm::Location.X - 8;
	int Curs_Y = Cursor->Position.Y - MyForm::pictureBox1->Location.Y - MyForm::Location.Y - 30;
	bool cuccessful_set = false;
	Graphics^ ris = MyForm::pictureBox1->CreateGraphics();

	try {
		for (int x = 0; x < size_of_field; x++) {
			for (int y = 0; y < size_of_field; y++) {
				if ((Curs_X > (x * cell_width)) && (Curs_X < ((x + 1) * cell_width)) && (Curs_Y > (y * cell_height)) && (Curs_Y < ((y + 1) * cell_height))) {
					cuccessful_set = MyForm::game_field->set_cell_value(x, y, 1);
					if (!cuccessful_set)
						throw 1;
					ris->FillRectangle(Brushes::Black, x * cell_width, y * cell_height, cell_width, cell_height);
					
				}
			}
		}
		
	}
	catch (...) {
		MessageBox::Show("Can't write there", "Error", MessageBoxButtons::OK);
	}


	int Imag_position_X = MyForm::pictureBox1->Location.X + MyForm::Location.X;
	int Imag_position_Y = MyForm::pictureBox1->Location.Y + MyForm::Location.Y;

	MyForm::labelCursCoordX->Text = Curs_X.ToString();
	MyForm::labelCursCoordY->Text = Curs_Y.ToString();
	MyForm::pictureBox1->Refresh();

	

	ris->FillRectangle(Brushes::Black, 0, 0, 200, 133);
}