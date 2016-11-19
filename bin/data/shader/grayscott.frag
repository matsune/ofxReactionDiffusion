#version 150

float kernel[9];
vec2 offset[9];

uniform float passes;
uniform float feed;
uniform float kill;
uniform float Du;
uniform float Dv;
uniform sampler2DRect tex0;

in vec2 varyingTexCoord;

out vec4 outputColor;

void main(){
	offset[0] = vec2( 0.0, -1.0);
	offset[1] = vec2(-1.0,  0.0);
	offset[2] = vec2( 0.0,  0.0);
	offset[3] = vec2( 1.0,  0.0);
	offset[4] = vec2( 0.0,  1.0);

	offset[5] = vec2(-1.0, -1.0);
	offset[6] = vec2( 1.0, -1.0);
	offset[7] = vec2(-1.0,  1.0);
	offset[8] = vec2( 1.0,  1.0);

	kernel[0] = 1.0;
	kernel[1] = 1.0;
	kernel[2] = -6.82842712;
	kernel[3] = 1.0;
	kernel[4] = 1.0;

	kernel[5] = 0.707106781;
	kernel[6] = 0.707106781;
	kernel[7] = 0.707106781;
	kernel[8] = 0.707106781;

	vec2 lap = vec2(0.0, 0.0);
	for(int i=0; i<9; i++){
		vec2 tmp = texture(tex0, varyingTexCoord + offset[i]).rb;
		lap += tmp * kernel[i];
	}

	float u = texture(tex0, varyingTexCoord).r;
	float v = texture(tex0, varyingTexCoord).b;
	float uvv = u*v*v;
	float du = Du * lap.x - uvv + feed * (1.0 - u);
	float dv = Dv * lap.y + uvv - (feed + kill)*v;
	u += du * passes;
	v += dv * passes;
	outputColor = vec4(clamp(u, 0.0, 1.0), 0, clamp(v, 0.0, 1.0), 1.0);
	// outputColor = vec4(clamp(u, 0.0, 1.0), clamp(1.0-(u/v), 0.0, 1.0), clamp(v, 0.0, 1.0), 1.0);
}