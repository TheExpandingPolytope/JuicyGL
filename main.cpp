#include "juicyGL.h"


int wmain()
{
	
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	window = SDL_CreateWindow("jWindow", x, y, width, height, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(window);
	glewExperimental = GL_TRUE;
	glewInit();

	//CREATE DISPLAY OBJECT
	vector3 obj_velocity = vec3(0.0f, 0.0f, 0.0f);
	
	//create camera
	jCamera cam;
	//create rendering scene
	jScene scene;
	//add camera to scene
	scene.setCamera(cam);
	
	//add sphere to scene
	Sphere sp; sp.Center = 0.0f; sp.radius = 1.0f;
	jSphere S; vector3 dd = vec3(64, 224, 208).normalize(); S.setColor(dd); S.setSphere(sp);
	scene.addObject(S.object);
	
	//add sphere to scene
	Sphere spp; spp.Center = vec3(10.0f,1.3,0); spp.radius = 1.0f;
	jSphere Sp; vector3 ddp = vec3(64, 224, 208).normalize(); Sp.setColor(ddp); Sp.setSphere(spp);
	scene.addObject(Sp.object);

	//add pbr object
	pbr_test_object o(cam);

	//test polytope expansion
	Simplex cs;
	polytope peepee;
	cs.add(vec3(0, 0, 0)); cs.add(vec3(1, 0, 0)); cs.add(vec3(0, 1, 0)); cs.add(vec3(0, 0, 1));
	peepee = cs;
	peepee.expand(vec3(-1.0f, 0.0f, 0.0f));

	
	float time;
	float timeTrash;
	float timeLast = 0;
	float x = 0; 
	float y = 0;
	float z = 0;
	float inc = 0;
	
	SDL_Event windowEvent;
	while (true)
	{
		if (SDL_PollEvent(&windowEvent))
		{
			if (windowEvent.type == SDL_QUIT) break;
		}
		GLfloat currentFrame = SDL_GetTicks();
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		if (state[SDL_SCANCODE_W]){
			cam.moveZ(-.01);
		}
		if (state[SDL_SCANCODE_S]) {
			cam.moveZ(.01);
		}
		if (state[SDL_SCANCODE_A]) {
			cam.moveX(-.01);
		}
		if (state[SDL_SCANCODE_D]) {
			cam.moveX(.01);
		}	
		
		if (state[SDL_SCANCODE_UP]) {
			sp.Center.z -= .06f;
		}
		if (state[SDL_SCANCODE_DOWN]) {
			sp.Center.z += .06f;
		}
		if (state[SDL_SCANCODE_LEFT]) {
			sp.Center.x -= .06f;
		}
		if (state[SDL_SCANCODE_RIGHT]) {
			sp.Center.x += .86f;
		}
		if (gjk_test(&sp, &spp)) {
			S.color = vec3(0, 0, 0);
		}
			
		else
			S.color = vec3(64, 224, 208).normalize();

		scene.render();
		SDL_GL_SwapWindow(window);
		

	}
	return 0;	
}