;-----------------------------------------------------------|
;															|
;					本文件用来存放全局变量					|
;															|
;___________________________________________________________|


; #########################################################################

;EQU 定义

; #########################################################################

IMG_0				equ		30
IMG_1				equ		1
IMG_2				equ		2

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
IMG_5020101			equ		46
IMG_5020102			equ		47
IMG_5020103			equ		48
IMG_5020104			equ		49
IMG_5020201			equ		50
IMG_5020202			equ		51
IMG_5020203			equ		52
IMG_5020204			equ		53
IMG_5020301			equ		54
IMG_5020302			equ		55
IMG_5020303			equ		56
IMG_5020304			equ		57
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
IMG_31103			equ		131
IMG_31201			equ		132
IMG_31202			equ		133
IMG_31203			equ		134
IMG_31301			equ		135
IMG_31302			equ		136
IMG_31303			equ		137
IMG_31401			equ		138
IMG_31402			equ		139
IMG_31403			equ		140
IMG_31404			equ		141
IMG_31405			equ		142
IMG_31406			equ		143
IMG_31407			equ		144
IMG_315				equ		145
IMG_316				equ		146
IMG_31701			equ		147
IMG_31702			equ		148
IMG_31703			equ		149
IMG_31704			equ		150
IMG_31801			equ		151
IMG_31802			equ		152
IMG_319				equ		153

IMG_700				equ		154
IMG_701				equ		155
IMG_702				equ		156
IMG_703				equ		157
IMG_704				equ		158
IMG_705				equ		159
IMG_706				equ		160

IMG_801				equ		161
IMG_802				equ		162
IMG_803				equ		163
IMG_804				equ		164
IMG_805				equ		165
IMG_806				equ		166
IMG_807				equ		167
IMG_808				equ		168

IMG_511				equ		169
IMG_320				equ		170

;窗体大小
SCREEN_X			equ		820
SCREEN_Y			equ		642

; #########################################################################

;结构体 定义

; #########################################################################

;MyItem结构体，用来表示游戏中的一个物体
MyItem STRUCT
	img			dd		0
	iwidth		dd		0
	iheight		dd		0
	x1			dd		0
	y1			dd		0
	x2			dd		0
	y2			dd		0
	pMethod		BYTE	0	;绘制方法,0使用DrawObject,1使用DrawTransparentObject
	eClick		BYTE	0	;是否有鼠标事件，0没有，1有
MyItem ends

; #########################################################################

;数据段

; #########################################################################

