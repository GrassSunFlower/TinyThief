;-----------------------------------------------------------|
;															|
;			本文件用于判断thief移动过程中的碰撞				|
;															|
;___________________________________________________________|

.code
;判断碰撞
JudgeCollision proc ID:DWORD
	mov eax, ID
	mov ebx, TYPE MyItem
	mul ebx
	mov edx, (ItemList[eax]).x1
	mov ebx, (ItemList[eax]).x2
	mov esi, Thief_Y
	sub esi, (ItemList[eax]).y1
	.IF Thief_X > edx && Thief_X < ebx && esi < 143
		mov edx, ID
		mov PassBy, edx
	.ENDIF
	ret
JudgeCollision endp

;判断所有碰撞
JudgeCollisions proc
	mov PassBy, -1
	.IF Scenario == 3
		.IF CollectionStep == 0	
			mov eax, IMG_30801
		.ELSEIF CollectionStep == 1
			mov eax, IMG_30803
		.ELSEIF CollectionStep == 2
			mov eax, IMG_30805
		.ELSEIF CollectionStep == 3
			mov eax, IMG_310
		.ELSE
			jmp _FinishStep
		.ENDIF
		INVOKE JudgeCollision, eax
		.IF PassBy != -1
			jmp	_EXIT
		.ENDIF
		_FinishStep:
		;上下楼梯
		.IF Thief_Y < 150
			INVOKE JudgeCollision, IMG_30601
			.IF PassBy != -1
				jmp	_EXIT
			.ENDIF
			.IF Thief_X > 710 && Thief_X < 740
				mov PassBy, IMG_30701
				jmp	_EXIT
			.ENDIF
		.ELSE
			INVOKE JudgeCollision, IMG_30602
			.IF PassBy != -1
				jmp	_EXIT
			.ENDIF
			.IF Thief_X > 710 && Thief_X < 740
				mov PassBy, IMG_30702
				jmp	_EXIT
			.ENDIF
		.ENDIF
	.ELSEIF Scenario == 4
		mov ecx, IMG_401
		.WHILE ecx < IMG_415
			INVOKE JudgeCollision, ecx
			.IF PassBy != -1
				jmp	_EXIT
			.ENDIF
			inc ecx
		.ENDW
		.IF Triangle == 0			;如果三角已捡起来了则不再判断
			INVOKE JudgeCollision, IMG_42001
			.IF PassBy != -1
				jmp	_EXIT
			.ENDIF
		.ENDIF
	.ELSEIF Scenario == 5
		;门
		mov ecx, IMG_503
		INVOKE JudgeCollision, ecx
		.IF PassBy != -1
			jmp	_EXIT
		.ENDIF
		inc ecx
		;三个圈
		.WHILE ecx <= IMG_506 && door5Open == 0
			INVOKE JudgeCollision, ecx
			.IF PassBy != -1
				jmp	_EXIT
			.ENDIF
			inc ecx
		.ENDW

		;梨子拾取
		.IF pearStep == 2
			INVOKE JudgeCollision, IMG_50904
		.ENDIF
		.IF PassBy != -1
			jmp	_EXIT
		.ENDIF
		.IF Cross == 0				;如果十字已捡起来了则不再判断
		INVOKE JudgeCollision, IMG_50801
			.IF PassBy != -1
				jmp	_EXIT
			.ENDIF
		.ENDIF
	.ELSEIF Scenario == 6
		.IF Thief_X < 155 && GhostStep == -1
			mov cClick, 0
			mov GhostStep, 0
			mov GhostCount, 10
			mov ebx, Thief_X
			mov Click_X, ebx
			jmp _EXIT
		.ENDIF
		.IF BananaShow == 0 && Banana == 0
			INVOKE JudgeCollision, IMG_61301
			.IF PassBy != -1
				jmp	_EXIT
			.ENDIF
		.ENDIF
		;门
		mov ecx, IMG_601
		INVOKE JudgeCollision, ecx
		.IF PassBy != -1
			jmp	_EXIT
		.ENDIF
		inc ecx
		;四个机关
		.WHILE ecx <= IMG_60501 && CircleShow == 0 && BananaShow == 0
			INVOKE JudgeCollision, ecx
			.IF PassBy != -1
				jmp	_EXIT
			.ENDIF
			add ecx, 2
		.ENDW
	.ENDIF
	;对pSequence中的物体进行检测
	mov ecx, 0
	.WHILE ecx < pSequenceLength
		mov ebx, pSequence[ecx * 4]
		.IF ebx == IMG_42101 || ebx == IMG_30201 || ebx == IMG_30301 || ebx == IMG_30401 || ebx == IMG_61101 || ebx == IMG_61401
			inc ebx
		.ELSE
			jmp _NEXT
		.ENDIF
		INVOKE JudgeCollision, ebx
		.IF PassBy != -1
			jmp	_EXIT
		.ENDIF
	_NEXT:
		inc ecx
	.ENDW
_EXIT:
	ret
JudgeCollisions endp