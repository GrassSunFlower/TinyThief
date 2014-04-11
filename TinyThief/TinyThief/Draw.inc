;-----------------------------------------------------------|
;															|
;					本文件用于游戏画面的绘制				|
;															|
;___________________________________________________________|

.code

; #########################################################################

;绘制物品
DrawObject proc bID:DWORD, img:DWORD, xDesc:DWORD, yDesc:DWORD, sWidth:DWORD, sHeight:DWORD

	.IF bID == IMG_30202
		mov xDesc, 198
	.ELSEIF bID == IMG_30302
		mov xDesc, 311
	.ELSEIF bID == IMG_30402
		mov xDesc, 424
	.ELSEIF bID == IMG_50901 || bID == IMG_50902
		mov yDesc, 404
	.ELSEIF bID == IMG_30803 || bID == IMG_30805
		mov xDesc, 613
	.ENDIF

	INVOKE SelectObject,hdcImage,img
	INVOKE BitBlt,hdcMem,xDesc,yDesc,sWidth,sHeight,hdcImage,0,0,SRCCOPY
	
	ret
DrawObject endp

; #########################################################################

;绘制背景透明的物品
DrawTransparentObject proc bID:DWORD, img:DWORD, xDesc:DWORD, yDesc:DWORD, sWidth:DWORD, sHeight:DWORD

	INVOKE SelectObject,hdcImage,img

	.IF bID == IMG_30601 || bID == IMG_30602
		mov xDesc, 601
		mov yDesc, 40
	.ELSEIF bID == IMG_30701 || bID == IMG_30702
		mov yDesc, 165
	.ENDIF

	INVOKE BitBlt,hdcMem,xDesc,yDesc,sWidth,sHeight,hdcImage,sWidth,0,SRCAND
	INVOKE BitBlt,hdcMem,xDesc,yDesc,sWidth,sHeight,hdcImage,0,0,SRCPAINT
	
	ret
DrawTransparentObject endp

; #########################################################################

;绘制盗贼
DrawThief proc
	local thiefX

	mov eax, Thief_X
	mov thiefX, eax
	sub thiefX, 16
	.IF Orientation == 0
		.IF Run == 0
			INVOKE DrawTransparentObject, 1111, Thief_right_s_img,thiefX,Thief_Y,25,32
		.ELSE
			INVOKE DrawTransparentObject, 3333, Thief_right_r_img,thiefX,Thief_Y,25,32
		.ENDIF
	.ELSEIF Run == 0
		INVOKE DrawTransparentObject, 2222, Thief_left_s_img,thiefX,Thief_Y,25,32
	.ELSE
		INVOKE DrawTransparentObject, 4444, Thief_left_r_img,thiefX,Thief_Y,25,32
	.ENDIF

    ret

DrawThief endp

; #########################################################################

;绘制背景
DrawBackground proc
	.IF Scenario == 0
		INVOKE DrawObject, IMG_0, (ItemList[IMG_0*(TYPE MyItem)]).img,0,0,SCREEN_X,SCREEN_Y
	.ELSEIF Scenario == 1
		INVOKE DrawObject, IMG_1, (ItemList[IMG_1*(TYPE MyItem)]).img,0,0,SCREEN_X,SCREEN_Y
	.ELSEIF Scenario == 2
		INVOKE DrawObject, IMG_2, (ItemList[IMG_2*(TYPE MyItem)]).img,0,0,SCREEN_X,SCREEN_Y
	.ELSEIF Scenario == 3
		INVOKE DrawObject, IMG_300, (ItemList[IMG_300*(TYPE MyItem)]).img,0,0,SCREEN_X,SCREEN_Y
	.ELSEIF Scenario == 4
		INVOKE DrawObject, IMG_400, (ItemList[IMG_400*(TYPE MyItem)]).img,0,0,SCREEN_X,SCREEN_Y
	.ELSEIF Scenario == 5
		INVOKE DrawObject, IMG_500, (ItemList[IMG_500*(TYPE MyItem)]).img,0,0,SCREEN_X,SCREEN_Y
	.ELSEIF Scenario == 6
		INVOKE DrawObject, IMG_600, (ItemList[IMG_600*(TYPE MyItem)]).img,0,0,SCREEN_X,SCREEN_Y
	.ENDIF
	ret
