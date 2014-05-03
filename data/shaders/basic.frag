#version 330 core

struct Material {
  float reflectance;
  float specularity;
  float shinyness;
  int texture_type;
};

// Input data
in vec3 position_worldspace;
in vec3 position_modelspace;
in vec3 position_viewspace;
in vec3 normal_viewspace;

in vec3 view_direction_to_fragment_viewspace;
in vec3 light_direction_to_fragment_viewspace;

in vec2 uv;

// Uniforms
uniform float far_clipping;

uniform float light_intensity;
uniform vec3 light_color;
uniform vec3 light_position_worldspace;
uniform sampler2D texture_sampler2D;

uniform Material material;

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
  float ambient_brightness = 0.1;
  vec3 ambient_color = vec3(1,1,1);
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

  // Vectors
  vec3 n = normalize(normal_viewspace);
  // Eye vector (away from the camera)
  vec3 e = normalize(view_direction_to_fragment_viewspace);
  vec3 l = normalize(light_direction_to_fragment_viewspace);
  vec3 r = reflect(l,n);

  float distance_to_light =
          length(light_position_worldspace - position_worldspace);
  float distance_square = pow(distance_to_light,2);
  float inv_distance_square =  1.0f/(distance_square);

  // Ambient light
  vec3 ambient = ambient_color * material_diffuse_color * ambient_brightness;
  
  // Diffuse light 
  float cos_theta = clamp(dot(-n, l), 0, 1);
  vec3 diffuse =
          material_diffuse_color *
          light_color *
          cos_theta *
          inv_distance_square *
          light_intensity;

  // Specular light
  float cos_alpha = clamp( dot( e,-r ), 0,1 );
  vec3 specular =
          light_color *
          clamp(pow(cos_alpha, material.shinyness),0,1) *
          inv_distance_square *
          light_intensity *
          material.specularity;

  // Fog
  float thickness = 1/far_clipping;
  float invisibility = clamp(-position_viewspace.z * thickness, 0, 1);
  vec3 fog_color = vec3(0.8, 0.8, 1.0);
  vec3 fog = fog_color * invisibility;

  // Total light
  color = (material.reflectance * (ambient + diffuse + specular)) * (1-invisibility) + 
          fog;
}
