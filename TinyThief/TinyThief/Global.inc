
;----------------------------------------------------------------

;EQU 定义

;----------------------------------------------------------------
IMG_0					equ		30
IMG_1					equ		1
IMG_2					equ		2

IMG_400				equ		3
IMG_401				equ		4
IMG_402				equ		5
IMG_403				equ		6
IMG_404				equ		7
IMG_405				equ		8
IMG_406				equ		9
IMG_407				equ		10
IMG_408				equ		11
IMG_409				equ		12
IMG_410				equ		13
IMG_411				equ		14
IMG_412				equ		15
IMG_413				equ		16
IMG_414				equ		17
IMG_415				equ		18
IMG_416				equ		19
IMG_417				equ		20
IMG_418				equ		21
IMG_419				equ		22
IMG_42001			equ		23
IMG_42002			equ		24
IMG_42101			equ		25
IMG_42102			equ		26
IMG_42103			equ		27
IMG_42104			equ		28
IMG_422				equ		29

;窗体大小
SCREEN_X EQU 820
SCREEN_Y EQU 642
;----------------------------------------------------------------

;结构体 定义

;----------------------------------------------------------------
MyItem STRUCT
	iwidth	dd	0
	iheight	dd	0
	x1			dd	0
	y1			dd	0
	x2			dd	0
	y2			dd	0
	pMethod		BYTE	0	;绘制方法,0使用DrawObject,1使用DrawTransparentObject
	eClick			BYTE 0	;是否有鼠标事件，0没有，1有
MyItem ends
;！！！！！！undone！！！！！！！！
;----------------------------------------------------------------

;数据段

;----------------------------------------------------------------


.data
	;窗口绘制的参数
	hInstance					dd		?
	hWinMain					dd		?
	hMenu						dd		?
	;hSubMenu				dd		?
	hdc							dd		?
	hdcImage					dd		?
	hdcMem					dd		?
	bmp							HBITMAP	?

	;播放音乐所需的参数
    Mp3Device				db			"MPEGVideo",0
    Mp3DeviceID			dd			0
	MusicName				db			"he is a pirate.mp3",0
	;控制型全局变量
	cClick						BYTE			1								;判断是否要响应接下来的鼠标事件
	pThief						BYTE			1								;判断是否要绘制Thief
	;数据型全局变量
	Scenario					dd			0								;当前场景
	Thief_X						dd			100							;Thief横坐标
	Thief_Y						dd			510							;Thief纵坐标
	Click_X						dd			100							;鼠标点击点的横坐标
	Click_Y						dd			510							;鼠标点击点的纵坐标
	Orientation				BYTE	0										;Thief朝向,0代表向右,1代表朝左
	Run							BYTE	0										;Thief状态,0代表站立,1代表运动
	PassBy						dd			-1								;路过的提示
	pSequence				dd			20		DUP(-1)		;需要绘制的物体序号数组
	pSequenceLength		dd			0
	ItemList					MyItem	100		DUP(<>)		;物体数组
	drawIcon					dd			IMG_415, IMG_416, IMG_417, IMG_418, IMG_419
	correctOrder			dd			IMG_415, IMG_416, IMG_417, IMG_418, IMG_419
	player						dd			5 DUP (?)
	step							dd			0
	
.const
	szClassName			db			"TinyThiefClass", 0
	szCaptionMain			db			"TinyThief", 0
	szText						db			"这是一个有趣的游戏!", 0
	szMenuHelp				db			"帮助", 0
	szCaption					db			"Hello", 0

.code

	InitItem proc id:DWORD, iwidth:DWORD, iheight:DWORD, x1:DWORD, y1:DWORD, x2:DWORD, y2:DWORD, pMethod:BYTE, eClick:BYTE

		mov eax, id
		mov ebx, TYPE MyItem
		mul ebx
		mov ecx, iwidth
		mov (MyItem PTR ItemList[eax]).iwidth, ecx
		mov ecx, iheight
		mov (MyItem PTR ItemList[eax]).iheight, ecx
		mov ecx, x1
		mov (MyItem PTR ItemList[eax]).x1, ecx
		mov ecx, y1
		mov (MyItem PTR ItemList[eax]).y1, ecx
		mov ecx, x2
		mov (MyItem PTR ItemList[eax]).x2, ecx
		mov ecx, y2
		mov (MyItem PTR ItemList[eax]).y2, ecx
		mov cl, pMethod
		mov (MyItem PTR ItemList[eax]).pMethod, cl
		mov cl, eClick
		mov (MyItem PTR ItemList[eax]).eClick, cl
	
		ret

	InitItem endp

	InitItemList proc

		INVOKE InitItem, IMG_401, 65, 143, 194, 43, 259, 96, 0, 1
		INVOKE InitItem, IMG_402, 65, 143, 194, 43, 259, 96, 0, 1
		INVOKE InitItem, IMG_403, 65, 143, 309, 39, 374, 93, 0, 1
		INVOKE InitItem, IMG_404, 65, 143, 658, 39, 723, 93, 0, 1
		INVOKE InitItem, IMG_405, 65, 143, 79, 185, 144, 240, 0, 1
		INVOKE InitItem, IMG_406, 65 ,143, 197, 185, 262, 236, 0, 1
		INVOKE InitItem, IMG_407, 65, 143, 368, 229, 433, 282, 1, 1
		INVOKE InitItem, IMG_408, 65, 143 ,545, 183, 610, 235, 0, 1
		INVOKE InitItem, IMG_409, 65, 143, 660, 181, 725, 235, 0, 1
		INVOKE InitItem, IMG_410, 65, 143, 92, 404, 157, 457, 0, 1
		INVOKE InitItem, IMG_411, 65, 143, 214, 405, 279, 457, 0, 1
		INVOKE InitItem, IMG_412, 65, 143, 424, 401, 489, 454, 0, 1
		INVOKE InitItem, IMG_413, 65, 143, 536, 398, 601, 454, 0, 1
		INVOKE InitItem, IMG_414, 65, 143, 652, 399, 717, 451, 0, 1
		INVOKE InitItem, IMG_415, 65, 44, 383, 216, 448, 260, 0, 1
		INVOKE InitItem, IMG_416, 65, 44, 277, 397, 342, 441, 0, 1
		INVOKE InitItem, IMG_417, 65, 44, 637, 359, 702, 403, 0, 1
		INVOKE InitItem, IMG_418, 65, 44, 114, 359, 179, 403, 0, 1
		INVOKE InitItem, IMG_419, 65, 44, 292, 283, 357, 327, 0, 1
		INVOKE InitItem, IMG_42001, 61, 91, 493, 73, 554, 126, 0, 1
		INVOKE InitItem, IMG_42002, 61, 91, 493, 73, 554, 126, 0, 0
		INVOKE InitItem, IMG_42101, 62, 109, 319, 438, 381, 491, 0, 0
		INVOKE InitItem, IMG_42102, 62, 109, 319, 438, 381, 491, 0, 1
		INVOKE InitItem, IMG_42103, 62, 109, 319, 438, 381, 491, 0, 0
		INVOKE InitItem, IMG_42104, 62, 109, 319, 438, 381, 491, 0, 0
		INVOKE InitItem, IMG_422, 43, 42, 749, 547, 792, 0, 0, 0
	
		ret

	InitItemList endp