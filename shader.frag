#version 150

const int number_of_targets = 200;

out vec4 outputColor;
uniform float time;
uniform vec2 resolution;
uniform vec2 targets[number_of_targets];
uniform sampler2DRect fbo;

void main() {

  vec2 p = (gl_FragCoord.xy * 2.0 - resolution) / min(resolution.x, resolution.y);
  vec3 color = vec3(0.0);

  for(int i = 0; i < number_of_targets; i++){

    vec2 t = vec2(targets[i].x, -targets[i].y) / min(resolution.x, resolution.y) * 2.0;
    t.xy += vec2(-resolution.x, resolution.y) / min(resolution.x, resolution.y);

    float r = 0.01 / length(p - t) * 0.2;
    float g = 0.01 / length(p - t) * 0.2;
    float b = 0.01 / length(p - t) * 0.5;
    vec3 c = vec3(smoothstep(0.2, 1.0, r), smoothstep(0.2, 1.0, g), smoothstep(0.2, 1.0, b));
    color += c;
  }

  vec4 fbo_value = texture(fbo, vec2(gl_FragCoord.x, gl_FragCoord.y));
  outputColor = vec4(color, 1.0) + fbo_value * 0.9;
}
