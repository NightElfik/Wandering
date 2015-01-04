#define WINDOWS

#include <iostream>
#include <sstream>
#include <time.h>

#include "RectMaze.cpp"
#include "HexaMaze.cpp"
#include "IMazeScreen.h"
#include "MenuScreen.cpp"
#include "MazeScreen.cpp"
#include "SplitScreen.cpp"
#include "TextMenuItem.cpp"
#include "ImageMenuItem.cpp"
#include "TextBoxMenuItem.cpp"
#include "PrimsMazeGenerator.cpp"
#include "ScreenManager.IScreen.h"
#include "RecursiveBacktrackerMazeGenerator.cpp"

#ifdef WINDOWS
#include "WindowsConsole.cpp"
#else
// import unix console class
#endif

bool run;

// I give up, I don't know how to move a namespace to different file...
namespace MenuLogic {
	enum MazeType { Rect, Hexa };

	MenuScreen *mainMenu, *messageBoxExit, *pickMazeType, *pickMazeSize, *pickGenerator,
		*ingameMenu, *victoryBox, *fileBox, *messageBox, *hintBox, *cppPromoBox, *asciiFontGen;
	MazeScreen *mazeScreen;
	IMazeScreen *currentScreen;
	SplitScreen *splitScreen;
	TextBoxMenuItem *mazeWidth, *mazeHeight, *hintLen, *fileName, *asciiText;
	TextMenuItem *victoryMessage, *fileBoxAccept, *message;
	ImageMenuItem *victoryImageText, *ascii;
	MazeType mt;
	IMazeGenerator* generator;

	const int victoryTextsLen = 6;
	std::string victoryTexts[victoryTextsLen] = { "Victory!", "Well done!", "Good job!", "C++ sucks!", "Great!",
		"Impressing!" };

	void mainMenuSingle() {
		currentScreen = mazeScreen;
		pickMazeType->SetSelectedItemIndex(0);
		mainMenu->GetScreenManager()->AddScreen(pickMazeType);
	}

	void mainMenuMulti() {
		currentScreen = splitScreen;
		pickMazeType->SetSelectedItemIndex(0);
		mainMenu->GetScreenManager()->AddScreen(pickMazeType);

	}

	void mainMenuExit() {
		messageBoxExit->SetSelectedItemIndex(2);
		mainMenu->GetScreenManager()->AddScreen(messageBoxExit);
	}

	void back() {
		mainMenu->GetScreenManager()->RemoveTopScreen();
	}

	void showMessage(const std::string& msg) {
		message->SetText(msg);
		mainMenu->GetScreenManager()->AddScreen(messageBox);
	}

	void endGame() {
		run = false;
	}

	void pickMazeTypeRect() {
		mt = Rect;
		pickMazeSize->SetSelectedItemIndex(0);
		mainMenu->GetScreenManager()->AddScreen(pickGenerator);
	}

	void pickMazeTypeHexa() {
		mt = Hexa;
		pickMazeSize->SetSelectedItemIndex(0);
		mainMenu->GetScreenManager()->AddScreen(pickGenerator);
	}

	void pickGeneratorRb() {
		if (generator != nullptr) {
			delete generator;
		}
		generator = new RecursiveBacktrackerMazeGenerator();
		mainMenu->GetScreenManager()->AddScreen(pickMazeSize);
	}

	void pickGeneratorPrim() {
		if (generator != nullptr) {
			delete generator;
		}
		generator = new PrimsMazeGenerator();
		mainMenu->GetScreenManager()->AddScreen(pickMazeSize);
	}

	bool stringToInt(const std::string& str, int& outInt) {
		std::istringstream is(str);
		is >> outInt;
		return !is.bad() && is.eof();
	}

