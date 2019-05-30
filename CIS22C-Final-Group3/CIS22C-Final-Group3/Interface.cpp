string generateBars(int number)
{
	string bars = string();
	string bar = UI::BARS_CHARACTER;

	for (int i = 0; i < number; i++)
	{
		bars.append(bar);
	}

	return bars;
}

void clearScreen(bool displayHeader)
{
	std::system("CLS");
	if (displayHeader)
	{
		printHeader();
	}
	return;
}

void pause()
{
	cout << "Press ENTER to continue.";
	cin.get();
}

void initialize()
{
	//Resize the terminal window
	string systemResizeStr = "mode " + to_string(UI::TERMINAL_WIDTH) + ", " + to_string(UI::TERMINAL_HEIGHT);
	system(systemResizeStr.c_str());

	//Rename the window
	system("title Serendipity Booksellers by Olivier Chan, Luis Guerrero, Samuel Ruiz Cervantes, and Manasi Gowda");

	//Format cout
	cout << fixed << setprecision(2);
}

void printHeader()
{
	const string bars = generateBars(UI::TERMINAL_WIDTH);
	const string header1 = R"(   _____                         _ _       _ _           ____              _             _ _               )";
	const string header2 = R"(  / ____|                       | (_)     (_) |         |  _ \            | |           | | |              )";
	const string header3 = R"( | (___   ___ _ __ ___ _ __   __| |_ _ __  _| |_ _   _  | |_) | ___   ___ | | _____  ___| | | ___ _ __ ___ )";
	const string header4 = R"(  \___ \ / _ \ '__/ _ \ '_ \ / _` | | '_ \| | __| | | | |  _ < / _ \ / _ \| |/ / __|/ _ \ | |/ _ \ '__/ __|)";
	const string header5 = R"(  ____) |  __/ | |  __/ | | | (_| | | |_) | | |_| |_| | | |_) | (_) | (_) |   <\__ \  __/ | |  __/ |  \__ \)";
	const string header6 = R"( |_____/ \___|_|  \___|_| |_|\__,_|_| .__/|_|\__|\__, | |____/ \___/ \___/|_|\_\___/\___|_|_|\___|_|  |___/)";
	const string header7 = R"(                                    | |           __/ |                                                    )";
	const string header8 = R"(                                    |_|          |___/                                                     )";

	cout << right;

	cout << setw((UI::TERMINAL_WIDTH + header1.length()) / 2) << header1 << endl
		<< setw((UI::TERMINAL_WIDTH + header2.length()) / 2) << header2 << endl
		<< setw((UI::TERMINAL_WIDTH + header3.length()) / 2) << header3 << endl
		<< setw((UI::TERMINAL_WIDTH + header4.length()) / 2) << header4 << endl
		<< setw((UI::TERMINAL_WIDTH + header5.length()) / 2) << header5 << endl
		<< setw((UI::TERMINAL_WIDTH + header6.length()) / 2) << header6 << endl
		<< setw((UI::TERMINAL_WIDTH + header7.length()) / 2) << header7 << endl
		<< setw((UI::TERMINAL_WIDTH + header8.length()) / 2) << header8 << endl << endl;

	cout << bars << endl << endl;

	return;
}