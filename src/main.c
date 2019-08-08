/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbesse <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/08 18:30:01 by cbesse            #+#    #+#             */
/*   Updated: 2019/08/08 18:30:20 by cbesse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"
#define WIDHT 1024
#define HEIGHT 800
#define COOLDOWN 20

int g_e = 1;
int key_cd = 0;
int g_flat = 0;

GLchar	*get_shader_source(char *filename)
{
	int		fd;
	int		ret;
	char	buffer[BUFFER_SIZE];
	char	*source;
	char	*del;

	source = ft_strnew(BUFFER_SIZE);
	fd = open(filename, O_RDONLY);
	while ((ret = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[ret] = '\0';
		del = source;
		source = ft_strjoin(source, buffer);
		ft_strdel(&del);
	}
	close(fd);
	return (source);
}

t_mat4	key_callback(GLFWwindow* window, t_mat4 view)
{
	int key;

	key_cd > 1 ? key_cd -= 1 : 0;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && key_cd <= 1)
	{
		g_e = !g_e;
		key_cd = COOLDOWN;
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && key_cd <= 1)
	{
		g_flat = !g_flat;
		key_cd = COOLDOWN;
	}
	key = glfwGetKey(window, 333);
	if (key == 1)
		view = mat4_translate(view, 0, 0, -0.25);
	key = glfwGetKey(window, 334);
	if (key == 1)
		view = mat4_translate(view, 0, 0, 0.25);
	key = glfwGetKey(window, 263);
	if (key == 1)
		view = mat4_translate(view, 0.25, 0, 0);
	key = glfwGetKey(window, 262);
	if (key == 1)
		view = mat4_translate(view, -0.25, 0, 0);
	key = glfwGetKey(window, 265);
	if (key == 1)
		view = mat4_translate(view, 0, 0.25, 0);
	key = glfwGetKey(window, 264);
	if (key == 1)
		view = mat4_translate(view, 0, -0.25, 0);
	return (view);
}

void	set_projection(t_mat4 *m, float fov)
{
	float	s;
	float	far;
	float	near;

	far = 100.0;
	near = 0.1;
	s = 1 / (tan(fov * 0.5 * M_PI / 180.0));
	set_mat4(m, 0);
	m->m[0] = s / ((float)(WIDHT / HEIGHT));
	m->m[5] = s;
	m->m[10] = -(far + near) / (far - near);
	m->m[11] = -1;
	m->m[14] = -2 * far * near / (far - near);
}

int	main(int ac, char **av) {
	GLFWwindow *window = NULL;
	const GLubyte *renderer;
	const GLubyte *version;
	GLuint vao;
	t_mat4 view;
	t_mat4 model;
	t_mat4 projection;
	GLint modelLocation;
	GLint viewLocation;
	GLint flat;
	GLint projectionLocation;
	GLint textLocation;
	mat4_id(&view);
	mat4_id(&model);
	set_projection(&projection, 90);
	view = mat4_translate(view, 0, 0, -5);
	GLuint ebo;
	GLuint *indices = NULL;
	GLuint texture;
	GLfloat *points = NULL;
	int idlen;
	int nbv;
	idlen = load_obj(&indices, &points, av[1], &nbv);
	/*
	   printf("     VERTEX       |       COLOR\n");
	   int i = 0;
	   while(i < nbv)
	   {
	   printf("%0.2f ",points[i]);
	   i++;
	   if (i % 6 == 0)
	   printf("\n");
	   else if(i % 3 == 0)
	   printf("  |  ");
	   }
	   i = 0;
	   printf("     INDICES\n");
	   while(i < idlen)
	   {
	   printf("%d ",indices[i]);
	   i++;
	   if (i % 3 == 0)
	   printf("\n");
	   }
	   */

	t_text text;
	load_bmp(&text, "./32bsys.bmp");
	printf("w = %d\n", text.width);
	printf("h = %d\n", text.height);
	printf("opp = %d\n", text.opp);
	printf("size = %d\n", text.size);
	printf("size = %d\n", text.line_size);

	/* these are the strings of code for the shaders
	   the vertex shader positions each vertex point */
	const GLchar *vertex_shader;
	const GLchar *fragment_shader;
	vertex_shader = get_shader_source("shaders/vertex2.glsl");
	fragment_shader = get_shader_source("shaders/fragment2.glsl");
	/* GL shader objects for vertex and fragment shader [components] */
	GLuint vert_shader, frag_shader;
	/* GL shader programme object [combined, to link] */
	GLuint shader_programme;

	/* start GL context and O/S window using the GLFW helper library */
	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return (1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIDHT, HEIGHT, "Hello Triangle", NULL, NULL);
	if (!window)
	{
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return (1);
	}
	glfwMakeContextCurrent(window);
	/* start GLEW extension handler */
	glewExperimental = GL_TRUE;
	glewInit();
	/* get version info */
	renderer = glGetString(GL_RENDERER); /* get renderer string */
	version = glGetString(GL_VERSION); /* version as a string */
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);
	/* tell GL to only draw onto a pixel if the shape is closer to the viewer
	   than anything already drawn at that pixel */
	glEnable(GL_DEPTH_TEST); /* enable depth-testing */
	/* with LESS depth-testing interprets a smaller depth value as meaning "closer" */
	glDepthFunc(GL_LESS);
	/* a vertex buffer object (VBO) is created here. this stores an array of
	   data on the graphics adapter's memory. in our case - the vertex points */


	GLuint vbo = 0;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof( GLfloat ) * nbv, points, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof( GLuint ) * idlen, indices, GL_STATIC_DRAW);

	/* the vertex array object (VAO) is a little descriptor that defines which
	   data from vertex buffer objects should be used as input variables to vertex
	   shaders. in our case - use our only VBO, and say 'every three floats is a
	   variable' **/
	/* "attribute #0 should be enabled when this vao is bound" */
	/* this VBO is already bound, but it's a good habit to explicitly specify which
	   VBO's data the following vertex attribute pointer refers to */
	/* "attribute #0 is created from every 3 variables in the above buffer, of type
	   float (i.e. make me vec3s)" */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);



	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, text.width, text.height, 0, GL_RGB, GL_UNSIGNED_BYTE, text.img);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);


	glBindVertexArray(0);
	/* here we copy the shader strings into GL shaders, and compile them. we
	   then create an executable shader 'program' and attach both of the compiled
	   shaders. we link this, which matches the outputs of the vertex shader to
	   the inputs of the fragment shader, etc. and it is then ready to use */
	vert_shader = glCreateShader(GL_VERTEX_SHADER);
	frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vert_shader, 1, &vertex_shader, NULL);
	glCompileShader(vert_shader);
	glShaderSource(frag_shader, 1, &fragment_shader, NULL);
	glCompileShader(frag_shader);
	shader_programme = glCreateProgram();
	glAttachShader(shader_programme, frag_shader);
	glAttachShader(shader_programme, vert_shader);
	glBindAttribLocation(shader_programme, 0, "vertex_position");
	glBindAttribLocation(shader_programme, 1, "vertex_colour");
	glLinkProgram(shader_programme);
	/* this loop clears the drawing surface, then draws the geometry described
	   by the VAO onto the drawing surface. we 'poll events' to see if the window
	   was closed, etc. finally, we 'swap the buffers' which displays our drawing
	   surface onto the view area. we use a double-buffering system which means
	   that we have a 'currently displayed' surface, and 'currently being drawn'
	   surface. hence the 'swap' idea. in a single-buffering system we would see
	   stuff being drawn one-after-the-other */
	printfmat(mat4_mult(projection, mat4_mult(view, model)));
	double lasttime = glfwGetTime();
	modelLocation = glGetUniformLocation(shader_programme, "model");
	viewLocation = glGetUniformLocation(shader_programme, "view");
	projectionLocation = glGetUniformLocation(shader_programme, "projection");
	flat = glGetUniformLocation(shader_programme, "flatmode");
	textLocation = glGetUniformLocation(shader_programme, "texture");

	while (!glfwWindowShouldClose(window ))
	{
		glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
		/* wipe the drawing surface clear */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_programme);
		view = key_callback(window, view);
		/*	printfmat(view);
			printf("\n");*/

		if (g_e == 1)
		{
			model = mat4_rot_axis(model, AXIS_X, 0.5);
			//model = mat4_rot_axis(model, AXIS_Z, 0.25);
			model = mat4_rot_axis(model, AXIS_Y, 1);
		}


		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, model.m);
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, view.m);
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, projection.m);
		glUniform1i(flat, g_flat);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(vao);
		/* draw points 0-3 from the currently bound VAO with current in-use shader */
		glDrawElements(GL_TRIANGLES, idlen, GL_UNSIGNED_INT, 0);
		/* update other events like input handling */
		glfwPollEvents();
		/* put the stuff we've been drawing onto the display */
		glfwSwapBuffers(window);

		while (glfwGetTime() < lasttime + 1.0 / FPS)
			;
		lasttime += 1.0 / FPS;
	}
	/* close GL context and any other GLFW resources */
	glfwTerminate();
	return 0;
}
