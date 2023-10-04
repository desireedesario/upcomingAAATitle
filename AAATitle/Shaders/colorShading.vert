#version 130
// the vertex shader operates on each vertex

// input data from the VBO. Each vertex is 2 floats
in vec2 vertexPosition;
in vec4 vertexColor;

// the mouse coords now do not change within the vertex when using uniform 
// the uniform specificer is for values that are constant across the entire thing being shaded.
uniform vec2 mouseCoordinates;

// output color
out vec2 fragmentPosition;
out vec4 fragmentColor;

void main(){
	// set the x,y position on the screen
	gl_Position.xy = vertexPosition + mouseCoordinates;
	
	// the z position is zero since we are in 2D
	gl_Position.z = 0.0;
	
	// indicate that the coordinates are normalized / not really sure what this means
	gl_Position.w = 1.0;

	fragmentPosition = vertexPosition;

	fragmentColor = vertexColor;
}