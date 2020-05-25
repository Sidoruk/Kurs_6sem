#include <iostream>
#include <string>
#include <time.h>
#include "ClassField.h"


using namespace std;

Game_Field::Game_Field() {
	srand(time(NULL));
	int RealSize;
	int player;
	cout << "Enter size of squared field (NxN): ";
	cin >> Size_of_Field;
	RealSize = Size_of_Field * Size_of_Field;
	cell = new Cells[RealSize];
	for (int i = 0; i < RealSize; i++)
	{
		cell[i].isFilled = false;
		cell[i].value = -1;
	}
	cout << "Sekond player is:" << endl << "1 - server" << endl << "0 - people" << endl;
	cin >> player;
	if (player == 1)
		second_player_is_server = true;
	else
		second_player_is_server = false;
}

Game_Field::~Game_Field() {
	delete [] cell;
}

void Game_Field::print_field() {
	int RealSize = Size_of_Field * Size_of_Field;
	for (int i = 0; i < RealSize; i++)
	{
		if(cell[i].value!=-1)
			cout << cell[i].value << "  |  ";
		else
			cout << " " << "  |  ";
		if ((i % Size_of_Field) == (Size_of_Field-1))
			cout << endl;
	}
}

bool Game_Field::set_cell_value(int x, int y, int value) {
	int cell_position = (x - 1) * Size_of_Field + (y - 1);
	if (cell[cell_position].isFilled)
	{
		cout << "Cell is just filled. Choose another cell." << endl;
		return false;
	}
	else
	{
		cell[cell_position].isFilled = true;
		cell[cell_position].value = value;
		return true;
	}
}

void Game_Field::game_process()
{
	int count_of_cells = Size_of_Field * Size_of_Field;
	for (int i = 0; i < count_of_cells; i++)
	{
		if (i % 2 == 0)
			move_of_player(1);
		else
			if (second_player_is_server)
				move_of_server();
			else
				move_of_player(2);

		system("cls");
		print_field();
	}
	count_even_summs();
}

void Game_Field::move_of_player(int player_number)
{
	int coordinate_x, coordinate_y;
	bool set_is_successfull;
	do {
		coordinate_x = choose_coordinate(0);
		coordinate_y = choose_coordinate(1);
		if (player_number == 1)
			set_is_successfull = set_cell_value(coordinate_x, coordinate_y, 1);
		else
			set_is_successfull = set_cell_value(coordinate_x, coordinate_y, 0);
	} while (!set_is_successfull);
}

int Game_Field::choose_coordinate(int coord){
	int a;
	do {
		if(coord==0)
			cout << "Choose row: ";
		else
			cout << "Choose column: ";
		cin >> a;
		if (a <= 0 || a > Size_of_Field)
		{
			system("cls");
			if(coord==0)
				cout << "You exeeded maximum! Enter correct row!" << endl;
			else
				cout << "You exeeded maximum! Enter correct column!" << endl;
		}
	} while (a <= 0 || a > Size_of_Field);
	return a;
}

void Game_Field::move_of_server() {
	bool successfull_set;
	int coordinate_x, coordinate_y;
	do {
		coordinate_x = (rand() % Size_of_Field) + 1;
		coordinate_y = (rand() % Size_of_Field) + 1;
		successfull_set = set_cell_value(coordinate_x, coordinate_y, false);
	} while (!successfull_set);
}

void Game_Field::count_even_summs() //число четных сумм
{
	int global_even_count, global_odd_count, summ_count_lines, rows, columns, diags;

	rows = count_rows();
	columns = count_columns();
	diags = count_diags();

	global_even_count = rows + columns + diags;
	summ_count_lines = 2 * Size_of_Field + (2 * Size_of_Field - 1);
	global_odd_count = summ_count_lines - global_even_count;
	cout << "Results:" <<endl << "Even sums: " << global_even_count << endl;
	cout << "Odd sums: " << global_odd_count << endl;
	if (global_even_count > global_odd_count)
		cout << "Second player win!" << endl;
	else if (global_odd_count > global_even_count)
		cout << "First player win!" << endl;
	else
		cout << "Draw!" << endl;
	system("pause");
}

int Game_Field::count_rows() {
	int sum, count=0;
	int number;
	for (int i = 0; i < Size_of_Field; i++) {
		sum = 0;
		for (int j = 0; j < Size_of_Field; j++) {
			number = i * Size_of_Field + j;
			sum += cell[number].value;
		}
		if (sum % 2 == 0)
			count++;
	}
	cout << "rows: " << count << endl;
	return count;
}

int Game_Field::count_columns() {
	int count = 0, sum;
	int number;
	for (int j = 0; j < Size_of_Field; j++) {
		sum = 0;
		for (int i = 0; i < Size_of_Field; i++) {
			number = i * Size_of_Field + j;
			sum += cell[number].value;
		}
		if (sum % 2 == 0)
			count++;
	}
	cout << "columns: " << count << endl;
	return count;
}

int Game_Field::count_diags() {
	int count = 0, sum;
	int i, j;
	int number;
	
	for (int k = 1; k <= Size_of_Field; k++) //upper triangle and main diag
	{
		sum = 0;
		for (int m = 0; m < k; m++) {
			i = m;
			j = Size_of_Field - k + m;
			number = i * Size_of_Field + j;
			sum += cell[number].value;
		}
		if (sum % 2 == 0)
			count++;
	}

	for (int k = 1; k <= Size_of_Field - 1; k++) //lower triangle and main diag
	{
		sum = 0;
		for (int m = 0; m < k; m++) {
			j = m;
			i = Size_of_Field - k + m;
			number = i * Size_of_Field + j;
			sum += cell[number].value;
		}
		if (sum % 2 == 0)
			count++;
	}
	cout << "diags: " << count << endl;
	return count;
}