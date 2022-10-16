## MLX
### 왜 MLX라이브러리가 생겼을까? 그냥 opengl로 만들면 안되나?
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

### 1. mlx_set_setting(MLX_MAXIMIZED, true);
- mlx_init()을 실행하기 전에 이미지를 그리거나 파일을 열 수 있다.
- 창을 띄우지 않고 실행하는 기능, 런타임 동안 작동방식을 바꿀 수 있는 기능 제공(MLX_STRETCH_IMAGE)
```c
typedef enum mlx_settings
{ MLX_STRETCH_IMAGE = 0,	// Should images resize with the window as its being resized or not. Default: false MLX_FULLSCREEN,			// Should the window be in Fullscreen, note it will fullscreen at the given resolution. Default: false
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
