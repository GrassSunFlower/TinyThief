.code
; #########################################################################

;针对场景3的事件响应
eventResponses3 proc imageID: DWORD
	mov ecx, 0
	mov Run, 0
	;到场景4的门
	.IF imageID == IMG_30202
		INVOKE mciSendString,ADDR closeTextBGM, NULL, 0, NULL
		INVOKE mciSendString,ADDR BGMName3, NULL, 0, NULL
		INVOKE mciSendString,ADDR playTextBGM, NULL, 0, NULL
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume3
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
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume3
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
		INVOKE mciSendString,ADDR closeTextBGM, NULL, 0, NULL
		.IF door5Open == 1
			mov pSequence[4], IMG_507
			inc pSequenceLength
		.ELSE
			INVOKE mciSendString,ADDR BGMName4, NULL, 0, NULL
			INVOKE mciSendString,ADDR playTextBGM, NULL, 0, NULL
		.ENDIF
	;到场景6的门
	.ELSEIF imageID == IMG_30402
		INVOKE mciSendString,ADDR closeTextBGM, NULL, 0, NULL
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume3
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
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume3
	;上下的门之下
	.ELSEIF imageID == IMG_30602
		mov Thief_X, 640
		mov Thief_Y, 148
		INVOKE CalculateThiefY3
		mov Orientation, 1
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume3
	;上下的楼梯之上
	.ELSEIF imageID == IMG_30701
		mov Thief_X, 720
		mov Thief_Y, 265
		mov Orientation, 1
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume3
	;上下的楼梯之下
	.ELSEIF imageID == IMG_30702
		mov Thief_X, 720
		mov Thief_Y, 148
		INVOKE CalculateThiefY3
		mov Orientation, 1
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume3
	;放三个collection
	.ELSEIF imageID == IMG_30801
		mov Triangle, 2
		INVOKE addTopSequence, IMG_30802
		mov CollectionStep, 1
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume8
	.ELSEIF imageID == IMG_30803
		mov Cross, 2
		mov CollectionStep, 2
		INVOKE ChangepSequence, IMG_30802, IMG_30804
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume8
	.ELSEIF imageID == IMG_30805
		mov Circle, 2
		mov CollectionStep, 3
		INVOKE ChangepSequence, IMG_30804, IMG_30806
		INVOKE addTopSequence, IMG_30901
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume8
		INVOKE PlayVolume,hWinMain,ADDR Volume14
	;开启第一层
	.ELSEIF imageID == IMG_310
		INVOKE ChangepSequence, IMG_30901, IMG_30902
		mov Thief_Y, 420
		mov CollectionStep, 4
		INVOKE addTopSequence, IMG_31103
		INVOKE addTopSequence, IMG_31203
		INVOKE addTopSequence, IMG_31303
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume16
	;第一层的图标
	.ELSEIF imageID == IMG_31101 && CollectionStep == 4
		INVOKE ChangepSequence, IMG_31101, IMG_31102
	.ELSEIF imageID == IMG_31102 && CollectionStep == 4
		INVOKE ChangepSequence, IMG_31102, IMG_31103
		INVOKE FindpSequence, IMG_31201
		.IF eax == 1
			INVOKE FindpSequence, IMG_31302
		.ELSE
			jmp _EXIT
		.ENDIF
		.IF eax == 1
			INVOKE ChangepSequence, IMG_30902, IMG_30903
			mov CollectionStep, 5
			mov Thief_Y, 368
			INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
			INVOKE PlayVolume,hWinMain,ADDR Volume16
		.ELSE
			jmp _EXIT
		.ENDIF
	.ELSEIF imageID == IMG_31103 && CollectionStep == 4
		INVOKE ChangepSequence, IMG_31103, IMG_31101
	.ELSEIF imageID == IMG_31201 && CollectionStep == 4
		INVOKE ChangepSequence, IMG_31201, IMG_31202
	.ELSEIF imageID == IMG_31202 && CollectionStep == 4
		INVOKE ChangepSequence, IMG_31202, IMG_31203
	.ELSEIF imageID == IMG_31203
		INVOKE ChangepSequence, IMG_31203, IMG_31201
		INVOKE FindpSequence, IMG_31103
		.IF eax == 1
			INVOKE FindpSequence, IMG_31302
		.ELSE
			jmp _EXIT
		.ENDIF
		.IF eax == 1
			INVOKE ChangepSequence, IMG_30902, IMG_30903
			mov CollectionStep, 5
			mov Thief_Y, 368
			INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
			INVOKE PlayVolume,hWinMain,ADDR Volume16
		.ELSE
			jmp _EXIT
		.ENDIF
	.ELSEIF imageID == IMG_31301 && CollectionStep == 4
		INVOKE ChangepSequence, IMG_31301, IMG_31302
		INVOKE FindpSequence, IMG_31103
		.IF eax == 1
			INVOKE FindpSequence, IMG_31201
		.ELSE
			jmp _EXIT
		.ENDIF
		.IF eax == 1
			INVOKE ChangepSequence, IMG_30902, IMG_30903
			mov CollectionStep, 5
			mov Thief_Y, 368
			INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
			INVOKE PlayVolume,hWinMain,ADDR Volume16
		.ELSE
			jmp _EXIT
		.ENDIF
	.ELSEIF imageID == IMG_31302 && CollectionStep == 4
		INVOKE ChangepSequence, IMG_31302, IMG_31303
	.ELSEIF imageID == IMG_31303 && CollectionStep == 4
		INVOKE ChangepSequence, IMG_31303, IMG_31301
	;第二层
	.ELSEIF CollectionStep == 5 && imageID >= IMG_31401 && imageID <= IMG_31407
		mov eax, imageID
		sub eax, IMG_31401
		INVOKE  MoveHoles, eax
	;点击了水獭
	.ELSEIF CollectionStep > 5 && imageID == IMG_31404 && Dog == 0
		mov Dog, 1
		mov Holes[12], IMG_31404
		INVOKE addTopSequence, IMG_316
		mov PPTstatus, 5
		mov get_collection, 1
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume5
	;第三层
	.ELSEIF CollectionStep == 6 && imageID >= IMG_31701 && imageID <= IMG_31704
		.IF imageID == IMG_31701
			mov EyesCount[0], 8
			INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
			INVOKE PlayVolume,hWinMain,ADDR Volume7
		.ELSEIF imageID == IMG_31702
			mov EyesCount[4], 24
			INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
			INVOKE PlayVolume,hWinMain,ADDR Volume7
		.ELSEIF imageID == IMG_31703
			mov EyesCount[8], 16
			INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
			INVOKE PlayVolume,hWinMain,ADDR Volume7
		.ELSEIF imageID == IMG_31704
			mov EyesCount[12], 32
			INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
			INVOKE PlayVolume,hWinMain,ADDR Volume7
		.ENDIF
	;拿虫子
	.ELSEIF CollectionStep == 7 && imageID == IMG_31801
		mov cJudge, 0
		mov PassBy, -1
		mov pThief, 0
		mov Bug, 1
		mov PPTstatus, 4
		mov get_collection, 1
		mov CollectionStep, 8
		INVOKE addTopSequence, IMG_31802
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume5
	.ELSEIF CollectionStep == 9 && imageID == IMG_319
		mov cClick, 0
		mov cJudge, 0
		mov CollectionStep, 10
		mov Click_X, 100
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume6
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
		mov esi, Thief_X 
		mov Click_X, esi
		mov esi, Thief_Y 
		mov Click_Y, esi
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume10
	;点击了门
	.ELSEIF imageID >= IMG_401 && imageID <=IMG_414
		INVOKE doorTransition, imageID
		mov eax, Thief_X
		mov Click_X, eax
		mov eax, Thief_Y
		mov Click_Y, eax
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume3
	;点击了拿起三角
	.ELSEIF imageID == IMG_42001
		mov Triangle, 1
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume4
		INVOKE addTopSequence, IMG_42002
		inc ecx
	;点击了拿起苹果
	.ELSEIF imageID == IMG_42102
		mov Apple, 1
		mov get_collection, 1
		INVOKE ChangepSequence, IMG_42101, IMG_42104
		mov pThief, 0
		mov PPTstatus, 1
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume2
		jmp _EXIT
	.ENDIF
	.IF step == 5 && Apple == 0 && AppleShow == 0 && Scenario == 4
		INVOKE isCorrectOrder
		.IF eax == 1
			mov AppleShow, 1
			mov ebx, pSequenceLength
			mov pSequence[ebx * 4], IMG_42101
			add pSequenceLength, 1
			INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
			INVOKE PlayVolume,hWinMain,ADDR Volume17
		.ELSE
			INVOKE resetIcon
			mov step, 0
		.ENDIF
	.ELSE
		jmp _EXIT
	.ENDIF
