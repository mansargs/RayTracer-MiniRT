# 🚀 MiniRT: Team Collaboration - START HERE

**Current Status**: 60% Complete | **Time to Finish**: 2-3 weeks with 2 developers  
**Generated**: January 8, 2026

---

## 📋 QUICK START (5 minutes)

### 1. **Understand the Situation** (2 min)
- The project has **parsing working perfectly** ✅
- The project **needs ray tracing** (the core rendering engine) ❌
- Two developers can work in **parallel** on different parts

### 2. **Who Does What** (2 min)

| **Developer 1** | **Developer 2** |
|---|---|
| **Ray Tracing Core** | **Features & Display** |
| Rays, intersections, lighting | Textures, checkerboards, window |
| 25 hours of work | 20 hours of work |
| **Starts**: Immediately | **Starts**: After Dev1 does Ray & Intersections |
| **Blocks**: Everything | **Blocks**: Nothing (but depends on Dev1) |

### 3. **Next 2 Hours**
```bash
# Both developers:
1. Read TEAM_SUMMARY.md (this is the executive overview)
2. Read TEAM_TASKS.md (this is YOUR specific task list)
3. Read PROJECT_ROADMAP.md (if you want all the details)

# Setup:
git branch                          # See current branch
git checkout -b feature/dev-name    # Create your branch

# Verify build:
make clean && make                  # Should compile without errors
```

---

## 📚 DOCUMENTATION GUIDE

| File | Purpose | Read Time | For Whom |
|------|---------|-----------|----------|
| **TEAM_SUMMARY.md** (this file) | Executive overview | 5 min | Both |
| **TEAM_TASKS.md** | Your specific task list | 20 min | Each Dev |
| **PROJECT_ROADMAP.md** | Complete timeline & math | 30 min | Reference |
| **PROJECT_STATUS.md** | Architecture & current state | 15 min | Reference |

---

## 👨‍💻 FOR DEVELOPER 1: Ray Tracing Core

### Your Mission
**Make rays trace through the 3D scene and calculate accurate colors**

### Your Tasks (In Order - Don't Skip):
1. **Ray Generation** (3-4 hours)
   - Create `hdrs/ray.h` and `srcs/ray_tracing/ray.c`
   - Generate rays from camera through each pixel
   
2. **Sphere Intersection** (2-3 hours)
   - Detect where rays hit spheres
   - Calculate the surface normal
   
3. **Plane Intersection** (1.5-2 hours)
   - Detect where rays hit planes
   
4. **Cylinder Intersection** (4-5 hours)
   - Trickier - need to handle body + caps
   
5. **Cone Intersection** (4-5 hours)
   - Similar to cylinder but with angle constraint
   
6. **Scene Intersection** (2-3 hours)
   - Test ray against ALL objects, find closest hit
   - **CRITICAL**: This unblocks Developer 2
   