DrawBackground endp

; #########################################################################

;绘制其余物品
DrawItems proc
	local i:DWORD
	mov i, 0
	mov ebx, i
	mov eax, pSequence[ebx]
	.WHILE eax != -1
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		mov cl, (ItemList[eax]).pMethod
		.IF cl == 0
			INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
		.ELSE
			INVOKE DrawTransparentObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1, (ItemList[eax]).iwidth, (ItemList[eax]).iheight
		.ENDIF
		add i, 4
		mov ebx, i
		mov eax, pSequence[ebx]

	.ENDW
	ret
DrawItems endp

; #########################################################################

;绘制Icons
DrawIcons proc
	local i:DWORD
	mov i, 0
	mov ebx, i
	mov eax, drawIcon[ebx]
	.WHILE eax != -1 && i < 20
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		mov cl, (ItemList[eax]).pMethod
		.IF cl == 0
			INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
		.ELSE
			INVOKE DrawTransparentObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1, (ItemList[eax]).iwidth, (ItemList[eax]).iheight
		.ENDIF
		add i, 4
		mov ebx, i
		mov eax, drawIcon[ebx]

	.ENDW
	ret
DrawIcons endp

; #########################################################################

;绘制收集品
DrawCollection proc
	.IF Triangle == 1
		mov eax, IMG_422
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawTransparentObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
	.ENDIF
	.IF Cross == 1
		mov eax, IMG_510
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawTransparentObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
	.ENDIF
	.IF Circle == 1
		mov eax, IMG_612
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawTransparentObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
	.ENDIF
	ret
DrawCollection endp

; #########################################################################

;绘制提示
DrawPassBy proc
	.IF PassBy == -1
		ret
	.ENDIF
	mov eax, PassBy
	mov esi, eax
	mov edx, TYPE MyItem
	mul edx
	mov cl, (ItemList[eax]).pMethod
	.IF cl == 0
		INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
	.ELSE
		INVOKE DrawTransparentObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1, (ItemList[eax]).iwidth, (ItemList[eax]).iheight
	.ENDIF
	ret
DrawPassBy endp

; #########################################################################

;绘制场景五的倒刺
DrawSting proc
	mov eax, IMG_501
	mov esi, eax
	mov edx, TYPE MyItem
	mul edx
	mov ebx, (ItemList[eax]).y1
	sub ebx, StingPos
	INVOKE DrawTransparentObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, ebx, (ItemList[eax]).iwidth, (ItemList[eax]).iheight
	.IF StingPos == 0 && cClick == 1
		mov PassBy, -1
		mov cJudge, 0
		mov cClick, 0
		mov Click_X, 105
		mov Orientation, 1
		INVOKE mciSendString,ADDR closeTextBGM, NULL, 0, NULL
		INVOKE RunForYourLife
		jmp _EXIT
	.ELSEIF StingPos == 0 && cClick == 0
		INVOKE RunForYourLife
		jmp _EXIT
	.ENDIF
	.IF door5Open == 0 && isStopped == 0 && check_collection == 0 && check_solution == 0
		sub StingPos, 1
	.ENDIF
_EXIT:
	ret
DrawSting endp

; #########################################################################

;绘制场景五的圈
DrawRounds proc
	LOCAL count:DWORD
	mov ecx, 0
	mov eax, Rounds[ecx*4]
	mov esi, eax
	mov edx, TYPE MyItem
	mul edx
	INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1, (ItemList[eax]).iwidth, (ItemList[eax]).iheight
	mov count, 1
	.WHILE count < 3
		mov ecx, count
		mov eax, Rounds[ecx*4]
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawTransparentObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1, (ItemList[eax]).iwidth, (ItemList[eax]).iheight
		inc count
	.ENDW
