
; #########################################################################

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

restartGame proc
	mov cClick, 1
	mov cJudge, 1
	mov pThief, 1
	mov isStopped, 0
	
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
	mov Triangle, 0
	mov Cross, 0	
	mov Circle, 0
	mov CircleShow, 0
	mov door3Open, 0
	mov door5Open, 0

	mov Scenario, 3
	mov Thief_X, 79
	mov Thief_Y, 128
	mov Click_X, 79
	mov Click_Y, 128
	mov pSequence[0], IMG_30201
	inc pSequenceLength

restartGame endp

; #########################################################################

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
;检查场景5的圈是否正确
CheckRounds proc
	.IF Rounds[0] == IMG_5020102 && Rounds[4] == IMG_5020203 && Rounds[8] == IMG_5020304
		mov door5Open, 1
		INVOKE addTopSequence, IMG_507
	.ENDIF
	ret
CheckRounds endp

; #########################################################################

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
;针对场景3的事件响应
eventResponses3 proc imageID: DWORD
	mov ecx, 0
	mov Run, 0
	;到场景4的门
	.IF imageID == IMG_30202
		INVOKE ResetpSequence
		mov Scenario, 4
		mov Thief_X, 120
		mov Thief_Y, 510
		mov Click_X, 120
		mov Click_Y, 510
		mov Orientation, 0
		.IF step == 5 && Apple == 0 && AppleShow == 0
			INVOKE isCorrectOrder
			.IF eax == 1
				mov AppleShow, 1
				mov ebx, pSequenceLength
				mov pSequence[ebx * 4], IMG_42101
				add pSequenceLength, 1
			.ENDIF
		.ENDIF
	;到场景5的门
	.ELSEIF imageID == IMG_30302
		INVOKE ResetpSequence
		mov Scenario, 5
		mov Thief_X, 120
		mov Thief_Y, 500
		mov Click_X, 120
		mov Click_Y, 500
		mov Orientation, 0
		.IF pearStep == 0
			mov eax, IMG_50901
		.ELSEIF pearStep == 1
			mov eax, IMG_50902
		.ELSEIF pearStep == 2
			mov eax, IMG_50903
		.ELSEIF pearStep == 3
			;mov eax, IMG_50902
		.ELSEIF pearStep == 4
			mov eax, IMG_50906
		.ENDIF
		mov pSequence[0], eax
		mov pSequenceLength, 1
		.IF door5Open == 1
			mov pSequence[4], IMG_507
			inc pSequenceLength
		.ENDIF
	;到场景6的门
	.ELSEIF imageID == IMG_30402
		INVOKE ResetpSequence
		mov Scenario, 6
		mov Thief_X, 675
		mov Thief_Y, 510
		mov Orientation, 1
	;上下的门之上
	.ELSEIF imageID == IMG_30601
		mov Thief_X, 720
		mov Thief_Y, 452
		mov Orientation, 1
	;上下的门之下
	.ELSEIF imageID == IMG_30602
		mov Thief_X, 640
		mov Thief_Y, 148
		INVOKE CalculateThiefY3
		mov Orientation, 1
	;上下的楼梯之上
	.ELSEIF imageID == IMG_30701
		mov Thief_X, 720
		mov Thief_Y, 265
		mov Orientation, 1
	;上下的楼梯之下
	.ELSEIF imageID == IMG_30702
		mov Thief_X, 720
		mov Thief_Y, 148
		INVOKE CalculateThiefY3
		mov Orientation, 1
	;放三个collection
	.ELSEIF imageID == IMG_30801
		mov Triangle, 2
		INVOKE addTopSequence, IMG_30802
		mov CollectionStep, 1
	.ELSEIF imageID == IMG_30803
		mov Cross, 2
		mov CollectionStep, 2
		INVOKE ChangepSequence, IMG_30802, IMG_30804
	.ELSEIF imageID == IMG_30805
		mov Circle, 2
		mov CollectionStep, 3
		INVOKE ChangepSequence, IMG_30804, IMG_30806
		INVOKE addTopSequence, IMG_30901
	.ELSEIF imageID == IMG_310
		INVOKE ChangepSequence, IMG_30901, IMG_30902
		mov Thief_Y, 451
		mov CollectionStep, 4
	.ELSE
		jmp _EXIT
	.ENDIF
	mov eax, Thief_X
	mov Click_X, eax
	mov eax, Thief_Y
	mov Click_Y, eax
