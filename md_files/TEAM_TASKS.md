# MiniRT Team Task Assignments - Quick Reference

## DEVELOPER 1: Ray Tracing Engine
**Responsibility**: Core rendering pipeline (rays, intersections, lighting)  
**Start Date**: Immediately  
**Duration**: 2-3 weeks

### TASKS IN ORDER (Do NOT skip steps):

```
┌─────────────────────────────────────────────────────────────┐
│ WEEK 1                                                      │
└─────────────────────────────────────────────────────────────┘

□ TASK 1.1: Ray Data Structure & Camera Ray Generation [3-4h]
  └─ Create: hdrs/ray.h, srcs/ray_tracing/ray.c
  └─ Functions:
     • t_ray create_ray(t_vec3 origin, t_vec3 direction)
     • t_ray camera_ray(t_camera *cam, double x, double y, int width, int height)
     • t_vec3 ray_at(t_ray *ray, double t)
  └─ Deliverable: Unit tests passing
  └─ Test: Generate 100 rays from camera, verify directions

□ TASK 1.2: Sphere Ray Intersection [2-3h]
  └─ Create: srcs/ray_tracing/intersection_sphere.c
  └─ Function:
     • bool ray_intersects_sphere(t_ray *ray, t_sphere *sphere, t_hit_info *hit)
  └─ Must detect:
     • Entry/exit points
     • Normal at intersection
     • Distance along ray
  └─ Test: Sphere at origin, rays from various angles

□ TASK 1.3: Plane Ray Intersection [1.5-2h]
  └─ Create: srcs/ray_tracing/intersection_plane.c
  └─ Function:
     • bool ray_intersects_plane(t_ray *ray, t_plane *plane, t_hit_info *hit)
  └─ Edge cases:
     • Ray parallel to plane
     • Ray behind plane
     • Normal calculation
  └─ Test: Plane at origin with different normals

┌─────────────────────────────────────────────────────────────┐
│ WEEK 2                                                      │
└─────────────────────────────────────────────────────────────┘

□ TASK 1.4: Cylinder Ray Intersection [4-5h]
  └─ Create: srcs/ray_tracing/intersection_cylinder.c
  └─ Handle:
     • Body intersection (quadratic equation)
     • Cap intersections (plane intersection)
     • Correct normal for each part
     • Height bounds check
  └─ Test: Cylinder at origin, axis-aligned first

□ TASK 1.5: Cone Ray Intersection [4-5h]
  └─ Create: srcs/ray_tracing/intersection_cone.c
  └─ Handle:
     • Surface intersection
     • Cap intersection
     • Cone angle calculation
     • Normal at different points
  └─ Test: Similar to cylinder tests

□ TASK 1.6: Scene Intersection System [2-3h]
  └─ Create: hdrs/hit.h, srcs/ray_tracing/scene_intersection.c
  └─ Define t_hit_info structure
  └─ Function:
     • bool trace_ray(t_scene *scene, t_ray *ray, t_hit_info *hit)
  └─ Must:
     • Loop through ALL objects in scene
     • Find closest intersection
     • Return only closest hit
  └─ Test: Scene with mixed objects, verify closest selection

□ TASK 2.1: Diffuse Lighting [2-3h]
  └─ Create: srcs/rendering/lighting.c
  └─ Functions:
     • t_rgb calculate_color(t_scene *scene, t_hit_info *hit, t_ray *ray)
     • double shadow_factor(t_scene *scene, t_hit_info *hit, t_light *light)
  └─ Implement:
     • Ambient + diffuse calculation
     • Shadow rays (check visibility)
     • Clamp RGB values
  └─ Test: Lit sphere, verify shading direction

□ TASK 2.2: Specular Highlights [2h]
  └─ Extend: srcs/rendering/lighting.c
  └─ Add:
     • Check material.has_specular
     • Phong specular term
     • n_s shininess factor
  └─ Test: Shiny object, verify highlights

┌─────────────────────────────────────────────────────────────┐
│ DELIVERABLE BY END OF WEEK 2:                               │
├─────────────────────────────────────────────────────────────┤
│ ✓ ray.c      - Ray generation from camera                   │
│ ✓ intersection_sphere.c   - Sphere collision                │
│ ✓ intersection_plane.c    - Plane collision                 │
│ ✓ intersection_cylinder.c - Cylinder collision              │
│ ✓ intersection_cone.c     - Cone collision                  │
│ ✓ scene_intersection.c    - Find closest hit                │
│ ✓ lighting.c     - Diffuse + Specular + Shadows             │
│ ✓ Full ray tracer working (output to file or console)       │
└─────────────────────────────────────────────────────────────┘
```