_EXIT:
	ret
DrawRounds endp

; #########################################################################

;绘制场景6的灯
DrawLight proc
	.IF Light6 == -1
		jmp _EXIT
	.ELSEIF LightCount == 0
		mov Light6, -1
		jmp _EXIT
	.ELSE
		.IF LightCount == 5
			mov pThief, 1
			mov cClick, 1
			mov cJudge, 1
			mov PassBy, -1
		.ENDIF
		mov eax, Light6
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1, (ItemList[eax]).iwidth, (ItemList[eax]).iheight
		dec LightCount
	.ENDIF
_EXIT:
	ret
DrawLight endp

; #########################################################################

;绘制鬼
DrawGhost proc
	.IF Light6 == IMG_60703 || Light6 == IMG_60803 || Light6 == IMG_60903 || Light6 == IMG_61003
		jmp _EXIT
	.ENDIF
	.IF GhostStep == -1
		jmp _EXIT
	.ELSEIF GhostStep == 4
		mov eax, IMG_60702
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1, (ItemList[eax]).iwidth, (ItemList[eax]).iheight
		jmp _EXIT
	.ELSEIF GhostStep == 5
		mov eax, IMG_60902
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1, (ItemList[eax]).iwidth, (ItemList[eax]).iheight
		jmp _EXIT
	.ELSEIF GhostStep == 6
		mov eax, IMG_60802
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1, (ItemList[eax]).iwidth, (ItemList[eax]).iheight
		jmp _EXIT
	.ELSEIF GhostStep == 7
		mov eax, IMG_61002
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1, (ItemList[eax]).iwidth, (ItemList[eax]).iheight
		jmp _EXIT
	.ELSEIF GhostStep == 8 && CircleShow == 0
		INVOKE addTopSequence, IMG_61101
		mov CircleShow, 1
	.ELSEIF GhostStep <= 3
		mov eax, IMG_60601
		add eax, GhostStep
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1, (ItemList[eax]).iwidth, (ItemList[eax]).iheight
		.IF GhostCount == 0
			inc GhostStep
			mov GhostCount, 10
			.IF GhostStep == 4
				mov cClick, 1
				INVOKE addTopSequence, IMG_60605
				INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
				INVOKE PlayVolume,hWinMain,ADDR Volume14
				jmp _EXIT
			.ENDIF
		.ENDIF
		dec GhostCount
	.ENDIF
_EXIT:
	ret
DrawGhost endp

; #########################################################################

;绘制暂停提示
DrawStopFlag proc
	
	.IF isPlayingBGM == 1
		mov eax, IMG_90101
	.ELSE
		mov eax, IMG_90102
	.ENDIF
	mov esi, eax
	mov edx, TYPE MyItem
	mul edx
	INVOKE DrawTransparentObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight

	ret
DrawStopFlag endp

; #########################################################################

;绘制所得星星
DrawStar proc
	LOCAL count:DWORD

	mov count, 0
	mov eax, IMG_90200
	mov esi, eax
	mov edx, TYPE MyItem
	mul edx
	INVOKE DrawTransparentObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight

	.IF Pear == 1
		inc count
		mov eax, IMG_90201
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
	.ENDIF
	.IF Apple == 1
		inc count
		mov eax, IMG_90202
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
	.ENDIF
	.IF Banana == 1
		inc count
		mov eax, IMG_90203
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
	.ENDIF

	.IF count == 3
		mov eax, IMG_90204
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
	.ENDIF

	.IF Dog == 1
		mov eax, IMG_90206
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
	.ENDIF

	.IF Bug == 1
		mov eax, IMG_90205
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawTransparentObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
	.ENDIF

	ret
DrawStar endp

; #########################################################################

;绘制提示书
DrawBook proc
	mov eax, book_page
	mov esi, eax
	mov edx, TYPE MyItem
	mul edx
	INVOKE DrawTransparentObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
	ret
DrawBook endp

; #########################################################################

