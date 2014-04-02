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
		;.IF doorNo == 1
		;	INVOKE JudgeCollision, IMG_30202
		;.ELSEIF doorNo == 2
		;	INVOKE JudgeCollision, IMG_30302
		;.ELSEIF doorNo == 3
		;		INVOKE JudgeCollision, IMG_30402
		;.ENDIF
		.IF PassBy != -1
			jmp	_EXIT
		.ENDIF
	.ELSEIF Scenario == 4
		mov ecx, IMG_401
		.WHILE ecx < IMG_415
			INVOKE JudgeCollision, ecx
			.IF PassBy != -1
				jmp	_EXIT
			.ENDIF
		_NEXTDOOR:
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
		.IF ebx == IMG_42101 || ebx == IMG_30201 || ebx == IMG_30301 || ebx == IMG_30401
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
	mov MAX_X, 750
	mov MIN_X, 50
	.IF Scenario == 1
	.ELSEIF Scenario == 2
	.ELSEIF Scenario == 3
		.IF Thief_Y >= 128 && Thief_Y <= 148 && doorOpen == 0	;门未开的上
			mov MAX_X, 561
			mov MIN_X, 71
		.ENDIF
	.ELSEIF Scenario == 4
		.IF Thief_Y == 510		;下
			mov MAX_X, 771
			mov MIN_X, 50
		.ELSEIF Thief_Y == 293	;左中
			mov MAX_X, 305
			mov MIN_X, 50
		.ELSEIF Thief_Y == 290	;右中
			mov MAX_X, 771
			mov MIN_X, 515
		.ELSEIF Thief_Y == 340	;中
			mov MAX_X, 468
			mov MIN_X, 350
		.ELSEIF Thief_Y == 151	;左上
			mov MAX_X, 413
			mov MIN_X, 50
		.ELSEIF Thief_Y == 146	;右上
			mov MAX_X, 771
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
	;普通移动处理
	mov ebx, Click_X
	.IF ebx > Thief_X
		;特殊移动处理1：场景3下楼梯
		.IF Scenario == 3 && Thief_Y >= 128 && Thief_Y <= 144 &&Thief_X >= 185 && Thief_X <= 205
			add Thief_Y, 4
		.ENDIF
		add Thief_X, 5
		.IF ebx > Thief_X
			mov Run, 1
		.ELSE
			mov Run, 0
			mov ebx, Thief_X
			mov Click_X, ebx
		.ENDIF
	.ELSEIF ebx < Thief_X
		;特殊移动处理1：场景3下楼梯
		.IF Scenario == 3 && Thief_Y >= 132 && Thief_Y <= 148 &&Thief_X >= 185 && Thief_X <= 205
			sub Thief_Y, 4
		.ENDIF
		sub Thief_X, 5
		.IF ebx < Thief_X
			mov Run, 1
		.ELSE
			mov Run, 0
			mov ebx, Thief_X
			mov Click_X, ebx
		.ENDIF
	.ELSE
		mov Run, 0
	.ENDIF
	.IF Scenario == 3 && Thief_Y == 128 && Thief_X > 180 && Thief_X < 185
		mov Thief_X, 185
	.ELSEIF Scenario == 3 && Thief_Y == 144 && Thief_X > 205 && Thief_X < 210
		mov Thief_X, 205
	.ENDIF
	ret
ThiefMove endp