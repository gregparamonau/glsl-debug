#version 330 core

in vec2 TexCoords;
out vec4 FragColor;
uniform sampler2D texture1;

void main() {
    vec4 texColor = texture(texture1, TexCoords);
    if(texColor.a < 0.1) discard;
    //fat fuck /**/
    FragColor = texColor;
}

/*#version 330 core

// GLSL 330 requires you to explicitly define the output color variable
out vec4 FragColor;

void main() {
    // Outputs solid red: (Red, Green, Blue, Alpha)
    FragColor = vec4(1.0, 0.0, 0.0, 1.0);
}*/

