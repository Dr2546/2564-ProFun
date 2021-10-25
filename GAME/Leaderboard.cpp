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

void Leaderboard::initGUI()
{
	this->board.setString("Leaderboard");
	this->board.setCharacterSize(50);
	this->board.setFillColor(Color::White);
	this->board.setPosition(
		this->window->getSize().x / 2.f - this->board.getGlobalBounds().width / 2.f,
		100.f);
	this->board.setFont(this->font);

	this->line1.setSize(Vector2f(this->window->getSize().x / 2.f - this->board.getGlobalBounds().width / 2.f, 5.f));
	this->line1.setPosition(Vector2f(this->window->getSize().x / 2.f - this->board.getGlobalBounds().width / 2.f, 160.f));
	this->line1.setFillColor(Color::White);

	this->line2.setSize(Vector2f(this->window->getSize().x / 2.f - this->board.getGlobalBounds().width / 2.f, 5.f));
	this->line2.setPosition(Vector2f(this->board.getGlobalBounds().width / 2.f, 160.f));
	this->line2.setFillColor(Color::White);
	this->line2.setRotation(90.f);
}

void Leaderboard::initFont()
{
	if (!this->font.loadFromFile("Resources/PixellettersFull.ttf"))
		cout << "Failed to load font" << "\n";
}

void Leaderboard::initButtons()
{
	this->buttons["BACK"] = new gui::Button(100.f, 200.f, 100.f, 100.f, &this->font, "Back", 50,
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0)
	);
	this->buttons["CLEAR"] = new gui::Button(100.f, 400.f, 100.f, 100.f, &this->font, "Clear Board", 50,
		Color(200, 200, 200, 200), Color(255, 255, 255, 255), Color(20, 20, 20, 50),
		Color(70, 70, 70, 0), Color(150, 150, 150, 0), Color(20, 20, 20, 0)
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
		dumname.setPosition(Vector2f(800.f, 200.f + space));
		players.push_back(dumname);

		Text dumscore;
		dumscore.setCharacterSize(50);
		dumscore.setFillColor(Color::White);
		dumscore.setFont(this->font);
		dumscore.setString(to_string(its->second));
		dumscore.setPosition(Vector2f(1000.f, 200.f + space));
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
	this->initFont();
	this->initGUI();
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
	this->window->draw(this->board);
	this->window->draw(this->line1);
	this->window->draw(this->line2);
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
