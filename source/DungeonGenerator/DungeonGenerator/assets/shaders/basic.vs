#version 400
layout ( location = 0 ) in vec3 v3_position;
layout ( location = 1 ) in vec3 v3_normal;
layout ( location = 2 ) in vec2 v2_texCoords;

out vec2 v2_TexCoords;

uniform mat4 m4_model;
uniform mat4 m4_view;
uniform mat4 m4_projection;

void main( )
{
    gl_Position = m4_projection * m4_view * m4_model * vec4( v3_position, 1.0f );
    v2_TexCoords = v2_texCoords;
}