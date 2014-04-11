;-----------------------------------------------------------|
;															|
;				本文件用于存放各类工具型函数				|
;															|
;___________________________________________________________|

.code

; #########################################################################

;将pSequence数组全部重置为-1
ResetpSequence proc
	mov ecx, 0
	.WHILE ecx < pSequenceLength
		mov pSequence[ecx*4], -1
		inc ecx
	.ENDW
	mov pSequenceLength, 0
	ret
ResetpSequence endp

; #########################################################################

;将某个图添加到pSequence序列尾
addTopSequence proc, imgID
	mov ebx, imgID
	mov ecx, pSequenceLength
	mov pSequence[ecx*4], ebx
	inc pSequenceLength
	ret
addTopSequence endp

; #########################################################################

;在pSequence序列中查找图
FindpSequence proc, imgID
	mov eax, 0
	mov ecx, 0
	.WHILE ecx < pSequenceLength
		mov ebx, pSequence[ecx * 4]
		.IF ebx == imgID
			mov eax, 1
		.ENDIF
		inc ecx
	.ENDW	
	ret
FindpSequence endp

; #########################################################################

;将pSequence序列中的某个值des修改为src
ChangepSequence proc, des, src
	mov ecx, 0
	mov edx, src
	.WHILE ecx < pSequenceLength
		mov ebx, pSequence[ecx * 4]
		.IF ebx == des
			mov pSequence[ecx * 4], edx
			mov eax, 1
		.ENDIF
		inc ecx
	.ENDW	
	ret
ChangepSequence endp

; #########################################################################

;场景3的非水平移动
CalculateThiefY3 proc 
	;左上的楼梯
	.IF Thief_Y >= 128 && Thief_Y <= 148 && Thief_X >= 170 && Thief_X <= 195
		mov eax, Thief_X
		mov edx, 0
		sub eax, 170
		mov ebx, 5
		div ebx
		mov ebx, 4
		mul ebx
		add eax, 128
		mov Thief_Y, eax
	;上的斜坡
	.ELSEIF Thief_Y < 150 && Thief_X > 195
		mov eax, Thief_X
		mov edx, 0
		sub eax, 195
		mov ebx, 50
		div ebx
		mov ebx, 1
		mul ebx
		mov ebx, 148
		sub ebx, eax
		mov Thief_Y, ebx
	;右下的楼梯
	.ELSEIF Thief_Y >= 452 && Thief_Y <= 516 && Thief_X <= 680 && Thief_X >= 600
		mov eax, Thief_X
		mov edx, 0
		sub eax, 600
		mov ebx, 5
		div ebx
		mov ebx, 4
		mul ebx
		mov ebx, 516
		sub ebx, eax
		mov Thief_Y, ebx
	.ENDIF
	ret
CalculateThiefY3 endp

; #########################################################################

;播放逃跑ppt
RunForYourLife proc
	
	.IF Thief_X > 105 
		sub Thief_X, 5
	.ELSE
		mov StingPos, 300
		mov cClick, 1
		mov cJudge, 1
		mov Scenario, 3
		INVOKE ResetpSequence
		mov pSequence[0], IMG_30301
		mov pSequenceLength, 1
		mov Thief_X, 333
		mov Thief_Y, 148
		INVOKE CalculateThiefY3
		mov Click_X, 333
		mov eax, Thief_Y
		mov Click_Y, eax
		INVOKE mciSendString,ADDR closeTextBGM, NULL, 0, NULL
		INVOKE mciSendString,ADDR BGMName2, NULL, 0, NULL
		INVOKE mciSendString,ADDR playTextBGM, NULL, 0, NULL
	.ENDIF
	ret
RunForYourLife endp

; #########################################################################