	void pickMazeSizeOk() {
		std::string wid = mazeWidth->GetText(),
			hei = mazeHeight->GetText();

		int width, height;
		if (wid.length() == 0 || hei.length() == 0 || !stringToInt(wid, width) || !stringToInt(hei, height)) {
			message->SetText("Failed to parse maze width or height");
			mainMenu->GetScreenManager()->AddScreen(messageBox);
			return;
		}

		if (width < 2 || height < 2) {
			message->SetText("Minimum maze size is 2 x 2");
			mainMenu->GetScreenManager()->AddScreen(messageBox);
			return;
		}

		back();	// maze size
		back();	// maze generator
		back();	// maze type

		IMaze* m = mt == Rect ? (IMaze*)new RectMaze(width, height) : (IMaze*)new HexaMaze(width, height);
		//generator->SetRandomSeed((unsigned)time(nullptr));
		m->Initialize(true);
		generator->Generate(m);

		currentScreen->Initialize(m);
		mainMenu->GetScreenManager()->AddScreen(currentScreen);
	}

	void ingameMenuExit() {
		back();
		back();
		currentScreen->Initialize(nullptr);
	}

	void ingameMenuReset() {
		back();
		currentScreen->ResetGame();
	}

	void ingameMenuRegen() {
		back();
		currentScreen->RegenerateMazeAndReset();
	}

	/*void save() {
	back();
	if (currentScreen->Save(fileName->GetText()))
	showMessage("Maze saved succesfully");
	else
	showMessage("Failed to save maze");
	}

	void ingameMenuSave() {
	back();
	fileBoxAccept->SetText("Save");
	fileBoxAccept->SetCallback(save);
	fileBox->SetSelectedItemIndex(0);
	mainMenu->GetScreenManager()->AddScreen(fileBox);
	}

	void load() {
	back();
	if (currentScreen->Load(fileName->GetText()))
	showMessage("Maze loaded succesfully");
	else
	showMessage("Failed to load maze");
	}

	void ingameMenuLoad() {
	back();
	fileBoxAccept->SetText("Load");
	fileBoxAccept->SetCallback(load);
	fileBox->SetSelectedItemIndex(0);
	mainMenu->GetScreenManager()->AddScreen(fileBox);
	}*/

	void exportFoFile() {
		back();
		if (currentScreen->ExportToFile(fileName->GetText())) {
			showMessage("Maze exportedd succesfully");
		}
		else {
			showMessage("Failed to export maze");
		}
	}

	void ingameMenuExport() {
		back();
		fileBoxAccept->SetText("Export");
		fileBoxAccept->SetCallback(exportFoFile);
		fileBox->SetSelectedItemIndex(0);
		mainMenu->GetScreenManager()->AddScreen(fileBox);
	}

	void showMenu() {
		mainMenu->GetScreenManager()->AddScreen(ingameMenu);
	}

	void shuffleVictoryText() {
		victoryImageText->ChangeToAsciiArtText(victoryTexts[rand() % victoryTextsLen]);
	}

	void showVictory() {
		victoryMessage->SetText("");
		shuffleVictoryText();
		mainMenu->GetScreenManager()->AddScreen(victoryBox);
	}
	void showLeftVictory() {
		victoryMessage->SetText("Left (light) player wins");
		shuffleVictoryText();
		mainMenu->GetScreenManager()->AddScreen(victoryBox);
	}
	void showRightVictory() {
		victoryMessage->SetText("Right (dark) player wins");
		shuffleVictoryText();
		mainMenu->GetScreenManager()->AddScreen(victoryBox);
	}

	void showHintBox() {
		mainMenu->GetScreenManager()->AddScreen(hintBox);
	}

	void showHint() {
		back();
		back();

		int len;
		if (!stringToInt(hintLen->GetText(), len)) {
			message->SetText("Failed to parse hint length");
			mainMenu->GetScreenManager()->AddScreen(messageBox);
			return;
		}

		currentScreen->ShowHint(len);
	}

	void showMaxHint() {
		back();
		back();
		currentScreen->ShowHint(9999999);
	}

	void showCppPromo() {
		mainMenu->GetScreenManager()->AddScreen(cppPromoBox);
	}

