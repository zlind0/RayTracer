#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 reflect(const vec3 &v, const vec3 &normal) {
    return -2 * dot(v, normal) * normal + v;
}

inline vec3 color_mix(const vec3 &c1, const vec3 &c2) {
    return vec3(c1.x[0] * c2.x[0], c1.x[1] * c2.x[1], c1.x[2] * c2.x[2]);
}

inline double double_max(double a, double b) {
    if (a > b)return a;
    else return b;
}

inline void trim_color(vec3 &color) {
    if (color.x[0] > 1)
        color.x[0] = 1;
    if (color.x[1] > 1) color.x[1] = 1;
    if (color.x[2] > 1) color.x[2] = 1;
}

vec3 Phong_Shader::
Shade_Surface(const Ray &ray, const vec3 &intersection_point,
              const vec3 &same_side_normal, int recursion_depth) const {
    vec3 color(0, 0, 0);
    // TODO: determine the color
    vec3 reflected_ray = reflect(ray.direction, same_side_normal);

    vec3 l;
    vec3 n = same_side_normal.normalized();
    vec3 e = ray.direction;
    vec3 h;

    double cr = 0.10;

    for (auto &einLight: world.lights) {
        vec3 neue_color;
        l = (einLight->position - intersection_point).normalized();
        h = (e + l).normalized();
        double cos_diff = fabs(dot(l, reflected_ray));
        vec3 emitted_light = einLight->Emitted_Light(ray);

        double dis_light_to_hitpoint_2 = (einLight->position - intersection_point).magnitude_squared();


        neue_color += color_mix(emitted_light, color_diffuse) * double_max(0, dot(n, l));
        neue_color += color_mix(emitted_light, color_specular) * pow(dot(h, n), specular_power * 4.0);
        neue_color += color_mix(emitted_light, color_ambient) * 0.0;
        neue_color *= 1 / dis_light_to_hitpoint_2;
        //printf("%f--%f\n",dot(h,n),pow(dot(h,n),specular_power));
        color += neue_color;


    }

    return color;
}