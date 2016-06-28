#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

struct Parameters {
	Vector2u WINDOW_SIZE = {800, 600};
	Vector2f FIRST_BOX_SIZE = {50, 50};
	Vector2f SECOND_BOX_SIZE = {300, 50};
	const Vector2f FIRST_BOX_POSITION = {200, 200.f};
	const Vector2f SECOND_BOX_POSITION = {300, 200.f};
	const Vector2f LINE_SIZE = {60, 5};
	const static int TIME_PER_FRAME = 25;
	const unsigned TEXT_SIZE = 40;
} param;

struct MouseState {
	Vector2f position;
	bool buttonPressedAtCheckBox = false;
	bool releasedButtonAtCheckBox = false;
	bool buttonPressedAtWriteField = false;
	bool releasedButtonAtWriteField = false;
};

struct CheckBoxControl {
	RectangleShape checkBox;
	RectangleShape writeField;
	bool chooseCheckBox = false;
	bool chooseWriteField = false;
};

struct BoxesArea {
	const float FIRST_BOX_LEFT_EDGE = param.FIRST_BOX_POSITION.x - 5;
	const float FIRST_BOX_RIGHT_EDGE = param.FIRST_BOX_POSITION.x + param.FIRST_BOX_SIZE.x + 5;
	const float FIRST_BOX_UPPER_EDGE = param.FIRST_BOX_POSITION.y - 5;
	const float FIRST_BOX_LOWER_EDGE = param.FIRST_BOX_POSITION.y + param.FIRST_BOX_SIZE.y + 5;

	const float SECOND_BOX_LEFT_EDGE = param.SECOND_BOX_POSITION.x - 5;
	const float SECOND_BOX_RIGHT_EDGE = param.SECOND_BOX_POSITION.x + param.SECOND_BOX_SIZE.x + 5;
	const float SECOND_BOX_UPPER_EDGE = param.SECOND_BOX_POSITION.y - 5;
	const float SECOND_BOX_LOWER_EDGE = param.SECOND_BOX_POSITION.y + param.SECOND_BOX_SIZE.y + 5;
} boxesArea;

struct LineEditControl {
	Font font;
	Text text;
	RectangleShape line1;
	RectangleShape line2;
};


void InitializeCheckBoxes(CheckBoxControl &box) {
	box.checkBox.setSize(param.FIRST_BOX_SIZE);
	box.checkBox.setPosition(param.FIRST_BOX_POSITION);
	box.checkBox.setFillColor(Color::White);
	box.checkBox.setOutlineThickness(5);
	box.checkBox.setOutlineColor(Color::Black);
}

void InitializeFieldsForWriting(CheckBoxControl &box) {
	box.writeField.setSize(param.SECOND_BOX_SIZE);
	box.writeField.setPosition(param.SECOND_BOX_POSITION);
	box.writeField.setFillColor(Color::White);
	box.writeField.setOutlineThickness(5);
	box.writeField.setOutlineColor(Color::Black);
}

void InitializeText(LineEditControl &control) {
	if (!control.font.loadFromFile("res/Ubuntu-R.ttf")) {
		throw;
	}
	control.text.setFont(control.font);
	control.text.setCharacterSize(param.TEXT_SIZE);
	control.text.setString("");
	control.text.setColor(Color::Red);
	control.text.setPosition(param.SECOND_BOX_POSITION.x, param.SECOND_BOX_POSITION.y - 5);
}

void InitializeSign(LineEditControl &control) {
	control.line1.setSize(param.LINE_SIZE);
	control.line1.setOrigin(param.LINE_SIZE.x / 2, param.LINE_SIZE.y / 2);
	control.line1.setPosition(param.FIRST_BOX_POSITION + (param.FIRST_BOX_SIZE) / 2.f);
	control.line1.setFillColor(Color::Red);
	control.line1.setRotation(-45);

	control.line2.setSize(param.LINE_SIZE);
	control.line2.setOrigin(param.LINE_SIZE.x / 2, param.LINE_SIZE.y / 2);
	control.line2.setPosition(param.FIRST_BOX_POSITION + (param.FIRST_BOX_SIZE) / 2.f);
	control.line2.setFillColor(Color::Red);
	control.line2.setRotation(45);
}

void InitializeObjects(CheckBoxControl &box, LineEditControl &control) {
	InitializeCheckBoxes(box);
	InitializeFieldsForWriting(box);
	InitializeText(control);
	InitializeSign(control);
}

void OnEnterText(LineEditControl &control, Event const& event) {
	std::wstring currentString = control.text.getString();

	Uint32 inputChar = event.text.unicode;

	if (iswprint(inputChar)) {
		currentString += inputChar;
		unsigned int characterSize = control.text.getCharacterSize() / 2;
		size_t sizeString = (currentString.size() + 2) * characterSize;
		if (sizeString < (param.SECOND_BOX_SIZE.x + param.SECOND_BOX_SIZE.y)) {
			control.text.setString(currentString);
		}
	}
}

void OnDeleteText(LineEditControl &control) {
	String currentString = control.text.getString();
	size_t sizeString = currentString.getSize();
	if (sizeString) {
		currentString.erase(sizeString - 1);
		control.text.setString(currentString);
	}
}

bool isMouseInCheckBox (MouseState &mouse) {
	return ((mouse.position.x >= boxesArea.FIRST_BOX_LEFT_EDGE && mouse.position.x <= boxesArea.FIRST_BOX_RIGHT_EDGE) &&
			(mouse.position.y >= boxesArea.FIRST_BOX_UPPER_EDGE && mouse.position.y <= boxesArea.FIRST_BOX_LOWER_EDGE));
}