_EXIT:
	ret
eventResponses3 endp

; #########################################################################

;针对场景4的事件响应
eventResponses4 proc imageID: DWORD
	mov ecx, 0
	mov Run, 0
	.IF imageID == IMG_0
	;点击了五个icon之一
	.ELSEIF imageID == IMG_415 || imageID == IMG_416 || imageID == IMG_417 || imageID == IMG_418 || imageID == IMG_419
		INVOKE removeIcon, imageID
		mov eax, step
		mov ebx, imageID
		mov player[eax*4], ebx
		add step, 1
	;点击了门
	.ELSEIF imageID >= IMG_401 && imageID <=IMG_414
		INVOKE doorTransition, imageID
	;点击了拿起三角
	.ELSEIF imageID == IMG_42001
		mov Triangle, 1
		INVOKE addTopSequence, IMG_42002
		inc ecx
	;点击了拿起苹果
	.ELSEIF imageID == IMG_42102
		mov Apple, 1
		INVOKE ChangepSequence, IMG_42101, IMG_42104
		mov pThief, 0
		mov PPTstatus, 1
		jmp _EXIT
	.ENDIF
	.IF step == 5 && Apple == 0 && AppleShow == 0
		INVOKE isCorrectOrder
		.IF eax == 1
			mov AppleShow, 1
			mov ebx, pSequenceLength
			mov pSequence[ebx * 4], IMG_42101
			add pSequenceLength, 1
		.ELSE
			INVOKE resetIcon
			mov step, 0
		.ENDIF
	.ELSE
		jmp _EXIT
	.ENDIF
	mov eax, Thief_X
	mov Click_X, eax
	mov eax, Thief_Y
	mov Click_Y, eax
_EXIT:
	ret
eventResponses4 endp

; #########################################################################
;针对场景5的事件响应
eventResponses5 proc imageID: DWORD
	mov ecx, 0
	mov Run, 0
	.IF imageID == IMG_503
		mov Scenario, 3
		INVOKE ResetpSequence
		.IF Cross == 1
			mov pSequence[0], IMG_30401
		.ELSE
			mov pSequence[0], IMG_30301
		.ENDIF
		mov pSequenceLength, 1
		mov Thief_Y, 148
		mov Thief_X, 353
		INVOKE CalculateThiefY3
		mov StingPos, 300
		mov Orientation, 0
	.ELSEIF imageID == IMG_504	;外圈
		.IF Rounds[0] == IMG_5020104
			mov Rounds[0], IMG_5020101
		.ELSE
			inc Rounds[0]
		.ENDIF
		INVOKE CheckRounds
	.ELSEIF imageID == IMG_505	;中圈
		.IF Rounds[4] == IMG_5020204
			mov Rounds[4], IMG_5020201
		.ELSE
			inc Rounds[4]
		.ENDIF
		INVOKE CheckRounds
	.ELSEIF imageID == IMG_506	;内圈
		.IF Rounds[8] == IMG_5020304
			mov Rounds[8], IMG_5020301
		.ELSE
			inc Rounds[8]
		.ENDIF
		INVOKE CheckRounds
	.ELSEIF imageID == IMG_50801
		mov Cross, 1
		INVOKE addTopSequence, IMG_50802
	.ELSEIF imageID == IMG_50901
		mov pearStep, 1
		mov pSequence[0], IMG_50902
	.ELSEIF imageID == IMG_50902
		mov pearStep, 2
		mov pSequence[0], IMG_50903
	.ELSEIF imageID == IMG_50904
		mov pearStep, 3
		mov PPTstatus, 2
		mov pSequence[0], IMG_50905
		mov pThief, 0
		jmp _EXIT
	.ELSE
		jmp _EXIT
	.ENDIF
	mov eax, Thief_X
	mov Click_X, eax
	mov eax, Thief_Y
	mov Click_Y, eax
