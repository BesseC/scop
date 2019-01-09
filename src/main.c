#include <GL/glew.h>	/* include GLEW and new version of GL on Windows */
#include <GLFW/glfw3.h> /* GLFW helper library */
#include <stdio.h>
#include "libft.h"
#include "libmat.h"

#define WIDHT 1024
#define HEIGHT 800

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

int main() {
	GLFWwindow *window = NULL;
	const GLubyte *renderer;
	const GLubyte *version;
	GLuint vao;
	t_mat4 view;
	t_mat4 model;
	t_mat4 projection;
	GLint transformLocation;
	GLint modelLocation;
	GLint viewLocation;
	GLint projectionLocation;
	mat4_id(&view);
	mat4_id(&model);
	set_projection(&projection, 90);
  view.m[14] = -5;
	//mat4_id(&projection);
	GLuint ebo;
	GLfloat points[] = {
				0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f, // Top Right
				-0.5f, 0.5f, 0.5f,   0.0f, 1.0f, 0.0f, // Bottom Right
				0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f, // Bottom Left
				-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 0.0f, //  Top Left
				0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f, // Top Right
				-0.5f, 0.5f, -0.5f,   0.0f, 1.0f, 0.0f, // Bottom Right
				0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f, // Bottom Left
				-0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f //  Top Left
		};
	GLuint indices[] = {
		0,1,2,
		1,2,3,
		0,4,6,
		0,2,6,
		0,4,1,
		4,1,5,
		4,6,7,
		4,5,7,
		1,5,7,
		1,3,7,
		2,6,3,
		3,7,6
	};
	/* these are the strings of code for the shaders
	the vertex shader positions each vertex point */
	const char *vertex_shader = "#version 410\n"
					"layout(location = 0) in vec3 vertex_position;"
					"layout(location = 1) in vec3 vertex_colour;"
															"out vec3 colour;"
															"uniform mat4 model;"
															"uniform mat4 view;"
															"uniform mat4 projection;"
															"void main () {"
															"colour = vertex_colour;"
															"gl_Position = projection * view * model * vec4(vertex_position, 1.0);"
															"}";
	/* the fragment shader colours each fragment (pixel-sized area of the
	triangle) */
	const char *fragment_shader = "#version 410\n"
																"in vec3 colour;"
																"out vec4 frag_colour;"
																"void main () {"
																"  frag_colour = vec4(colour, 1.0);"
																"}";
	/* GL shader objects for vertex and fragment shader [components] */
	GLuint vert_shader, frag_shader;
	/* GL shader programme object [combined, to link] */
	GLuint shader_programme;

	/* start GL context and O/S window using the GLFW helper library */
	if ( !glfwInit() ) {
		fprintf( stderr, "ERROR: could not start GLFW3\n" );
		return 1;
	}
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );
	glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

	window = glfwCreateWindow( WIDHT, HEIGHT, "Hello Triangle", NULL, NULL );
	if ( !window ) {
		fprintf( stderr, "ERROR: could not open window with GLFW3\n" );
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent( window );
	/* start GLEW extension handler */
	glewExperimental = GL_TRUE;
	glewInit();
	/* get version info */
	renderer = glGetString( GL_RENDERER ); /* get renderer string */
	version = glGetString( GL_VERSION );	 /* version as a string */
	printf( "Renderer: %s\n", renderer );
	printf( "OpenGL version supported %s\n", version );
	/* tell GL to only draw onto a pixel if the shape is closer to the viewer
	than anything already drawn at that pixel */
	glEnable( GL_DEPTH_TEST ); /* enable depth-testing */
	/* with LESS depth-testing interprets a smaller depth value as meaning "closer" */
	glDepthFunc( GL_LESS );
	/* a vertex buffer object (VBO) is created here. this stores an array of
	data on the graphics adapter's memory. in our case - the vertex points */
	GLuint vbo = 0;
	glGenVertexArrays( 1, &vao );
	glGenBuffers( 1, &vbo );
	glGenBuffers(1, &ebo);
	glBindVertexArray( vao );
	glBindBuffer( GL_ARRAY_BUFFER, vbo );
	glBufferData( GL_ARRAY_BUFFER, sizeof( points ), points, GL_STATIC_DRAW );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo );
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );

	/* the vertex array object (VAO) is a little descriptor that defines which
	data from vertex buffer objects should be used as input variables to vertex
	shaders. in our case - use our only VBO, and say 'every three floats is a
	variable' **/
	/* "attribute #0 should be enabled when this vao is bound" */
	/* this VBO is already bound, but it's a good habit to explicitly specify which
	VBO's data the following vertex attribute pointer refers to */
	/* "attribute #0 is created from every 3 variables in the above buffer, of type
	float (i.e. make me vec3s)" */
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL );
	glEnableVertexAttribArray(0);
	glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)) );
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	/* here we copy the shader strings into GL shaders, and compile them. we
	then create an executable shader 'program' and attach both of the compiled
			shaders. we link this, which matches the outputs of the vertex shader to
	the inputs of the fragment shader, etc. and it is then ready to use */
	vert_shader = glCreateShader( GL_VERTEX_SHADER );
	frag_shader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( vert_shader, 1, &vertex_shader, NULL );
	glCompileShader( vert_shader );
	glShaderSource( frag_shader, 1, &fragment_shader, NULL );
	glCompileShader( frag_shader );
	shader_programme = glCreateProgram();
	glAttachShader( shader_programme, frag_shader );
	glAttachShader( shader_programme, vert_shader );
	glBindAttribLocation(shader_programme, 0, "vertex_position");
	glBindAttribLocation(shader_programme, 1, "vertex_colour");
	glLinkProgram( shader_programme );
	/* this loop clears the drawing surface, then draws the geometry described
			by the VAO onto the drawing surface. we 'poll events' to see if the window
	was closed, etc. finally, we 'swap the buffers' which displays our drawing
			surface onto the view area. we use a double-buffering system which means
			that we have a 'currently displayed' surface, and 'currently being drawn'
			surface. hence the 'swap' idea. in a single-buffering system we would see
			stuff being drawn one-after-the-other */

	printfmat(mat4_mult(projection, mat4_mult(view, model)));


	while ( !glfwWindowShouldClose( window ) ) {
		 glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
		/* wipe the drawing surface clear */
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glUseProgram( shader_programme );

		model = mat4_rot_axis(model, AXIS_X, 0.5);
		model = mat4_rot_axis(model, AXIS_Y, 1);
		modelLocation = glGetUniformLocation(shader_programme, "model");
		viewLocation = glGetUniformLocation(shader_programme, "view");
		projectionLocation = glGetUniformLocation(shader_programme, "projection");

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, model.m );
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, view.m );
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, projection.m );
		glBindVertexArray( vao );
		/* draw points 0-3 from the currently bound VAO with current in-use shader */
   	glDrawElements( GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0 );
		/* update other events like input handling */
		glfwPollEvents();
		/* put the stuff we've been drawing onto the display */
		glfwSwapBuffers( window );
	}
	/* close GL context and any other GLFW resources */
	glfwTerminate();
	return 0;
}