### INTEGRATION POINTS FOR DEVELOPER 2:

After you complete TASK 1.6, notify Dev2:
```c
// Define this structure (in hdrs/hit.h)
typedef struct s_hit_info {
    bool      is_hit;          // Did ray hit anything?
    t_vec3    point;           // Where it hit
    t_vec3    normal;          // Surface normal
    double    distance;        // How far along ray (t value)
    // Optional - helps Dev2 with materials:
    void     *object;          // Pointer to object hit
    int       object_type;     // SPHERE, PLANE, CYLINDER, CONE
    t_material *material;      // Material properties
} t_hit_info;
```

After you complete TASK 2.1, Dev2 can hook up display.

---

## DEVELOPER 2: Features, Texturing & Display
**Responsibility**: Advanced features, rendering to window, event handling  
**Start Date**: After Week 1.5 (when Dev1 reaches Task 1.6)  
**Duration**: 2-3 weeks

### PREPARATION (While Dev1 works on core):

```
□ DESIGN PHASE [Week 1 - async]:
  □ Review parsing.c to understand scene structure
  □ Design texture coordinate mapping for each object type
  □ Outline bump mapping algorithm
  □ Design color blending operations
  □ Create unit test framework
  □ Review MLX API (mlx_pixel_put, mlx_loop_hook)

□ INFRASTRUCTURE [Week 1.5 - async]:
  □ Create: hdrs/texture.h
  □ Create: srcs/texturing/ directory
  □ Create: srcs/rendering/color.c (for color operations)
  □ Set up git branch: feature/dev2-rendering
```

### MAIN TASKS (Start when Dev1 completes Task 1.6):

