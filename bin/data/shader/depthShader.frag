#version 150

uniform float low1;
uniform float high1;
uniform float low2;
uniform float high2;
uniform sampler2DRect tex0;

in vec2 varyingTexCoord;

out vec4 outputColor;

void main() {
    vec3 color = vec3(0.0, 0.0, 0.0);

    float value = texture(tex0, varyingTexCoord).r;
    float d = clamp(low2 + (value - low1) * (high2 - low2) / (high1 - low1), 0.0, 1.0);

    (d == 1.0 || d == 0.0) ? color = vec3(1.0) : color = vec3(0.0);
    // (d == 1.0 || d == 0.0) ? color.r = 1.0 : color.b = d;
    outputColor = vec4(color, 1.0);
}