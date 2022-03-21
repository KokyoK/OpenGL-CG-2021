#pragma once

#include "Engine.h"		//! Superclass for accessing OpenGL/Context windowing
#include "Texture.h"	//! Handles Texture loading for bitmap images
#include "Camera.h"  //! Camera class
#include <vector>		//! Utility for maintaining DispalyableObjects in system

class DisplayableObject; // Anonymous

class Scene : public Engine
{
public:
	/**
	 * Constructor, overrides Engine() and takes in command line arguments, a title and initial window dimensions.
	 */
	Scene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight);
	virtual ~Scene();

	/** Return window width */
	static int GetWindowWidth();
	/** Return window height */
	static int GetWindowHeight();

	static int GetTexture(std::string fileName);
	/** Returns a pointer to the Camera */
	static Camera* GetCamera() {
		return &camera;
	}

protected:

	virtual void Initialise() = 0;
	void Draw();
	void Reshape(int w, int h);
	virtual void Projection();
	void Update(const double& deltaTime);

	// Input handling methods
	void HandleKey(unsigned char key, int state, int x, int y);
	void HandleSpecialKey(int key, int state, int x, int y);
	void HandleMouse(int button, int state, int x, int y);
	void HandleMouseDrag(int x, int y);
	void HandleMouseMove(int x, int y);
	void AddObjectToScene(DisplayableObject *obj);

private:
	static Camera camera;
	static Texture texture;
	std::vector<DisplayableObject*> objects;
};
