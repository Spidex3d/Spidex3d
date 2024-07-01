#include "Input.h"

Input* Input::Instance()
{
    static Input* inputObject = new Input();
    return nullptr;
}

bool Input::IsXClicked()
{
    return m_IsXClicked;
}

Input::Input()
{
    // TODO: insert return statement here
    m_IsXClicked = false;
}
