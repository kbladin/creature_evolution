#version 330 core

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

// Ouput data
out vec3 color;

void main()
{ 
  float ambient_brightness = 0.1;
  vec3 ambient_color = vec3(1,1,1);

  // Material
  float reflectance = 0.5;
  float specularity = 0.5;
  float shinyness = 32;

  vec3 material_diffuse_color = vec3(uv.x, uv.y, 0.5);

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
          clamp(pow(cos_alpha, shinyness),0,1) *
          inv_distance_square *
          light_intensity *
          specularity;

  // Fog
  float thickness = 1/far_clipping;
  float invisibility = clamp(-position_viewspace.z * thickness, 0, 1);
  vec3 fog_color = vec3(0.8, 0.8, 1.0);
  vec3 fog = fog_color * invisibility;

  // Total light
  color = (reflectance * (ambient + diffuse + specular)) * (1-invisibility) + 
          fog;
}