_EXIT:
	ret
eventResponses5 endp

; #########################################################################

;针对场景6的事件响应
eventResponses6 proc imageID: DWORD
	mov ecx, 0
	mov Run, 0
	;门
	.IF imageID == IMG_601
		mov Scenario, 3
		INVOKE ResetpSequence
		.IF Circle == 1
			mov door3Open, 1
			mov pSequence[0], IMG_305
		.ELSE
			mov pSequence[0], IMG_30401
		.ENDIF
		mov pSequenceLength, 1
		mov Thief_Y, 148
		mov Thief_X, 470
		INVOKE CalculateThiefY3
		mov Click_X, 470
		mov eax, Thief_Y
		mov Click_Y, eax
		mov Orientation, 0
	;四个控制灯的把手
	.ELSEIF imageID == IMG_60201
		mov PassBy, IMG_60202
		mov pThief, 0
		mov cClick, 0
		mov cJudge, 0
		.IF GhostStep == 5
			mov Light6, IMG_60903
			mov LightCount, 15
			inc GhostStep
		.ELSE
			mov Light6, IMG_60901
			mov LightCount, 15
		.ENDIF
	.ELSEIF imageID == IMG_60301
		mov PassBy, IMG_60302
		mov pThief, 0
		mov cClick, 0
		mov cJudge, 0
		.IF GhostStep == 4
			mov Light6, IMG_60703
			mov LightCount, 15
			inc GhostStep
		.ELSE
			mov Light6, IMG_60701
			mov LightCount, 15
		.ENDIF
	.ELSEIF imageID == IMG_60401
		mov PassBy, IMG_60402
		mov pThief, 0
		mov cClick, 0
		mov cJudge, 0
		.IF GhostStep == 7
			mov Light6, IMG_61003
			mov LightCount, 15
			inc GhostStep
		.ELSE
			mov Light6, IMG_61001
			mov LightCount, 15
		.ENDIF
	.ELSEIF imageID == IMG_60501
		mov PassBy, IMG_60502
		mov pThief, 0
		mov cClick, 0
		mov cJudge, 0
		.IF GhostStep == 6
			mov Light6, IMG_60803
			mov LightCount, 15
			inc GhostStep
		.ELSE
			mov Light6, IMG_60801
			mov LightCount, 15
		.ENDIF
	;拿圆
	.ELSEIF imageID == IMG_61102
		mov Circle, 1
		mov ecx, 0
		.WHILE ecx < pSequenceLength
			mov ebx, pSequence[ecx * 4]
			.IF ebx == IMG_61101
				mov ebx, ecx
				inc ebx
				mov eax, pSequence[ebx * 4]
				mov pSequence[ecx * 4], eax
				mov pSequence[ecx * 4+4], -1
				dec pSequenceLength
				jmp _EXIT
			.ENDIF
			inc ecx
		.ENDW
	;香蕉机关
	.ELSEIF imageID == IMG_61301
		INVOKE addTopSequence, IMG_61401
		mov BananaShow, 1
	;香蕉
	.ELSEIF imageID == IMG_61402
		;INVOKE addTopSequence, IMG_61404
		mov pThief, 0
		mov PPTstatus, 3
		INVOKE ChangepSequence, IMG_61401, IMG_61403
		jmp _EXIT
	.ELSE
		jmp _EXIT
	.ENDIF
	mov eax, Thief_X
	mov Click_X, eax
	mov eax, Thief_Y
	mov Click_Y, eax
_EXIT:
	ret
eventResponses6 endp

; #########################################################################