;播放音效
PlayVolume proc hWin:DWORD,NameOfFile:DWORD
	local mciOpenParms:MCI_OPEN_PARMS,mciPlayParms:MCI_PLAY_PARMS

    mov eax,hWin        
    mov mciPlayParms.dwCallback,eax
    mov eax,OFFSET Mp3Device
    mov mciOpenParms.lpstrDeviceType,eax
    mov eax,NameOfFile
    mov mciOpenParms.lpstrElementName,eax
    INVOKE mciSendCommand,0,MCI_OPEN,MCI_OPEN_TYPE or MCI_OPEN_ELEMENT,ADDR mciOpenParms
    mov eax,mciOpenParms.wDeviceID
    mov VolumeID,eax
    INVOKE mciSendCommand,VolumeID,MCI_PLAY,0,ADDR mciPlayParms
    ret  

PlayVolume endp

; #########################################################################

;判断是否点击有效区域
clickPosition proc left: DWORD, top: DWORD, right: DWORD, bottom: DWORD
	mov eax, 0
	mov ebx, left
	mov ecx, right
	.IF Click_X > ebx && Click_X < ecx
		mov ebx, top
		mov ecx, bottom
		.IF Click_Y > ebx && Click_Y < ecx
			mov eax, 1
		.ENDIF
	.ENDIF
	ret
clickPosition endp

; #########################################################################

;重置icon
resetIcon proc
	mov eax, IMG_415
	mov ecx, 0
	.WHILE ecx < 5
		mov drawIcon[ecx*4], eax
		add eax, 1
		add ecx, 1
	.ENDW
	ret
resetIcon endp

; #########################################################################

;移除icon
removeIcon proc imageID: DWORD
	mov ecx, 0
	mov ebx, imageID
	.WHILE drawIcon[ecx*4] != ebx
		add ecx, 1
	.ENDW
	.WHILE ecx < 4 && drawIcon[ecx*4] != -1
		mov ebx, ecx
		add ebx, 1
		mov edx, drawIcon[ebx*4]
		mov drawIcon[ecx*4], edx
		add ecx, 1
	.ENDW
	.IF ecx == 4
		mov drawIcon[ecx*4], -1
	.ENDIF
	ret
removeIcon endp

; #########################################################################


;判断icon顺序是否正确
isCorrectOrder proc
	mov eax, 1
	mov ecx, 0
	.WHILE ecx < 5
		mov ebx, player[ecx*4]
		.IF correctOrder[ecx*4] != ebx
			mov eax, 0
			ret
		.ENDIF
		add ecx, 1
	.ENDW
	ret
isCorrectOrder endp

; #########################################################################

;检查场景3的七个洞是否顺序正确
CheckHoles proc
	mov ecx, 0
	.WHILE ecx < 7
		mov ebx, Holes[ecx*4]
		.IF CorrectHoles[ecx*4] != ebx
			ret
		.ENDIF
		add ecx, 1
	.ENDW
	mov CollectionStep, 6
	INVOKE ChangepSequence, IMG_30903, IMG_30904
	INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
	INVOKE PlayVolume,hWinMain,ADDR Volume16
	mov Thief_Y, 313
	mov Holes[12], IMG_315
	ret
CheckHoles endp

; #########################################################################

;处理场景3的七个洞移动
MoveHoles proc ID: DWORD
	mov ebx, ID
	.IF Holes[ebx*4] != IMG_31404
		mov eax, Holes[ebx*4]
		mov ecx, 0
		.WHILE ecx < 7
			.IF Holes[ecx*4] == IMG_31404
				mov Holes[ecx*4], eax
				mov Holes[ebx*4], IMG_31404
			.ENDIF
			inc ecx
		.ENDW
	.ENDIF
	INVOKE CheckHoles
	ret
MoveHoles endp

; #########################################################################

