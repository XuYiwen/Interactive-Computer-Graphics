// texture index from main program
uniform sampler2D texture;
uniform sampler2D envmap;

// vertex position and normal for light model
varying vec3 v;
varying vec3 N;

void main() {
		// Compute lighting helper vertex
		vec3 L = normalize(gl_LightSource[0].position.xyz - v);
    vec3 E = normalize(-v);
    vec3 R = normalize(-reflect(L,N));

		// Using texture as diffuse color and add environment lighting as part of specular lights
		vec4 tex = texture2D(texture, gl_TexCoord[0].st);
		vec4 env = texture2D(envmap, gl_TexCoord[1].st);

		// Compute lighting compounents
		vec4 Iamb = gl_FrontLightProduct[0].ambient;
		vec4 Idiff = tex* max(dot(N,L), 0.0);
				 Idiff = clamp(Idiff, 0.0, 1.0);
		vec4 Ispec = gl_FrontLightProduct[0].specular * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess);
    		 Ispec = clamp(Ispec, 0.0, 1.0);

		// Get final color
    gl_FragColor = Iamb + Idiff + Ispec * 0.7 + env * 0.3;
    gl_FragColor.a = tex.a;
}
