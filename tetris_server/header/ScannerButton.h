#pragma once
#include "Scanner.h"
#include "Button.h"

class ScannerButton : public Button{
private:
	Scanner* scanner;
	void drawButton() {
		Button::draw();
	}
	void drawScanner() {
		scanner->draw(x + selectedPainter->getWidth(), y + selectedPainter->getHeight());
	}
public:
	ScannerButton(int x, int y, Scanner* scanner, Painter* unselectPainter, Printer* unselectPrinter, Painter* selectPainter, Printer* selectPrinter, const bool borderFlag = true):
		Button(x, y, scanner->getWidth()+2*selectPainter->getWidth(), scanner->getHeight()+2*selectPainter->getHeight(), "", unselectPainter, unselectPrinter, selectPainter, selectPrinter, borderFlag) {

		this->scanner = scanner;
	}
	void draw() {
		drawButton();
		drawScanner();
	}
	string getText() {
		return scanner->getText();
	}
	void update(char input, bool redraw) override{
		scanner->enter(input, redraw);
	}
};