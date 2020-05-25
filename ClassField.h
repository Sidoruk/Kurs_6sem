#pragma once
struct Cells {
	bool isFilled;
	int value;
};

class Game_Field {
private:
	int Size_of_Field;
	Cells* cell;
	bool second_player_is_server;
public:
	Game_Field();
	bool set_cell_value(int x, int y, int value);
	void print_field();
	void game_process();
	void move_of_player(int player_number);
	void move_of_server();
	int choose_coordinate(int coord);
	void count_even_summs();
	int count_rows();
	int count_columns();
	int count_diags();
	~Game_Field();
};