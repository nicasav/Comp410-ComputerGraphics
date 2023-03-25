// Two-Dimensional Sierpinski Gasket
// Generated using randomly selected vertices and bisection

#include "Angel.h"

const int NumPoints = 50000;

//----------------------------------------------------------------------------

void
init( void )
{
    vec2 points[NumPoints];

    // Specifiy the vertices for a triangle
    vec2 vertices[3] = {
        vec2( -1.0, -1.0 ), vec2( 0.0, 1.0 ), vec2( 1.0, -1.0 )
    };

    // Select an arbitrary initial point inside of the triangle
    points[0] = vec2( 0.25, 0.50 );

    // compute and store N-1 new points
    for ( int i = 1; i < NumPoints; ++i ) {
        int j = rand() % 3;   // pick a vertex at random

        // Compute the point halfway between the selected vertex
        //   and the previous point
        points[i] = ( points[i - 1] + vertices[j] ) / 2.0;
    }

    // Create a vertex array object
    GLuint vao[1];
    glGenVertexArrays( 1, vao );
    glBindVertexArray( vao[0] );
    

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );
    glUseProgram( program );

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );

    glClearColor( 1.0, 1.0, 1.0, 1.0 ); // white background
}

//----------------------------------------------------------------------------

void
display( void )
{
    glClear( GL_COLOR_BUFFER_BIT );     // clear the buffer
    glDrawArrays( GL_POINTS, 0, NumPoints );    // draw the points
    glFlush();
}

//----------------------------------------------------------------------------
// exit when escape key pressed
void
key_callback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
    switch ( key ) {
    case GLFW_KEY_ESCAPE:
        exit( EXIT_SUCCESS );
        break;
    }
}

//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{
    if (!glfwInit())
            exit(EXIT_FAILURE);
     
     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
     glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

     GLFWwindow* window = glfwCreateWindow(500, 500, "Sierpinski", NULL, NULL);
     glfwMakeContextCurrent(window);

    //comment out the following two lines for windows and linux (don't need glew in macos)
    glewExperimental = GL_TRUE;
    glewInit();

    if (!window)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
    
    glfwSetKeyCallback(window, key_callback);

    init();

    while (!glfwWindowShouldClose(window))
    {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents(); // glfwWaitEvents
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

