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
	.IF Scenario == 4
		mov ecx, IMG_401
		.WHILE ecx < IMG_415
			INVOKE JudgeCollision, ecx
			.IF PassBy != -1
				jmp	_EXIT
			.ENDIF
			inc ecx
		.ENDW
		.IF Triangle == 0	;如果三角已捡起来了则不再判断
			INVOKE JudgeCollision, IMG_42001
			.IF PassBy != -1
				jmp	_EXIT
			.ENDIF
		.ENDIF
	.ENDIF
	mov ecx, 0
	.WHILE ecx < pSequenceLength
		mov ebx, pSequence[ecx * 4]
		.IF ebx == IMG_42101
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

ThiefMove proc
	local MAX_X:DWORD
	local MIN_X:DWORD
	.IF Scenario == 1
	.ELSEIF Scenario == 2
	.ELSEIF Scenario == 4
		.IF Thief_Y == 510		;下
			mov MAX_X, 735
			mov MIN_X, 50
		.ELSEIF Thief_Y == 293	;左中
			mov MAX_X, 269
			mov MIN_X, 50
		.ELSEIF Thief_Y == 290	;右中
			mov MAX_X, 735
			mov MIN_X, 515
		.ELSEIF Thief_Y == 340	;中
			mov MAX_X, 432
			mov MIN_X, 350
		.ELSEIF Thief_Y == 151	;左上
			mov MAX_X, 377
			mov MIN_X, 50
		.ELSEIF Thief_Y == 146	;右上
			mov MAX_X, 735
			mov MIN_X, 463
		.ENDIF
	.ENDIF
	mov ebx, MAX_X
	.IF Click_X > ebx
		mov Click_X, ebx
	.ENDIF
	mov ebx, MIN_X
	.IF Click_X < ebx
		mov Click_X, ebx
	.ENDIF
	mov ebx, Click_X
	.IF ebx > Thief_X
		add Thief_X, 5
		.IF ebx > Thief_X
			mov Run, 1
		.ELSE
			mov Run, 0
			mov ebx, Click_X
			mov Thief_X, ebx
		.ENDIF
	.ELSEIF ebx < Thief_X
		sub Thief_X, 5
		.IF ebx < Thief_X
			mov Run, 1
		.ELSE
			mov Run, 0
			mov ebx, Click_X
			mov Thief_X, ebx
		.ENDIF
	.ELSE
		mov Run, 0
	.ENDIF
	ret
ThiefMove endp