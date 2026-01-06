/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 18:28:33 by mansargs          #+#    #+#             */
/*   Updated: 2026/01/05 19:54:09 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minirt.h"
#include "vector.h"

// Forward declaration
void print_material(t_material *mat)
{
    if (!mat)
    {
        printf("      Material: NULL\n");
        return;
    }
    printf("      Material:\n");
    if (mat->has_specular)
        printf("        Specular: k_s=%.2f, n_s=%d\n", mat->spec.k_s, mat->spec.n_s);
    if (mat->texture_path)
        printf("        Texture: %s\n", mat->texture_path);
    if (mat->bump_map_path)
        printf("        Bump map: %s\n", mat->bump_map_path);
}

void print_scene(t_scene *scene)
{
    if (!scene)
    {
        printf("Scene: NULL\n");
        return;
    }

    printf("Scene:\n");

    // Ambient
    printf("  Ambient: ");
    if (scene->ambient.is_set)
        printf("lighting_ratio=%.2f, color=(%d,%d,%d)\n",
            scene->ambient.lighting_ratio,
            scene->ambient.color.r,
            scene->ambient.color.g,
            scene->ambient.color.b);
    else
        printf("NULL\n");

    // Camera
    printf("  Camera: ");
    if (scene->camera.is_set)
        printf("pos=(%.2f,%.2f,%.2f), dir=(%.2f,%.2f,%.2f), fov=%.2f\n",
            scene->camera.position.x,
            scene->camera.position.y,
            scene->camera.position.z,
            scene->camera.orientation.x,
            scene->camera.orientation.y,
            scene->camera.orientation.z,
            scene->camera.fov);
    else
        printf("NULL\n");

    // Helper macro for printing vectors
    #define PRINT_VECTOR(vec, type, print_body) \
        printf("  %s: ", #vec); \
        if ((vec).size == 0) \
            printf("is not\n"); \
        else \
        { \
            printf("%zu element(s)\n", (vec).size); \
            for (size_t i = 0; i < (vec).size; ++i) \
            { \
                type *obj = (type *)vector_get(&(vec), i); \
                print_body; \
            } \
        }

    // Lights
    PRINT_VECTOR(scene->lights, t_light,
        printf("    Light %zu: pos=(%.2f,%.2f,%.2f), brightness=%.2f, color=(%d,%d,%d)\n",
            i, obj->position.x, obj->position.y, obj->position.z,
            obj->brightness, obj->color.r, obj->color.g, obj->color.b));

    // Spheres
    PRINT_VECTOR(scene->spheres, t_sphere,
        printf("    Sphere %zu: center=(%.2f,%.2f,%.2f), radius=%.2f, color=(%d,%d,%d), checker=%d\n",
            i, obj->center.x, obj->center.y, obj->center.z,
            obj->radius, obj->color.r, obj->color.g, obj->color.b,
            obj->checkerboard_enabled);
        print_material(&obj->mat));

    // Planes
    PRINT_VECTOR(scene->planes, t_plane,
        printf("    Plane %zu: pos=(%.2f,%.2f,%.2f), orientation=(%.2f,%.2f,%.2f), color=(%d,%d,%d), checker=%d\n",
            i, obj->position.x, obj->position.y, obj->position.z,
            obj->orientation.x, obj->orientation.y, obj->orientation.z,
            obj->color.r, obj->color.g, obj->color.b,
            obj->checkerboard_enabled);
        print_material(&obj->mat));

    // Cylinders
    PRINT_VECTOR(scene->cylinders, t_cylinder,
        printf("    Cylinder %zu: center=(%.2f,%.2f,%.2f), orientation=(%.2f,%.2f,%.2f), radius=%.2f, height=%.2f, color=(%d,%d,%d), checker=%d\n",
            i, obj->center.x, obj->center.y, obj->center.z,
            obj->orientation.x, obj->orientation.y, obj->orientation.z,
            obj->radius, obj->height,
            obj->color.r, obj->color.g, obj->color.b,
            obj->checkerboard_enabled);
        print_material(&obj->mat));

    // Cones
    PRINT_VECTOR(scene->cones, t_cone,
        printf("    Cone %zu: center=(%.2f,%.2f,%.2f), orientation=(%.2f,%.2f,%.2f), height=%.2f, angle=%.2f, color=(%d,%d,%d), checker=%d\n",
            i, obj->center.x, obj->center.y, obj->center.z,
            obj->orientation.x, obj->orientation.y, obj->orientation.z,
            obj->height, obj->angle,
            obj->color.r, obj->color.g, obj->color.b,
            obj->checkerboard_enabled);
        print_material(&obj->mat));

    #undef PRINT_VECTOR
}
