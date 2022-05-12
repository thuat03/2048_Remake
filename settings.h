#pragma once
class Settings {
public:
	bool music;
	Settings(bool _music = true) {
		this->music = _music;
	}
};