_EXIT:
	ret
eventResponses4 endp

; #########################################################################

;针对场景5的事件响应
eventResponses5 proc imageID: DWORD
	mov ecx, 0
	mov Run, 0
	;切换回场景3
	.IF imageID == IMG_503
		INVOKE mciSendString,ADDR closeTextBGM, NULL, 0, NULL
		INVOKE mciSendString,ADDR BGMName2, NULL, 0, NULL
		INVOKE mciSendString,ADDR playTextBGM, NULL, 0, NULL
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
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume3
	.ELSEIF imageID == IMG_504	;外圈
		.IF Rounds[0] == IMG_5020104
			mov Rounds[0], IMG_5020101
		.ELSE
			inc Rounds[0]
		.ENDIF
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume18
		INVOKE CheckRounds
	.ELSEIF imageID == IMG_505	;中圈
		.IF Rounds[4] == IMG_5020204
			mov Rounds[4], IMG_5020201
		.ELSE
			inc Rounds[4]
		.ENDIF
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume18
		INVOKE CheckRounds
	.ELSEIF imageID == IMG_506	;内圈
		.IF Rounds[8] == IMG_5020304
			mov Rounds[8], IMG_5020301
		.ELSE
			inc Rounds[8]
		.ENDIF
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume18
		INVOKE CheckRounds
	.ELSEIF imageID == IMG_50801
		mov Cross, 1
		INVOKE addTopSequence, IMG_50802
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume4
	.ELSEIF imageID == IMG_50901
		mov pearStep, 1
		mov pSequence[0], IMG_50902
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume11
	.ELSEIF imageID == IMG_50902
		mov pearStep, 2
		mov pSequence[0], IMG_50903
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume11
	.ELSEIF imageID == IMG_50904
		mov pearStep, 3
		mov PPTstatus, 2
		mov Pear, 1
		mov get_collection, 1
		mov pSequence[0], IMG_50905
		mov pThief, 0
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume2
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
		INVOKE mciSendString,ADDR closeTextBGM, NULL, 0, NULL
		INVOKE mciSendString,ADDR BGMName2, NULL, 0, NULL
		INVOKE mciSendString,ADDR playTextBGM, NULL, 0, NULL
		mov Scenario, 3
		INVOKE ResetpSequence
		.IF Circle == 1
			mov door3Open, 1
			mov pSequence[0], IMG_305
			INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
			INVOKE PlayVolume,hWinMain,ADDR Volume17
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
		;INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume3
	;四个控制灯的把手
	.ELSEIF imageID == IMG_60201
		mov PassBy, IMG_60202
		mov pThief, 0
		mov cClick, 0
		mov cJudge, 0
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume9
		.IF GhostStep == 5
			mov Light6, IMG_60903
			mov LightCount, 15
			inc GhostStep
			;INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
			INVOKE PlayVolume,hWinMain,ADDR Volume14
		.ELSE
			mov Light6, IMG_60901
			mov LightCount, 15
		.ENDIF
	.ELSEIF imageID == IMG_60301
		mov PassBy, IMG_60302
		mov pThief, 0
		mov cClick, 0
		mov cJudge, 0
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume9
		.IF GhostStep == 4
			mov Light6, IMG_60703
			mov LightCount, 15
			inc GhostStep
			;INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
			INVOKE PlayVolume,hWinMain,ADDR Volume14
		.ELSE
			mov Light6, IMG_60701
			mov LightCount, 15
		.ENDIF
	.ELSEIF imageID == IMG_60401
		mov PassBy, IMG_60402
		mov pThief, 0
		mov cClick, 0
		mov cJudge, 0
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume9
		.IF GhostStep == 7
			mov Light6, IMG_61003
			mov LightCount, 15
			inc GhostStep
			;INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
			INVOKE PlayVolume,hWinMain,ADDR Volume13
		.ELSE
			mov Light6, IMG_61001
			mov LightCount, 15
		.ENDIF
	.ELSEIF imageID == IMG_60501
		mov PassBy, IMG_60502
		mov pThief, 0
		mov cClick, 0
		mov cJudge, 0
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume9
		.IF GhostStep == 6
			mov Light6, IMG_60803
			mov LightCount, 15
			inc GhostStep
			;INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
			INVOKE PlayVolume,hWinMain,ADDR Volume14
		.ELSE
			mov Light6, IMG_60801
			mov LightCount, 15
		.ENDIF
	;拿圆
	.ELSEIF imageID == IMG_61102
		mov Circle, 1
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume4
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
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume17
	;香蕉
	.ELSEIF imageID == IMG_61402
		;INVOKE addTopSequence, IMG_61404
		mov pThief, 0
		mov PPTstatus, 3
		mov Banana, 1
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume2
		mov get_collection, 1
		INVOKE ChangepSequence, IMG_61401, IMG_61403
		.IF Apple == 1 && Pear == 1
			INVOKE PlayVolume,hWinMain,ADDR Volume5
		.ENDIF
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
		
		INVOKE mciSendString,ADDR closeTextBGM, NULL, 0, NULL
		INVOKE mciSendString,ADDR BGMName2, NULL, 0, NULL
		INVOKE mciSendString,ADDR playTextBGM, NULL, 0, NULL
        INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume1
	.ENDIF
	ret