processScenario0 proc
	INVOKE clickPosition, 350, 477, 446, 574
	.IF eax == 1
		mov Scenario, 1
	.ENDIF
	ret
processScenario0 endp

; #########################################################################

processScenario1 proc
	INVOKE clickPosition, 362, 495, 434, 568
	.IF eax == 1
		mov Scenario, 2
	.ENDIF
	ret
processScenario1 endp

; #########################################################################

processScenario2 proc
	INVOKE clickPosition, 365, 429, 443, 506
	.IF eax == 1
		mov Scenario, 3
		mov Thief_X, 79
		mov Thief_Y, 128
		mov Click_X, 79
		mov Click_Y, 128
		mov pSequence[0], IMG_30201
		inc pSequenceLength
	.ENDIF
	ret
processScenario2 endp

; #########################################################################

processScenario3 proc
	LOCAL imgID: DWORD, count: DWORD
	;提示
	mov ebx, PassBy
	.IF ebx != -1
		mov edx, TYPE MyItem
		mov eax, ebx
		mul edx
		mov ebx, eax
		INVOKE clickPosition, (ItemList[ebx]).x1, (ItemList[ebx]).y1, (ItemList[ebx]).x2, (ItemList[ebx]).y2
		.IF eax == 1
			INVOKE eventResponses3, PassBy
		.ENDIF
	.ENDIF
	;其余
	mov ecx, 0
	mov count, 0
	.WHILE pSequence[ecx*4] >= 0 && ecx < pSequenceLength
		mov ebx, pSequence[ecx*4]
		mov imgID, ebx
		mov edx, TYPE MyItem
		mov eax, ebx
		mul edx
		mov esi, eax
		mov dl, (ItemList[esi]).eClick
		.IF dl == 0
			jmp _NEXT
		.ENDIF
		INVOKE clickPosition, (ItemList[esi]).x1, (ItemList[esi]).y1, (ItemList[esi]).x2, (ItemList[esi]).y2
		.IF eax == 1
			INVOKE eventResponses3, imgID
			mov ebx, Thief_X
			mov Click_X, ebx
			ret
		.ENDIF
		_NEXT:
			add count, 1
			mov ecx, count
	.ENDW
ending:
	ret
processScenario3 endp

; #########################################################################

processScenario4 proc
	LOCAL imgID: DWORD, count: DWORD
	;拿苹果时的ppt
	.IF PPTstatus == 1
		INVOKE ChangepSequence, IMG_42104, IMG_42103
		mov pThief, 1
		mov Thief_X, 380
		mov Click_X, 380
		mov Orientation, 1
		mov PPTstatus, 0
		jmp ending
	.ENDIF
	;提示
	mov ebx, PassBy
	.IF ebx != -1
		mov edx, TYPE MyItem
		mov eax, ebx
		mul edx
		mov ebx, eax
		INVOKE clickPosition, (ItemList[ebx]).x1, (ItemList[ebx]).y1, (ItemList[ebx]).x2, (ItemList[ebx]).y2
		.IF eax == 1
			INVOKE eventResponses4, PassBy
			jmp ending
		.ENDIF
		.IF Scenario == 3
			jmp ending
		.ENDIF
	.ENDIF
	;五个icon
	mov count, 0
	mov ecx, 0
	.WHILE drawIcon[ecx*4] >= 0 && ecx < 5
		mov ebx, drawIcon[ecx*4]
		mov imgID, ebx
		mov edx, TYPE MyItem
		mov eax, ebx
		mul edx
		mov esi, eax
		mov dl,  (ItemList[esi]).eClick 
		.IF dl== 0
			ret
		.ENDIF
		INVOKE clickPosition, (ItemList[esi]).x1, (ItemList[esi]).y1, (ItemList[esi]).x2, (ItemList[esi]).y2
		.IF eax == 1
			INVOKE eventResponses4, imgID
			ret
		.ELSE
			add count, 1
			mov ecx, count
		.ENDIF
	.ENDW
	;其余
	mov ecx, 0
	mov count, 0
	.WHILE pSequence[ecx*4] >= 0 && ecx < pSequenceLength
		mov ebx, pSequence[ecx*4]
		mov imgID, ebx
		mov edx, TYPE MyItem
		mov eax, ebx
		mul edx
		mov esi, eax
		mov dl, (ItemList[esi]).eClick
		.IF dl == 0
			jmp _NEXT
		.ENDIF
		INVOKE clickPosition, (ItemList[esi]).x1, (ItemList[esi]).y1, (ItemList[esi]).x2, (ItemList[esi]).y2
		.IF eax == 1
			INVOKE eventResponses4, imgID
			mov ebx, Thief_X
			mov Click_X, ebx
			ret
		.ENDIF
		_NEXT:
			add count, 1
			mov ecx, count
	.ENDW
