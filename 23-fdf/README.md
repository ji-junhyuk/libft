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

## Basic
### Installation
- Do mind that you need the libmlx.dylib in the same directory as your build target as it is a dynamic library! 
### 1. void *mlx = mlx_init(void)
- return : connection to the correct graphical system and will return a void * which holds the location of our current MLX instance.

### 2. void	*mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");;
- return : a pointer to the window we have just created.
	- @Param1 : mlx_init에서 초기화한 instance
	- @Param2 : width
	- @Param3 : height
	- @param4 : title
```c
public func mlx_init_swift() -> UnsafeRawPointer
{
	let mm = MlxMain()
	return (_mlx_bridge_retained(obj:mm))
}
```
```swift
public class MlxMain {

      public var winList = [MlxWin]()
      public var imgList = [MlxImg]()
      var myMlxApp:NSApplication?
      public var device:MTLDevice!
      var loopHook:UnsafeMutableRawPointer?
      var loopParam:UnsafeMutableRawPointer
      var loopHookTimer:CFRunLoopTimer?
      public var inLoop = false

      public init(_ flag:Int = 0)
      {
	/// make app with top menubar
        myMlxApp = NSApplication.shared
	if (flag == 1)
	{
		NSApp.setActivationPolicy(NSApplication.ActivationPolicy.prohibited)   /// for non clickable win, no top menu
	}
	else
	{
		NSApp.setActivationPolicy(NSApplication.ActivationPolicy.regular)
	}

	device = MTLCreateSystemDefaultDevice()!
	loopParam = UnsafeMutableRawPointer(bitPattern:1)! /// set to 1-1
	loopParam -= 1

	/// Add observer anyway to flush pixels every loop. If loop_hook exists, call it.
        var ocontext = CFRunLoopObserverContext(version:0, info:_mlx_bridge(obj:self), retain:nil, release:nil, copyDescription:nil)
	let observer = CFRunLoopObserverCreate(kCFAllocatorDefault, CFRunLoopActivity.beforeWaiting.rawValue, true, 0, createOCallback(), &ocontext)
	CFRunLoopAddObserver(CFRunLoopGetMain(), observer, CFRunLoopMode.commonModes)

      }

      public func addWinToList(_ win:MlxWin)
      { winList.append(win) }
      public func addImgToList(_ img:MlxImg)
      { imgList.append(img) }


    func doCallLoopHook()
    {
///	if (loopHook != nil)
///	{
	   _ = (unsafeBitCast(loopHook!,to:(@convention(c)(UnsafeRawPointer)->Void).self))(loopParam)
///	}
    }

    func createOCallback() -> CFRunLoopObserverCallBack
    {
        return { (cfRunloopObserver, cfrunloopactivity, info) -> Void in
	    let mlx:MlxMain = _mlx_bridge(ptr:info!)
	    mlx.winList.forEach { $0.flushImages() }
///         mlx.doCallLoopHook()
        }
    }

    func createTCallback() -> CFRunLoopTimerCallBack
    {
        return { (cfRunloopTimer, info) -> Void in
	    let mlx:MlxMain = _mlx_bridge(ptr:info!)
            mlx.doCallLoopHook()
        }
    }

    public func addLoopHook(_ f:UnsafeMutableRawPointer?, _ p:UnsafeMutableRawPointer)
      {
        var tcontext = CFRunLoopTimerContext(version:0, info:_mlx_bridge(obj:self), retain:nil, release:nil, copyDescription:nil)
	if (loopHook != nil)
	{
		CFRunLoopTimerInvalidate(loopHookTimer)
	}

	loopHook = f
	loopParam = p
	if (loopHook != nil)
	{
	   loopHookTimer = CFRunLoopTimerCreate(kCFAllocatorDefault, 0.0, 0.0001, 0, 0, createTCallback(), &tcontext)
	   CFRunLoopAddTimer(CFRunLoopGetMain(), loopHookTimer, CFRunLoopMode.commonModes)
	}
      }
```
```swift
func _mlx_bridge_retained<T : AnyObject>(obj : T) -> UnsafeRawPointer {
    return UnsafeRawPointer(Unmanaged.passRetained(obj).toOpaque())
}
```