processScenario2 endp

; #########################################################################

processScenario3 proc
	LOCAL imgID: DWORD, count: DWORD
	;拿虫子时的ppt
	.IF PPTstatus == 4
		INVOKE ChangepSequence, IMG_31802, -1
		dec pSequenceLength
		mov PPTstatus, 0
		mov get_collection, 0
		mov Thief_X, 380
		mov Click_X, 380
		mov Thief_Y, 516
		INVOKE ResetpSequence
		INVOKE addTopSequence, IMG_305
		INVOKE addTopSequence, IMG_30806
		INVOKE addTopSequence, IMG_319
		INVOKE addTopSequence, IMG_320
		mov CollectionStep, 9
		mov pThief, 1
		mov Orientation, 1
		INVOKE mciSendCommand,VolumeID,MCI_CLOSE,0,0
		INVOKE PlayVolume,hWinMain,ADDR Volume15
		jmp ending
	;水獭移动ppt
	.ELSEIF PPTstatus == 5
		INVOKE ChangepSequence, IMG_316, -1
		dec pSequenceLength
		mov PPTstatus, 0
		mov get_collection, 0
		mov eax, Thief_X
		mov Click_X, eax
		mov eax, Thief_Y
		mov Click_Y, eax
	.ENDIF
	;判断是否点击出口
	.IF CollectionStep == 9
		mov edx, TYPE MyItem
		mov eax, IMG_319
		mul edx
		mov ebx, eax
		INVOKE clickPosition, (ItemList[ebx]).x1, (ItemList[ebx]).y1, (ItemList[ebx]).x2, (ItemList[ebx]).y2
		.IF eax == 1
			INVOKE eventResponses3, IMG_319
		.ENDIF
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
			INVOKE eventResponses3, PassBy
		.ENDIF
	.ENDIF
	;判断是否点击四个眼睛
	mov count, IMG_31701
	mov ecx, count
	.WHILE count <= IMG_31704
		mov ecx, count
		mov esi, ecx
		mov edx, TYPE MyItem
		mov eax, ecx
		mul edx
		mov ebx, eax
		INVOKE clickPosition, (ItemList[ebx]).x1, (ItemList[ebx]).y1, (ItemList[ebx]).x2, (ItemList[ebx]).y2
		.IF eax == 1
			INVOKE eventResponses3, esi
		.ENDIF
		inc count
	.ENDW
	;判断是否点击七个孔
	mov count, IMG_31401
	.WHILE count <= IMG_31407
		mov ecx, count
		mov esi, ecx
		mov edx, TYPE MyItem
		mov eax, ecx
		mul edx
		mov ebx, eax
		INVOKE clickPosition, (ItemList[ebx]).x1, (ItemList[ebx]).y1, (ItemList[ebx]).x2, (ItemList[ebx]).y2
		.IF eax == 1
			INVOKE eventResponses3, esi
		.ENDIF
		inc count
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
		mov get_collection, 0
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
		mov get_collection, 0
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
	;拿香蕉的ppt
	.IF PPTstatus == 3
		INVOKE ChangepSequence, IMG_61403, IMG_61404
		mov PPTstatus, 0
		mov get_collection, 0
		mov pThief, 1
		mov Thief_X, 485
		mov Thief_Y, 510
		mov Click_X, 485
		mov Click_Y, 510
		mov Orientation, 0
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

