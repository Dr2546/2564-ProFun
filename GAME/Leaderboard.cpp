#include "Leaderboard.h"

void Leaderboard::initScoreboard()
{
	this->scoreboard.open("Resources/scoreboard.txt", ios_base::in);
	
	vector<string> v;
	string line;
	for (; getline(this->scoreboard, line); )
		v.push_back(line);
	sort(v.begin(), v.end(), [&](string s1, string s2) -> bool { return this->get_rank(s1) > this->get_rank(s2); });

	for (auto i = v.begin(); i != v.end(); i++)
	{
		string name, scores;
		name = *i;

		string::size_type pos = name.find(' ');

		if (name.npos != pos)
		{
			scores = name.substr(pos + 1);
			name = name.substr(0, pos);
		}

		score.push_back(make_pair(name, stoi(scores)));

		if (score.size() >= 5)
			break;
	}

	this->scoreboard.close();
}

void Leaderboard::initSprite()
{
	Vector2u Ts;
	Vector2u Ws = this->window->getSize();

	float scalex, scaley;
	Ts = txtbg.getSize();
	scalex = (float)Ws.x / Ts.x;
	scaley = (float)Ws.y / Ts.y;
	this->spritebg.setTexture(txtbg);
	this->spritebg.setScale(scalex, scaley);
}

void Leaderboard::initTexture()
{
	if (!this->txtbg.loadFromFile("Resources/Background/bg5.jpg"))
	{
		cout << "Could not load texture file." << "\n";
	}
}

void Leaderboard::initGUI()
{
	this->leaderbox.setPosition(Vector2f(this->window->getSize().x / 4.f - 50.f, 125.f));
	this->leaderbox.setSize(Vector2f(this->window->getSize().x / 2.f + 100.f, 200.f + this->window->getSize().y / 2.f));
	this->leaderbox.setFillColor(Color(75, 75, 75));

	this->board.setFont(this->font);
	this->board.setString("Leaderboard");
	this->board.setCharacterSize(70);
	this->board.setFillColor(Color::White);
	this->board.setOrigin(this->board.getLocalBounds().width / 2.f, this->board.getLocalBounds().height / 2.f);
	this->board.setPosition(this->window->getSize().x / 2.f, 150.f);

	this->line1.setSize(Vector2f(this->window->getSize().x / 2.f, 5.f));
	this->line1.setPosition(Vector2f(this->window->getSize().x / 4.f , 250.f));
	this->line1.setFillColor(Color::White);

	this->line2.setSize(Vector2f(5.f, this->window->getSize().y/2.f));
	this->line2.setPosition(Vector2f(this->window->getSize().x / 2.f - 5.f, 250.f));
	this->line2.setFillColor(Color::White);

	this->line3.setSize(Vector2f(this->window->getSize().x / 2.f, 5.f));
	this->line3.setPosition(Vector2f(this->window->getSize().x / 4.f, 250.f + this->window->getSize().y/2.f));
	this->line1.setFillColor(Color::White);

	this->con1.setFillColor(Color(75, 75, 75));
	this->con1.setPosition(Vector2f(0.f, 0.f));
	this->con1.setSize(Vector2f(this->window->getSize().x, 100.f));

	this->con2.setFillColor(Color(75, 75, 75));
	this->con2.setPosition(Vector2f(0.f, this->window->getSize().y - 80.f));
	this->con2.setSize(Vector2f(this->window->getSize().x, 80.f));

	this->gamename.setFont(font);
	this->gamename.setCharacterSize(80);
	this->gamename.setFillColor(Color(255, 99, 71));
	this->gamename.setString("C a s t l e     B r e a k");
	this->gamename.setOrigin(this->gamename.getLocalBounds().width / 2.f, this->gamename.getLocalBounds().height / 2.f);
	this->gamename.setPosition(
		this->con1.getPosition().x + this->con1.getSize().x / 2.f,
		this->con1.getPosition().y + this->con1.getSize().y / 4.f - 10.f);

	this->student.setFont(font);
	this->student.setCharacterSize(50);
	this->student.setFillColor(Color::Black);
	this->student.setString("64010272 Daniel Riyavong");
	this->student.setOrigin(this->student.getLocalBounds().width / 2.f, this->student.getLocalBounds().height / 2.f);
	this->student.setPosition(
		this->con2.getPosition().x + this->con2.getSize().x / 2.f,
		this->con2.getPosition().y + this->con2.getSize().y / 4.f);
}