;场景4的门移动函数
doorTransition proc imageID: DWORD
	.IF imageID == IMG_401
		mov Thief_X, 120
		mov Thief_Y, 293
		mov PassBy, -1
		mov Orientation, 0
	.ELSEIF imageID == IMG_402
		mov Thief_X, 465
		mov Thief_Y, 510
		mov PassBy, -1
		mov Orientation, 0
	.ELSEIF imageID == IMG_403
		mov Thief_X, 575
		mov Thief_Y, 290
		mov PassBy, -1
		mov Orientation, 0
	.ELSEIF imageID == IMG_404
		mov Thief_X, 400
		mov Thief_Y, 340
		mov PassBy, -1
		mov Orientation, 0
	.ELSEIF imageID == IMG_405
		mov Thief_X, 702
		mov Thief_Y, 146
		mov PassBy, -1
		mov Orientation, 1
	.ELSEIF imageID == IMG_406
		mov Thief_X, 575
		mov Thief_Y, 510
		mov PassBy, -1
		mov Orientation, 1
	.ELSEIF imageID == IMG_407
		mov Thief_X, 248
		mov Thief_Y, 510
		mov PassBy, -1
		mov Orientation, 1
	.ELSEIF imageID == IMG_408
		mov Thief_X, 700
		mov Thief_Y, 510
		mov PassBy, -1
		mov Orientation, 1
	.ELSEIF imageID == IMG_409
		mov Thief_X, 349
		mov Thief_Y, 151
		mov PassBy, -1
		mov Orientation, 1
	.ELSEIF imageID == IMG_410	;切换回场景3
		INVOKE mciSendString,ADDR closeTextBGM, NULL, 0, NULL
		INVOKE mciSendString,ADDR BGMName2, NULL, 0, NULL
		INVOKE mciSendString,ADDR playTextBGM, NULL, 0, NULL
		mov Thief_X, 270
		mov Thief_Y, 148
		INVOKE CalculateThiefY3
		mov Click_X, 270
		mov eax, Thief_Y
		mov Click_Y, eax
		mov Scenario, 3
		INVOKE ResetpSequence
		.IF Triangle == 1
			mov pSequence[0], IMG_30301
			mov pSequenceLength, 1
		.ELSE
			mov pSequence[0], IMG_30201
			mov pSequenceLength, 1
			mov AppleShow, 0
		.ENDIF
	.ELSEIF imageID == IMG_411
		mov Thief_X, 700
		mov Thief_Y, 290
		mov PassBy, -1
		mov Orientation, 1
	.ELSEIF imageID == IMG_412
		mov Thief_X, 400
		mov Thief_Y, 340
		mov PassBy, -1
		mov Orientation, 0
	.ELSEIF imageID == IMG_413
		mov Thief_X, 248
		mov PassBy, -1
		mov Orientation, 1
	.ELSEIF imageID == IMG_414
		mov Thief_X, 565
		mov PassBy, -1
		mov Orientation, 0
	.ENDIF
	ret
doorTransition endp

; #########################################################################

;检查场景5的圈是否正确
CheckRounds proc
	.IF Rounds[0] == IMG_5020102 && Rounds[4] == IMG_5020203 && Rounds[8] == IMG_5020304
		mov door5Open, 1
		INVOKE addTopSequence, IMG_507
		INVOKE mciSendString,ADDR closeTextBGM, NULL, 0, NULL
		INVOKE ChangepSequence, IMG_30903, IMG_30904
		INVOKE PlayVolume,hWinMain,ADDR Volume17
	.ENDIF
	ret
CheckRounds endp

; #########################################################################

;重启游戏
restartGame proc
	mov cClick, 1
	mov cJudge, 1
	mov pThief, 1
	mov isStopped, 0
	mov isFinished, 0

	mov Orientation, 0
	mov Run, 0
	mov PassBy, -1
	INVOKE ResetpSequence 
	INVOKE resetIcon

	mov ecx, 0
	.WHILE ecx < 5
		mov player[ecx*4], 0
		add ecx, 1
	.ENDW

	mov step, 0
	mov pearStep, 0
	mov PPTstatus, 0
	mov StingPos, 300

	mov Rounds[0], IMG_5020101
	mov Rounds[4], IMG_5020201
	mov Rounds[8], IMG_5020301
	mov Light6, -1
	mov LightCount, 0
	mov GhostCount, 0
	mov GhostStep, -1
	mov CollectionStep, 0

	mov Apple, 0
	mov AppleShow, 0
	mov Banana, 0
	mov BananaShow, 0
	mov Pear, 0
	mov Dog, 0
	mov Bug, 0
	mov Triangle, 0
	mov Cross, 0	
	mov Circle, 0
	mov CircleShow, 0
	mov door3Open, 0
	mov door5Open, 0

	mov Scenario, 3
	INVOKE mciSendString,ADDR closeTextBGM, NULL, 0, NULL
	INVOKE mciSendString,ADDR BGMName2, NULL, 0, NULL
	INVOKE mciSendString,ADDR playTextBGM, NULL, 0, NULL
    INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
	INVOKE PlayVolume,hWinMain,ADDR Volume1
	mov Thief_X, 79
	mov Thief_Y, 128
	mov Click_X, 79
	mov Click_Y, 128
	mov pSequence[0], IMG_30201
	inc pSequenceLength