```
┌─────────────────────────────────────────────────────────────┐
│ WEEK 1.5 - WEEK 2                                           │
└─────────────────────────────────────────────────────────────┘

□ TASK 4.1: Pixel Rendering Loop [1-2h]
  └─ Create: srcs/rendering/render.c
  └─ Function:
     • void render_scene(t_scene *scene, t_window *window)
  └─ Algorithm:
     FOR each pixel (x, y):
       • ray = camera_ray(camera, x, y, width, height)
       • trace_ray(scene, ray, &hit)
       • IF hit: color = calculate_color(scene, hit)
       • ELSE: color = background_color (0, 0, 0)
       • mlx_pixel_put(window, x, y, rgb_to_hex(color))
  └─ Test: Simple render to window, verify output

□ TASK 3.1: Checkerboard Patterns [1.5-2h]
  └─ Modify: srcs/rendering/lighting.c (in calculate_color)
  └─ Logic:
     • IF object.checkerboard_enabled:
       • pattern = (int)hit.point.x/scale XOR (int)hit.point.y/scale
       • IF pattern & 1: swap colors or darken
  └─ Test: Checkerboard sphere/plane

□ TASK 3.2: Texture Mapping [3-4h]
  └─ Create: srcs/texturing/texture_loader.c
  └─ Create: srcs/texturing/uv_mapping.c
  └─ Functions:
     • t_texture *load_xpm_texture(const char *path)
     • t_vec2 get_uv_sphere(t_hit_info *hit, t_sphere *sphere)
     • t_vec2 get_uv_plane(t_hit_info *hit, t_plane *plane)
     • t_rgb sample_texture(t_texture *tex, double u, double v)
  └─ Texture blend:
     • IF material.texture_path: sample texture
     • Blend with base color (or replace)
  └─ Test: Textured sphere with valid XPM file

□ TASK 3.3: Bump Mapping [2-3h]
  └─ Extend: srcs/texturing/
  └─ Functions:
     • t_vec3 sample_bump_map(t_texture *bump, double u, double v)
     • t_vec3 perturb_normal(t_vec3 normal, t_vec3 bump_sample)
  └─ In lighting.c:
     • IF material.bump_map_path:
       • Load bump map
       • Sample at texture coordinates
       • Perturb normal
       • Use perturbed normal for lighting
  └─ Test: Bumpy object vs smooth

┌─────────────────────────────────────────────────────────────┐
│ WEEK 2.5 (Final Integration)                                │
└─────────────────────────────────────────────────────────────┘

□ TASK 4.2: Anti-aliasing (Optional, if time) [1-2h]
  └─ Modify: srcs/rendering/render.c
  └─ Algorithm:
     FOR each pixel (x, y):
       samples = 0
       FOR sample in [1..N]:
         • random_x = x + random(-0.5 to 0.5)
         • random_y = y + random(-0.5 to 0.5)
         • ray = camera_ray(camera, random_x, random_y, ...)
         • color += trace_and_shade(ray)
       • color /= N

□ TASK 4.3: Display & Event Loop [2-3h]
  └─ Modify: srcs/main.c
  └─ Changes:
     • Remove: sleep(5)
     • Add: render_scene(scene, window)
     • Add: mlx_loop_hook(window->mlx, update_hook, window)
     • Add: mlx_key_hook(window->mlx, key_hook, window)
  └─ Event handlers:
     • key_hook(): ESC → exit
     • Optional: WASD → move camera, arrows → rotate
  └─ Test: Render in real-time window

□ TASK 4.4: Performance (if time) [Variable]:
  □ Profile with `gprof` or `perf`
  □ Optimize hotspots:
     • Cache results
     • SIMD for vector math
     • Parallel rays (OpenMP)
  □ Implement spatial partitioning (BVH, octree)

┌─────────────────────────────────────────────────────────────┐
│ DELIVERABLE BY END OF WEEK 2.5:                             │
├─────────────────────────────────────────────────────────────┤
│ ✓ render.c       - Pixel loop, renders scene                │
│ ✓ checkerboard   - Pattern rendering working                │
│ ✓ texture loading - XPM textures loaded correctly            │
│ ✓ texture mapping - UV coordinates correct per object       │
│ ✓ bump mapping   - Normals perturbed, lighting affected      │
│ ✓ main.c updated - Display window, event loop active        │
│ ✓ Full working ray tracer with all features!                │
└─────────────────────────────────────────────────────────────┘
```

### WAITING POINTS:

```
BLOCKED on Dev 1:
  ├─ Task 4.1 needs: trace_ray() and calculate_color() [Task 1.6, 2.1]
  ├─ Task 3.1 needs: calculate_color() signature [Task 2.1]
  └─ Task 3.2, 3.3 need: t_hit_info with material pointer [Task 1.6]

CAN DO IN PARALLEL:
  ├─ Design phase (all of Week 1)
  ├─ Texture system structure (no dependencies)
  └─ Color utilities (utility functions)
```

---

## COMMUNICATION PROTOCOL

### Daily Standups (15 min):
```
Dev 1:
  "Completed: [task]"
  "Currently on: [task]"
  "Blocker: [if any]"

Dev 2:
  "Completed: [design/prep]"
  "Currently on: [task]"
  "Waiting for: Dev1 to finish [task]"
```

### Code Review Checklist (before merging):
```
□ All functions have prototypes in .h files
□ No undefined behavior (valgrind clean)
□ Consistent style with existing code
□ Comments on complex math
□ Unit tests included and passing
□ Makefile updated with new source files
```

