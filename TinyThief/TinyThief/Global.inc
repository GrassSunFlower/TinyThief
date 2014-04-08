
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

IMG_90101			equ		72
IMG_90102			equ		73
IMG_90200			equ		74
IMG_90201			equ		75
IMG_90202			equ		76
IMG_90203			equ		77
IMG_90204			equ		78
IMG_90205			equ		79
IMG_90206			equ		80

IMG_600				equ		81
IMG_601				equ		82
IMG_60201			equ		83
IMG_60202			equ		84
IMG_60301			equ		85
IMG_60302			equ		86
IMG_60401			equ		87
IMG_60402			equ		88
IMG_60501			equ		89
IMG_60502			equ		90
IMG_60601			equ		91
IMG_60602			equ		92
IMG_60603			equ		93
IMG_60604			equ		94
IMG_60605			equ		95
IMG_60701			equ		96
IMG_60702			equ		97
IMG_60703			equ		98
IMG_60801			equ		99
IMG_60802			equ		100
IMG_60803			equ		101
IMG_60901			equ		102
IMG_60902			equ		103
IMG_60903			equ		104
IMG_61001			equ		105
IMG_61002			equ		106
IMG_61003			equ		107
IMG_61101			equ		108
IMG_61102			equ		109
IMG_612				equ		110
IMG_61301			equ		111
IMG_61302			equ		112
IMG_61401			equ		113
IMG_61402			equ		114
IMG_61403			equ		115
IMG_61404			equ		116

IMG_30801			equ		117
IMG_30802			equ		118
IMG_30803			equ		119
IMG_30804			equ		120
IMG_30805			equ		121
IMG_30806			equ		122
IMG_30901			equ		123
IMG_30902			equ		124
IMG_30903			equ		125
IMG_30904			equ		126
IMG_30905			equ		127
IMG_310				equ		128
IMG_31101			equ		129
IMG_31102			equ		130
IMG_31201			equ		131
IMG_31202			equ		132
IMG_31301			equ		133
IMG_31302			equ		134
IMG_31401			equ		135
IMG_31402			equ		136
IMG_31403			equ		137
IMG_31404			equ		138
IMG_31405			equ		139
IMG_31406			equ		140
IMG_31407			equ		141
IMG_315				equ		142
IMG_316				equ		143
IMG_31701			equ		144
IMG_31702			equ		145
IMG_31703			equ		146
IMG_31704			equ		147
IMG_31801			equ		148
IMG_31802			equ		149
IMG_319				equ		150

IMG_700				equ		151
IMG_701				equ		152
IMG_702				equ		153
IMG_703				equ		154
IMG_704				equ		155
IMG_705				equ		156
IMG_706				equ		157

