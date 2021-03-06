#pragma once

#include <iostream>
#include <map>

/************************************************************
*
* Singleton encapsulating keyboard events and properties
*
* TODO - Add modifier keys to the value section of the maps
*
*************************************************************/

class Keyboard{
public:

	/**
	* Returns true if the given key is currently pressed down
	*
	* @param The GLFW key code - eg. GLFW_KEY_A
	* @return Whether the key is currently down or not
	*/
	bool keyDown(int _glfwKeyCode);

	/**
	* Returns true if the given key was released since the keyboard's last call to update
	*
	* @param The GLFW key code - eg. GLFW_KEY_A
	* @return Whether the key was released since the last keyboard update
	*/
	bool keyJustUp(int _glfwKeyCode);

	/**
	* Returns true if the given key was pressed down since the keyboard's last call to update
	*
	* @param The GLFW key code - eg. GLFW_KEY_A
	* @return Whether the key was pressed down since the last keyboard update
	*/
	bool keyJustDown(int _glfwKeyCode);

	/**
	* Clears the maps of justPressed and justReleased keys
	*/
	void update();

	/**
	* Inserts _glfwKeyCode into the maps of justPressed and pressed keys
	*
	* @param The GLFW key code - eg. GLFW_KEY_A
	*/
	void keyDownListener(int _glfwKeyCode);

	/**
	* Inserts _glfwKeyCode into the map of justPressed keys and removes it from the maps of justPressed and pressed keys
	*
	* @param The GLFW key code - eg. GLFW_KEY_A
	*/
	void keyUpListener(int _glfwKeyCode);

	/**
	* Used to get a reference to the Keyboard singleton instance
	*
	* @return a reference to the keyboard singleton
	*/
	static Keyboard& getInstance();

private:
	Keyboard();
	~Keyboard();

	/** Map of keys which are currently pressed down */
	std::map<int, int> pressedKeys;
	/** Map of keys which were pressed down since the keyboard's last call to update */
	std::map<int, int> justPressedKeys;
	/** Map of keys which were released since the keyboard's last call to update */
	std::map<int, int> justReleasedKeys;
};