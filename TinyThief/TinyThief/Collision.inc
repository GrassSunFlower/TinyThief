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
			inc ecx
		.ENDW
		.IF Triangle == 0	;如果三角已捡起来了则不再判断
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
		;处理梨子拾取过程
		.IF pearStep == 2
			INVOKE JudgeCollision, IMG_50904

		.ENDIF
		.IF PassBy != -1
			jmp	_EXIT
		.ENDIF
		.IF Cross == 0	;如果十字已捡起来了则不再判断
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
		;特殊移动处理1：场景3下楼梯
		.IF Scenario == 3 && Thief_Y >= 128 && Thief_Y <= 144 && Thief_X >= 170 && Thief_X <= 190
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
		.IF Scenario == 3 && Thief_Y >= 132 && Thief_Y <= 148 && Thief_X >= 170 && Thief_X <= 190
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
	.IF Scenario == 3 && Thief_Y == 128 && Thief_X > 165 && Thief_X < 170
		mov Thief_X, 170
	.ELSEIF Scenario == 3 && Thief_Y == 144 && Thief_X > 190 && Thief_X < 195
		mov Thief_X, 190
	.ENDIF
	ret
ThiefMove endp

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
;播放逃跑ppt
RunForYouLife proc
	
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
		mov Thief_Y, 148
		mov Thief_X, 333
		mov Click_Y, 148
		mov Click_X, 333
	.ENDIF
	ret
RunForYouLife endp