7. **Diffuse Lighting** (2-3 hours)
   - Calculate how light hits surfaces
   - Add shadows (block light if something's in the way)
   
8. **Specular Highlights** (2 hours)
   - Add shiny reflections

### What You'll Produce
A complete ray tracer that:
- Generates rays from the camera
- Finds where rays hit objects
- Calculates correct lighting
- Produces colored pixels

### Code Locations
```
You'll create:
  hdrs/ray.h
  hdrs/intersection.h
  hdrs/hit.h
  srcs/ray_tracing/ray.c
  srcs/ray_tracing/intersection_sphere.c
  srcs/ray_tracing/intersection_plane.c
  srcs/ray_tracing/intersection_cylinder.c
  srcs/ray_tracing/intersection_cone.c
  srcs/ray_tracing/scene_intersection.c
  srcs/rendering/lighting.c (shared with Dev2)
```

### Key Functions You'll Write
```c
// Ray generation
t_ray create_ray(t_vec3 origin, t_vec3 direction);
t_ray camera_ray(t_camera *cam, double x, double y, int w, int h);

// Intersections
bool ray_intersects_sphere(t_ray *ray, t_sphere *s, t_hit_info *hit);
bool ray_intersects_plane(t_ray *ray, t_plane *p, t_hit_info *hit);
// ... cylinder, cone ...

// Scene query
bool trace_ray(t_scene *scene, t_ray *ray, t_hit_info *hit);

// Lighting
t_rgb calculate_color(t_scene *scene, t_hit_info *hit, t_ray *view);
```

### Timeline
- **Week 1**: Tasks 1-3 (ray + sphere + plane)
- **Week 2**: Tasks 4-8 (cylinder, cone, intersection, lighting)
- **Friday Week 2**: Ready for merge with Developer 2

### ✅ Success Criteria
```
□ All rays generate correctly from camera
□ Sphere intersections accurate
□ Plane intersections accurate
□ Cylinder intersections accurate
□ Cone intersections accurate
□ Closest hit detection works
□ Shadows cast correctly
□ Specular highlights appear on shiny objects
□ Zero memory leaks
□ All code passes -Wall -Wextra -Werror
```

---

## 👨‍💻 FOR DEVELOPER 2: Features, Textures & Display

### Your Mission
**Make the ray tracer beautiful and interactive**

### WAIT! (Week 1)
You **cannot start** main coding until Developer 1 finishes ray intersection. But you can:
- [ ] Review MLX graphics API
- [ ] Design texture coordinate system
- [ ] Design bump mapping algorithm
- [ ] Create unit test framework
- [ ] Design color utilities

### Your Main Tasks (Start Week 1.5, when Dev1 finishes Task 1.6):
1. **Pixel Rendering Loop** (1-2 hours)
   - Loop through each pixel
   - Call Dev1's trace_ray() function
   - Write color to window
   
2. **Checkerboard Patterns** (1.5-2 hours)
   - Use hit point position to create checker pattern
   - Alternate colors based on pattern
   
3. **Texture Mapping** (3-4 hours)
   - Load XPM texture files
   - Map 2D texture to 3D objects
   - Blend with base color
   
4. **Bump Mapping** (2-3 hours)
   - Load bump maps
   - Perturb surface normals
   - Affects how light interacts
   
5. **Anti-Aliasing** (1-2 hours, optional)
   - Sample multiple rays per pixel
   - Average results
   
6. **Display & Events** (2-3 hours)
   - Replace sleep(5) with actual render loop
   - Handle keyboard (ESC to exit)
   - Display rendered frame in window

### What You'll Produce
A beautiful, interactive ray tracer:
- Renders textured objects
- Shows bumpy surfaces realistically
- Displays in real-time window
- Responds to user input

### Code Locations
```
You'll create:
  hdrs/texture.h
  hdrs/renderer.h
  srcs/rendering/render.c
  srcs/rendering/color.c
  srcs/texturing/texture_loader.c
  srcs/texturing/uv_mapping.c
  srcs/texturing/bump_mapping.c
  
Update:
  srcs/main.c (replace sleep with render loop)
```

### Key Functions You'll Write
```c
// Rendering
void render_scene(t_scene *scene, t_window *window);

// Color utilities
int rgb_to_hex(t_rgb color);
t_rgb clamp_rgb(t_rgb color);

// Texture loading
t_texture *load_xpm_texture(const char *path);
t_rgb sample_texture(t_texture *tex, double u, double v);

// UV mapping
t_vec2 get_uv_sphere(t_hit_info *hit, t_sphere *sphere);
t_vec2 get_uv_plane(t_hit_info *hit, t_plane *plane);

// Bump mapping
t_vec3 sample_bump_map(t_texture *bump, double u, double v);
```

### Timeline
- **Week 1**: Design & prepare (no coding yet, waiting for Dev1)
- **Week 1.5**: Start rendering (after Dev1 finishes intersections)
- **Week 2**: Textures & bump maps
- **Week 2.5**: Final display & polish

### ✅ Success Criteria
```
□ Pixel rendering loop works
□ Checkerboard patterns visible
□ Textures load from XPM files
□ Texture coordinates correct on all objects
□ Bump maps affect lighting
□ Window displays rendered image
□ ESC key closes window
□ No memory leaks
□ All code passes -Wall -Wextra -Werror
```

---

## 🔗 HOW YOU WORK TOGETHER

### Critical Synchronization Points

**Week 1 End** (Dev 1):
```
Dev1 completes: Ray generation + Sphere + Plane intersections
Dev1 pushes: git push origin feature/dev1-ray-tracing
Dev2 reviews: "Looks good, ready for you to start rendering"
```

**Week 2 Start** (Dev 1 + Dev 2):
```
Dev1 continues: Cylinder, Cone, Scene intersection
Dev2 starts: Render loop (using Dev1's trace_ray API)
Daily syncs: "What's the exact function signature for trace_ray?"
```

**Week 2 Mid** (Integration Point):
```
Dev1 completes: All intersections + diffuse lighting
Dev2 can now: Add colors, shadows, materials
Both: Code review each other's work
```

**Week 2.5 End** (Final):
```
Dev2 completes: Textures, display, events
Both: Merge to main branch
Result: COMPLETE RAY TRACER
```

### Daily Communication
```
Morning (10 min):
├─ Dev1: "Finishing spheres today, will have scene_intersection API ready"
├─ Dev2: "Preparing texture system, can start render loop soon"
└─ Both: Any blockers?

Afternoon (if needed):
├─ "Question about normal direction..."
├─ "Check the math on page X of notes"
└─ Git push with good commit messages

Before merge:
├─ Code review
├─ Run valgrind
└─ Test together
```

---

## 🎯 IMMEDIATE ACTIONS

### TODAY (Both):
```bash
□ Read TEAM_SUMMARY.md (5 min)
□ Read TEAM_TASKS.md (15 min)
□ Read PROJECT_ROADMAP.md (if time - detailed reference)
□ Meet for 30 min to discuss:
  • Branch strategy
  • How often to sync
  • API design principles
  • Test strategy
```

### TOMORROW (Dev 1):
```bash
□ Create git branch: git checkout -b feature/dev1-ray-tracing
□ Create hdrs/ray.h with basic structure
□ Create srcs/ray_tracing/ directory
□ Start Task 1.1: Ray generation
□ Commit often with clear messages
```

### TOMORROW (Dev 2):
```bash
□ Create git branch: git checkout -b feature/dev2-rendering
□ Create design document: texture_strategy.txt
□ Review MLX API documentation
□ Review hdrs/minirt.h and understand data structures
□ Prepare to wait (you'll start coding in 1 week)
```

---

## 📖 REFERENCE MATERIALS INCLUDED

1. **PROJECT_ROADMAP.md** - Complete detailed timeline
   - All tasks with estimated hours
   - Math formulas
   - Dependency graph
   - Merge strategy

2. **TEAM_TASKS.md** - Task-by-task breakdown
   - Exactly what code to write
   - Where to write it
   - What functions to implement
   - Success criteria for each task

3. **PROJECT_STATUS.md** - Current state & architecture
   - What's done vs what's needed
   - Data structures
   - File organization
   - Common pitfalls

4. **TEAM_SUMMARY.md** - Executive overview (this file)
   - Quick reference
   - Timeline visualization
   - Work breakdown

---

## ⚠️ CRITICAL SUCCESS FACTORS

1. **Dev 1 must complete Task 1.6 before Dev 2 starts main work**
   - Dev 2 cannot render without trace_ray() function

2. **Keep intersections numerically stable**
   - Use epsilon for floating point comparisons
   - Normalize vectors before use
   - Clamp output values

3. **Clear API contracts**
   - Define function signatures in headers first
   - Both devs should agree on data structures
   - Document assumptions (e.g., "normal must be normalized")

4. **Test as you go**
   - Unit test each function immediately
   - Don't wait until end to test
   - Use printf debugging if needed

5. **Regular merges to main**
   - Merge working code every few days
   - Don't create mega-branches that drift
   - Keep main always compilable

---

## 🚀 BY THE END: YOU WILL HAVE

```
./miniRT sample.rt

→ Window opens
→ Shows photo-realistic 3D rendered scene
→ Full lighting with shadows
→ Textured objects with bump maps
→ Smooth checkerboard patterns
→ Press ESC to close

That's a complete ray tracer! 🎉
```

---

## 💡 HELPFUL TIPS

### For Developer 1:
- Start by rendering rays to verify they're correct
- Test spheres alone before adding planes
- Use printf to debug intersection values
- Normalize all normals before using them
- Keep track of which direction is "outward"

### For Developer 2:
- Use test images (try your phone pic as texture)
- Start with simple checkerboard before complex textures
- Test each object type separately
- Keep MLX simple - just pixels for now
- Worry about performance later

### Both:
- Commit often with clear messages
- Use git branches - don't work on main
- Read each other's code
- Ask questions early
- Document assumptions in comments

---

## ❓ COMMON QUESTIONS

**Q: "How long will this really take?"**  
A: 2-3 weeks with both working in parallel. Longer if solo.

**Q: "What if Dev 1 gets blocked?"**  
A: Go back and debug the previous task. Don't move forward.

**Q: "When do I stop coding?"**  
A: When success criteria are met AND valgrind is clean.

**Q: "What if we finish early?"**  
A: Implement bonus features: reflections, refraction, soft shadows, etc.

**Q: "Do we need to work full-time?"**  
A: No, the hours are estimates. Adjust pace as needed.

---

## 📞 SUPPORT RESOURCES

**Inside the project**:
- `hdrs/` - All type definitions
- `srcs/parsing/` - How file parsing works
- `srcs/vec_maths/` - Vector operations you can use
- `libraries/libft/` - Utility functions (malloc, string funcs)
- `libraries/mlx/` - Graphics API

**Ray tracing references** (general knowledge):
- Ray equation: `p(t) = origin + t * direction`
- Quadratic formula for intersections
- Phong lighting model
- Normal vectors for surfaces

**Testing approach**:
- Create simple scenes first (one object)
- Verify with math before coding
- Use unit tests, not just running the program
- Check for memory leaks with valgrind

---

## ✅ YOU'RE READY!

You have:
- ✅ Clear task assignments
- ✅ Documented timeline
- ✅ Code structure defined
- ✅ Success criteria
- ✅ Merge strategy

**Questions?** See PROJECT_ROADMAP.md or TEAM_TASKS.md

**Ready to start?** Read TEAM_TASKS.md for YOUR specific work.

**Let's build an awesome ray tracer!** 🚀

