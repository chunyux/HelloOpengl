#define _CRT_SECURE_NO_DEPRECATE
#include <gl\glew.h>
#include <gl\freeglut.h>
#include <gl\GL.h>
#include <gl\glu.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

#define BUFFER_OFFSET(i) ((char*)NULL + (i))
GLuint shaderProgramID;
GLuint vao = 0;
GLuint vbo;
GLuint positionID, colorID;

using namespace std;

static char* readFile(const char* fn){
	FILE* fp = fopen(fn, "r");
	fseek(fp, 0, SEEK_END);
	long file_length = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* contents = new char[file_length + 1];
	for (int i = 0; i < file_length + 1; i++){
		contents[i] = 0;
	}
	fread(contents, 1, file_length, fp);
	contents[file_length + 1] = '\0';
	fclose(fp);
	return contents;
}

GLuint makeVertexShader(const char* shaderSource){
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, (const GLchar **)&shaderSource, NULL);
	glCompileShader(vertexShaderID);
	return vertexShaderID;
}

GLuint makeFragmentShader(const char* shaderSource){
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, (const GLchar **)&shaderSource, NULL);
	glCompileShader(fragmentShaderID);
	return fragmentShaderID;
}

GLuint makeShaderProgram(GLuint vertexShaderID, GLuint fragmentShaderID){
	GLuint shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShaderID);
	glAttachShader(shaderID, fragmentShaderID);
	glLinkProgram(shaderID);
	return shaderID;
}


int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA );
	glutInitWindowSize(800, 600);
	glutCreateWindow("Shaders");
	glewInit();
 
	char* vertexShaderSourceCode = readFile("vertexShader.vsh");
	char* fragmentShaderSourceCode = readFile("fragmentShader.fsh");
	GLuint vertShaderID = makeVertexShader(vertexShaderSourceCode);
	GLuint fragShaderID = makeFragmentShader(fragmentShaderSourceCode);
	GLuint shaderProgramID = makeShaderProgram(vertShaderID, fragShaderID);
	glUseProgram(shaderProgramID);
	printf("vertShaderID is %d\n", vertShaderID);
	printf("fragShaderID is %d\n", fragShaderID);
	printf("ShaderProgramID is %d\n", shaderProgramID);
	glDeleteProgram(shaderProgramID);
	int temp;
	scanf("%d", &temp);
	
	return 0;

}
