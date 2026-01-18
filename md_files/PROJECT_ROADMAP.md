# RayTracer-MiniRT: Complete Project Roadmap for Team Collaboration

**Project Status**: ~60% Complete (Parsing Phase Finished, Rendering Phase Critical Path Needed)

**Current Date**: January 8, 2026

---

## Project Overview

MiniRT is a ray tracing renderer that:
- Parses `.rt` scene files with camera, lights, and geometric objects (spheres, planes, cylinders, cones)
- Renders the 3D scene using ray tracing algorithm
- Displays the result in a window using MLX graphics library
- Supports advanced features: textures, bump maps, specular highlights, checkerboard patterns

**Architecture**:
```
Parsing (✅ DONE) → Scene Data Structure (✅ DONE) → Ray Tracing (❌ NEEDED) → Rendering (❌ NEEDED) → Display (⚠️ PARTIAL)
```

---

## COMPLETED WORK (✅)

### 1. **Infrastructure & Libraries** ✅
- [x] MLX (graphics library) - Configured and building
- [x] libft (custom C library) - Complete with bonus functions
- [x] GNL (Get Next Line) - Parsing support
- [x] Build system - Makefile fully functional

### 2. **Data Structures** ✅
- [x] Vector container (`t_vector`) - Dynamic arrays for objects
- [x] Scene structure (`t_scene`) - Holds all scene data
- [x] Geometry types:
  - [x] Sphere (`t_sphere`)
  - [x] Plane (`t_plane`)
  - [x] Cylinder (`t_cylinder`)
  - [x] Cone (`t_cone`)
- [x] Supporting structures:
  - [x] Material/Specular properties
  - [x] Camera configuration
  - [x] Ambient lighting
  - [x] Point lights
  - [x] RGB color struct

### 3. **File Parsing** ✅
- [x] File validation (`.rt` extension check)
- [x] Argument validation
- [x] Ambient light parsing (`parse_ambient.c`)
- [x] Camera parsing (`parse_camera.c`)
- [x] Light parsing (`parse_lights.c`)
- [x] Sphere parsing (`parse_spheres.c`)
- [x] Plane parsing (`parse_planes.c`)
- [x] Cylinder parsing (`parse_cylinders.c`)
- [x] Cone parsing (`parse_cones.c`)
- [x] Optional features parsing (`parse_optional.c`):
  - [x] Specular highlights (Phong model)
  - [x] Texture paths
  - [x] Bump map paths
  - [x] Checkerboard patterns

### 4. **Data Validation** ✅
- [x] Point validation (XYZ coordinates)
- [x] RGB color validation (0-255)
- [x] Double/Integer validation
- [x] Attribute count checking
- [x] Range validation for parameters (FOV, brightness, etc.)
- [x] Vector normalization checks
- [x] File extension validation

### 5. **Vector Mathematics** ✅
- [x] Vector addition (`vec_add`)
- [x] Vector subtraction (`vec_sub`)
- [x] Scalar multiplication (`vec_scale`)
- [x] Dot product (`vec_dot_product`)
- [x] Cross product (`vec_cross_product`)
- [x] Magnitude calculation (`vec_magnitude`)
- [x] Normalization (`vec_normalize`)

### 6. **Memory Management** ✅
- [x] Scene initialization (`init_scene`)
- [x] Scene cleanup (`free_scene`)
- [x] Vector container lifecycle

### 7. **Utilities** ✅
- [x] Scene printing/debug output
- [x] Error handling functions
- [x] Helper parsing functions

---

## CRITICAL PATH: REMAINING WORK ❌ (Priority Order)

### **Phase 1: Ray Tracing Engine (Core Rendering)** — HIGHEST PRIORITY

#### **Task 1.1: Ray Structure & Ray Generation** 🚨 BLOCK
**Dependency**: None
**Estimated Time**: 3-4 hours
**Can Work in Parallel**: Yes (Task 1.2)

**Subtasks**:
- [ ] Create `t_ray` structure (origin point, direction, t_min/t_max)
- [ ] Implement ray generation from camera:
  - [ ] Camera space to world space transformation
  - [ ] FOV calculation to determine ray direction per pixel
  - [ ] Handle different FOV angles correctly
- [ ] Helper: Ray parameter equation `p(t) = origin + t * direction`
- [ ] Unit tests for ray generation

**Files to Create**:
- `hdrs/ray.h`
- `srcs/ray_tracing/ray.c`

