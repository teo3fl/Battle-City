#pragma once
#include "State.h"

class MainMenuState :
	public State
{
private:
	void InitializeKeybinds() override;
public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys);
	virtual ~MainMenuState();

	//Functions
	void EndState() override;

	void UpdateInput(const float& dt) override;
	void Update(const float& dt) override;
	void Render(sf::RenderTarget* target = nullptr) override;

};