#pragma once



class Input
{
public:

	static Input* Instance();

	bool IsXClicked();

private:

	Input();
	Input(const Input&);
	Input& operator=(Input&);

	bool m_IsXClicked;


};