eventResponsesBook proc
	; 关闭
	INVOKE clickPosition, 623, 100, 664, 142
	.IF eax == 1
		mov check_solution, 0
		mov cl, pThiefOld
		mov pThief, cl
		mov esi, Thief_X 
		mov Click_X, esi
		mov esi, Thief_Y 
		mov Click_Y, esi
		.IF PassBy_Old != -1
			mov esi, PassBy_Old
			mov PassBy, esi
		.ENDIF
		mov cJudge, 1
	.ENDIF
	; 下一页
	INVOKE clickPosition, 579, 420, 635, 463
	.IF eax == 1 && book_page != IMG_808
		inc book_page
	.ENDIF
	; 上一页
	INVOKE clickPosition, 121, 420, 175, 463
	.IF eax == 1 && book_page != IMG_801
		dec book_page
	.ENDIF
	; bug
	INVOKE clickPosition, 631, 157, 682, 212
	.IF eax == 1 && book_page > IMG_805
		mov book_page, IMG_801
	.ENDIF
	; ?
	INVOKE clickPosition, 631, 225, 682, 281
	.IF eax == 1 && book_page != IMG_806 && book_page != IMG_807
		mov book_page, IMG_806
	.ENDIF
	; dog
	INVOKE clickPosition, 631, 295, 682, 350
	.IF eax == 1 && book_page != IMG_808
		mov book_page, IMG_808
	.ENDIF
	ret
