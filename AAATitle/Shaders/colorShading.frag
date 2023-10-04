#version 130
// The fragment shader operates on each pixel in a given polygon

in vec2 fragmentPosition;
in vec4 fragmentColor;


// This is the float vector that gets output to the screen for each pixel.
out vec4 color;

//creating a uniform var for each time - this is why the colors are changing over time
uniform float time;

void main(){
	// transferring from input color vec4 to output color vec4
	color = vec4(fragmentColor.r * (cos(fragmentPosition.x + time) +1.0) * 0.5,
			     fragmentColor.g * (cos(fragmentPosition.y + time) +1.0) * 0.5,
			     fragmentColor.b * (cos(fragmentPosition.x*0.5 + time) +1.0) * 0.5, fragmentColor.a);
}