### Integration Commits:
```
Week 2 Friday:
  [MERGE] Dev1: ray-tracing core complete
  - All intersection functions
  - Lighting calculations
  - Passes unit tests

Week 2.5 Friday:
  [MERGE] Dev2: features complete
  - Texturing, bump mapping
  - Display loop working
  - Full feature parity
```

---

## TESTING STRATEGY

### Dev 1 Test Suite:
```c
// tests/unit_tests/ray_tests.c
void test_ray_generation();
void test_sphere_intersection_simple();
void test_sphere_intersection_edge_cases();
void test_plane_intersection();
void test_cylinder_intersection();
void test_cone_intersection();
void test_scene_trace_closest_hit();
void test_lighting_diffuse();
void test_lighting_specular();
```

### Dev 2 Test Suite:
```c
// tests/unit_tests/render_tests.c
void test_pixel_rendering();
void test_checkerboard_pattern();
void test_texture_uv_mapping_sphere();
void test_texture_uv_mapping_plane();
void test_bump_mapping_normal_perturbation();
```

### Integration Tests:
```
1. Render sample.rt to file
2. Compare output with reference image
3. Test event handling
4. Memory leak check (valgrind)
```

---

## FILE STRUCTURE AFTER COMPLETION

```
srcs/
├── main.c                      [Updated: render loop, events]
├── parsing/                    [Unchanged - Dev 1 doesn't touch]
├── container/                  [Unchanged]
├── utils/                      [Unchanged]
├── vec_maths/                  [Unchanged]
├── ray_tracing/                [NEW - Dev 1]
│   ├── ray.c
│   ├── intersection_sphere.c
│   ├── intersection_plane.c
│   ├── intersection_cylinder.c
│   ├── intersection_cone.c
│   └── scene_intersection.c
├── rendering/                  [NEW - Dev 2]
│   ├── render.c
│   ├── lighting.c              [Dev 1 contributes here]
│   └── color.c
└── texturing/                  [NEW - Dev 2]
    ├── texture_loader.c
    ├── uv_mapping.c
    └── bump_mapping.c

hdrs/
├── minirt.h                    [Unchanged]
├── parsing.h                   [Unchanged]
├── vector.h                    [Unchanged]
├── vec_math.h                  [Unchanged]
├── window.h                    [Unchanged]
├── ray.h                       [NEW - Dev 1]
├── intersection.h              [NEW - Dev 1]
├── hit.h                       [NEW - Dev 1]
├── renderer.h                  [NEW - Dev 2]
└── texture.h                   [NEW - Dev 2]

tests/
├── unit_tests/                 [NEW]
│   ├── ray_tests.c             [Dev 1]
│   ├── intersection_tests.c    [Dev 1]
│   ├── lighting_tests.c        [Dev 1]
│   ├── texture_tests.c         [Dev 2]
│   └── render_tests.c          [Dev 2]
└── [Existing parser tests]     [Unchanged]
```

---

## SUCCESS CRITERIA

### Dev 1 (Ray Tracing):
- [ ] All intersection functions return correct results (unit tested)
- [ ] Shadow rays properly block light
- [ ] Specular highlights visible
- [ ] Multi-object scenes work correctly
- [ ] Code compiles with -Wall -Wextra -Werror
- [ ] Zero memory leaks (valgrind)

### Dev 2 (Features/Display):
- [ ] Image renders to window at reasonable speed
- [ ] Checkerboard patterns visible
- [ ] Textures load and map correctly
- [ ] Bump mapping affects lighting
- [ ] Window responds to ESC key
- [ ] Code compiles with -Wall -Wextra -Werror
- [ ] Zero memory leaks (valgrind)

### Both:
- [ ] Single Makefile builds everything
- [ ] `./miniRT sample.rt` runs without crashes
- [ ] Output is visually correct (ray traced image)
- [ ] Git history is clean (logical commits)
- [ ] Code is readable and documented

