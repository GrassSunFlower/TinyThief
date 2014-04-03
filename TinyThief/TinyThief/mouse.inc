
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
		mov ecx, pSequenceLength
		mov pSequence[ecx*4], IMG_507
		inc pSequenceLength
	.ENDIF
	ret
CheckRounds endp

; #########################################################################

doorTransition proc imageID: DWORD
	.IF imageID == IMG_401
		mov Thief_X, 136
		mov Thief_Y, 293
		mov PassBy, -1
		mov Orientation, 0
	.ELSEIF imageID == IMG_402
		mov Thief_X, 481
		mov Thief_Y, 510
		mov PassBy, -1
		mov Orientation, 0
	.ELSEIF imageID == IMG_403
		mov Thief_X, 591
		mov Thief_Y, 290
		mov PassBy, -1
		mov Orientation, 0
	.ELSEIF imageID == IMG_404
		mov Thief_X, 416
		mov Thief_Y, 340
		mov PassBy, -1
		mov Orientation, 0
	.ELSEIF imageID == IMG_405
		mov Thief_X, 718
		mov Thief_Y, 146
		mov PassBy, -1
		mov Orientation, 1
	.ELSEIF imageID == IMG_406
		mov Thief_X, 591
		mov Thief_Y, 510
		mov PassBy, -1
		mov Orientation, 1
	.ELSEIF imageID == IMG_407
		mov Thief_X, 264
		mov Thief_Y, 510
		mov PassBy, -1
		mov Orientation, 1
	.ELSEIF imageID == IMG_408
		mov Thief_X, 714
		mov Thief_Y, 510
		mov PassBy, -1
		mov Orientation, 1
	.ELSEIF imageID == IMG_409
		mov Thief_X, 364
		mov Thief_Y, 151
		mov PassBy, -1
		mov Orientation, 1
	.ELSEIF imageID == IMG_410	;切换回场景3
		mov Thief_X, 286
		mov Thief_Y, 148
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
		mov Thief_X, 716
		mov Thief_Y, 290
		mov PassBy, -1
		mov Orientation, 1
	.ELSEIF imageID == IMG_412
		mov Thief_X, 416
		mov Thief_Y, 340
		mov PassBy, -1
		mov Orientation, 0
	.ELSEIF imageID == IMG_413
		mov Thief_X, 264
		mov PassBy, -1
		mov Orientation, 1
	.ELSEIF imageID == IMG_414
		mov Thief_X, 581
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
	.IF imageID == IMG_30202
		INVOKE ResetpSequence
		mov Scenario, 4
		mov Thief_X, 136
		mov Thief_Y, 510
		mov Click_X, 136
		mov Thief_Y, 510
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
	.ELSEIF imageID == IMG_30302
		INVOKE ResetpSequence
		mov Scenario, 5
		mov Thief_X, 136
		mov Thief_Y, 500
		mov Click_X, 136
		mov Thief_Y, 500
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
	.ELSEIF imageID == IMG_30402
		INVOKE ResetpSequence
		mov Scenario, 6
		mov Thief_X, 136
		mov Thief_Y, 510
		mov Click_X, 136
		mov Thief_Y, 510
		mov Orientation, 0
	.ENDIF
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
		mov edx, Thief_X
		mov Click_X, edx
		mov edx, Thief_Y
		mov Click_Y, edx
	;点击了门
	.ELSEIF imageID >= IMG_401 && imageID <=IMG_414
		INVOKE doorTransition, imageID
		mov edx, Thief_X
		mov Click_X, edx
		mov edx, Thief_Y
		mov Click_Y, edx
		jmp _EXIT
	;点击了拿起三角
	.ELSEIF imageID == IMG_42001
		mov Triangle, 1
		mov ecx, pSequenceLength
		mov pSequence[ecx * 4], IMG_42002
		inc pSequenceLength
		inc ecx
	;点击了拿起苹果
	.ELSEIF imageID == IMG_42102
		mov Apple, 1
		mov ecx, 0
		.WHILE ecx < pSequenceLength
			mov ebx, pSequence[ecx * 4]
			.IF ebx == IMG_42101
				mov pSequence[ecx * 4], IMG_42104
				mov pThief, 0
				mov PPTstatus, 1
				jmp _EXIT
			.ENDIF
			inc ecx
		.ENDW
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
	.ENDIF
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
		mov Thief_X, 368
		mov Click_Y, 148
		mov Click_X, 368
		mov StingPos, 300
		mov Orientation, 0
	.ELSEIF imageID == IMG_504
		.IF Rounds[0] == IMG_5020104
			mov Rounds[0], IMG_5020101
		.ELSE
			inc Rounds[0]
		.ENDIF
		INVOKE CheckRounds
	.ELSEIF imageID == IMG_505
		.IF Rounds[4] == IMG_5020204
			mov Rounds[4], IMG_5020201
		.ELSE
			inc Rounds[4]
		.ENDIF
		INVOKE CheckRounds
	.ELSEIF imageID == IMG_506
		.IF Rounds[8] == IMG_5020304
			mov Rounds[8], IMG_5020301
		.ELSE
			inc Rounds[8]
		.ENDIF
		INVOKE CheckRounds
	.ELSEIF imageID == IMG_50801
		mov Cross, 1
		mov ecx, pSequenceLength
		mov pSequence[ecx*4], IMG_50802
		inc pSequenceLength
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
	.ENDIF
_EXIT:
	ret
eventResponses5 endp

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
	INVOKE clickPosition, 0, 0, SCREEN_X, SCREEN_Y
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
		mov Thief_X, 109
		mov Thief_Y, 128
		mov Click_X, 109
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
		mov ecx, 0
		.WHILE ecx < pSequenceLength
			mov ebx, pSequence[ecx * 4]
			.IF ebx == IMG_42104
				mov pSequence[ecx * 4], IMG_42103
				mov pThief, 1
				mov Thief_X, 396
				mov Click_X, 396
				mov Orientation, 1
				mov PPTstatus, 0
				jmp ending
			.ENDIF
			inc ecx
		.ENDW
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
	;提示
	;拿梨子时的ppt
	.IF PPTstatus == 2
		mov pSequence[0], IMG_50906
		mov pThief, 1
		mov Thief_X, 735
		mov Click_X, 735
		mov Orientation, 0
		mov PPTstatus, 0
		mov Pear, 1
		mov pearStep, 4
		jmp ending
	.ENDIF
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
	mov ebx, 0
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

	ret
processMouseEvent endp

; #########################################################################