### 3. mlx_loop(mlx);
- initiate the window rendering
```c
@_cdecl("mlx_loop")
public func mlx_loop_swift(_ mlxptr:UnsafeRawPointer)
{
	let mlx:MlxMain = _mlx_bridge(ptr:mlxptr)
	mlx.inLoop = true
        NSApp.run()
}
```
```swift
func _mlx_bridge<T : AnyObject>(ptr : UnsafeRawPointer) -> T {
    return Unmanaged<T>.fromOpaque(ptr).takeUnretainedValue()
}
```

### Writing pixel to image
- First of all, we should take into account that the `mlx_pixel_put function is very, very slow.`
- This is because it tries to push the pixel instantly to the window (without waiting for the frame to be entirely rendered)
- we will have to buffer all of our pixels to a image, which we will then push to the window

### 4. void	*img = mlx_new_image(mlx, 1920, 1080);
- initialize the image
- Now, we have an image but how exactly `do we write pixels to this?`
- need to `get the memory address` on which we will mutate the bytes accordingly.
```
@_cdecl("mlx_new_image")
public func mlx_new_image(_ mlxptr:UnsafeRawPointer, _ width:Int32, _ height:Int32) -> UnsafeRawPointer
{
	let mlx:MlxMain = _mlx_bridge(ptr:mlxptr)
	let img = MlxImg(d:mlx.device, w:Int(width), h:Int(height))
	mlx.addImgToList(img)
///	print(CFGetRetainCount(img))
	return (_mlx_bridge_retained(obj:img))
}
```

### get the memory address
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
- 바이트 주소를 변환하는 것
	- 너비가 1920이라는 것은 가로 줄에 픽셀 1920개가 들어간다는 뜻.
	- 한 픽셀은 일반적으로 1바이트로서 각 비트 단위로 투명도/RED/GREEN/BLUE 정보를 표시
	- mlx_get_data_addr로 인해 line_length에 1920 * 4 = 7680 가로 줄 총 바이트수가 나오게 된다.
```c
@_cdecl("mlx_get_data_addr")
public func mlx_get_data_addr_swift(_ imgptr:UnsafeRawPointer, _ bpp:UnsafeMutablePointer<Int32>, _ sizeline:UnsafeMutablePointer<Int32>, _ endian:UnsafeMutablePointer<Int32>) -> UnsafeMutablePointer<UInt32>
{
	let img:MlxImg = _mlx_bridge(ptr:imgptr)
	bpp.pointee = 32
	sizeline.pointee = Int32(img.texture_sizeline)
	endian.pointee = Int32(0)
	return img.texture_data
}
```

### 5. 이미지에 픽셀 단위로 칠하는 방법 
```
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
```
- (y * data->line_length)는 y좌표를 의미한다.
- 한 픽셀은 4비트로 표현하므로, (x * (data->bits_per_pixel(32) / 8))  한 픽셀만큼 접근하는 식이다.

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

## event
- 모르는 이벤트가 나왔을 때 [참고](https://tronche.com/gui/x/xlib/events/)

### mlx_hook
```swift
@_cdecl("mlx_hook")
public func mlx_hook_swift(_ winptr:UnsafeRawPointer, _ xevent:Int32, _ xmask:Int32, _ fctptr:UnsafeMutableRawPointer, _ paramptr:UnsafeMutableRawPointer) -> Int32
{
        let win:MlxWin = _mlx_bridge(ptr:winptr)
        win.addHook(index: Int(xevent), fct: fctptr, param: paramptr)
        return (Int32(0));
}
```
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
}
```
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
