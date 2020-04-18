#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>

using namespace std::chrono;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const unsigned int N_CURVE_PTS = 3;  // change N_CURVE_PTS= 1001 for actual implementation
float controlPts[] = { -0.50f, 0.25f, 0.0f, -0.25f, 0.75f, 0.0f, 0.25f, 0.50f, 0.0f, 0.50, 0.00f, 0.0f };

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

void getVertices_bez3DeCasteljau (unsigned int N_CURVE_PTS, float* vertices) {
	float x[4][3], y[4][3], z[4][3];
	float px[4],py[4],pz[4];
	float t = 0;

	for(int i=0; i<=3; i++)
	{
		px[i] = *vertices;
		vertices++;
		py[i] = *vertices;
		vertices++;
		pz[i] = *vertices;
		vertices++;
	}
	
	while (t <= 1) {
		x[1][0] = (1 - t)*x0 + t * x1;
		y[1][0] = (1 - t)*y0 + t * y1;
		z[1][0] = (1 - t)*z0 + t * z1;
		x[1][1] = (1 - t)*x1 + t * x2;
		y[1][1] = (1 - t)*y1 + t * y2;
		z[1][1] = (1 - t)*z1 + t * z2;
		x[1][2] = (1 - t)*x2 + t * x3;
		y[1][2] = (1 - t)*y2 + t * y3;
		z[1][2] = (1 - t)*z2 + t * z3;

		x[2][0] = (1 - t)*x[1][0] + t * x[1][1];
		y[2][0] = (1 - t)*y[1][0] + t * y[1][1];
		z[2][0] = (1 - t)*z[1][0] + t * z[1][1];
		x[2][1] = (1 - t)*x[1][1] + t * x[1][2];
		y[2][1] = (1 - t)*y[1][1] + t * y[1][2];
		z[2][1] = (1 - t)*z[1][1] + t * z[1][2];

		x[3][0] = (1 - t)*x[2][0] + t * x[2][1];
		y[3][0] = (1 - t)*y[2][0] + t * y[2][1];
		z[3][0] = (1 - t)*z[2][0] + t * z[2][1];
		cout << x[3][0] << " " << y[3][0] << " "<<z[3][0]<<endl;
		t += 0.1;
	}
}
void getVertices_bez3Mat(unsigned int N_CURVE_PTS, float* vertices) {
	
	float b[3][4], a[4][4], c[4][1], ans[3][4];
	float temp = 0;
	float r = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			b[j][i] = *vertices;
			vertices++;
		}
	}

	a = [
		1,-3, 3,-1,
		0, 3,-6, 3,
		0, 0, 3,-3,
		0, 0, 0, 1
	];

	for (int i = 0; i < 3; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			for (int k = 0; k < 4; k++) 
			{
				ans[i][j] = b[i][k] * a[k][j];
				temp += ans[i][j];
				if (k == 3) 
				{
					ans[i][j] = temp;
					temp = 0;
				}

			}
		}
	}

	while (r < 1.1) {
		float x = ans[0][0] + ans[0][1] * r + ans[0][2] * r*r + ans[0][3] * r*r*r;
		float y = ans[1][0] + ans[1][1] * r + ans[1][2] * r*r + ans[1][3] * r*r*r;
		float z = ans[2][0] + ans[2][1] * r + ans[2][2] * r*r + ans[2][3] * r*r*r;
		cout << x << " " << y << " " << z << endl;
		r = r + 0.1;
	}
	
}
void getVertices_bez3Horner(unsigned int N_CURVE_PTS, float* vertices) {
	float px[4],py[4],pz[4];
	float h = 0;

	for(int i=0; i<=3; i++)
	{
		px[i] = *vertices;
		vertices++;
		py[i] = *vertices;
		vertices++;
		pz[i] = *vertices;
		vertices++;
	}
	
	while (h < 1.1) {
		float s = 1 - h;
		float x = ((s*px[0] + 3 * h*px[1])*s + 3 * h*h*px[2])*s + h*h*h*px[3];
		float y = ((s*py[0] + 3 * h*py[1])*s + 3 * h*h*py[2])*s + h*h*h*py[3];
		float z = ((s*pz[0] + 3 * h*pz[1])*s + 3 * h*h*pz[2])*s + h*h*h*pz[3];
		cout << x << " " << y << " " << z <<endl;
		h += 0.1;
	}
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	unsigned int chunkSzytes = N_CURVE_PTS * 3 * sizeof(float);
	float *vertices = (float*)malloc(chunkSzytes);   //note that malloc always should come with corresponding free() at the end

	auto start = high_resolution_clock::now();  //Note need C++11 and #include <chrono> using namespace std::chrono

	getVertices_bez3DeCasteljau(N_CURVE_PTS, vertices);

	auto stop_1 = high_resolution_clock::now();

	getVertices_bez3Mat(N_CURVE_PTS, vertices);

	auto stop_2 = high_resolution_clock::now();

	getVertices_bez3Horner(N_CURVE_PTS, vertices);

	auto stop_3 = high_resolution_clock::now();

	auto duration_bez3DeCasteljau = duration_cast<microseconds>(stop_1 - start);
	std::cout << "de Casteljau time (ms)=  " << duration_bez3DeCasteljau.count() << std::endl;

	auto duration_bez3Mat = duration_cast<microseconds>(stop_2 - stop_1);
	std::cout << "bezMat time (ms)=  " << duration_bez3Mat.count() << std::endl;

	auto duration_bez3Horner = duration_cast<microseconds>(stop_3 - stop_2);
	std::cout << "Horner time (ms)=  " << duration_bez3Horner.count() << std::endl;

	GLfloat points[33]
	{
		1, 1, 0,
		1.732, 1.414, 0,
		2, 1.618, 0,
		3.142, 1.999, 0,
		3.188, 1.967, 0,
		4.064, 1.662, 0,
		5.744, 1.988, 0,
		5.775, 1.113, 0,
		6.711, 1.493, 0,
		7.817, 1.813, 0,
		8, 2, 0
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, chunkSzytes, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_LINE_STRIP, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}