.data
	;窗口绘制的参数
	hInstance				dd			?
	hWinMain				dd			?
	hMenu					dd			?
	hdc						dd			?
	hdcImage				dd			?
	hdcMem					dd			?
	bmp						HBITMAP		?

	;全局变量
	cClick					BYTE		1			;判断是否要响应接下来的鼠标事件
	cJudge					BYTE		1			;判断是否要判断接下来的碰撞事件
	pThief					BYTE		1			;判断是否要绘制Thief
	pThiefOld				BYTE		1

	Orientation				BYTE		0			;Thief朝向,0代表向右,1代表朝左
	Run						BYTE		0			;Thief状态,0代表站立,1代表运动

	Apple					BYTE		0			;是否收集到了苹果
	AppleShow				BYTE		0			;是否已画出苹果
	Banana					BYTE		0			;是否收集到了香蕉
	BananaShow				BYTE		0			;是否已画出香蕉
	Pear					BYTE		0			;是否收集到了梨子
	Dog						BYTE		0			;是否收集到了水獭
	Bug						BYTE		0			;是否收集到了虫子
	Triangle				BYTE		0			;当前是否拿到了三角
	Cross					BYTE		0			;当前是否拿到了十字
	Circle					BYTE		0			;当前是否拿到了圆
	CircleShow				BYTE		0			;圆是否已出现
	door3Open				BYTE		0			;场景三的上侧阻挡门是否已经打开
	door5Open				BYTE		0			;场景五的阻挡门是否已经打开
	isPlayingBGM			BYTE		1			;是否播放背景音乐
	isStopped				BYTE		0			;游戏是否暂停
	check_collection		BYTE		0			;点击star，查看收藏物品
	check_solution			BYTE		0			;点击书，查看线索
	get_collection			BYTE		0			;获得物品
	isFinished				BYTE		0			;是否已结束

	Scenario				dd			0			;当前场景
	Thief_X					dd			675			;Thief横坐标
	Thief_Y					dd			510			;Thief纵坐标
	Click_X					dd			675			;鼠标点击点的横坐标
	Click_Y					dd			510			;鼠标点击点的纵坐标
	PassBy					dd			-1			;路过的提示
	PassBy_Old				dd			-1
	step					dd			0			;五个icon的点击步骤
	pearStep				dd			0			;梨子隐藏的点击步骤
	PPTstatus				dd			0			;需要播放PPT的状态
	StingPos				dd			300			;刺的位置
	book_page				dd			IMG_801
	Light6					dd			-1			;场景6的灯
	LightCount				dd			0			;灯亮计时
	GhostCount				dd			0			;鬼的动画计时
	GhostStep				dd			-1			;鬼的系列状态
	CollectionStep			dd			0			;收集品放入的步骤
	Thief_right_s_img		dd			0
	Thief_left_s_img		dd			0
	Thief_right_r_img		dd			0
	Thief_left_r_img		dd			0

	pSequence				dd			20		DUP(-1)		;需要绘制的物体序号数组
	pSequenceLength			dd			0
	ItemList				MyItem		200		DUP(<>)		;物体数组
	drawIcon				dd			IMG_415, IMG_416, IMG_417, IMG_418, IMG_419
	correctOrder			dd			IMG_415, IMG_416, IMG_417, IMG_418, IMG_419
	player					dd			5 DUP (?)
	Rounds					dd			IMG_5020101, IMG_5020201, IMG_5020301	;场景5三个圈
	Holes					dd			IMG_31401,IMG_31402,IMG_31403,IMG_31404,IMG_31405,IMG_31406,IMG_31407	;场景三第二层的孔
	CorrectHoles			dd			IMG_31407,IMG_31405,IMG_31406,IMG_31404,IMG_31403,IMG_31401,IMG_31402	;孔的正确顺序
	HolesX1					dd			247,287,326,371,415,455,495												;场景三第二层的孔的x1值数组
	EyesCount				dd			0,0,0,0																	;场景三第三层的眼睛倒计时

	;播放音乐所需的参数
    BGMID					dd			0
	VolumeID				dd			0

.const
	szClassName				db			"TinyThiefClass", 0
	szCaptionMain			db			"TinyThief", 0

    Mp3Device				db			"MPEGVideo",0
	playTextBGM				db			"play bgm repeat", 0
	closeTextBGM			db			"close bgm",0
	pauseTextBGM			db			"pause bgm",0
	BGMName1				db			"open AssetMusic_Theme.mp3 alias bgm",0
	BGMName2				db			"open AssetSound_Campfire.mp3 alias bgm", 0
	BGMName3				db			"open AssetSound_Cave.mp3 alias bgm", 0
	BGMName4				db			"open AssetSound_PirateTemple_SpikedWall.mp3 alias bgm", 0
	Volume1					db			"AssetSound_Commons_CameraOut.mp3", 0
	Volume2					db			"AssetSound_Commons_Extra.mp3", 0
	Volume3					db			"AssetSound_Commons_HandTap.mp3", 0
	Volume4					db			"AssetSound_Commons_PickUp.mp3", 0
	Volume5					db			"AssetSound_Commons_Star.mp3", 0
	Volume6					db			"AssetSound_Commons_WinLevel.mp3", 0
	Volume7					db			"AssetSound_PirateTemple_Eye.mp3", 0
	Volume8					db			"AssetSound_PirateTemple_InsertStoneItems.mp3", 0
	Volume9					db			"AssetSound_PirateTemple_LightLever.mp3", 0
	Volume10				db			"AssetSound_PirateTemple_LightSigns.mp3", 0
	Volume11				db			"AssetSound_PirateTemple_SignFood.mp3", 0
	Volume13				db			"AssetSound_PirateTemple_SpiritBurned.mp3", 0
	Volume14				db			"AssetSound_PirateTemple_SpiritEffect.mp3", 0
	Volume15				db			"AssetSound_PirateTemple_StoneFloorDestroy.mp3", 0
	Volume16				db			"AssetSound_PirateTemple_StoneFloorUp.mp3", 0
	Volume17				db			"AssetSound_PirateTemple_StoneMiniDoor.mp3", 0
	Volume18				db			"AssetSound_PirateTemple_StoneOpen.mp3", 