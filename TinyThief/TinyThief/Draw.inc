
.code

;绘制物品
DrawObject proc bID:DWORD, xDesc:DWORD, yDesc:DWORD, sWidth:DWORD, sHeight:DWORD
	local Hold:DWORD

	INVOKE LoadBitmap, hInstance, bID	;load bmp
	mov Hold, eax
	INVOKE SelectObject,hdcImage,Hold
	INVOKE BitBlt,hdcMem,xDesc,yDesc,sWidth,sHeight,hdcImage,0,0,SRCCOPY
	
	ret
DrawObject endp

;绘制背景透明的物品
DrawTransparentObject proc bID:DWORD, xDesc:DWORD, yDesc:DWORD, sWidth:DWORD, sHeight:DWORD
	local Hold:DWORD

	INVOKE LoadBitmap, hInstance, bID	;load bmp
	mov Hold, eax
	INVOKE SelectObject,hdcImage,Hold
	INVOKE BitBlt,hdcMem,xDesc,yDesc,sWidth,sHeight,hdcImage,sWidth,0,SRCAND
	INVOKE BitBlt,hdcMem,xDesc,yDesc,sWidth,sHeight,hdcImage,0,0,SRCPAINT
	
	ret
DrawTransparentObject endp

;绘制盗贼
DrawThief proc 
	.IF Orientation == 0
		.IF Run == 0
			INVOKE DrawTransparentObject,1111,Thief_X,Thief_Y,25,32
		.ELSE
			INVOKE DrawTransparentObject,3333,Thief_X,Thief_Y,25,32
		.ENDIF
	.ELSEIF Run == 0
		INVOKE DrawTransparentObject,2222,Thief_X,Thief_Y,25,32
	.ELSE
		INVOKE DrawTransparentObject,4444,Thief_X,Thief_Y,25,32
	.ENDIF

    ret

DrawThief endp

;绘制背景
DrawBackground proc
	.IF Scenario == 0
		INVOKE DrawObject,IMG_0,0,0,SCREEN_X,SCREEN_Y
	.ELSEIF Scenario == 1
		INVOKE DrawObject,IMG_1,0,0,SCREEN_X,SCREEN_Y
	.ELSEIF Scenario == 2
		INVOKE DrawObject,IMG_2,0,0,SCREEN_X,SCREEN_Y
	.ELSEIF Scenario == 3

	.ELSEIF Scenario == 4
		INVOKE DrawObject,IMG_400,0,0,SCREEN_X,SCREEN_Y
	.ENDIF
	ret
DrawBackground endp

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
			INVOKE DrawObject, esi, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
		.ELSE
			INVOKE DrawTransparentObject, esi, (ItemList[eax]).x1, (ItemList[eax]).y1, (ItemList[eax]).iwidth, (ItemList[eax]).iheight
		.ENDIF
		add i, 4
		mov ebx, i
		mov eax, pSequence[ebx]

	.ENDW
	ret
DrawItems endp

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
			INVOKE DrawObject, esi, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
		.ELSE
			INVOKE DrawTransparentObject, esi, (ItemList[eax]).x1, (ItemList[eax]).y1, (ItemList[eax]).iwidth, (ItemList[eax]).iheight
		.ENDIF
		add i, 4
		mov ebx, i
		mov eax, drawIcon[ebx]

	.ENDW
	ret
DrawIcons endp

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
		INVOKE DrawObject, esi, (ItemList[eax]).x1, (ItemList[eax]).y1,(ItemList[eax]).iwidth, (ItemList[eax]).iheight
	.ELSE
		INVOKE DrawTransparentObject, esi, (ItemList[eax]).x1, (ItemList[eax]).y1, (ItemList[eax]).iwidth, (ItemList[eax]).iheight
	.ENDIF
	ret
DrawPassBy endp

DrawProc proc

	INVOKE DrawBackground
	.IF Scenario == 4
		INVOKE DrawIcons
	.ENDIF
	.IF Scenario > 2
		INVOKE DrawItems
		INVOKE DrawPassBy
		.IF pThief == 1
			INVOKE DrawThief
		.ENDIF
	.ENDIF
    ret

DrawProc endp