ending:
	ret
processScenario4 endp

; #########################################################################

processScenario5 proc
	LOCAL imgID: DWORD, count: DWORD
	;拿梨子时的ppt
	.IF PPTstatus == 2
		mov pSequence[0], IMG_50906
		mov pThief, 1
		mov Thief_X, 720
		mov Click_X, 720
		mov Orientation, 0
		mov PPTstatus, 0
		mov Pear, 1
		mov pearStep, 4
		jmp ending
	.ENDIF
	;提示
	mov ebx, PassBy
	.IF ebx != -1
		mov edx, TYPE MyItem
		mov eax, ebx
		mul edx
		mov ebx, eax
		INVOKE clickPosition, (ItemList[ebx]).x1, (ItemList[ebx]).y1, (ItemList[ebx]).x2, (ItemList[ebx]).y2
		.IF eax == 1
			INVOKE eventResponses5, PassBy
		.ENDIF
	.ENDIF
	;其余
	mov ecx, 0
	mov count, 0
	.WHILE pSequence[ecx*4] >= 0 && ecx < pSequenceLength
		mov ebx, pSequence[ecx*4]
		mov imgID, ebx
		mov edx, TYPE MyItem
		mov eax, ebx
		mul edx
		mov esi, eax
		mov dl, (ItemList[esi]).eClick
		.IF dl == 0
			jmp _NEXT
		.ENDIF
		INVOKE clickPosition, (ItemList[esi]).x1, (ItemList[esi]).y1, (ItemList[esi]).x2, (ItemList[esi]).y2
		.IF eax == 1
			INVOKE eventResponses5, imgID
			mov ebx, Thief_X
			mov Click_X, ebx
			ret
		.ENDIF
		_NEXT:
			add count, 1
			mov ecx, count
	.ENDW
ending:
	ret
processScenario5 endp

; #########################################################################

processScenario6 proc
	LOCAL imgID: DWORD, count: DWORD
	;
	.IF PPTstatus == 3
		INVOKE ChangepSequence, IMG_61403, IMG_61404
		mov PPTstatus, 0
		mov pThief, 1
		mov Thief_X, 485
		mov Thief_Y, 510
		mov Click_X, 485
		mov Click_Y, 510
		mov Orientation, 0
		mov Banana, 1
		mov BananaShow, 0
		jmp ending
	.ENDIF
	;提示
	mov ebx, PassBy
	.IF ebx != -1
		mov edx, TYPE MyItem
		mov eax, ebx
		mul edx
		mov ebx, eax
		INVOKE clickPosition, (ItemList[ebx]).x1, (ItemList[ebx]).y1, (ItemList[ebx]).x2, (ItemList[ebx]).y2
		.IF eax == 1
			INVOKE eventResponses6, PassBy
			mov ebx, Thief_X
			mov Click_X, ebx
			mov ebx, Thief_Y
			mov Click_Y, ebx
		.ENDIF
	.ENDIF
	;其余
	mov ecx, 0
	mov count, 0
	.WHILE pSequence[ecx*4] >= 0 && ecx < pSequenceLength
		mov ebx, pSequence[ecx*4]
		mov imgID, ebx
		mov edx, TYPE MyItem
		mov eax, ebx
		mul edx
		mov esi, eax
		mov dl, (ItemList[esi]).eClick
		.IF dl == 0
			jmp _NEXT
		.ENDIF
		INVOKE clickPosition, (ItemList[esi]).x1, (ItemList[esi]).y1, (ItemList[esi]).x2, (ItemList[esi]).y2
		.IF eax == 1
			INVOKE eventResponses6, imgID
			mov ebx, Thief_X
			mov Click_X, ebx
			ret
		.ENDIF
		_NEXT:
			add count, 1
			mov ecx, count
	.ENDW