;绘制结束图
DrawFinish proc
	mov eax, IMG_700
	mov esi, eax
	mov edx, TYPE MyItem
	mul edx
	INVOKE DrawTransparentObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
	mov pThief, 0
	mov cClick, 1
	
	.IF Pear == 1
		mov eax, IMG_701
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
	.ENDIF
	.IF Apple == 1
		mov eax, IMG_702
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
	.ENDIF
	.IF Banana == 1
		mov eax, IMG_703
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
	.ENDIF

	.IF Pear == 1 && Apple == 1 && Banana == 1
		mov eax, IMG_705
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawTransparentObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
	.ENDIF

	.IF Dog == 1
		mov eax, IMG_704
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
		mov eax, IMG_706
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawTransparentObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
	.ENDIF

	ret
DrawFinish endp

; #########################################################################

;绘制场景三第二层的孔
DrawHoles proc
	LOCAL count:DWORD
	mov count, 0
	.WHILE count < 7
		mov ecx, count
		mov eax, Holes[ecx*4]
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawObject, esi, (ItemList[eax]).img, HolesX1[ecx*4], 441, (ItemList[eax]).iwidth, (ItemList[eax]).iheight
		inc count
	.ENDW
_EXIT:
	ret
DrawHoles endp

; #########################################################################

;绘制场景三第三层的眼睛
DrawEyes proc
	LOCAL count:DWORD
	mov ecx, 0
	.IF EyesCount[0] > 0 && EyesCount[4] > 0 && EyesCount[8] > 0 && EyesCount[12] > 0 && CollectionStep == 6
		INVOKE ChangepSequence, IMG_30904, IMG_30905
		mov CollectionStep, 7
		mov Thief_Y, 258
		mov cJudge, 0
		mov PassBy, IMG_31801
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume16
	.ENDIF
	mov count, 0
	.WHILE count < 4
		mov ecx, count
		.IF EyesCount[ecx*4] == 0
			jmp _NEXT
		.ELSEIF CollectionStep == 6
			dec EyesCount[ecx*4]
		.ENDIF
		mov eax, IMG_31701
		add eax, count
		mov esi, eax
		mov edx, TYPE MyItem
		mul edx
		INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1, (ItemList[eax]).iwidth, (ItemList[eax]).iheight
	_NEXT:
		inc count
	.ENDW
_EXIT:
	ret
DrawEyes endp

; #########################################################################

;进行画面绘制的函数
DrawProc proc

	INVOKE DrawBackground
	.IF Scenario > 2
		.IF Scenario == 4
			INVOKE DrawIcons
		.ENDIF
		INVOKE DrawItems
		.IF Scenario == 5
			INVOKE DrawRounds
		.ENDIF
		INVOKE DrawPassBy
		INVOKE DrawCollection
		.IF Scenario == 3 && CollectionStep >= 5
			.IF CollectionStep <= 8
				INVOKE DrawHoles
				.IF CollectionStep >= 6
					INVOKE DrawEyes
				.ENDIF
			.ENDIF
			.IF CollectionStep == 10 && Thief_X < 105
				mov isFinished, 1
			.ENDIF
		.ELSEIF Scenario == 5
			INVOKE DrawSting
			mov eax, IMG_511
			mov esi, eax
			mov edx, TYPE MyItem
			mul edx
			INVOKE DrawObject, esi, (ItemList[eax]).img, (ItemList[eax]).x1, (ItemList[eax]).y1, (ItemList[eax]).iwidth, (ItemList[eax]).iheight
		.ELSEIF Scenario == 6
			INVOKE DrawLight
			INVOKE DrawGhost
		.ENDIF
		.IF pThief == 1
			INVOKE DrawThief
		.ENDIF
	.ENDIF
	.IF isStopped == 1
		INVOKE DrawStopFlag
	.ELSEIF check_collection == 1 || get_collection == 1
		INVOKE DrawStar
	.ELSEIF check_solution == 1
		INVOKE DrawBook
	.ELSEIF isFinished == 1
		INVOKE DrawFinish
	.ENDIF
    ret

DrawProc endp

