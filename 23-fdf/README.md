* [intro](#intro)
	* [MiniLibx](#minilibx)
	* [X-Window](#x-window)
	* [Cocoa](#cocoa)
* [Use MLX](#use-mlx)
	* [왜 MLX라이브러리가 생겼을까? 그냥 opengl로 만들면 안되나?](#왜-mlx라이브러리가-생겼을까-그냥-opengl로-만들면-안되나)
	* [Installation](#installation)
	* [1. void *mlx = mlx_init(void)](#1-void-mlx--mlx_initvoid)
	* [2. void	*mlx_win = mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);](#2-voidmlx_win--mlx_new_windowvoid-mlx_ptr-int-size_x-int-size_y-char-title)
	* [3. mlx_loop(mlx);](#3-mlx_loopmlx)
	* [Writing pixel to image](#writing-pixel-to-image)
	* [4. void	*img = mlx_new_image(void *mlx_ptr, int width, int height);](#4-voidimg--mlx_new_imagevoid-mlx_ptr-int-width-int-height)
	* [5. char	*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian);](#5-charmlx_get_data_addrvoid-img_ptr-int-bits_per_pixel-int-size_line-int-endian)
	* [6. 이미지에 픽셀 단위로 칠하는 방법](#6-이미지에-픽셀-단위로-칠하는-방법)
	* [7. int	mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param);](#7-intmlx_hookvoid-win_ptr-int-x_event-int-x_mask-int-funct-void-param)
	* [평가](#평가)

## intro	
### MiniLibx
- tiny graphics library.
- rendering something in screeens without any knowledge of X-Window and Cocoa.

### X-Window
- 주로 유닉스 계열 운영체제에서 사용되는 윈도 시스템 및 X 윈도우 GUI환경
- 기존의 디스플레이 시스템과 다른 점은 `네트워크 프로토콜(X 프로토콜)을 기반`한 `클라이언트와 서버 모델`의 네트워크 지향 윈도 시스템이다. 서로 네트워크로 연결되어 있는 단말기에 접속한 모든 사람은 입력 장치를 통해 컴퓨터를 이용할 수 있다

### Cocoa
-  Cocoa는 크게 `OS X, iOS 애플리케이션을 개발할 때 사용하는 프레임워크를 모두`를 포함하는 개념이다. 작게는  OS X을 개발할 때 사용하는 프레임워크로, `Foundation, Appkit`을 지칭합니다.
	1. AppKit: 사용자 인터페이스를 구성하고 각종 이벤트를 관리하는 응용 프레임워크입니다.
	2. Foundation: Core Service 층에 속하며 Foundation은 원시 데이터 타입(String, Int, Double), 컬렉션 타입(Array, Dictionary, Set) 및 운영체제 서비스를 사용해 애플리케이션의 기본적인 기능을 관리하는 프레임워크입니다.
- 코코아 아키텍처:https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/CocoaFundamentals/WhatIsCocoa/WhatIsCocoa.html

## Use MLX
### 왜 MLX라이브러리가 생겼을까? 그냥 opengl로 만들면 안되나?
- OpenGL 자체가 게임을 비롯한 멀티미디어만을 위한 존재가 아닌만큼 고려해야할 영역이 많은 API.
- 현시점에서 OpenGL의 가장 큰 문제는 드라이버이다. 25년이 넘는 동안 OpenGL 스펙에 추가된 기능들이 엄청나게 많아 드라이버의 복잡도는 상상을 초월하는 수준이다. (https://namu.moe/w/OpenGL)
- OpenGL이 그래픽스 API이고, GLFW는 창을 생성, 제어할 수 있게 하고 OpenGL context를 생성 및 관리한다. `MLX는 opengl과 glfw를 좀 더 쉽게 사용할 수 있는 라이브러리`다.
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

### Installation
- Do mind that you need the `libmlx.dylib in the same directory` as your build target as it is a dynamic library! 

### 1. void *mlx = mlx_init(void)
- return: 
	- success: void *window identifier.
	- fail: void *0.
- callstack
	- mlx_init_swift();
		- MlxMain();
			- init();
			- addWinToList(_ win:MlxWin)
			- addImgToList(_ img:MlxImg)
			- doCallLoopHook()
    	    - createOCallback() -> CFRunLoopObserverCallBack
			- createTCallback() -> CFRunLoopTimerCallBack
			- addLoopHook(_ f:UnsafeMutableRawPointer?, _ p:UnsafeMutableRawPointer)
		- _mlx_bridge_retained();
   			- UnsafeRawPointer(Unmanaged.passRetained(obj).toOpaque())

### 2. void	*mlx_win = mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
- return
	- success: a pointer to the window we have just created.
	- fail: void *0.
- argument
	- @Param1 : mlx_init에서 초기화한 instance
	- @Param2 : width
	- @Param3 : height
	- @param4 : title
- callstack
	- mlx_new_window_swift()
		- let mlx:MlxMain = _mlx_bridge(ptr:mlxptr)
		- let mw = MlxWin(device: mlx.device, width: Int(w), height: Int(h), title: String(cString: t))
		- mw.setNotifs()
		- mw.initMetal()
		- mlx.addWinToList(mw)
		- return (_mlx_bridge_retained(obj:mw))

### 3. mlx_loop(mlx);
- description
	- infinite loop, `waits for an event, and then calls a user-defined function` associated with this event.
	- A single parameter is needed, the connection identifier
- return
	- never returns.
- callstack
	- let mlx:MlxMain = _mlx_bridge(ptr:mlxptr)
	- mlx.inLoop = true
	- NSApp.run() // 코코아 핵심 클래스

### Writing pixel to image
- First of all, we should take into account that the `mlx_pixel_put function is very, very slow.`
- This is because it tries to push the pixel instantly to the window (without waiting for the frame to be entirely rendered)
- we will have to `buffer all of our pixels to a image`, which we will then push to the window

### 4. void	*img = mlx_new_image(void *mlx_ptr, int width, int height);
- description
	- creates a new image in memory
- return
	- success: void *indentifer.
	- fail: void *0.
- callstack
	- let mlx:MlxMain = _mlx_bridge(ptr:mlxptr)
	- let img = MlxImg(d:mlx.device, w:Int(width), h:Int(height))
	- mlx.addImgToList(img)
	- ///	print(CFGetRetainCount(img))
	- return (_mlx_bridge_retained(obj:img))
- Now, we have an image but how exactly `do we write pixels to this?`
- need to `get the memory address` on which we will mutate the bytes accordingly.

### 5. char	*mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian);
```c
typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;
```
```
int	main(void)
{
	void	*mlx;
	t_data	img;

	mlx = mlx_init();
	img.img = mlx_new_image(mlx, 1920, 1080);
	
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
}
```
- returns
	- success: information about the created image, allowing a user to modify it later
- param
	- @img_ptr: specifies the image to use.
	- @bits_per_pixel: will be filled with the number of bits needed to represent a pixel color.
		- 한 픽셀은 일반적으로 1바이트, 각 비트 단위로 투명도/R/G/B 정보
	- @line_length(size_line): is the number of bytes used to store one line of the image in memory. This information is needed to move from one line to another in the image.
		- ex)너비가 1920이라면 가로 줄에 픽셀 1920(픽셀) * 4 = 7680(바이트	)개가 들어간다. 
	- @endian: tells you wether the pixel color in the image needs to be stored in little endian or big endian.
- callstack
	- let img:MlxImg = _mlx_bridge(ptr:imgptr)
	- bpp.pointee = 32
	- sizeline.pointee = Int32(img.texture_sizeline)
	- endian.pointee = Int32(0)
	- return img.texture_data
}

### 6. 이미지에 픽셀 단위로 칠하는 방법 
```
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
```
- (y * data->line_length)는 y좌표를 의미한다.
- 1픽셀은 4바이트, A/R/G/B를 각각 표현하기 위해선 1바이트가 필요. 즉, 1바이트씩 컬러를 찍으며 1픽셀을 완성함. 

### 7. int	mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param);
- description
	- in the same manner mlx_*_hook functions work. The event and mask values will be taken from the X11 include file "X.h"
- callstack
	- let win:MlxWin = _mlx_bridge(ptr:winptr)
	- win.addHook(index: Int(xevent), fct: fctptr, param: paramptr)
	- return (Int32(0));

```c
func addHook(index idx:Int, fct fptr:UnsafeMutableRawPointer?, param pptr:UnsafeMutableRawPointer)
{
	eventFuncts[idx] = fptr;
	eventParams[idx] = pptr;
	if (idx == 6 || idx == 32)
	{
		if (fptr != nil) ///  == nullptr)
		   { self.acceptsMouseMovedEvents = true }
		else { self.acceptsMouseMovedEvents = false }
	}
} ```
- Event functions have a different prototype depending of the hooking event.
	- Hooking event	code	Prototype
```c
Hooking			code	Prototype
ON_KEYDOWN		2		int (*f)(int keycode, void *param)
ON_KEYUP*		3		int (*f)(int keycode, void *param)
ON_MOUSEDOWN*	4		int (*f)(int button, int x, int y, void *param)
ON_MOUSEUP		5		int (*f)(int button, int x, int y, void *param)
ON_MOUSEMOVE	6		int (*f)(int x, int y, void *param)
ON_EXPOSE*		12		int (*f)(void *param)
ON_DESTROY		17		int (*f)(void *param)
```
	- expose_hook, mlx_key_hook, mlx_mouse_hook이 있는데, 실행하는 함수포인터 인덱스만 다르다.
	- 모르는 이벤트가 나왔을 때 [참고](https://tronche.com/gui/x/xlib/events/)

### 키 코드 사진
![1](https://user-images.githubusercontent.com/67992469/197664317-88f181aa-9f5f-4e7a-bc14-f95334251e30.png)
- 참고: https://eastmanreference.com/complete-list-of-applescript-key-codes

## Color
### Encoding and decoding color
- encoding
```c
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
```
	- encoding을 할 때 value의 자료형을 `unsigned int`로 받아야 오버플로우 없이 비트를 온전히 받는다.
 
- decoding
```c
int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}
```

### Char/int conversion
- char는 1byte이므로, 변환 가능
```c
int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

unsigned char	get_t(int trgb)
{
	return (((unsigned char *)&trgb)[3]);
}
```

## 참고자료
- https://bigpel66.oopy.io/library/c/etc/3
- https://harm-smits.github.io/42docs/

### FDF 과제 진행
1. 선을 그리려면 2개의 점이 필요하다.
2. 좌표(x, y, z)에 offset을 적용한다.
	- offset이란 1920이라는 이미지크기에 20개의 점이 있다면그 점 사이의 거리를 의미한다.
3. 3차원 도형을 평면에 나타내기 위해선 `등축투영법`을 쓴다.
	- 등축투영법이란 아랫각이 30의 배수각이라고 한다.
	- 변환 공식을 사용한다.
4. 0,0에 있는 (offset)을 적용한 점에서부터 마지막 점까지 `직선의 방정식 `이 아닌 `브레젠험`알고리즘으로 연결한다.
	- 직선의 방정식은 실수값까지 표현하므로 연산량이 많고, 부드럽게 보인다. 반면 브레젠험은 임의의 점을 직선의 기울기에 맞춰서 대략적으로 표현하므로 점들이 매끈하게 이어지지는 않지만, 빠르다는 장점이 있다.

### FDF 과제를 진행하면서 매끈하게 이어지지 않았던 부분
1. 수학 공식
	1. 등축투영법으로 표현
```c
*x = prev_x * cos(M_PI / 60 * 4) - prev_y * cos(M_PI / 60 * 4);
*y = prev_x * sin(M_PI / 60 * 4) + prev_y * sin(M_PI / 60 * 4) - *z;
```
		- 공식이 무엇을 의미하는지는 알겠지만, 이 식의 유도 과정은 모르겠다..
		- x축, y축, z축을 등각투영(30도의 배수)각도로 회전변환 한 것이다.
	2. 브레젠험 알고리즘 중 임의의 점을 선택해 직선의 기울기로 대략적으로 맞추는 과정
```c
void	plot_line(t_point *start, t_point *end, t_tool *tool)
{
	t_point	delta;
	t_point	*cur;
	t_point	step;
	int		error[2];

	init_delta_step(&delta, start, end, &step);
	error[0] = delta.x + delta.y; // x의 변화량과 y의 변화량을 왜 더하는가?
	cur = start;
	while (!(cur->x == end->x && cur->y == end->y))
	{
		my_mlx_pixel_put(cur, tool);
		error[1] = 2 * error[0]; 
		if (error[1] >= delta.y) 
		{
			error[0] += delta.y;
			cur->x += step.x;
		}
		if (error[1] <= delta.x)
		{
			error[0] += delta.x;
			cur->y += step.y;
		}
	}
	free(start);
	free(end);
}
``` 
	- 다음에 찍어야 할 점의 좌표를 구할 때,
		- `x의 변화량과 y의 변화량을 합한 값을 2배한 값`이 `y의 변화량`보다 크다면 error[0]에 delta.y를 더해주는 작업이 잘 이해가 가지 않음.
```c
약 2주 안되게 걸린거 같은데, 혼자 했으면 
아마 한 달 이상은 잡지 않았을까
점을 찍고, offset을 적용해서 길게 늘이고,
식을 적용하고, 이해하는 데 있어 팀원들의 도움이 굉장히 컸음.
```

### 평가
- open을 열고, close를 하지 않았다. 꼭 세트로 적어두기.
- 인자가 2개이고 이름이 잘못 되었을 때는 perror()에 의해 errno(no such file...)가 설정된다. 그런데, 인자가 2개이고 이름에 디렉토리만 적어둔다면(ex: ./test_maps/ `segmentation fault`가 나온다.
