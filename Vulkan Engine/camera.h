#pragma once
#include <glm\glm.hpp>
class Camera
{
private:
	float fov;
	float znear, zfar;

	void updateViewMatrix();
public:
	enum CameraType { lookat, firstperson };
	CameraType type = CameraType::firstperson;

	glm::vec3 rotation = glm::vec3();
	glm::vec3 position = glm::vec3();

	float rotationSpeed = 1.0f;
	float movementSpeed = 1.0f;

	struct
	{
		glm::mat4 perspective;
		glm::mat4 view;
	} matrices;

	struct
	{
		bool left = false;
		bool right = false;
		bool up = false;
		bool down = false;
	} keys;

	bool moving();
	

	void setPerspective(float fov, float aspect, float znear, float zfar);


	void updateAspectRatio(float aspect);


	void setRotation(glm::vec3 rotation);

	void rotate(glm::vec3 delta);

	void setTranslation(glm::vec3 translation);

	void translate(glm::vec3 delta);

	void update(float deltaTime);

	// Update camera passing separate axis data (gamepad)
	// Returns true if view or position has been changed
	bool updatePad(glm::vec2 axisLeft, glm::vec2 axisRight, float deltaTime);

	bool viewChanged;
};