**Functions Needed**:
```c
typedef struct s_ray {
    t_vec3  origin;
    t_vec3  direction;
    double  t_min;
    double  t_max;
} t_ray;

t_ray   create_ray(t_vec3 origin, t_vec3 direction);
t_ray   camera_ray(t_camera *cam, double x, double y, int width, int height);
t_vec3  ray_at(t_ray *ray, double t);
```

---

#### **Task 1.2: Sphere Ray Intersection** 🚨 BLOCK
**Dependency**: Task 1.1
**Estimated Time**: 2-3 hours
**Can Work in Parallel**: Yes (with Task 1.1)

**Subtasks**:
- [ ] Implement sphere-ray intersection algorithm
  - [ ] Solve quadratic equation (discriminant method)
  - [ ] Find closest intersection point
  - [ ] Calculate normal at intersection
- [ ] Handle ray entering/exiting sphere
- [ ] Return intersection data (hit point, normal, distance)
- [ ] Unit tests

**Files to Create**:
- `hdrs/intersection.h`
- `srcs/ray_tracing/intersection_sphere.c`

**Key Math**:
```
Sphere: |p - center|² = radius²
Ray: p = origin + t * direction
Substitute and solve quadratic: a*t² + b*t + c = 0
```

---

#### **Task 1.3: Plane Ray Intersection**
**Dependency**: Task 1.2 (pattern)
**Estimated Time**: 1.5-2 hours
**Can Work in Parallel**: Yes (with Task 1.2)

**Subtasks**:
- [ ] Implement plane-ray intersection
  - [ ] Solve linear equation (plane normal · (p - point) = 0)
  - [ ] Check ray direction isn't parallel to plane
  - [ ] Return hit information
- [ ] Unit tests

**Key Math**:
```
Plane: normal · (p - position) = 0
Ray: p = origin + t * direction
Solve: normal · direction * t = normal · (position - origin)
```

---

#### **Task 1.4: Cylinder Ray Intersection**
**Dependency**: Task 1.3
**Estimated Time**: 4-5 hours
**Can Work in Parallel**: Yes (with Task 1.3)

**Subtasks**:
- [ ] Implement cylinder-ray intersection (body)
  - [ ] Project ray onto cylinder axis
  - [ ] Solve quadratic in 2D plane perpendicular to axis
  - [ ] Check bounds (height)
- [ ] Implement cylinder caps intersection
- [ ] Choose closest intersection
- [ ] Calculate proper normals (body vs. caps)
- [ ] Unit tests

**Note**: Most complex geometric intersection

---

#### **Task 1.5: Cone Ray Intersection**
**Dependency**: Task 1.4
**Estimated Time**: 4-5 hours
**Can Work in Parallel**: Yes (with Task 1.4)

**Subtasks**:
- [ ] Implement cone-ray intersection (surface)
- [ ] Implement cone caps intersection
- [ ] Handle cone angle properly
- [ ] Calculate correct normals
- [ ] Unit tests

---

#### **Task 1.6: Unified Intersection System**
**Dependency**: Tasks 1.2-1.5
**Estimated Time**: 2-3 hours

**Subtasks**:
- [ ] Create `t_hit_info` structure (point, normal, distance, object_type)
- [ ] Implement scene intersection query:
  - [ ] Test ray against ALL objects
  - [ ] Find closest intersection
  - [ ] Return hit info
- [ ] Optimization: Bounding box checks (optional for first version)

**Files to Create**:
- `hdrs/hit.h`
- `srcs/ray_tracing/scene_intersection.c`

---

### **Phase 2: Lighting & Shading Model**

#### **Task 2.1: Basic Diffuse Lighting**
**Dependency**: Task 1.6
**Estimated Time**: 2-3 hours