IMG_801				equ		158
IMG_802				equ		159
IMG_803				equ		160
IMG_804				equ		161
IMG_805				equ		162
IMG_806				equ		163
IMG_807				equ		164
IMG_808				equ		165

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
	cJudge						BYTE			1								;判断是否要判断接下来的碰撞事件
	pThief						BYTE			1								;判断是否要绘制Thief
	;数据型全局变量
	Scenario					dd			3								;当前场景
	Thief_X						dd			79							;Thief横坐标
	Thief_Y						dd			128							;Thief纵坐标
	Click_X						dd			675							;鼠标点击点的横坐标
	Click_Y						dd			510							;鼠标点击点的纵坐标
	Orientation				BYTE	0										;Thief朝向,0代表向右,1代表朝左
	Run							BYTE	0										;Thief状态,0代表站立,1代表运动
	PassBy						dd			-1								;路过的提示
	PassBy_Old					dd			-1
	pSequence				dd			20		DUP(-1)		;需要绘制的物体序号数组
	pSequenceLength		dd			0
	ItemList					MyItem	200		DUP(<>)		;物体数组
	drawIcon					dd			IMG_415, IMG_416, IMG_417, IMG_418, IMG_419
	correctOrder			dd			IMG_415, IMG_416, IMG_417, IMG_418, IMG_419
	player						dd			5 DUP (?)
	step							dd			0						;五个icon的点击步骤
	pearStep					dd			0							;梨子隐藏的点击步骤
	PPTstatus					dd			0							;需要播放PPT的状态
	StingPos					dd				300						;刺的位置
	Rounds						dd				IMG_5020101, IMG_5020201, IMG_5020301	;场景5三个圈
	Light6						dd				-1						;场景6的灯
	LightCount					dd				0						;灯亮计时
	GhostCount					dd				0						;鬼的动画计时
	GhostStep					dd				-1						;鬼的系列状态
	CollectionStep				dd				0						;收集品放入的步骤
	Apple						BYTE			0						;是否收集到了苹果
	AppleShow					BYTE			0						;是否已画出苹果
	Banana						BYTE			0						;是否收集到了香蕉
	BananaShow					BYTE			0						;是否已画出香蕉
	Pear						BYTE			0						;是否收集到了梨子
	Dog							BYTE			0						;是否收集到了狗？水獭？狐狸？
	Triangle					BYTE			1						;当前是否拿到了三角
	Cross						BYTE			1						;当前是否拿到了十字
	Circle						BYTE			1						;当前是否拿到了圆
	CircleShow					BYTE			0						;圆是否已出现
	door3Open					BYTE			0						;场景三的上侧阻挡门是否已经打开
	door5Open					BYTE			0						;场景五的阻挡门是否已经打开
	Thief_right_s_img		dd			0
	Thief_left_s_img		dd			0
	Thief_right_r_img		dd			0
	Thief_left_r_img		dd			0
	isPlayingBGM			BYTE		1
	isStopped					BYTE			0
	
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
		
		INVOKE InitItem, IMG_400, 0, 0, 0, 0, 0, 0, 0, 1
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
		INVOKE InitItem, IMG_422, 39, 39, 750, 547, 0, 0, 1, 0
		
		INVOKE InitItem, IMG_300, 0, 0, 0, 0, 0, 0, 0, 1
		INVOKE InitItem, IMG_301, 93, 101, 45, 61, 138, 162, 0, 0
		INVOKE InitItem, IMG_30201, 105, 149, 198, 41, 303, 190, 0, 0
		INVOKE InitItem, IMG_30202, 105, 149, 222, 41, 279, 95, 0, 1
		INVOKE InitItem, IMG_30301, 105, 149, 311, 36, 416, 185, 0, 0
		INVOKE InitItem, IMG_30302, 105, 149, 333, 36, 395, 93, 0, 1
		INVOKE InitItem, IMG_30401, 105, 149, 424, 34, 529, 183, 0, 0
		INVOKE InitItem, IMG_30402, 105, 149, 444, 34, 508, 90, 0, 1
		INVOKE InitItem, IMG_305, 45, 133, 543, 46, 587, 179, 0, 0
		INVOKE InitItem, IMG_30601, 148, 451, 610, 40, 677, 94, 1, 1	
		INVOKE InitItem, IMG_30602, 148, 451, 685, 354, 746, 407, 1, 1
		INVOKE InitItem, IMG_30701, 111, 138, 635, 190, 690, 244, 1, 1	
		INVOKE InitItem, IMG_30702, 111, 138, 635, 204, 690, 257, 1, 1
		
		INVOKE InitItem, IMG_500, 0, 0, 0, 0, 0, 0, 0, 1
		INVOKE InitItem, IMG_501, 490, 406, 52, 78, 0, 0, 1, 0
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
		INVOKE InitItem, IMG_510, 39, 39, 700, 547, 0, 0, 1, 0

		INVOKE InitItem, IMG_90101, 150, 350, 0, 30, 0, 0, 1, 0
		INVOKE InitItem, IMG_90102, 150, 350, 0, 30, 0, 0, 1, 0
		INVOKE InitItem, IMG_90200, 261, 123, 270, 13, 0, 0, 1, 0
		INVOKE InitItem, IMG_90201, 26, 26, 290, 54, 0, 0, 0, 0
		INVOKE InitItem, IMG_90202, 26, 26, 304, 28, 0, 0, 0, 0
		INVOKE InitItem, IMG_90203, 26, 26, 318, 54, 0, 0, 0, 0
		INVOKE InitItem, IMG_90204, 24, 23, 306, 78, 0, 0, 0, 0
		INVOKE InitItem, IMG_90205, 78, 95, 360, 27, 0, 0, 1, 0
		INVOKE InitItem, IMG_90206, 49, 67, 460, 33, 0, 0, 0, 0
		
		INVOKE InitItem, IMG_600, 0, 0, 0, 0, 0, 0, 0, 1
		INVOKE InitItem, IMG_601, 62, 138, 632, 404, 694, 459, 0, 1
		INVOKE InitItem, IMG_60201, 69, 112, 478, 434, 535, 489, 1, 1
		INVOKE InitItem, IMG_60202, 69, 112, 478, 434, 0, 0, 1, 0
		INVOKE InitItem, IMG_60301, 69, 112, 384, 434, 439, 488, 0, 1
		INVOKE InitItem, IMG_60302, 69, 112, 384, 434, 0, 0, 0, 0
		INVOKE InitItem, IMG_60401, 69, 112, 295, 438, 350, 491, 0, 1
		INVOKE InitItem, IMG_60402, 69, 112, 295, 438, 0, 0, 0, 0
		INVOKE InitItem, IMG_60501, 69, 112, 201, 438, 257, 491, 0, 1
		INVOKE InitItem, IMG_60502, 69, 112, 201, 438, 0, 0, 0, 0
		INVOKE InitItem, IMG_60601, 96, 92, 42, 461, 0, 0, 0, 0
		INVOKE InitItem, IMG_60602, 96, 92, 42, 461, 0, 0, 0, 0
		INVOKE InitItem, IMG_60603, 96, 92, 42, 461, 0, 0, 0, 0
		INVOKE InitItem, IMG_60604, 96, 92, 42, 461, 0, 0, 0, 0
		INVOKE InitItem, IMG_60605, 96, 92, 42, 461, 0, 0, 0, 0
		INVOKE InitItem, IMG_60701, 345, 306, 123, 66, 0, 0, 0, 0
		INVOKE InitItem, IMG_60702, 65, 83, 153, 285, 0, 0, 0, 0
		INVOKE InitItem, IMG_60703, 345, 306, 123, 66, 0, 0, 0, 0
		INVOKE InitItem, IMG_60801, 210, 358, 162, 74, 0, 0, 0, 0
		INVOKE InitItem, IMG_60802, 68, 80, 285, 351, 0, 0, 0, 0
		INVOKE InitItem, IMG_60803, 210, 358, 162, 74, 0, 0, 0, 0
		INVOKE InitItem, IMG_60901, 252, 329, 384, 65, 0, 0, 0, 0
		INVOKE InitItem, IMG_60902, 68, 83, 415, 311, 0, 0, 0, 0
		INVOKE InitItem, IMG_60903, 252, 329, 384, 65, 0, 0, 0, 0
		INVOKE InitItem, IMG_61001, 329, 278, 317, 66, 0, 0, 0, 0
		INVOKE InitItem, IMG_61002, 68, 81, 553, 263, 0, 0, 0, 0
		INVOKE InitItem, IMG_61003, 329, 278, 317, 66, 0, 0, 0, 0
		INVOKE InitItem, IMG_61101, 53, 109, 353, 440, 0, 0, 0, 0
		INVOKE InitItem, IMG_61102, 53, 109, 353, 440, 406, 495, 0, 1
		INVOKE InitItem, IMG_612, 39, 39, 650, 547, 0, 0, 1, 0
		INVOKE InitItem, IMG_61301, 58, 91, 44, 438, 102, 490, 0, 1
		INVOKE InitItem, IMG_61302, 58, 91, 44, 438, 0, 0, 0, 0
		INVOKE InitItem, IMG_61401, 65, 121, 449, 427, 0, 0, 0, 0
		INVOKE InitItem, IMG_61402, 65, 121, 449, 427, 514, 480, 0, 1
		INVOKE InitItem, IMG_61403, 65, 121, 449, 427, 0, 0, 0, 0
		INVOKE InitItem, IMG_61404, 65, 121, 449, 427, 0, 0, 0, 0

		INVOKE InitItem, IMG_30801, 104, 106, 613, 193, 667, 246, 0, 1
		INVOKE InitItem, IMG_30802, 104, 106, 613, 193, 0, 0, 0, 0
		INVOKE InitItem, IMG_30803, 104, 106, 633, 193, 688, 246, 0, 1
		INVOKE InitItem, IMG_30804, 104, 106, 613, 193, 0, 0, 0, 0
		INVOKE InitItem, IMG_30805, 104, 106, 656, 193, 710, 246, 0, 1
		INVOKE InitItem, IMG_30806, 104, 106, 613, 193, 0, 0, 0, 0
		INVOKE InitItem, IMG_30901, 426, 363, 173, 193, 0, 0, 0, 0
		INVOKE InitItem, IMG_30902, 426, 363, 173, 193, 0, 0, 0, 0
		INVOKE InitItem, IMG_30903, 426, 363, 173, 193, 0, 0, 0, 0
		INVOKE InitItem, IMG_30904, 426, 363, 173, 193, 0, 0, 0, 0
		INVOKE InitItem, IMG_30905, 426, 363, 173, 193, 0, 0, 0, 0
		INVOKE InitItem, IMG_310, 59, 102, 358, 446, 417, 499, 0, 1
		INVOKE InitItem, IMG_31101, 40, 38, 234, 502, 274, 540, 0, 1
		INVOKE InitItem, IMG_31102, 40, 38, 234, 502, 274, 540, 0, 1
		INVOKE InitItem, IMG_31201, 40, 38, 369, 502, 409, 540, 0, 1
		INVOKE InitItem, IMG_31202, 40, 38, 369, 502, 409, 540, 0, 1
		INVOKE InitItem, IMG_31301, 40, 38, 501, 502, 541, 540, 0, 1
		INVOKE InitItem, IMG_31302, 40, 38, 501, 502, 541, 540, 0, 1
		INVOKE InitItem, IMG_31401, 31, 32, 247, 441, 278, 473, 0, 1
		INVOKE InitItem, IMG_31402, 31, 32, 287, 441, 318, 473, 0, 1
		INVOKE InitItem, IMG_31403, 31, 32, 326, 441, 357, 473, 0, 1
		INVOKE InitItem, IMG_31404, 31, 32, 370, 441, 401, 473, 0, 1
		INVOKE InitItem, IMG_31405, 31, 32, 415, 441, 446, 473, 0, 1
		INVOKE InitItem, IMG_31406, 31, 32, 455, 441, 486, 473, 0, 1
		INVOKE InitItem, IMG_31407, 31, 32, 495, 441, 526, 473, 0, 1
		INVOKE InitItem, IMG_315, 31, 40, 370, 441, 401, 473, 0, 1
		INVOKE InitItem, IMG_316, 51, 17, 279, 471, 0, 0, 0, 0
		INVOKE InitItem, IMG_31701, 41, 39, 296, 372, 337, 411, 0, 1
		INVOKE InitItem, IMG_31702, 41, 39, 342, 372, 383, 411, 0, 1
		INVOKE InitItem, IMG_31703, 41, 39, 388, 372, 429, 411, 0, 1
		INVOKE InitItem, IMG_31704, 41, 39, 435, 372, 476, 411, 0, 1
		INVOKE InitItem, IMG_31801, 60, 109, 358, 183, 418, 292, 0, 1
		INVOKE InitItem, IMG_31802, 60, 109, 358, 183, 0, 0, 0, 0
		INVOKE InitItem, IMG_319, 47, 48, 95, 501, 142, 549, 0, 0

		INVOKE InitItem, IMG_700, 297, 377, 250, 111, 0, 0, 1, 0
		INVOKE InitItem, IMG_701, 25, 25, 299, 157, 0, 0, 0, 0
		INVOKE InitItem, IMG_702, 25, 25, 312, 132, 0, 0, 0, 0
		INVOKE InitItem, IMG_703, 25, 25, 327, 158, 0, 0, 0, 0
		INVOKE InitItem, IMG_704, 53, 45, 448, 137, 0, 0, 0, 0
		INVOKE InitItem, IMG_705, 80, 82, 275, 210, 0, 0, 1, 0
		INVOKE InitItem, IMG_706, 80, 82, 444, 208, 0, 0, 1, 0
		
		;INVOKE InitItem, IMG_801, 608, 396, 94, 90, 0, 0, 1, 0
		;INVOKE InitItem, IMG_802, 608, 396, 94, 90, 0, 0, 1, 0
		;INVOKE InitItem, IMG_803, 608, 396, 94, 90, 0, 0, 1, 0
		;INVOKE InitItem, IMG_804, 608, 396, 94, 90, 0, 0, 1, 0
		;INVOKE InitItem, IMG_805, 608, 396, 94, 90, 0, 0, 1, 0
		;INVOKE InitItem, IMG_806, 608, 396, 94, 90, 0, 0, 1, 0
		;INVOKE InitItem, IMG_807, 608, 396, 94, 90, 0, 0, 1, 0
		;INVOKE InitItem, IMG_808, 608, 396, 94, 90, 0, 0, 1, 0

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