void main(void) {
    vec4 a = gl_Vertex;
    a.x = a.x * .5;
    a.y = a.y * .5;
    gl_Position = gl_ModelViewProjectionMatrix * a;
}
