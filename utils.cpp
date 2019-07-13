#include "utils.h"


void clearScreen(){

	COORD upperLeftCorner = { 0, 0 };
	DWORD charsWritten;
	DWORD conSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO  csbi;

	GetConsoleScreenBufferInfo(hCon, &csbi);
	conSize = csbi.dwSize.X * csbi.dwSize.Y;

	// fill with spaces
	FillConsoleOutputCharacter(hCon, TEXT(' '), conSize, upperLeftCorner, &charsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, conSize, upperLeftCorner, &charsWritten);

	// cursor to upper left corner
	SetConsoleCursorPosition(hCon, upperLeftCorner);
}

/*
unsigned short int leUnsignedShortInt(unsigned short int min, unsigned short int  max){
unsigned short int num;

cin >> num;
while (num < min || num > max);
{
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cout << "\nInput Invalido. Introduza um numero entre " << min << " e " << max << " : ";
cin >> num;
}
return num;

}
*/


int le_num()
{
	string input;
	int num;

	getline(cin, input);
	stringstream ss(input);

	while (!(ss >> num  && ss.eof())) {
		cout << "Input invalido" << endl;
		cout << "Introduza um numero valido: ";
		getline(cin, input);
		ss.str("");	ss.clear(); //apagar conteudo da stringsstream
		ss << input;
	}
	return num;
}

int leInteiro(int min, int max){
	int num = le_num();

	while (num < min || num > max)
	{
		cout << "\nInput Invalido. Introduza um numero entre " << min << " e " << max << " : ";
		num = le_num();
	}
	return num;

}

float le_float_positivo()
{

	string input;
	float num;

	getline(cin, input);
	stringstream ss(input);

	while (!(ss >> num  && ss.eof() && num >= 0)) {
		cout << "Input invalido" << endl;
		cout << "Introduza um numero valido: ";
		getline(cin, input);
		ss.str("");	ss.clear(); //apagar conteudo da stringsstream
		ss << input;
	}
	return num;
}

bool ambos_espacos(char lhs, char rhs)
{
	return (lhs == rhs) && (lhs == ' ');
}


bool tem_algarismos(const string &input)
{
	return (input.find_first_of("0123456789") != string::npos);
}


string le_string()
{
	string input;

	while (true)
	{
		getline(cin, input);

		if (input.empty())      //verifica se o input esta vazio
		{
			cout << "Input invalido. Nao e possivel ter um input vazio\n" << "Introduza um input valido: ";
			continue;
		}


		string::iterator new_end = unique(input.begin(), input.end(), ambos_espacos);
		input.erase(new_end, input.end());               /// apaga espacos repetidos

		if (input.at(0) == ' ')                //apaga 1 espaco se houver
			input.erase(input.begin());

		if (input.at(input.size() - 1) == ' ')  //apaga ulltimo espaco se houver
			input.erase(input.end() - 1);

		if (tem_algarismos(input))                     /// se tiver algarismo da erro
			cout << "Input invalido. Nao e possivel ter numeros\n" << "Introduza um input valido: ";
		else return input;

	}



}


void linha()
{
	for (int i = 1; i < 41; i++)
		cout << "--";

	cout << "\n";
}



void estrela()
{
	for (int i = 1; i < 41; i++)
		cout << "**";

	cout << "\n";
}


void espera_input()
{
	cout << "\nPressione Enter para continuar.";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//cin.clear();
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//string s;
	//getline(cin, s);
	//_getch;
}