eventResponsesBook endp

; #########################################################################

processMouseEvent proc currentScenario:DWORD
	;已结束
	.IF isFinished == 1
		INVOKE clickPosition, 296, 407, 508, 472
		.IF eax == 1
			INVOKE restartGame
			jmp _EXIT
		.ENDIF
	.ENDIF
	.IF currentScenario > 2
		.IF isStopped == 1
			; continue
			INVOKE clickPosition, 72, 88, 118, 145
			.IF eax == 1
				mov isStopped, 0
				mov cl, pThiefOld
				mov pThief, cl
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
					mov isPlayingBGM, 0
					; stop the music
					INVOKE mciSendString,ADDR pauseTextBGM, NULL, 0, NULL
				.ELSEIF isPlayingBGM == 0
					mov isPlayingBGM, 1
					; restart the music
					INVOKE mciSendString,ADDR playTextBGM, NULL, 0, NULL
				.ENDIF
				jmp _EXIT
			.ENDIF
			jmp _EXIT
		.ELSEIF check_collection == 1
			mov check_collection, 0
			mov cl, pThiefOld
			mov pThief, cl
			mov esi, Thief_X 
			mov Click_X, esi
			mov esi, Thief_Y 
			mov Click_Y, esi
			.IF PassBy_Old != -1
				mov esi, PassBy_Old
				mov PassBy, esi
			.ENDIF
			mov cJudge, 1
			jmp _EXIT
		.ELSEIF check_solution == 1
			.IF eax == 1
				INVOKE eventResponsesBook
			.ENDIF
			jmp _EXIT
		.ELSEIF isStopped == 0
			; stop
			INVOKE clickPosition, 19, 16, 55, 45
			.IF eax == 1 
				mov isStopped, 1
				mov cl, pThief
				mov pThiefOld, cl
				mov pThief, 0
				.IF PassBy != -1
					mov esi, PassBy
					mov PassBy_Old, esi
					mov PassBy, -1
				.ENDIF
				jmp _EXIT
			.ENDIF
			; star
			.IF check_collection == 0
				INVOKE clickPosition, 63, 16, 96, 45
				.IF eax == 1
					mov check_collection, 1
					mov cl, pThief
					mov pThiefOld, cl
					mov pThief, 0
					mov esi, Thief_X 
					mov Click_X, esi
					mov esi, Thief_Y 
					mov Click_Y, esi
					.IF PassBy != -1
						mov esi, PassBy
						mov PassBy_Old, esi
						mov PassBy, -1
					.ENDIF
					mov cJudge, 0
					jmp _EXIT
				.ENDIF
				.IF check_solution == 0
					INVOKE clickPosition, 740, 13, 788, 50
					.IF eax == 1
						mov check_solution, 1
						mov cl, pThief
						mov pThiefOld, cl
						mov pThief, 0
						mov esi, Thief_X 
						mov Click_X, esi
						mov esi, Thief_Y 
						mov Click_Y, esi
						.IF PassBy != -1
							mov esi, PassBy
							mov PassBy_Old, esi
							mov PassBy, -1
						.ENDIF
						mov cJudge, 0
						jmp _EXIT
					.ENDIF
				.ENDIF
			.ENDIF
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
	.ENDIF

_EXIT:
	ret
processMouseEvent endp

; #########################################################################