**Subtasks**:
- [ ] Implement Phong reflection model basics:
  - [ ] Ambient component
  - [ ] Diffuse component (Lambert's law)
  - [ ] Light visibility (shadow rays)
- [ ] Shadow casting:
  - [ ] Cast shadow ray toward each light
  - [ ] Check if ray hits any object
  - [ ] Mark surface in shadow if blocked
- [ ] Handle multiple lights
- [ ] Clamp color values (0-255)

**Math**:
```
diffuse = Kd * I * max(0, normal · light_direction)
where Kd = surface diffusivity, I = light intensity
```

---

#### **Task 2.2: Specular Highlights**
**Dependency**: Task 2.1
**Estimated Time**: 2 hours

**Subtasks**:
- [ ] Read specular properties from material
- [ ] Implement specular component (Phong):
  ```
  specular = Ks * I * max(0, view_direction · reflect_direction)^n
  ```
- [ ] Combine with diffuse
- [ ] Handle shininess factor (n_s)

---

#### **Task 2.3: Ambient Occlusion / Global Illumination (OPTIONAL - Advanced)**
**Dependency**: Task 2.2
**Estimated Time**: 4+ hours

**Subtasks**:
- [ ] Implement simple ambient occlusion
- [ ] Or: implement basic reflections for mirrors

---

### **Phase 3: Advanced Features**

#### **Task 3.1: Checkerboard Patterns**
**Dependency**: Task 2.1
**Estimated Time**: 1.5-2 hours

**Subtasks**:
- [ ] Check `checkerboard_enabled` flag
- [ ] If enabled: determine checkerboard pattern using hit point coordinates
- [ ] Alternate colors based on pattern

---

#### **Task 3.2: Texture Mapping**
**Dependency**: Task 3.1
**Estimated Time**: 3-4 hours

**Subtasks**:
- [ ] Load XPM texture files
- [ ] UV mapping for each object type
- [ ] Bilinear filtering (optional)
- [ ] Blend with base color

---

#### **Task 3.3: Bump Mapping**
**Dependency**: Task 3.2
**Estimated Time**: 2-3 hours

**Subtasks**:
- [ ] Load bump map (XPM)
- [ ] Calculate tangent space
- [ ] Perturb surface normal
- [ ] Affect lighting calculations

---

### **Phase 4: Rendering & Display Loop**

#### **Task 4.1: Pixel Rendering Loop**
**Dependency**: Task 2.1 (minimum)
**Estimated Time**: 1-2 hours

**Subtasks**:
- [ ] For each pixel (x, y):
  - [ ] Generate ray from camera
  - [ ] Find closest intersection
  - [ ] Calculate color (diffuse + specular)
  - [ ] Handle no intersection (background color)
- [ ] Write color to image buffer

**Files to Create**:
- `hdrs/renderer.h`
- `srcs/rendering/renderer.c`

---

#### **Task 4.2: Multi-sampling (Anti-aliasing)** (OPTIONAL - Advanced)
**Dependency**: Task 4.1
**Estimated Time**: 1-2 hours

**Subtasks**:
- [ ] Implement MSAA (Multi-Sample Anti-Aliasing)
- [ ] Average multiple rays per pixel
- [ ] Reduce aliasing artifacts

---

#### **Task 4.3: Display & Event Loop** ⚠️ PARTIAL
**Dependency**: Task 4.1
**Estimated Time**: 2-3 hours

**Current State**: Window opens, displays for 5 seconds, then closes (dummy)

**Subtasks**:
- [ ] Replace sleep(5) with actual render loop
- [ ] Render image to MLX window
- [ ] Handle window events:
  - [ ] ESC key → close window
  - [ ] Mouse movement → rotate camera (optional)
  - [ ] Keyboard → move camera (optional)
- [ ] Display loop callback

---

#### **Task 4.4: Performance Optimization** (OPTIONAL)
**Dependency**: Task 4.3
**Estimated Time**: Variable

**Subtasks**:
- [ ] Multi-threading (if time permits)
- [ ] Spatial partitioning (BVH, octree)
- [ ] Cache optimizations

---

## RECOMMENDED TEAM SPLIT

### **Developer 1: Ray Tracing Engine (Intersection & Core Rendering)**
**Timeline**: Weeks 1-2

**Tasks** (Sequential):
1. Task 1.1: Ray Generation (3-4h)
2. Task 1.2: Sphere Intersection (2-3h)
3. Task 1.3: Plane Intersection (1.5-2h)
4. Task 1.4: Cylinder Intersection (4-5h)
5. Task 1.5: Cone Intersection (4-5h)
6. Task 1.6: Unified Intersection System (2-3h)
7. Task 2.1: Diffuse Lighting (2-3h)
8. Task 2.2: Specular Highlights (2h)

**Total**: ~25 hours
**Deliverable**: Complete ray-traced image without display

---

### **Developer 2: Features, Texturing & Display**
**Timeline**: Weeks 1.5-2.5 (starts when Task 1.6 done)

**Tasks** (Can partially parallel with Dev1):
1. **PREPARATION** (While Dev1 works on 1.1-1.6):
   - Design texture loading system
   - Design bump mapping pipeline
   - Create unit tests framework

2. **After Dev1 delivers Task 1.6**:
   - Task 3.1: Checkerboard Patterns (1.5-2h)
   - Task 3.2: Texture Mapping (3-4h)
   - Task 3.3: Bump Mapping (2-3h)
   - Task 4.1: Pixel Rendering Loop (1-2h)
   - Task 4.2: Anti-aliasing (1-2h)
   - Task 4.3: Display & Event Loop (2-3h)
   - Task 4.4: Optimization (if time)

**Total**: ~20-25 hours
**Deliverable**: Full feature-complete application

---

## DEPENDENCY GRAPH

```
Task 1.1 (Ray) ─┬─→ Task 1.2 (Sphere) ─┬─→ Task 1.6 (Scene) ─→ Task 2.1 (Lighting) ─→ Task 4.1 (Render)
                │                       │                                                    ↑
                └─→ Task 1.3 (Plane) ───┤                                                    │
                                         │                                                    │
                    Task 1.4 (Cylinder)──┤                                    ┌──────────────┘
                                         │                                    │
                    Task 1.5 (Cone) ─────┘                    ┌──→ Task 2.2 ──┘
                                                              │
                                                          ┌───┘
                                              Task 3.1 ────┤
                                              Task 3.2 ────┤
                                              Task 3.3 ────┘
```

---

## MERGE STRATEGY

### **Weekly Sync Points**:

**End of Week 1 (Dev1)**:
- All intersection functions implemented
- Diffuse lighting working
- Demo: Ray trace simple scene, output to PPM file

**Mid Week 2 (Dev2 starts)**:
- Coordinate on shading interface
- Dev1 continues: specular highlights
- Dev2 starts: texture system design

**End of Week 2**:
- Both developers merge code
- Full rendering pipeline operational
- Display window working with animation

**Week 3** (if needed):
- Optimization, bug fixes
- Polish, code review

---

## CODE INTEGRATION CHECKLIST

- [ ] Create new header files in `hdrs/`:
  - [ ] `hdrs/ray.h`
  - [ ] `hdrs/intersection.h`
  - [ ] `hdrs/hit.h`
  - [ ] `hdrs/renderer.h`
  - [ ] `hdrs/texture.h` (optional)

- [ ] Create new source directories:
  - [ ] `srcs/ray_tracing/` — core engine
  - [ ] `srcs/rendering/` — render loop
  - [ ] `srcs/texturing/` (optional) — texture handling

- [ ] Update Makefile:
  - [ ] Add new source files
  - [ ] Update include paths

- [ ] Update main.c:
  - [ ] Replace `sleep(5)` with render loop
  - [ ] Hook renderer to window

- [ ] Testing:
  - [ ] Unit tests for each function
  - [ ] Integration tests
  - [ ] Sample `.rt` files for testing

---

## ESTIMATED TOTAL PROJECT TIME

- **Dev 1**: ~25 hours (ray tracing core)
- **Dev 2**: ~20-25 hours (features & display)
- **Combined effort**: ~45-50 hours
- **Wall clock time**: 2-3 weeks (working in parallel)

---

## CRITICAL SUCCESS FACTORS

1. ✅ **Task 1.1 must complete first** — gates all ray tracing
2. ✅ **Task 1.6 must be clean** — affects all lighting code
3. ✅ **Regular code reviews** — intersection bugs are hard to debug
4. ✅ **Unit tests as you go** — EPSecially for geometry math
5. ✅ **Keep interface simple** — EPSecially between intersection and shading

---

## NOTES FOR DEVELOPERS

### Dev 1 (Ray Tracing):
- Consider creating test files that render to PPM format initially (easier than MLX debugging)
- Use simple test cases (axis-aligned objects first)
- Document the intersection function signatures clearly for Dev 2
- Include hit_info structure design in code review with Dev 2 early

### Dev 2 (Features/Display):
- Wait for Dev 1's `scene_intersection` function to be finalized
- Set up MLX rendering early (can be a stub that fills random colors)
- Prepare texture loading system in parallel
- Coordinate with Dev 1 on shading parameters (how colors are calculated)

### Both:
- Use git branches: `feature/dev1-ray-tracing`, `feature/dev2-rendering`
- Merge to main weekly
- Keep main branch always compilable
- Document any assumptions in code comments