	void showAscii() {
		mainMenu->GetScreenManager()->AddScreen(asciiFontGen);
	}

	void asciiTextChaged() {
		ascii->ChangeToAsciiArtText(asciiText->GetText());
	}

	void createMenus() {
		mainMenu = new MenuScreen();
		mainMenu->AddMenuItem(new ImageMenuItem("Wandering"));
		mainMenu->AddMenuItem(new TextMenuItem("Single-player", mainMenuSingle));
		mainMenu->AddMenuItem(new TextMenuItem("Multi-player split screen", mainMenuMulti));
		mainMenu->AddMenuItem(new TextMenuItem("About", showCppPromo));
		mainMenu->AddMenuItem(new TextMenuItem("Extra", showAscii));
		mainMenu->AddMenuItem(new TextMenuItem("Exit", mainMenuExit, 1));
		mainMenu->AddMenuItem(new TextMenuItem("by Marek Fiser \x03 2011", nullptr, 0, false, TextMenuItem::Right));
		mainMenu->AddMenuItem(new TextMenuItem("made as credit work on C++ at MFF CUNI", nullptr, -1, false, TextMenuItem::Left));
		mainMenu->AddMenuItem(new TextMenuItem("wandering@marekfiser.cz", nullptr, 0, false, TextMenuItem::Right));

		messageBoxExit = new MenuScreen(true, true);
		messageBoxExit->AddMenuItem(new ImageMenuItem("Really?!?"));
		messageBoxExit->AddMenuItem(new TextMenuItem("Do you really want to exit Wandering?", nullptr, 2, false));
		messageBoxExit->AddMenuItem(new TextMenuItem("Hmmm, yes...", endGame, -1, true, TextMenuItem::Left));
		messageBoxExit->AddMenuItem(new TextMenuItem("Of course no!", back, 0, true, TextMenuItem::Right));

		messageBox = new MenuScreen(true, true);
		messageBox->AddMenuItem(message = new TextMenuItem("Message", nullptr, 2, false));
		messageBox->AddMenuItem(new TextMenuItem("OK", back, 0));

		pickMazeType = new MenuScreen();
		pickMazeType->AddMenuItem(new TextMenuItem("             Pick the maze type             ", nullptr, 2, false));
		pickMazeType->AddMenuItem(new ImageMenuItem(19, 13, "+--+--+--+--+--+--+|              |  |+--+--+--+--+  +  +|  |     |     |  |+  +  +  +  +--+  +|     |     |     |+  +--+--+--+  +  +|     |     |  |  |+--+  +  +  +  +  +|        |     |  |+--+--+--+--+--+--+                     Rectangular maze ",
			pickMazeTypeRect, -13, true, TextMenuItem::Left));
		pickMazeType->AddMenuItem(new ImageMenuItem(20, 13, "  ____        ____   /    \\      /    \\ /      \\____/      \\\\      /           / \\    /           /  /    \\      /    \\ /      \\    /      \\\\           \\      / \\____       \\____/       \\      /             \\____/                              Hexagonal maze   ",
			pickMazeTypeHexa, 1, true, TextMenuItem::Right));
		pickMazeType->AddMenuItem(new TextMenuItem("back", back, 0, true, TextMenuItem::Right));


		pickGenerator = new MenuScreen();
		pickGenerator->AddMenuItem(new ImageMenuItem("Generator"));
		pickGenerator->AddMenuItem(new ImageMenuItem(40, 4, "Recursive backtracker                       as high a \"river\" factor as possible    fewer but longer dead ends              very long and twisty solution       ",
			pickGeneratorRb, 1, true));
		pickGenerator->AddMenuItem(new ImageMenuItem(40, 4, "Prims algorithm                             very low \"river\" factor                 many short dead ends                    solution is usually pretty direct   ",
			pickGeneratorPrim, 1, true));
		pickGenerator->AddMenuItem(new TextMenuItem("back", back, 0, true, TextMenuItem::Right));

		pickMazeSize = new MenuScreen();
		pickMazeSize->AddMenuItem(new ImageMenuItem("Maze size"));
		pickMazeSize->AddMenuItem(mazeWidth = new TextBoxMenuItem("Width: ", "20", 3, true));
		pickMazeSize->AddMenuItem(mazeHeight = new TextBoxMenuItem("Height: ", "10", 3, true));
		pickMazeSize->AddMenuItem(new TextMenuItem("OK", pickMazeSizeOk, -1, true, TextMenuItem::Left));
		pickMazeSize->AddMenuItem(new TextMenuItem("back", back, 0, true, TextMenuItem::Right));

		ingameMenu = new MenuScreen(true, true);
		ingameMenu->AddMenuItem(new TextMenuItem("Continue", back));
		ingameMenu->AddMenuItem(new TextMenuItem("Back to start", ingameMenuReset));
		ingameMenu->AddMenuItem(new TextMenuItem("Regenerate maze", ingameMenuRegen));
		ingameMenu->AddMenuItem(new TextMenuItem("Show hint", showHintBox));
		/*ingameMenu->AddMenuItem(new TextMenuItem("Load", ingameMenuLoad));
		ingameMenu->AddMenuItem(new TextMenuItem("Save", ingameMenuSave));*/
		ingameMenu->AddMenuItem(new TextMenuItem("Export", ingameMenuExport));
		ingameMenu->AddMenuItem(new TextMenuItem("Back to main menu", ingameMenuExit, 0));

		victoryBox = new MenuScreen(true, true);
		victoryBox->AddMenuItem(victoryImageText = new ImageMenuItem("Victory!"));
		victoryBox->AddMenuItem(victoryMessage = new TextMenuItem("Some extra message", nullptr, 1, false));
		victoryBox->AddMenuItem(new TextMenuItem("Back to main menu", ingameMenuExit, -1, true, TextMenuItem::Left));
		victoryBox->AddMenuItem(new TextMenuItem("Once again", ingameMenuRegen, 0, true, TextMenuItem::Right));

		fileBox = new MenuScreen(true, true);
		fileBox->AddMenuItem(new TextMenuItem("Specify file path", nullptr, 2, false));
		fileBox->AddMenuItem(fileName = new TextBoxMenuItem("", "", 32));
		fileBox->AddMenuItem(fileBoxAccept = new TextMenuItem("Accept", nullptr, -1, true, TextMenuItem::Left));
		fileBox->AddMenuItem(new TextMenuItem("Cancel", back, 0, true, TextMenuItem::Right));

		asciiFontGen = new MenuScreen();
		asciiFontGen->AddMenuItem(ascii = new ImageMenuItem("Example", nullptr, 2, false));
		asciiFontGen->AddMenuItem(asciiText = new TextBoxMenuItem("Enter your text here:", "Example", 16));
		asciiFontGen->AddMenuItem(new TextMenuItem("back", back, 0, true, TextMenuItem::Right));
		asciiText->SetTextChanged(asciiTextChaged);

		hintBox = new MenuScreen(true, true);
		hintBox->AddMenuItem(new TextMenuItem("This will highlight cells wich are on the nearest", nullptr, 0, false));
		hintBox->AddMenuItem(new TextMenuItem("path to exit, how many do you want to highlight?", nullptr, 2, false));
		hintBox->AddMenuItem(hintLen = new TextBoxMenuItem("Number: ", "5", 5, true, -1, TextMenuItem::Left));
		hintBox->AddMenuItem(new TextMenuItem("OK", showHint, -1, true, TextMenuItem::Center));
		hintBox->AddMenuItem(new TextMenuItem("Whole way to exit", showMaxHint, 2, true, TextMenuItem::Right));
		hintBox->AddMenuItem(new TextMenuItem("To clear hint, press key [c] in game", nullptr, -1, false, TextMenuItem::Left));
		hintBox->AddMenuItem(new TextMenuItem("back", back, 0, true, TextMenuItem::Right));

		cppPromoBox = new MenuScreen(true, true); cppPromoBox->AddMenuItem(new TextMenuItem("C++ is like teenage sex:", nullptr, 1, false, TextMenuItem::Left)); cppPromoBox->AddMenuItem(new TextMenuItem("It is on everyone's mind all the time.", nullptr, 0, false, TextMenuItem::Left)); cppPromoBox->AddMenuItem(new TextMenuItem("Everyone talks about it all the time.", nullptr, 0, false, TextMenuItem::Left)); cppPromoBox->AddMenuItem(new TextMenuItem("Everyone thinks everyone else is doing it.", nullptr, 0, false, TextMenuItem::Left)); cppPromoBox->AddMenuItem(new TextMenuItem("Almost no one is really doing it.", nullptr, 0, false, TextMenuItem::Left)); cppPromoBox->AddMenuItem(new TextMenuItem("The few who are doing it are:", nullptr, 0, false, TextMenuItem::Left)); cppPromoBox->AddMenuItem(new TextMenuItem("    Doing it poorly.", nullptr, 0, false, TextMenuItem::Left)); cppPromoBox->AddMenuItem(new TextMenuItem("    Sure it will be better next time.", nullptr, 0, false, TextMenuItem::Left)); cppPromoBox->AddMenuItem(new TextMenuItem("    Not practising it safely.", nullptr, 0, false, TextMenuItem::Left)); cppPromoBox->AddMenuItem(new TextMenuItem("Everyone's bragging about their successes all the time,", nullptr, 0, false, TextMenuItem::Left)); cppPromoBox->AddMenuItem(new TextMenuItem("although very few have actually had any.", nullptr, 1, false, TextMenuItem::Left));
		cppPromoBox->AddMenuItem(new TextMenuItem("back", back, 0, true, TextMenuItem::Right));

		mazeScreen = new MazeScreen(showMenu, showVictory);
		splitScreen = new SplitScreen(showMenu, showLeftVictory, showRightVictory);
	}