ending:
	ret
processScenario6 endp

; #########################################################################

processScenario7 proc
	ret
processScenario7 endp

; #########################################################################

processScenario8 proc
	ret
processScenario8 endp

; #########################################################################

processMouseEvent proc currentScenario:DWORD
	.IF isStopped == 0 && currentScenario >= 3 && currentScenario <= 6
		; stop
		INVOKE clickPosition, 19, 16, 55, 45
		.IF eax == 1 
			mov isStopped, 1
			mov pThief, 0
			.IF PassBy != -1
				mov esi, PassBy
				mov PassBy_Old, esi
				mov PassBy, -1
			.ENDIF
			.IF isPlayingBGM == 1
				mov ecx, pSequenceLength
				mov pSequence[ecx*4], IMG_90101
				inc pSequenceLength
			.ELSEIF isPlayingBGM == 0
				mov ecx, pSequenceLength
				mov pSequence[ecx*4], IMG_90102
				inc pSequenceLength
			.ENDIF
			jmp _EXIT
		.ENDIF
		; star
		INVOKE clickPosition, 63, 16, 96, 45
		.IF eax == 1
			jmp _EXIT
		.ENDIF
	.ELSEIF isStopped == 1 && currentScenario >= 3 && currentScenario <= 6
		; continue
		INVOKE clickPosition, 72, 88, 118, 145
		.IF eax == 1
			mov isStopped, 0
			mov pThief, 1
			dec pSequenceLength
			mov ecx, pSequenceLength
			mov pSequence[ecx*4], -1
			mov esi, Thief_X 
			mov Click_X, esi
			mov esi, Thief_Y 
			mov Click_Y, esi
			.IF PassBy_Old != -1
				mov esi, PassBy_Old
				mov PassBy, esi
			.ENDIF
			jmp _EXIT
		.ENDIF
		; restart
		INVOKE clickPosition, 72, 172, 118, 225
		.IF eax == 1
			INVOKE restartGame
			jmp _EXIT
		.ENDIF
		; sound
		INVOKE clickPosition, 72, 255, 118, 310
		.IF eax == 1
			.IF isPlayingBGM == 1
				mov ecx, pSequenceLength
				dec ecx
				mov pSequence[ecx*4], IMG_90102
				mov isPlayingBGM, 0
				; stop the music
			.ELSEIF isPlayingBGM == 0
				mov ecx, pSequenceLength
				dec ecx
				mov pSequence[ecx*4], IMG_90101
				mov isPlayingBGM, 1
				; restart the music
			.ENDIF
			jmp _EXIT
		.ENDIF
	.ENDIF
	.IF currentScenario == 0
		INVOKE processScenario0
	.ELSEIF currentScenario == 1
		INVOKE processScenario1
	.ELSEIF currentScenario == 2
		INVOKE processScenario2
	.ELSEIF currentScenario == 3
		INVOKE processScenario3
	.ELSEIF currentScenario == 4
		INVOKE processScenario4
	.ELSEIF currentScenario == 5
		INVOKE processScenario5
	.ELSEIF currentScenario == 6
		INVOKE processScenario6
	.ELSEIF currentScenario == 7
		INVOKE processScenario7
	.ELSEIF currentScenario == 8
		INVOKE processScenario8
	.ENDIF

_EXIT:
	ret
processMouseEvent endp

; #########################################################################