#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include "Window.h"
#include "Camera.h"
#include "Texture.h"

Window mainWindow;


constexpr float toRadians = 3.14159265f / 180.0f; // PI / 180

std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Camera camera;

Texture brickTexture;
Texture dirtTexture;

GLfloat curAngle = 0.0f;
static const std::string vShaderPath = std::string(SHADER_DIR) + "/shader.vert";
static const std::string fShaderPath = std::string(SHADER_DIR) + "/shader.frag";

static const char* vShader = vShaderPath.c_str();
static const char* fShader = fShaderPath.c_str();

static const std::string dirtPath = std::string(ASSETS_DIR) + "/textures/dirt.png";
static const std::string brickPath = std::string(ASSETS_DIR) + "/textures/bricks.png";

static const char* dirt = dirtPath.c_str();
static const char* brick = brickPath.c_str();


// a redundant comment to tell you that this method is for creating an object
void CreateObjects() {
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] = {
    	// x, y, z, u, v -> u and v are the texture coordinates.
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 1.0f, 0.5f, 0.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.5f, 1.0f
    };

    Mesh *obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 20, 12);
    meshList.push_back(obj1);

    Mesh *obj2 = new Mesh();
    obj2->CreateMesh(vertices, indices, 20, 12);
    meshList.push_back(obj2);
}


void CreateShaders() {
    auto *shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);
}

int main() 
{
	mainWindow = Window(1920, 1024 );
	if(mainWindow.Initialise()==1){
		return 1;
	} 

	CreateObjects();
	CreateShaders();
	camera = Camera(glm::vec3(0,0,0),glm::vec3(0,1,0),90.0f,0,0.01f,0.1f);

	const std::string brickLocation = std::string(ASSETS_DIR) + "/textures/brick.jpg";
	brickTexture = Texture(brick);
	brickTexture.LoadTexture();
	dirtTexture = Texture(dirt);
	dirtTexture.LoadTexture();

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	// Loop until window closed
	while (!mainWindow.getShouldClose())
	{
		// Get + Handle User Input
		glfwPollEvents();

		camera.keyControl(mainWindow.getKeys());
		camera.mouseControl(mainWindow.getXChange(),mainWindow.getYChange());

		// Clear the window
		glClearColor(0.1f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();

		glm::mat4 model(1.0f);	

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView,1,GL_FALSE,glm::value_ptr(camera.calculateViewMatrix()));
		brickTexture.UseTexture();
		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dirtTexture.UseTexture();
		meshList[1]->RenderMesh();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}