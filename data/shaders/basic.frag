// All preprocessor code is in separate string
struct Material {
  float reflectance;
  float specularity;
  float shinyness;
  int texture_type;
};

struct LightSource {
  float intensity;
  vec3 color;
  vec4 position;
  float constant_attenuation, linear_attenuation, quadratic_attenuation;
  float spot_cutoff, spot_exponent;
  vec3 spot_direction;
};

// Internal data
LightSource lights[N_LIGHTS];

// Input data
in vec3 position_worldspace;
in vec3 position_modelspace;
in vec3 position_viewspace;
//in vec3 normal_viewspace;
in vec3 normal_worldspace;

//in vec3 view_direction_to_fragment_viewspace;
in vec3 view_direction_to_fragment_worldspace;
//in vec3 light_position_viewspace;
in vec2 uv;

// Uniforms
uniform float far_clipping;
uniform LightSource light;
uniform sampler2D texture_sampler2D;
uniform Material material;

uniform float light_data[16 * N_LIGHTS]; // 16 floats for each light

// Ouput data
out vec3 color;

vec3 diffuseCheckerboard(float x, float y, float z) {
  int ix = int((x < 0) ? -x+1 : x);
  int iy = int((y < 0) ? -y+1 : y);
  int iz = int((z < 0) ? -z+1 : z);
  float val = (ix%2 + iy%2 + iz%2)%2;
  return vec3(val, val, val);
}

vec3 diffuseCircles(float x, float y, float z, float scale) {
  x *= 1/scale;
  y *= 1/scale;
  z *= 1/scale;

  x = (x < 0) ? -x+1 : x;
  y = (y < 0) ? -y+1 : y;
  z = (z < 0) ? -z+1 : z;

  x = abs(((x - int(x)) - 0.5) * 2) - 1;
  y = abs(((y - int(y)) - 0.5) * 2) - 1;
  z = abs(((z - int(z)) - 0.5) * 2) - 1;
  float val = clamp(round(length(vec3(x,y,z))),0,1);
  return vec3(val, val, val);
}

void main()
{

  float ambient_brightness = 0.4;
  vec3 ambient_color = vec3(1,1,1);
  
  // Diffuse color
  vec3 material_diffuse_color;
  switch(material.texture_type) {
    case 0: // Texture from file
      material_diffuse_color = texture(texture_sampler2D, uv ).rgb;
      break;
    case 1: // Checkerboard
      material_diffuse_color =
            diffuseCheckerboard(
                  position_modelspace.x + 0.001, // Ugly solution
                  position_modelspace.y + 0.001,
                  position_modelspace.z + 0.001);
      break;
    case 2: // Checkerboard
      vec3 circles = diffuseCircles(
                  position_modelspace.x,
                  position_modelspace.y,
                  position_modelspace.z,
                  0.7);
      material_diffuse_color = (vec3(1,1,1) - circles) * vec3(1,0,0) + circles;
      break;
    default: // Checkerboard
      material_diffuse_color =
        diffuseCheckerboard(
              position_modelspace.x,
              position_modelspace.y,
              position_modelspace.z);
  }

  // Convert light data to LightSource struct
  // (readability is better with structs but it can be changed for efficiency)
  for (int i = 0; i < N_LIGHTS; ++i){
    lights[i] = LightSource(
      light_data[i*16 + 0],
      vec3(light_data[i*16 + 1], light_data[i*16 + 2], light_data[i*16 + 3]),
      vec4(light_data[i*16 + 4],light_data[i*16 + 5],light_data[i*16 + 6],light_data[i*16 + 7]),
      light_data[i*16 + 8], light_data[i*16 + 9], light_data[i*16 + 10],
      light_data[i*16 + 11], light_data[i*16 + 12],
      vec3(light_data[i*16 + 13], light_data[i*16 + 14], light_data[i*16 + 15])
      );
  }  

  // Directional vectors
  vec3 n = normalize(normal_worldspace);
  vec3 v = normalize(view_direction_to_fragment_worldspace);
  vec3 l; // Light direction to fragment
  float attenuation;

  // ----- Ambient light -----
  vec3 ambient = ambient_color * material_diffuse_color * ambient_brightness;
  // initialize total lighting with ambient lighting
  vec3 total_lighting = ambient;

  for (int i = 0; i < N_LIGHTS; ++i){ // For all light sources
    if (lights[i].position.w == 0.0){
      attenuation = 1.0; // No attenuation
      l = normalize(vec3(lights[i].position));
    }
    else { // Point light or spot light
      vec3 position_to_lightsource = vec3(vec3(lights[i].position) - position_worldspace);
      float distance_to_light = length(position_to_lightsource);
      l = normalize(position_to_lightsource);
      attenuation = 1.0 /
            (lights[i].constant_attenuation
           + lights[i].linear_attenuation * distance_to_light
           + lights[i].quadratic_attenuation * distance_to_light * distance_to_light);
      if (lights[i].spot_cutoff <= 90.0) { // Spotlight, else it is a point light
        float clamped_cosine = max(0.0, dot(-l, normalize(lights[i].spot_direction)));
        if (clamped_cosine < cos(radians(lights[i].spot_cutoff))) {// outside of spotlight cone?
          attenuation = 0.0;
        }
        else {
          attenuation = attenuation * pow(clamped_cosine, lights[i].spot_exponent);
        }
      }
    }
    // ----- Diffuse light -----
    vec3 diffuse = attenuation * lights[i].color * material_diffuse_color *
            max(0.0, dot(n,l));

    // ----- Specular light -----
    vec3 specular;
    if (dot(n,l) < 0.0) // Light source on wrong side
      specular = vec3(0.0, 0.0, 0.0);
    else {// Light source on right side
    vec3 r = reflect(l,n);
    float cos_alpha = clamp( dot( v,-r ), 0,1 );
    specular =
            lights[i].color *
            clamp(pow(cos_alpha, material.shinyness),0,1) *
            attenuation *
            material.specularity;
    }
    total_lighting = total_lighting + lights[i].intensity * (diffuse + specular);
  }
  // Fog
  float thickness = 0.02; // 0 < thickness < 1
  float fog_border = 10.0;
  float visibility = (-position_viewspace.z < fog_border) ? 1.0 :
          pow(1 - thickness, -position_viewspace.z - fog_border);
  vec3 fog_color = vec3(0.8, 0.8, 1.0);
  vec3 fog = fog_color * (1-visibility);

  // Total light
  color = material.reflectance * total_lighting * visibility +fog;
}
