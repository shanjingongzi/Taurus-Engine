#version 460 core
in vec2 textureCoord;
uniform  sampler2D image;
out vec4 fragColor;
void main()
{
   fragColor=texture(image,textureCoord);
    //fragColor=vec4(1.0,0.0,0.0,1.0);
}