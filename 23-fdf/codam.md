## 왜 MLX라이브러리가 생겼을까? 그냥 opengl로 만들면 안되나?
- OpenGL 자체가 게임을 비롯한 멀티미디어만을 위한 존재가 아닌만큼 고려해야할 영역이 많은 API.
- 현시점에서 OpenGL의 가장 큰 문제는 드라이버이다. 25년이 넘는 동안 OpenGL 스펙에 추가된 기능들이 엄청나게 많아 드라이버의 복잡도는 상상을 초월하는 수준이다. (https://namu.moe/w/OpenGL)
- OpenGL이 그래픽스 API이고, GLFW는 창을 생성, 제어할 수 있게 하고 OpenGL context를 생성 및 관리할 수 한다. `MLX는 opengl과 glfw를 좀 더 쉽게 사용할 수 있는 라이브러리`다.
```
- OpenGL은 API 규격으로 라이브러리가 아닌 문서이다.
- OpenGL은 그래픽 처리 장치 제조업체에서 구현 후
그래픽 카드에 드라이버와 함께 제공한다.
- 우리는 이 구현된 코드들을 라이브러리처럼 가져다 사용한다.
- OpenGL은 크게 두 가지 기능으로 분류된다.
	- GL : 가장 기본적인 그리기 기능을 제공하는 
	핵심 라이브러리이며 OpenGL의 본체에 해당한다. 
	기초 도형을 랜더링하는 함수들이 포함되어 있다.
	
	- GLU : GL의 도우미 역할을 하는 유틸리티 라이브러리이다.
	분할, 투영 등의 고급 기능을 제공하며 원구나 원뿔, 원기둥 등
	테스트 입체 도형을 생성하는 편의 기능도 제공한다.
```
https://kyoungwhankim.github.io/ko/blog/opengl_intro/
https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=tlqor123&logNo=220359144262

## MLX basic function
### 1. mlx_set_setting(MLX_MAXIMIZED, true);
- mlx_init()을 실행하기 전에 이미지를 그리거나 파일을 열 수 있다.
- 창을 띄우지 않고 실행하는 기능, 런타임 동안 작동방식을 바꿀 수 있는 기능 제공(MLX_STRETCH_IMAGE)
```c
typedef enum mlx_settings
{
	MLX_STRETCH_IMAGE = 0,	// Should images resize with the window as its being resized or not. Default: false MLX_FULLSCREEN,			// Should the window be in Fullscreen, note it will fullscreen at the given resolution. Default: false
	MLX_MAXIMIZED,			// Start the window in a maximized state, overwrites the fullscreen state if this is true. Default: false
	MLX_DECORATED,			// Have the window be decorated with a window bar. Default: true
	MLX_HEADLESS,			// Run in headless mode, no window is created. (NOTE: Still requires some form of window manager such as xvfb)
	MLX_SETTINGS_MAX,		// Setting count.
}	mlx_settings_t;

void mlx_set_setting(mlx_settings_t setting, int32_t value)
{
	MLX_ASSERT(setting >= 0 && setting < MLX_SETTINGS_MAX, "Invalid settings value");
	mlx_settings[setting] = value;
}
```

### 2. mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
- mlx_init()은 기본적으로 창에 관한 중요한 정보를 저장하는 핸들.
```c
typedef struct mlx
{
	void*		window;
	void*		context;
	int32_t		width;
	int32_t		height;
	double		delta_time;
}	mlx_t;
```
```c
mlx_t* mlx_init(int32_t width, int32_t height, const char* title, bool resize)
{
	MLX_ASSERT(width > 0, "Window width must be positive");
MLX_ASSERT(height > 0, "Window height must be positive");
	MLX_ASSERT(title, "Window title can't be null");

	bool init;
	mlx_t* mlx;
	if (!(init = glfwInit()))
		return ((void*)mlx_error(MLX_GLFWFAIL));
	if (!(mlx = calloc(1, sizeof(mlx_t))))
		return ((void*)mlx_error(MLX_MEMFAIL));
	if (!(mlx->context = calloc(1, sizeof(mlx_ctx_t))))
		return (free(mlx), (void*)mlx_error(MLX_MEMFAIL));

	mlx_ctx_t* const mlxctx = mlx->context;
	mlx->width = width;
	mlx->height = height;
	mlxctx->initialWidth = width;
	mlxctx->initialHeight = height;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_MAXIMIZED, mlx_settings[MLX_MAXIMIZED]);
	glfwWindowHint(GLFW_DECORATED, mlx_settings[MLX_DECORATED]);
	glfwWindowHint(GLFW_VISIBLE, !mlx_settings[MLX_HEADLESS]);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	glfwWindowHint(GLFW_RESIZABLE, resize);
	if (!(mlx->window = glfwCreateWindow(width, height, title, mlx_settings[MLX_FULLSCREEN] ? glfwGetPrimaryMonitor() : NULL, NULL)))
		return (mlx_terminate(mlx), (void*)mlx_error(MLX_WINFAIL));
	if (!mlx_init_render(mlx) || !mlx_create_buffers(mlx))
		return (mlx_terminate(mlx), NULL);
	return (mlx);
}
```

### 3. mlx_image_t* img = mlx_new_image(mlx, 256, 256);
- Draws a new instance of an image, it will then share the same pixel buffer as the image.
	* @param[in] mlx The MLX instance handle.
	* @param[in] img The image to draw onto the screen.
	* @param[in] x The X position.
	* @param[in] y The Y position.
```c
mlx_image_t* mlx_new_image(mlx_t* mlx, uint32_t width, uint32_t height)
{
	MLX_NONNULL(mlx); //assert

	if (!width || !height || width > INT16_MAX || height > INT16_MAX)
		return ((void*)mlx_error(MLX_INVDIM));

	const mlx_ctx_t* mlxctx = mlx->context;
	mlx_image_t* newimg = calloc(1, sizeof(mlx_image_t));
	mlx_image_ctx_t* newctx = calloc(1, sizeof(mlx_image_ctx_t));
	if (!newimg || !newctx)
	{
		mlx_freen(2, newimg, newctx); //free
		return ((void *)mlx_error(MLX_MEMFAIL));
	}
	newimg->enabled = true;
	newimg->context = newctx;
	(*(uint32_t*)&newimg->width) = width;
	(*(uint32_t*)&newimg->height) = height;
	if (!(newimg->pixels = calloc(width * height, sizeof(int32_t))))
	{
		mlx_freen(2, newimg, newctx);
		return ((void *)mlx_error(MLX_MEMFAIL));
	}

	mlx_list_t* newentry;
	if (!(newentry = mlx_lstnew(newimg)))
	{
		mlx_freen(3, newimg->pixels, newimg->context, newimg);
		return ((void *)mlx_error(MLX_MEMFAIL));
	}
	// Generate OpenGL texture
	glGenTextures(1, &newctx->texture);
	glBindTexture(GL_TEXTURE_2D, newctx->texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	mlx_lstadd_front((mlx_list_t**)(&mlxctx->images), newentry);
	return (newimg);
}
```

### 4. mlx_put_pixel(img, 0, 0, 0xFF0000FF);
- Sets / puts a pixel onto an image.
	* @param[in] image The MLX instance handle.
	* @param[in] x The X coordinate position.
	* @param[in] y The Y coordinate position.
	* @param[in] color The color value to put.
```c
void mlx_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	MLX_NONNULL(image);
	MLX_ASSERT(x < image->width, "Pixel is out of bounds");
	MLX_ASSERT(y < image->height, "Pixel is out of bounds");

	uint8_t* pixelstart = &image->pixels[(y * image->width + x) * BPP];
	mlx_draw_pixel(pixelstart, color);
}
```
```c
void mlx_draw_pixel(uint8_t* pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}
```

### 5. 	mlx_loop_hook(mlx, ft_hook, mlx);
- Generic loop hook for any custom hooks to add to the main loop.
- Executes a function per frame, so be careful.
	* @param[in] mlx The MLX instance handle.
	* @param[in] f The function.
	* @param[in] param The parameter to pass onto the function.
	* @returns Wether the hook was added successfuly.
```c
bool mlx_loop_hook(mlx_t* mlx, void (*f)(void*), void* param)
{
	MLX_ASSERT(mlx, "Parameter can't be null");
	MLX_ASSERT(f, "Parameter can't be null");

	mlx_hook_t* hook;
	if (!(hook = malloc(sizeof(mlx_hook_t))))
		return (mlx_error(MLX_MEMFAIL));

	mlx_list_t* lst;
	if (!(lst = mlx_lstnew(hook)))
	{
		free(hook);
		return (mlx_error(MLX_MEMFAIL));
	}
	hook->func = f;
	hook->param = param;
	const mlx_ctx_t	*mlxctx = mlx->context;
	mlx_lstadd_back((mlx_list_t**)(&mlxctx->hooks), lst);
	return (true);
}
```

### 6. 	mlx_loop(mlx);
- Initializes the rendering of MLX, this function won't return until mlx_close_window is called.
- meaning it will loop until the user requests that the window should close.
	* @param[in] mlx The MLX instance handle.
```c
void mlx_loop(mlx_t* mlx)
{
	MLX_ASSERT(mlx, "Parameter can't be null");

	double start, oldstart = 0;
	while (!glfwWindowShouldClose(mlx->window))
	{
		start = glfwGetTime();
		mlx->delta_time = start - oldstart;
		oldstart = start;

		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwGetWindowSize(mlx->window, &(mlx->width), &(mlx->height));

		if ((mlx->width > 1 || mlx->height > 1))
			mlx_update_matrix(mlx, mlx->width, mlx->height); // 이미지를 늘리는 설정이 있으면, 적용

		mlx_exec_loop_hooks(mlx);
		mlx_render_images(mlx);
		mlx_flush_batch(mlx->context);

		glfwSwapBuffers(mlx->window);
		glfwPollEvents();
	}
}
```
```c
void mlx_update_matrix(const mlx_t* mlx, int32_t width, int32_t height)
{
	const mlx_ctx_t* mlxctx = mlx->context;
	const float depth = mlxctx->zdepth;

	/**
	 * Incase the setting to stretch the image is set, we maintain the width and height but not
	 * the depth.
	 */
	width = mlx_settings[MLX_STRETCH_IMAGE] ? mlxctx->initialWidth : mlx->width;
	height = mlx_settings[MLX_STRETCH_IMAGE] ? mlxctx->initialHeight : mlx->height;

	const float matrix[16] = {
		2.f / width, 0, 0, 0,
		0, 2.f / -(height), 0, 0,
		0, 0, -2.f / (depth - -depth), 0,
		-1, -(height / -height),
		-((depth + -depth) / (depth - -depth)), 1
	};

	glUniformMatrix4fv(glGetUniformLocation(mlxctx->shaderprogram, "ProjMatrix"), 1, GL_FALSE, matrix);
}
```

```c
static void mlx_exec_loop_hooks(mlx_t* mlx)
{
	const mlx_ctx_t* mlxctx = mlx->context;

	mlx_list_t* lstcpy = mlxctx->hooks;
	while (lstcpy && !glfwWindowShouldClose(mlx->window))
	{
		mlx_hook_t* hook = ((mlx_hook_t*)lstcpy->content);
		hook->func(hook->param);
		lstcpy = lstcpy->next;
	}
}
```

```c
static void mlx_render_images(mlx_t* mlx)
{
	mlx_ctx_t* mlxctx = mlx->context;
	mlx_list_t* imglst = mlxctx->images;

	if (sort_queue)
	{
		sort_queue = false;
		mlx_sort_renderqueue(&mlxctx->render_queue);
	}

	// Upload image textures to GPU
	while (imglst)
	{
		mlx_image_t* image;
		if (!(image = imglst->content))
			return ((void)mlx_error(MLX_INVIMG));
		glBindTexture(GL_TEXTURE_2D, ((mlx_image_ctx_t*)image->context)->texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
		imglst = imglst->next;
	}

	// Execute draw calls
	mlx_list_t* render_queue = mlxctx->render_queue;
	while (render_queue)
	{
		draw_queue_t* drawcall = render_queue->content;
		mlx_instance_t* instance =  &drawcall->image->instances[drawcall->instanceid];

		if (drawcall && drawcall->image->enabled && instance->enabled)
			mlx_draw_instance(mlx->context, drawcall->image, instance);
		render_queue = render_queue->next;
	}
}
```

```c
void mlx_draw_instance(mlx_ctx_t* mlx, mlx_image_t* img, mlx_instance_t* instance)
{
	float w = (float) img->width;
	float h = (float) img->height;
	float x = (float) instance->x;
	float y = (float) instance->y;
	float z = (float) instance->z;
	int8_t tex = mlx_bind_texture(mlx, img);

	vertex_t vertices[6] = {
			(vertex_t){x, y, z, 0.f, 0.f, tex},
			(vertex_t){x + w, y + h, z, 1.f, 1.f, tex},
			(vertex_t){x + w, y, z, 1.f, 0.f, tex},
			(vertex_t){x, y, z, 0.f, 0.f, tex},
			(vertex_t){x, y + h, z, 0.f, 1.f, tex},
			(vertex_t){x + w, y + h, z, 1.f, 1.f, tex},
	};
	memmove(mlx->batch_vertices + mlx->batch_size, vertices, sizeof(vertices));
	mlx->batch_size += 6;

	if (mlx->batch_size >= MLX_BATCH_SIZE)
		mlx_flush_batch(mlx);
}
```

```c
void mlx_flush_batch(mlx_ctx_t* mlx)
{
	if (mlx->batch_size <= 0)
		return;

	glBindBuffer(GL_ARRAY_BUFFER, mlx->vbo);
	glBufferData(GL_ARRAY_BUFFER, mlx->batch_size * sizeof(vertex_t), mlx->batch_vertices, GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, mlx->batch_size);

	mlx->batch_size = 0;
	memset(mlx->bound_textures, 0, sizeof(mlx->bound_textures));
}
```

### 7. 	mlx_terminate(mlx);
- All of glfw & glads resources are cleaned up by the terminate function.

```c
void mlx_terminate(mlx_t* mlx)
{
	MLX_NONNULL(mlx);

	mlx_ctx_t *const mlxctx = mlx->context;

	glfwTerminate();
	mlx_lstclear((mlx_list_t**)(&mlxctx->hooks), &free);
	mlx_lstclear((mlx_list_t**)(&mlxctx->render_queue), &free);
	mlx_lstclear((mlx_list_t**)(&mlxctx->images), &mlx_free_image);
	mlx_freen(2, mlxctx, mlx);
}
```

## MLX color
## Color
- A common color model is `RGBA`, which MLX uses for storing and displaying images.
- Colors are commonly represented `as 4-byte integers`. 
- This 4-byte integer is a grouping of four individual channels: `red, green, blue and alpha`
- with `alpha representing transparency`. Additionally, colors are usually shown in `hexadecimal` to make each channel value identifiable:
