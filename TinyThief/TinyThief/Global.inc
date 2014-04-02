
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

IMG_300				equ		31
IMG_301				equ		32
IMG_30201			equ		33
IMG_30202			equ		34
IMG_30301			equ		35
IMG_30302			equ		36
IMG_30401			equ		37
IMG_30402			equ		38
IMG_305				equ		39
IMG_30601			equ		40
IMG_30602			equ		41
IMG_30701			equ		42
IMG_30702			equ		43

IMG_500				equ		44
IMG_501				equ		45
IMG_5020101		equ		46
IMG_5020102		equ		47
IMG_5020103		equ		48
IMG_5020104		equ		49
IMG_5020201		equ		50
IMG_5020202		equ		51
IMG_5020203		equ		52
IMG_5020204		equ		53
IMG_5020301		equ		54
IMG_5020302		equ		55
IMG_5020303		equ		56
IMG_5020304		equ		57
IMG_503				equ		58
IMG_504				equ		59
IMG_505				equ		60
IMG_506				equ		61
IMG_507				equ		62
IMG_50801			equ		63
IMG_50802			equ		64
IMG_50901			equ		65
IMG_50902			equ		66
IMG_50903			equ		67
IMG_50904			equ		68
IMG_50905			equ		69
IMG_50906			equ		70
IMG_510				equ		71

;窗体大小
SCREEN_X EQU 820
SCREEN_Y EQU 642
;----------------------------------------------------------------

;结构体 定义

;----------------------------------------------------------------
MyItem STRUCT
	img			dd	0
	iwidth		dd	0
	iheight		dd	0
	x1			dd	0
	y1			dd	0
	x2			dd	0
	y2			dd	0
	pMethod		BYTE	0	;绘制方法,0使用DrawObject,1使用DrawTransparentObject
	eClick			BYTE 0	;是否有鼠标事件，0没有，1有
MyItem ends
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
	isStopped					BYTE			0
	;数据型全局变量
	Scenario					dd			0								;当前场景
	Thief_X						dd			136							;Thief横坐标
	Thief_Y						dd			510							;Thief纵坐标
	Click_X						dd			136							;鼠标点击点的横坐标
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
	step							dd			0						;五个icon的点击步骤
	PPTstatus					dd			0							;需要播放PPT的状态
	Apple						BYTE			0						;是否收集到了苹果
	AppleShow					BYTE			0						;是否已画出苹果
	Banana						BYTE			0						;是否收集到了香蕉
	Pear						BYTE			0						;是否收集到了梨子
	Dog							BYTE			0						;是否收集到了狗？水獭？狐狸？
	Triangle					BYTE			0						;当前是否拿到了三角
	Cross						BYTE			0						;当前是否拿到了十字
	Circle						BYTE			0						;当前是否拿到了圆
	doorNo						BYTE			0						;场景三打开的门序号，0表示全关
	doorOpen					BYTE			0						;场景三的上侧阻挡门是否已经打开
	Thief_right_s_img		dd			0
	Thief_left_s_img		dd			0
	Thief_right_r_img		dd			0
	Thief_left_r_img		dd			0
	
.const
	szClassName			db			"TinyThiefClass", 0
	szCaptionMain			db			"TinyThief", 0
	szText						db			"这是一个有趣的游戏!", 0
	szMenuHelp				db			"帮助", 0
	szCaption					db			"Hello", 0

.code

	InitItem proc id:DWORD, iwidth:DWORD, iheight:DWORD, x1:DWORD, y1:DWORD, x2:DWORD, y2:DWORD, pMethod:BYTE, eClick:BYTE
		local count:DWORD

		mov eax, id
		mov ebx, TYPE MyItem
		mul ebx
		mov count, eax
		INVOKE LoadBitmap, hInstance, id
		mov ecx, count
		mov (MyItem PTR ItemList[ecx]).img, eax
		mov ebx, iwidth
		mov (MyItem PTR ItemList[ecx]).iwidth, ebx
		mov ebx, iheight
		mov (MyItem PTR ItemList[ecx]).iheight, ebx
		mov ebx, x1
		mov (MyItem PTR ItemList[ecx]).x1, ebx
		mov ebx, y1
		mov (MyItem PTR ItemList[ecx]).y1, ebx
		mov ebx, x2
		mov (MyItem PTR ItemList[ecx]).x2, ebx
		mov ebx, y2
		mov (MyItem PTR ItemList[ecx]).y2, ebx
		mov bl, pMethod
		mov (MyItem PTR ItemList[ecx]).pMethod, bl
		mov bl, eClick
		mov (MyItem PTR ItemList[ecx]).eClick, bl
	
		ret

	InitItem endp

	InitItemList proc
	
		INVOKE InitItem, IMG_0, 0, 0, 0, 0, 0, 0, 0, 1
		INVOKE InitItem, IMG_1, 0, 0, 0, 0, 0, 0, 0, 1
		INVOKE InitItem, IMG_2, 0, 0, 0, 0, 0, 0, 0, 1
		INVOKE InitItem, IMG_300, 0, 0, 0, 0, 0, 0, 0, 0
		
		INVOKE InitItem, IMG_400, 0, 0, 0, 0, 0, 0, 0, 1
		INVOKE InitItem, IMG_401, 65, 143, 74, 43, 139, 96, 0, 1
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

		INVOKE InitItem, IMG_301, 93, 101, 45, 61, 138, 162, 0, 0
		INVOKE InitItem, IMG_30201, 105, 149, 198, 41, 303, 190, 0, 0
		INVOKE InitItem, IMG_30202, 105, 149, 222, 41, 279, 95, 0, 1
		INVOKE InitItem, IMG_30301, 105, 149, 311, 36, 416, 185, 0, 0
		INVOKE InitItem, IMG_30302, 105, 149, 333, 36, 395, 93, 0, 1
		INVOKE InitItem, IMG_30401, 105, 149, 424, 34, 529, 183, 0, 0
		INVOKE InitItem, IMG_30402, 105, 149, 444, 34, 508, 90, 0, 1
		INVOKE InitItem, IMG_305, 45, 133, 543, 46, 587, 179, 0, 0
		INVOKE InitItem, IMG_30601, 148, 451, 610, 40, 677, 94, 1, 1	
		INVOKE InitItem, IMG_30602, 105, 149, 685, 354, 746, 407, 1, 1
		INVOKE InitItem, IMG_30701, 111, 138, 635, 190, 690, 244, 1, 1	
		INVOKE InitItem, IMG_30702, 111, 138, 635, 204, 690, 257, 1, 1
		
		INVOKE InitItem, IMG_501, 490, 106, 52, 78, 0, 0, 1, 0
		INVOKE InitItem, IMG_5020101, 287, 287, 148, 151, 0, 0, 1, 0
		INVOKE InitItem, IMG_5020102, 287, 287, 148, 151, 0, 0, 1, 0
		INVOKE InitItem, IMG_5020103, 287, 287, 148, 151, 0, 0, 1, 0
		INVOKE InitItem, IMG_5020104, 287, 287, 148, 151, 0, 0, 1, 0
		INVOKE InitItem, IMG_5020201, 287, 287, 148, 151, 0, 0, 1, 0
		INVOKE InitItem, IMG_5020202, 287, 287, 148, 151, 0, 0, 1, 0
		INVOKE InitItem, IMG_5020203, 287, 287, 148, 151, 0, 0, 1, 0
		INVOKE InitItem, IMG_5020204, 287, 287, 148, 151, 0, 0, 1, 0
		INVOKE InitItem, IMG_5020301, 287, 287, 148, 151, 0, 0, 1, 0
		INVOKE InitItem, IMG_5020302, 287, 287, 148, 151, 0, 0, 1, 0
		INVOKE InitItem, IMG_5020303, 287, 287, 148, 151, 0, 0, 1, 0
		INVOKE InitItem, IMG_5020304, 287, 287, 148, 151, 0, 0, 1, 0
		INVOKE InitItem, IMG_503, 62, 140, 89, 397, 151, 450, 0, 1
		INVOKE InitItem, IMG_504, 56, 110, 214, 427, 270, 480, 1, 1
		INVOKE InitItem, IMG_505, 56, 110, 297, 426, 353, 478, 1, 1
		INVOKE InitItem, IMG_506, 56, 110, 383, 425, 439, 477, 0, 1
		INVOKE InitItem, IMG_507, 48, 114, 553, 419, 0, 0, 0, 0
		INVOKE InitItem, IMG_50801, 57, 108, 629, 421, 686, 473, 0, 1
		INVOKE InitItem, IMG_50802, 57, 108, 629, 421, 0, 0, 0, 0
		INVOKE InitItem, IMG_50901, 56, 97, 686, 451, 741, 500, 0, 1
		INVOKE InitItem, IMG_50902, 56, 97, 686, 451, 741, 500, 0, 1
		INVOKE InitItem, IMG_50903, 56, 97, 686, 404, 0, 0, 0, 0
		INVOKE InitItem, IMG_50904, 56, 97, 686, 404, 741, 459, 0, 1
		INVOKE InitItem, IMG_50905, 56, 97, 682, 433, 0, 0, 0, 1
		INVOKE InitItem, IMG_50906, 56, 97, 686, 404, 0, 0, 0, 0
		INVOKE InitItem, IMG_510, 44, 40, 699, 549, 0, 0, 0, 0
		INVOKE LoadBitmap, hInstance, 1111
		mov Thief_right_s_img, eax
		INVOKE LoadBitmap, hInstance, 2222
		mov Thief_left_s_img, eax
		INVOKE LoadBitmap, hInstance, 3333
		mov Thief_right_r_img, eax
		INVOKE LoadBitmap, hInstance, 4444
		mov Thief_left_r_img, eax
	
		ret

	InitItemList endp