	void deleteMenus() {
		//delete mainMenu;
	}
}

IConsole* console;
ScreenManager* sManager;
ScreenBuffer* screenBuff;


void moveCmd(int dx, int dy) {
	std::cout << "[" << dx << "," << dy << "]";
}

int readKey() {
	int c = console->ReadCharUnbuffered();
	if (c != EOF && c == SPEC_KEY_PREFIX && (c = console->ReadCharUnbuffered()) != EOF) {
		return (SPEC_KEY_PREFIX << 8) | (c & 0xFF);
	}
	return c;
}

int main(int argc, char* argv[]) {
	srand((unsigned)time(nullptr));
	AsciiFont::Initialize();
	MenuLogic::generator = nullptr;

	console = new Console();

	short w = -1, h = -1;

	if (!console->GetWindowSize(w, h)) {
		w = -1;
		h = -1;

		while (w < 8) {
			std::cout << "Specify width of your console: ";
			std::cin >> w;
		}
		while (h < 4) {
			std::cout << "Specify height of your console: ";
			std::cin >> h;
		}
	}

	if (w < 70 || h < 20) {
		std::cout << "To paly this game your console size should be at least 70 x 20";
		return 0;
	}

	w--;

	screenBuff = new ScreenBuffer(w, h);
	sManager = new ScreenManager();

	MenuLogic::createMenus();
	sManager->AddScreen(MenuLogic::mainMenu);

	sManager->PrintScreens(screenBuff);
	console->PrintBuffer(screenBuff);

	run = true;
	do {
		int key = readKey();
		if (key == EOF || key == CTRL_C_KEY)
			break;

		sManager->KeyPressed(key);
		screenBuff->Clear();
		sManager->PrintScreens(screenBuff);
		console->PrintBuffer(screenBuff);
	} while (run);

	delete console;
	std::cout << std::endl;

	return 0;
}
