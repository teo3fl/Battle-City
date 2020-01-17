#pragma once

#ifdef LOGGING_EXPORTS
#define LOGGER __declspec(dllimport)
#else
#define LOGGER __declspec(dllimport)
#endif

class State
{

public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~State();
	virtual void InitializeKeybinds() = 0;
	void SetText(sf::Text& text, const sf::Font& font, const sf::Color& fillColor, uint16_t size, const sf::Vector2f& position, float thickness = 0);
	void SetText(sf::Text& text, const sf::Font& font, const sf::Color& fillColor, uint16_t size, float thickness = 0);

	const bool& GetQuit() const;
	const bool GetKeytime();

	virtual void CheckForQuit();

	void LoadHighScore();
	virtual void UpdateKeytime(const float& dt);
	virtual void UpdateInput(const float& dt) = 0;
	virtual void Update(const float& dt) = 0;
	virtual void Render(sf::RenderTarget* target = nullptr) = 0;

protected:
	sf::RenderWindow* m_window;
	std::map<std::string, int>* m_supportedKeys;
	std::map<std::string, int> m_keybinds;
	bool m_quit : 1;

	float m_keytime;
	float m_keytimeMax;

	//Resources
	std::map<std::string, sf::Texture> m_textures;

	sf::Text m_highScoreText;
	uint32_t m_highScore;

	Logger logger;
};