restartGame endp

; #########################################################################

;计算thief移动的坐标
ThiefMove proc
	local MAX_X:DWORD
	local MIN_X:DWORD
	mov MAX_X, 735
	mov MIN_X, 35
	.IF Scenario == 1
	.ELSEIF Scenario == 2
	.ELSEIF Scenario == 3
		.IF Thief_Y >= 128 && Thief_Y <= 148 && door3Open == 0	;门未开的上
			mov MAX_X, 545
			mov MIN_X, 55
		.ELSEIF Thief_Y == 265		;右中部
			mov MAX_X, 735
			mov MIN_X, 630
		.ELSEIF Thief_Y == 420		;石像第一层
			mov MAX_X, 430
			mov MIN_X, 345
		.ELSEIF Thief_Y == 368		;石像第二层
			mov MAX_X, 430
			mov MIN_X, 345
		.ELSEIF Thief_Y == 313		;石像第三层
			mov MAX_X, 430
			mov MIN_X, 345
		.ELSEIF Thief_Y == 258		;石像第三层
			mov MAX_X, 430
			mov MIN_X, 345
		.ENDIF
	.ELSEIF Scenario == 4
		.IF Thief_Y == 510		;下
			mov MAX_X, 755
			mov MIN_X, 70
		.ELSEIF Thief_Y == 293	;左中
			mov MAX_X, 290
			mov MIN_X, 70
		.ELSEIF Thief_Y == 290	;右中
			mov MAX_X, 755
			mov MIN_X, 535
		.ELSEIF Thief_Y == 340	;中
			mov MAX_X, 452
			mov MIN_X, 370
		.ELSEIF Thief_Y == 151	;左上
			mov MAX_X, 398
			mov MIN_X, 70
		.ELSEIF Thief_Y == 146	;右上
			mov MAX_X, 755
			mov MIN_X, 484
		.ENDIF
	.ELSEIF Scenario == 5
		.IF door5Open == 0	;门未开的上
			mov MAX_X, 545
			mov MIN_X, 55
		.ELSE
			mov MAX_X, 745
			mov MIN_X, 55
		.ENDIF
	.ELSEIF Scenario == 6
		mov MAX_X, 745
		mov MIN_X, 55
	.ENDIF
	mov ebx, MAX_X
	.IF Click_X > ebx
		mov Click_X, ebx
	.ENDIF
	mov ebx, MIN_X
	.IF Click_X < ebx
		mov Click_X, ebx
	.ENDIF
	;普通移动处理
	mov ebx, Click_X
	.IF ebx > Thief_X
		add Thief_X, 5
		.IF ebx > Thief_X
			mov Run, 1
		.ELSE
			mov Run, 0
			mov ebx, Thief_X
			mov Click_X, ebx
		.ENDIF
	.ELSEIF ebx < Thief_X
		sub Thief_X, 5
		.IF ebx < Thief_X
			mov Run, 1
		.ELSE
			mov Run, 0
			mov ebx, Thief_X
			mov Click_X, ebx
		.ENDIF
		mov Run, 0
	.ENDIF
	.IF Scenario == 3
		INVOKE CalculateThiefY3
	.ENDIF
	mov eax, Thief_X
	.IF eax != Click_X
		mov Run, 1
	.ENDIF
	ret
ThiefMove endp

; #########################################################################