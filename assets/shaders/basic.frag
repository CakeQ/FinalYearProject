#version 400

in vec2 v2_TexCoords;

out vec4 v4_color;

uniform sampler2D s2d_texture_diffuse;

void main( )
{
   v4_color = vec4( texture( s2d_texture_diffuse, v2_TexCoords ));
}