void Leaderboard::initFont()
{
	if (!this->font.loadFromFile("Resources/PixellettersFull.ttf"))
		cout << "Failed to load font" << "\n";
}

void Leaderboard::initButtons()
{
	this->buttons["BACK"] = new gui::Button(this->window->getSize().x / 3.f, 900.f,
		250.f, 50.f, &this->font, "Back", 50,
		Color(55, 55, 55), Color(255, 255, 255), Color(255, 255, 255),
		Color(150, 150, 150), Color(75, 75, 75), Color(75, 75, 75),
		Color(200, 200, 200), Color(255, 255, 255), Color(255, 255, 255)
	);
	this->buttons["CLEAR"] = new gui::Button(this->window->getSize().x * 2.f / 3.f - 250.f, 900.f,
		250.f, 50.f, &this->font, "Clear Board", 50,
		Color(55, 55, 55), Color(255, 255, 255), Color(255, 255, 255),
		Color(150, 150, 150), Color(75, 75, 75), Color(75, 75, 75),
		Color(200, 200, 200), Color(255, 255, 255), Color(255, 255, 255)
	);
}

void Leaderboard::resetButtons()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();

	this->initButtons();
}

void Leaderboard::initScoreboardText()
{
	float space = 0.f;	
	auto its = this->score.begin();
	for (its = this->score.begin(); its != this->score.end(); its++)
	{
		Text dumname;
		dumname.setCharacterSize(50);
		dumname.setFillColor(Color::White);
		dumname.setFont(this->font);
		dumname.setString(its->first);
		dumname.setOrigin(dumname.getLocalBounds().width / 2.f, dumname.getLocalBounds().height / 2.f);
		dumname.setPosition(Vector2f(this->window->getSize().x / 3.f, 300.f + space));
		players.push_back(dumname);

		Text dumscore;
		dumscore.setCharacterSize(50);
		dumscore.setFillColor(Color::White);
		dumscore.setFont(this->font);
		dumscore.setString(to_string(its->second));
		dumscore.setOrigin(dumscore.getLocalBounds().width / 2.f, dumscore.getLocalBounds().height / 2.f);
		dumscore.setPosition(Vector2f(this->window->getSize().x * 2.f / 3.f, 300.f + space));
		player_score.push_back(dumscore);

		space += 100.f;
	}
}

int Leaderboard::get_rank(string input)
{
	stringstream ss(input);
	string s;
	// keep extracting strings, last one would be your 'int' rank
	for (; ss >> s; );
	return atoi(s.c_str());
}

Leaderboard::Leaderboard(StateData* statedata) : State(statedata)
{
	this->initTexture();
	this->initFont();
	this->initGUI();
	this->initSprite();
	this->initScoreboard();
	this->initScoreboardText();
	this->initButtons();
	this->resetButtons();
}

Leaderboard::~Leaderboard()
{
}

void Leaderboard::updateInput(const float& dt)
{
}

void Leaderboard::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
}

void Leaderboard::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderGUI();
	this->renderButtons();
	this->renderScoreboardText();
}

void Leaderboard::updateButtons()
{
	for (auto& it : this->buttons)
		it.second->update(this->mousePosWindow);

	if (this->buttons["BACK"]->isPress())
	{
		this->endState();
	}

	if (this->buttons["CLEAR"]->isPress())
	{
		if (remove("Resources/scoreboard.txt"))
			this->endState();
	}
}

void Leaderboard::renderGUI()
{
	this->window->draw(this->spritebg);
	this->window->draw(this->leaderbox);
	this->window->draw(this->board);
	this->window->draw(this->line1);
	this->window->draw(this->line2);
	this->window->draw(this->line3);
	this->window->draw(this->con1);
	this->window->draw(this->con1);
	this->window->draw(this->con2);
	this->window->draw(this->gamename);
	this->window->draw(this->student);
}

void Leaderboard::renderButtons()
{
	for (auto& it : this->buttons)
		it.second->render(*this->window);
}

void Leaderboard::renderScoreboardText()
{
	for (auto& its : this->players)
	{
		this->window->draw(its);
	}
	for (auto& it : this->player_score)
	{
		this->window->draw(it);
	}
}
