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

eventResponses proc imageID: DWORD
	mov ecx, 0
	mov Run, 0
	.IF imageID == IMG_0
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
	.ENDIF
	.IF step == 5
		INVOKE isCorrectOrder
		.IF eax == 1
			INVOKE MessageBox, NULL, addr szText, addr szCaption, MB_OK
		.ELSE
			INVOKE resetIcon
			mov step, 0
		.ENDIF
	.ENDIF
	ret
eventResponses endp

; #########################################################################

processScenario0 proc
	;INVOKE InitItem, IMG_0, 0, 0, 350, 477, 446, 574, 0, 1
		;INVOKE InitItem, IMG_1, 0, 0, 360, 434, 491, 568, 0, 1
		;INVOKE InitItem, IMG_2, 0, 0, 363, 436, 423, 499, 0, 1
	INVOKE clickPosition, 350, 477, 446, 574
	.IF eax == 1
		scenario = 1
	.ENDIF
	ret
processScenario0 endp

; #########################################################################

processScenario1 proc
	ret
processScenario1 endp

; #########################################################################

processScenario2 proc
	ret
processScenario2 endp

; #########################################################################

processScenario3 proc
	ret
processScenario3 endp

; #########################################################################

processScenario4 proc
	LOCAL imgID: DWORD, count: DWORD

	.IF cClick == 1
		.IF pThief == 0
			mov pThief, 1
			mov eax, pSequenceLength
			.IF Scenario == 4
				mov pSequence[eax*4], 0
			.ENDIF
			add eax, 1
			mov pSequence[eax*4], -1
			ret
		.ELSE
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
					INVOKE eventResponses, imgID
					ret
				.ELSE
					add count, 1
					mov ecx, count
				.ENDIF
			.ENDW
			mov ecx, 0
			mov count, 0
			.WHILE pSequence[ecx*4] >= 0 && ecx < pSequenceLength
				mov ebx, pSequence[ecx*4]
				mov edx, TYPE MyItem
				mov eax, ebx
				mul edx
				mov esi, eax
				mov dl, (ItemList[edx]).eClick
				.IF dl == 0
					ret
				.ENDIF
				INVOKE clickPosition, (ItemList[esi]).x1, (ItemList[esi]).y1, (ItemList[esi]).x2, (ItemList[esi]).y2
				.IF eax == 1
					INVOKE eventResponses, imgID
					ret
				.ELSE
					add count, 1
					mov ecx, count
				.ENDIF
			.ENDW
		.ENDIF
	.ENDIF

	ending:
	ret
processScenario4 endp

; #########################################################################

processScenario5 proc
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