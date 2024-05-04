#include "DrawHuman.h"

void DrawHuman::draw(float fov, float theta, GLuint modelMatLoc, GLuint projMatLoc)
{
	switch (ProcessInput::Current_DrawingMode)
	{
	case Points:
		glPointSize(10);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		break;
	case Lines:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case FilledTriangle:
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	default:
		break;
	}

	//Draw Head
	Shapes::BindPrism();
	glm::mat4 ModelMat =
		glm::translate(glm::vec3(5, 1, 0.0f)) *
		glm::rotate(theta * 180 / 3.14f, glm::vec3(0, 1, 0)) *
		glm::scale(glm::vec3(0.3f, 0.3f, 0.3f));

	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(ModelMat));
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, NULL);

	//Draw Body
	Shapes::BindCube();
	ModelMat =
		glm::translate(glm::vec3(5, 0.1f, 0.f)) *
		glm::rotate(theta * 180 / 3.14f, glm::vec3(0, 1, 0)) *
		glm::scale(glm::vec3(0.3f, 1.2f, 0.3f));

	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(ModelMat));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

	// Draw Left Hand
	Shapes::BindCube();
	ModelMat =
		glm::translate(glm::vec3(5.f, 0.f, 0.f)) *
		glm::rotate(theta * 180 / 3.14f, glm::vec3(0, 1, 0)) *
		glm::translate(glm::vec3(0.3f, 0.3f, 0.f)) *
		glm::rotate(180 / 3.14f, glm::vec3(0.f, 0.f, 1.f)) *
		glm::scale(glm::vec3(0.1f, 0.5f, 0.1f));

	ModelMat *= glm::rotate(theta * 180 / 3.14f, glm::vec3(0, 1, 0));

	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(ModelMat));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

	//Draw Right Hand
	Shapes::BindCube();
	ModelMat =
		glm::translate(glm::vec3(5.f, 0.f, 0.f)) *
		glm::rotate(theta * 180 / 3.14f, glm::vec3(0, 1, 0)) *
		glm::translate(glm::vec3(-0.3f, 0.3f, 0.f)) *
		glm::rotate(180 / 3.14f, glm::vec3(0.f, 0.f, 1.f)) *
		glm::scale(glm::vec3(0.1f, 0.5f, 0.1f));

	ModelMat *= glm::rotate(theta * 180 / 3.14f, glm::vec3(0, 1, 0));

	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(ModelMat));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

	//Draw Right Leg
	Shapes::BindCube();
	ModelMat = glm::translate(glm::vec3(5.f, 0.f, 0.f)) *
		glm::rotate(theta * 180 / 3.14f, glm::vec3(0, 1, 0)) *
		glm::translate(glm::vec3(0.3f, -0.6f, 0.f)) *
		glm::rotate(180 / 3.14f, glm::vec3(-0.5, 1, 1.2)) *
		glm::scale(glm::vec3(0.1f, 0.8f, 0.1f));

	ModelMat *= glm::rotate(theta * 180 / 3.14f, glm::vec3(0, 1, 0));

	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(ModelMat));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

	//Draw Left Leg
	Shapes::BindCube();
	ModelMat =
		glm::translate(glm::vec3(5.f, 0.f, 0.f)) *
		glm::rotate(theta * 180 / 3.14f, glm::vec3(0, 1, 0)) *
		glm::translate(glm::vec3(-0.3f, -0.6f, 0.f)) *
		glm::rotate(180 / 3.14f, glm::vec3(-0.5, -1, -1.2)) *
		glm::scale(glm::vec3(0.1f, 0.8f, 0.1f));

	ModelMat *= glm::rotate(theta * 180 / 3.14f, glm::vec3(0, 1, 0));

	glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, glm::value_ptr(ModelMat));
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

	// Update the projection matrix with the zoom level
	glm::mat4 projMat = glm::perspectiveFov(fov, static_cast<float>(WIDTH), static_cast<float>(HEIGHT), 0.1f, 100.0f);
	glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, glm::value_ptr(projMat));
}