bool isMouseInWriteField (MouseState &mouse) {
	return (mouse.position.x >= boxesArea.SECOND_BOX_LEFT_EDGE && mouse.position.x <= boxesArea.SECOND_BOX_RIGHT_EDGE) &&
		   (mouse.position.y >= boxesArea.SECOND_BOX_UPPER_EDGE && mouse.position.y <= boxesArea.SECOND_BOX_LOWER_EDGE);
}

void ChangeColorFirstBox(CheckBoxControl &box, MouseState &mouse) {
	if (!(isMouseInCheckBox(mouse)) && !box.chooseCheckBox) {
		box.checkBox.setFillColor(Color::White);
		box.checkBox.setOutlineColor(Color::Black);
	}
	else if (!box.chooseCheckBox) {
		box.checkBox.setFillColor(Color::White);
		box.checkBox.setOutlineColor(Color::Green);
	}
	else {
		box.checkBox.setFillColor(Color::White);
		box.checkBox.setOutlineColor(Color::Red);
	}
}

void ChangeColorSecondBox(CheckBoxControl &box, MouseState &mouse) {
	if (!(isMouseInWriteField(mouse)) && !box.chooseWriteField) {
		box.writeField.setFillColor(Color::White);
		box.writeField.setOutlineColor(Color::Black);
	}
	else if (!box.chooseWriteField) {
		box.writeField.setFillColor(Color::White);
		box.writeField.setOutlineColor(Color::Green);
	}
	else {
		box.writeField.setFillColor(Color::White);
		box.writeField.setOutlineColor(Color::Red);
	}
}

void FindMousePosition(RenderWindow & window, MouseState &mouse) {
	mouse.position.x = Mouse::getPosition(window).x;
	mouse.position.y = Mouse::getPosition(window).y;
}

void Draw(RenderWindow & window, LineEditControl &control, CheckBoxControl &box) {
    window.clear(Color::Cyan);
	window.draw(box.checkBox);
	window.draw(box.writeField);
	if (box.chooseCheckBox) {
		window.draw(control.line1);
		window.draw(control.line2);
	}
	if (box.chooseWriteField) {
		window.draw(control.text);
	}
    window.display();
}

bool isMousePressed(Event & event) {
	return Event::MouseButtonPressed;
}

bool isMouseReleased(Event & event) {
	return Event::MouseButtonReleased;
}

void CheckBoxProcessEvents(Event &event, MouseState &mouse, CheckBoxControl &box) {
	if (event.mouseButton.button == sf::Mouse::Left && isMousePressed(event) && isMouseInCheckBox(mouse)) {
		mouse.buttonPressedAtCheckBox = true;
	}
	else if (isMouseReleased(event) && isMouseInCheckBox(mouse) && mouse.buttonPressedAtCheckBox) {
		mouse.releasedButtonAtCheckBox = true;
	}
	if (mouse.buttonPressedAtCheckBox && mouse.releasedButtonAtCheckBox) {
		box.chooseCheckBox = !(box.chooseCheckBox);
		mouse.buttonPressedAtCheckBox = false;
		mouse.releasedButtonAtCheckBox = false;
	}
}

void WriteFieldProcessEvents(Event &event, MouseState &mouse, CheckBoxControl &box, LineEditControl &control) {
	if (event.mouseButton.button == sf::Mouse::Left && isMousePressed(event) && isMouseInWriteField(mouse)) {
		mouse.buttonPressedAtWriteField = true;
	}
	else if (isMouseReleased(event) && isMouseInWriteField(mouse) && mouse.buttonPressedAtWriteField) {
		mouse.releasedButtonAtWriteField = true;
	}
	if (mouse.buttonPressedAtWriteField && mouse.releasedButtonAtWriteField) {
		box.chooseWriteField = !(box.chooseWriteField);
		mouse.buttonPressedAtWriteField = false;
		mouse.releasedButtonAtWriteField = false;
		control.text.setString("");
	}
	if (Keyboard::isKeyPressed(Keyboard::BackSpace)) {
		OnDeleteText(control);
	}
}

void ProcessEvents(RenderWindow &window, LineEditControl &control, CheckBoxControl &box, MouseState &mouse) {
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
		}
		if (box.chooseWriteField && event.type != Event::MouseButtonPressed)
			OnEnterText(control, event);
	}
	CheckBoxProcessEvents(event, mouse, box);
	WriteFieldProcessEvents(event, mouse, box, control);
};

int main() {
	CheckBoxControl box;
	LineEditControl control;
	MouseState mouse;
	Clock frameClock;
	sf::RenderWindow window(sf::VideoMode(param.WINDOW_SIZE.x, param.WINDOW_SIZE.y), "GUI");
	int timeSinceLastUpdate;
	InitializeObjects(box, control);
	while (window.isOpen()) {
		timeSinceLastUpdate = frameClock.getElapsedTime().asMilliseconds();
		if (timeSinceLastUpdate >= param.TIME_PER_FRAME) {
			frameClock.restart();
			ProcessEvents(window, control, box, mouse);
			FindMousePosition(window, mouse);
			ChangeColorFirstBox(box, mouse);
			ChangeColorSecondBox(box, mouse);
			Draw(window, control, box);
		}
	}
	return 0;
}
